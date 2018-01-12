basedir = 'root://polgrid4.in2p3.fr//dpm/in2p3.fr/home/cms/trivcat/store/user/jsauvan/HGCAL/'

input_signal = ['{}/SingleElectronPt25Eta1p6_2p8/EleGunPt25_PU200_HGCTDR_panel_tc_ntuple/171201_144742/0000/ntuple_1.root'.format(basedir)]
input_signal_0pu = ['{}/SingleElectronPt25Eta1p6_2p8/EleGunPt25_PU200_HGCTDR_panel_tc_ntuple/171201_144742/0000/ntuple_1.root'.format(basedir)]
input_background = [
        '{}/DoubleNuE1Eta14_31/NuGun_PU200_ECALTDR_panel_ntuple/171201_092153/0000/ntuple_8.root'.format(basedir),
        '{}/DoubleNuE1Eta14_31/NuGun_PU200_ECALTDR_panel_ntuple/171201_092153/0000/ntuple_9.root'.format(basedir),
        '{}/DoubleNuE1Eta14_31/NuGun_PU200_ECALTDR_panel_ntuple/171201_092153/0000/ntuple_10.root'.format(basedir),
        '{}/DoubleNuE1Eta14_31/NuGun_PU200_ECALTDR_panel_ntuple/171201_092153/0000/ntuple_11.root'.format(basedir),
        ]
input_tree = 'hgcalTriggerNtuplizer/HGCalTriggerNtuple'
input_first_event = 0
input_last_event = 100
output_file = 'output_pu_tdr_dpm.root'
output_tree = 'tree'
#
bunch_pattern = [1,0,0,0,0,0,0,0]
#  panel_mapping = 'data/panel_mapping_60deg_6mod_0.txt'
panel_mapping = '/home/llr/cms/sauvan/Projects/L1CalorimeterTrigger_Phase2HGCal/Studies/TDR/HGCTPGFrontendStudies/concentrator-ntuplizer/data/panel_mapping_tdr.txt'


### Batch config
from HGCTPG.FrontendNtuplizer.Parameters import Parameters
parameters = Parameters()
parameters.working_dir = '/home/llr/cms/sauvan/DATA/HGCAL/ConcentratorNtuples/'
parameters.events_per_job = 10
parameters.total_events = 98

