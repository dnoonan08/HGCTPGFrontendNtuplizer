basedir = '/home/llr/cms/sauvan/Projects/L1CalorimeterTrigger_Phase2HGCal/CMSSW/CMSSW_9_4_0_pre2/src/L1Trigger/L1THGCal/test/crab/'

input_signal = ['{}/ntuple.root'.format(basedir)]
input_signal_0pu = ['{}/ntuple.root'.format(basedir)]
input_background = ['{}/ntuple.root'.format(basedir)]
input_tree = 'hgcalTriggerNtuplizer/HGCalTriggerNtuple'
input_first_event = 0
input_last_event = -1
mixing_random_seed = 1234
output_file = 'output_nopu.root'
output_tree = 'tree'
#
bunch_pattern = [1,0,0,0,0,0,0,0]
#  panel_mapping = 'data/panel_mapping_60deg_6mod_0.txt'
panel_mapping = 'data/panel_mapping_tdr.txt'
