basedir = 'root://polgrid4.in2p3.fr//dpm/in2p3.fr/home/cms/trivcat/store/user/jsauvan/HGCAL/'

input_signal = [
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_2.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_3.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_7.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_8.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_9.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_10.root'.format(basedir),
                ]
input_signal_0pu = [
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_2.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_3.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_7.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_8.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_9.root'.format(basedir),
                '{}/SingleElectronPt10Eta1p6_2p8/EleGunPt10_PU200_HGCTDR_panel_tc_ntuple/171220_201702/0000/ntuple_10.root'.format(basedir),
                ]
input_background = ['{0}/DoubleNuE1Eta14_31/NuGun_PU200_ECALTDR_panel_ntuple/171210_202454/0000/ntuple_{1}.root'.format(basedir,i) for i in xrange(1,101)]
input_tree = 'hgcalTriggerNtuplizer/HGCalTriggerNtuple'
input_first_event = 0
input_last_event = 100
mixing_random_seed = 1234
signal_hit_selection_type = 'DeltaEtaPhi'
signal_hit_selection_parameters = {
                                'delta_eta':0.05,
                                'delta_phi':0.2
                                }
output_file = 'cc_ntuple_ele_pt10_200pu_tdr_layout.root'
output_tree = 'tree'
#
bunch_pattern = [1,0,0,0,0,0,0,0]
#  panel_mapping = 'data/panel_mapping_60deg_6mod_0.txt'
panel_mapping = '/home/llr/cms/sauvan/Projects/L1CalorimeterTrigger_Phase2HGCal/Studies/TDR/HGCTPGFrontendStudies/concentrator-ntuplizer/data/panel_mapping_tdr.txt'


### Batch config
from HGCTPG.FrontendNtuplizer.Parameters import Parameters
parameters = Parameters()
parameters.working_dir = '/home/llr/cms/sauvan/DATA/HGCAL/ConcentratorNtuples/ele_pt10_200pu_tdr_layout'
parameters.events_per_job = 100
parameters.total_events = -1

