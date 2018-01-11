#!/usr/bin/env python

from datetime import date 
import os
import sys
import shutil
import subprocess
import time
import glob
import random
import ROOT


def job_version(directory):
    version_date = "v_1_"+str(date.today())
    if os.path.isdir(directory):
        dirs= [f for f in os.listdir(directory) if os.path.isdir(os.path.join(directory,f)) and f[:2]=='v_']
        version_max = 0
        for d in dirs:
            version = int(d.split("_")[1])
            if version > version_max: version_max = version
        version_date = "v_"+str(version_max+1)+"_"+str(date.today())
    return version_date


def prepare_jobs(working_dir, exe, config_name, events, name='batch'):
    # Create working area
    if not os.path.isdir(working_dir): os.makedirs(working_dir)
    # Create one subdirectory for each version
    version = job_version(working_dir)
    os.makedirs(working_dir+'/'+version)
    os.makedirs(working_dir+'/'+version+'/jobs')
    os.makedirs(working_dir+'/'+version+'/logs')
    job_dir = working_dir+'/'+version+'/jobs'
    log_dir = working_dir+'/'+version+'/logs'
    # Create job files
    input_lines = []
    with open(config_name) as f:
        input_lines = f.readlines()
    random.seed()
    for i,event in enumerate(events):
        pars  = 'jobs/'+os.path.basename(config_name)
        pars = pars.replace('.py', '_{}.py'.format(i))
        with open(working_dir+'/'+version+'/'+pars, 'w') as f:
            for line in input_lines:
                if 'Parameters' in line: break
                tokens = line.split('=')
                if len(tokens)==2 and 'input_first_event' in tokens[0]:
                    tokens[1] = ' '+str(event[0])
                    line = '='.join(tokens)
                elif len(tokens)==2 and 'input_last_event' in tokens[0]:
                    tokens[1] = ' '+str(event[1])
                    line = '='.join(tokens)
                elif len(tokens)==2 and 'output_file' in tokens[0]:
                    tokens[1] = tokens[1].replace('.root', '_{}.root'.format(i))
                    line = '='.join(tokens)
                elif len(tokens)==2 and 'mixing_random_seed' in tokens[0]:
                    tokens[1] = str(random.randint(0, 10000))
                    line = '='.join(tokens)
                print >>f, line.replace('\n', '')
        with open(job_dir+'/'+name+'_{}.sub'.format(i), 'w') as script:
            print >>script, '#! /bin/bash'
            print >>script, 'uname -a'
            print >>script, 'cd', os.environ['CC_NTUPLE_BASE']
            print >>script, 'source init_env_polui.sh'
            print >>script, 'cd', working_dir+'/'+version
            print >>script, os.environ['CC_NTUPLE_BASE']+'/'+exe, pars, '&>', log_dir+'/'+name+'_{}.log'.format(i)
            print >>script, 'touch', name+'_{}.done'.format(i)
    return working_dir+'/'+version



def launch_jobs(working_dir, events, name='batch', queue='long', proxy='~/.t3/proxy.cert'):
    print 'Sending {0} jobs on {1}'.format(len(events), queue+'@llrt3')
    print '==============='
    for i,event in enumerate(events):
        qsub_args = []
        qsub_args.append('-{}'.format(queue))
        qsub_args.append(working_dir+'/jobs/'+name+'_{}.sub'.format(i))
        qsub_command = ['/opt/exp_soft/cms/t3/t3submit'] + qsub_args
        print ' '.join(qsub_command)
        subprocess.call(qsub_command)
    print '==============='

def main(parameter_file, input_files, input_tree, parameters):
    working_dir = parameters.working_dir
    events_per_job = parameters.events_per_job
    total_events = parameters.total_events
    chain = ROOT.TChain(input_tree)
    for f in input_files:
        chain.Add(f)
    if total_events==-1: total_events = chain.GetEntries()
    total_events = min(total_events, chain.GetEntries())
    events = []
    evt = 0
    while evt < total_events:
        last_event = min(total_events, evt+events_per_job)
        events.append((evt, last_event))
        evt += events_per_job
    jobs_dir = prepare_jobs(working_dir, 'bin/concentrator_ntuplizer.exe', parameter_file, events, name='batch')
    launch_jobs(jobs_dir, events, name='batch')



if __name__=='__main__':
    import sys
    import os
    import optparse
    import importlib
    usage = 'usage: %prog [options]'
    parser = optparse.OptionParser(usage)
    parser.add_option('--cfg', dest='parameter_file', help='Python file containing the definition of parameters ', default='pars.py')
    (opt, args) = parser.parse_args()
    current_dir = os.getcwd();
    sys.path.append(current_dir)
    parameter_file = opt.parameter_file
    # Remove the extension of the python file before module loading
    if opt.parameter_file[-3:]=='.py': opt.parameter_file = opt.parameter_file[:-3]
    parameters = importlib.import_module(opt.parameter_file).parameters
    input_files = importlib.import_module(opt.parameter_file).input_signal
    input_tree = importlib.import_module(opt.parameter_file).input_tree
    main(parameter_file, input_files, input_tree,  parameters)
