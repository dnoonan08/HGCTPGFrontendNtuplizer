# Ntuplizer for HGCal front-end studies
This code is producing ntuples that can be used for the study of trigger cell selections in the HGCal frontend, in particular in the concentrator. It reads trigger cells and panels information from [CMSSW HGCal TPG ntuples](https://github.com/PFCal-dev/cmssw/tree/hgc-tpg-devel-CMSSW_9_4_0_pre2/L1Trigger/L1THGCal/plugins/ntuples) and produces much smaller ntuples with a panel-centered view on which selection algorithms can be run.

Two main things are implemented:
* Association of trigger cells to signal particle: trigger cells are associated to generated particles based on their simulated energy. Trigger cells containing non-zero simulated energy are associated to the generated particles in the event. Some additional geometric selection is applied to separate hits from several particles in the event and to reduce PU contamination.
* Bunch crossing mixing: dataframes covering 10 bunch crossings are created. They contain information from one signal bx and 9 Minbias bx. Minbias events are randomly picked among all the input Minbias events.

## Installation
This code can be used as a CMSSW package and be compiled with SCRAM.
```bash
export SCRAM_ARCH=slc6_amd64_gcc630
cmsrel CMSSW_9_4_2
cd CMSSW_9_4_2/src/
cmsenv
git clone https://github.com/dnoonan08/HGCTPGFrontendNtuplizer.git HGCTPG/FrontendNtuplizer
scram b -j4
```

## Running the code
The command to run the ntuplizer is as follows.
```bash
# Inside config/
frontend_ntuplizer.exe config_file.py
```
The python configuration files are python files containing all the parameters to configure the code. There are examples of configuration files in `config/`. The parameters definition is given below.


There is also a script used to launch the code on a batch system. Currently it is only implemented for the LLR batch system. It can be run as follows.
```bash
# From inside batch/
./launcher_cmslpc.py --cfg=config_file.py
```
The same config file can be used with additional parameters defined in `python/Parameters.py` (the working directory, the total number of events and the number of events per jobs).

## Parameters
| Name | Values | Definition |  
| ------ | ------ | ------------ |  
| `input_signal` | `list(string)`  | List of input signal files |  
| `input_signal_0pu` | `list(string)`  | List of input signal files containing simhit information |  
| `input_background` | `list(string)`  | List of input Minbias files used for the PU mixing |  
| `input_tree` | `string`  | Name of the input tree |  
| `input_first_event` | `int`  | First signal event to use |  
| `input_last_event` | `int`  | Last signal event to use |  
| `mixing_random_seed` | `int`  | Random seed used for the PU mixing |  
| `signal_hit_selection` | `string` in (`DeltaEtaPhi`)  | Type of selection to apply on signal hits |  
| `signal_hit_selection_parameters` | `dict(string:float)`  | Parameters of the signal hit selection |  
| `output_file` | `string`  | Name of the output file |  
| `output_tree` | `string`  | Name of the output tree |  
| `bunch_pattern` (not used) | `list(int)` (`0` or `1`) | Pattern of the PU mixing, `0`=PU, `1`=signal |  


### Signal selections

| Selection type | parameters | Definition |  
| -------------- | ---------- | ------------ |  
| `DeltaEtaPhi` | `delta_eta`  |  Distance in eta |  
|               | `delta_phi`  |  Distance in phi |  

### Notes
* `input_signal_0pu` and `input_signal` can be the same files if they contain simhit information (needed to define signal trigger cells). In the case there is no simhit information in the PU sample (for instance if it is based on `GEN-SIM-RECO` and not on `GEN-SIM_DIGI-RAW`) then the corresponding NoPU sample can be given in `input_signal_0pu` (of course it needs to contain simhit information). The code will map together the PU events to the NoPU events based on their event numbers.
* Currently the bunch pattern is fixed with a bunch window of 10 bunches. The first bunch is the signal event while the 9 others are Minbias events.

## Output ntuple branches
Two trees are created, the `signal_` and the `panel_` trees. The signal tree contain one entry per signal particle, with the following branches:

| Branch name |Type |  Definition |  
| ----------- | ---- | ------------ |  
| `event` | `unsigned int` | Event of the particle |
| `gen_index` | `unsigned int` | Index of the particle in the original tree |
| `gen_id` | `int` | Particle id |
| `gen_pt` | `float` | Generated pt of the particle | 
| `gen_eta` | `float` | Generated eta of the particle | 
| `gen_phi` | `float` | Generated phi of the particle | 
| `gen_energy` | `float` | Generated energy of the particle | 
| `hits_panel` | `vector<unsigned int>` | Panel ids of the hits associated to the particle |
| `hits_tc` | `vector<unsigned int>` | TC ids within the panel of the hits associated to the particle |
| `hits_eta` | `vector<float>` | eta of the hits associated to the particle |
| `hits_phi` | `vector<float>` | phi of the hits associated to the particle |
| `hits_pt`  | `vector<float>` |  pt of the hits associated to the particle |
| `hits_simenergy` | `vector<float>` | Simulated energy of the hits associated to the particle |

The panel tree contains all the panels that contain signal hits. There is one entry per panel.

| Branch name |Type |  Definition |  
| ----------- | ---- | ------------ |  
| `signal_event` | `unsigned int` | Signal event number |
| `panel_id` | `unsigned int` | Panel id |
| `panel_layer` | `unsigned int` | Layer of the panel  |
| `modules_n` | `unsigned int` | Number of modules contained in this panel  |
| `events` | `unsigned int[10]` | All (10) event numbers. The first one is the same as `signal_event` |
| `events_type` | `unsigned int[10]` | Types of events (signal or background) |
| `tc_mipPt` | `float[10*6*48]` | Transverse mip values of all the trigger cells in the panel over the 10 bx  |
| `tc_pt` | `float[10*6*48]` | pt values of all the trigger cells in the panel over the 10 bx  |

The sizes of the arrays are defined by:
* The number of mixed bunch crossings (10)
* The max number of modules per panel (6)
* The number of trigger cells per module (48)
