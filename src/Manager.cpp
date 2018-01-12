#include <iostream>

#include "HGCTPG/FrontendNtuplizer/interface/Manager.h"
#include "HGCTPG/FrontendNtuplizer/interface/SignalSelectionDeltaEtaPhi.h"

Manager::
Manager(const Parameters& params):
  params_(params),
  input_signal_(params.input().signal_files, params.input().tree, false, Event::Type::Signal),
  input_signal_0pu_(params.input().signal_files_0pu, params.input().tree, true, Event::Type::Signal),
  input_background_(params.input().background_files, params.input().tree, false, Event::Type::Background),
  output_(params.output().output_file),
  geometry_(params.geometry().panel_mapping_file),
  packer_(geometry_),
  random_(params.mixing().random_seed)
{
  if(params.signal().hit_selection_type=="DeltaEtaPhi")
  {
    signal_selection_.reset(new SignalSelectionDeltaEtaPhi(params));
  }
}

void
Manager::
run()
{ 
  fillEventMap();
  unsigned events_signal = input_signal_.events();
  unsigned events_background = input_background_.events();
  unsigned first = (unsigned)params_.input().first_event;
  unsigned last = (params_.input().last_event==-1 ? events_signal : params_.input().last_event);
  for(unsigned ie=first; ie<last; ie++)
  {
    std::vector<Event> events;
    std::cerr<<"Reading entry "<<ie<<"\n";
    // read main signal event
    input_signal_.read(ie);
    events.emplace_back(input_signal_.buildEvent());
    // Retrieve signal cells from 0PU event
    unsigned entry_0pu = event_to_entry_signal_0pu_.at(events.back().event());
    input_signal_0pu_.read(entry_0pu);
    Event event_0pu = input_signal_0pu_.buildEvent();
    auto signal_particles = input_signal_0pu_.buildSignal(event_0pu, geometry_);
    // Retrieve background events
    for(unsigned ib=0; ib<9; ib++)
    {
      unsigned entry_background = random_.Integer(events_background);
      input_background_.read(entry_background);
      events.emplace_back(input_background_.buildEvent());
    }
    auto dataframes = packer_.pack(events, event_0pu, signal_particles);
    for(const auto& dataframe : dataframes)
    {
      output_.fillDataframe(dataframe);
    }
    for(auto& particle: signal_particles)
    {
      if(signal_selection_) particle.applySelection(signal_selection_);
      output_.fillSignal(particle);
    }

  }
}

void
Manager::
fillEventMap()
{
  TChain chain(params_.input().tree.c_str());
  for(const auto& file : params_.input().signal_files_0pu)
  {
    chain.Add(file.c_str());
  }
  int event = 0;
  chain.SetBranchStatus("*", 0);
  chain.SetBranchStatus("event", 1);
  chain.SetBranchAddress("event", &event);
  unsigned events = chain.GetEntries();
  for(unsigned ie=0; ie<events; ie++)
  {
    chain.GetEntry(ie);
    event_to_entry_signal_0pu_.emplace(event, ie);
  }
}
