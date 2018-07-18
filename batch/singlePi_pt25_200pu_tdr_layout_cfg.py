#basedir = 'root://polgrid4.in2p3.fr//dpm/in2p3.fr/home/cms/trivcat/store/user/jsauvan/HGCAL/'
basedir = 'root://cmsxrootd.fnal.gov//store/user/jsauvan/HGCAL/'

basedir = 'root://cmseos.fnal.gov//store/user/lpchgcal/ConcentratorNtuples/L1THGCal_Ntuples/'

input_signal     = ['{0}/RelValSinglePiPt25Eta1p7_2p7/crab_RelValSinglePiPt25Eta1p7_2p7/180411_205312/0000/ntuple_{1}.root'.format(basedir,i) for i in xrange(1,91)]

input_signal_0pu = ['{0}/RelValSinglePiPt25Eta1p7_2p7/crab_RelValSinglePiPt25Eta1p7_2p7/180411_205312/0000/ntuple_{1}.root'.format(basedir,i) for i in xrange(1,91)]

input_background = ['{0}/RelValNuGun/crab_RelValNuGun/180413_042405/0000/ntuple_{1}.root'.format(basedir,i) for i in xrange(1,401)]

input_tree = 'hgcalTriggerNtuplizer/HGCalTriggerNtuple'
input_first_event = 0
input_last_event = 2
mixing_random_seed = 1234
signal_hit_selection_type = 'DeltaR'
signal_gen_type = 'genParton'
signal_gen_jet_threshold = 15
signal_hit_selection_parameters = {
                                'delta_eta':0.05,
                                'delta_phi':0.2,
                                'delta_R':0.4,
                                }
output_file = 'cc_ntuple_singlePi_pt25_200pu_tdr_layout.root'
output_tree = 'tree'
#
bunch_pattern = [1,0,0,0,0,0,0,0]
#  panel_mapping = 'data/panel_mapping_60deg_6mod_0.txt'
panel_mapping = '../../data/panel_mapping_tdr.txt'


### Batch config
from HGCTPG.FrontendNtuplizer.Parameters import Parameters
parameters = Parameters()
parameters.working_dir = '/uscms_data/d2/dnoonan/HGCAL/CMSSW_9_4_2/src/HGCTPG/FrontendNtuplizer/singlePi_pt25_200pu_tdr_layout'
parameters.events_per_job = 100
parameters.total_events = -1

