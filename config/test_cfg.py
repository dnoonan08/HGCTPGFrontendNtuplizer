basedir = '/home/llr/cms/sauvan/Projects/L1CalorimeterTrigger_Phase2HGCal/CMSSW/CMSSW_9_4_0_pre2/src/L1Trigger/L1THGCal/test/crab/'

input_signal = ['{}/ntuple_ele_140pu_tdr_test.root'.format(basedir)]
#  input_signal_0pu = ['{}/ntuple_ele_140pu_tdr_test.root'.format(basedir)]
input_signal_0pu = ['{}/ntuple_ele_0pu_tdr.root'.format(basedir)]
input_background = ['{}/ntuple_nu_200pu_tdr.root'.format(basedir)]
input_tree = 'hgcalTriggerNtuplizer/HGCalTriggerNtuple'
input_first_event = 0
input_last_event = -1
output_file = 'output_pu_tdr_test_2.root'
output_tree = 'tree'
#
bunch_pattern = [1,0,0,0,0,0,0,0]
#  panel_mapping = 'data/panel_mapping_60deg_6mod_0.txt'
panel_mapping = 'data/panel_mapping_tdr.txt'
