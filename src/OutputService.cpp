#include <iostream>

#include "TString.h"
#include "HGCTPG/FrontendNtuplizer/interface/OutputService.h"

OutputService::
OutputService(const std::string& file_name):
  file_(TFile::Open(file_name.c_str(), "recreate")),
  panel_tree_(new TTree("panel_tree", "panel_tree")),
  signal_tree_(new TTree("signal_tree", "signal_tree"))
{
  panel_tree_->Branch("signal_event", &signal_event_, "signal_event/i");
  panel_tree_->Branch("panel_id", &panel_id_, "panel_id/i");
  panel_tree_->Branch("panel_layer", &panel_layer_, "panel_layer/i");
  panel_tree_->Branch("panel_subdet", &panel_subdet_, "panel_subdet/i");
  panel_tree_->Branch("modules_n", &modules_n_, "modules_n/i");
  panel_tree_->Branch("events", &events_[0], TString::Format("events[%i]/i", kbunches));
  panel_tree_->Branch("events_type", &events_type_[0], TString::Format("events_type[%i]/i", kbunches));
  panel_tree_->Branch("tc_mipPt", &tc_mipPt_[0], TString::Format("tc_mipPt[%i]/F", kdatasize));
  panel_tree_->Branch("tc_pt", &tc_pt_[0], TString::Format("tc_pt[%i]/F", kdatasize));
  //
  signal_tree_->Branch("event", &event_, "event/i");
  signal_tree_->Branch("gen_index", &gen_index_, "gen_index/i");
  signal_tree_->Branch("gen_id", &gen_id_, "gen_id/I");
  signal_tree_->Branch("gen_pt", &gen_pt_, "gen_pt/F");
  signal_tree_->Branch("gen_eta", &gen_eta_, "gen_eta/F");
  signal_tree_->Branch("gen_phi", &gen_phi_, "gen_phi/F");
  signal_tree_->Branch("gen_energy", &gen_energy_, "gen_energy/F");
  signal_tree_->Branch("hits_panel", &hits_panel_);
  signal_tree_->Branch("hits_subdet", &hits_subdet_);

  signal_tree_->Branch("hits_tc", &hits_tc_);
  signal_tree_->Branch("hits_eta", &hits_eta_);
  signal_tree_->Branch("hits_phi", &hits_phi_);
  signal_tree_->Branch("hits_pt", &hits_pt_);
  signal_tree_->Branch("hits_simenergy", &hits_simenergy_);
} 

OutputService::
~OutputService()
{
  signal_tree_->Write();
  panel_tree_->Write();
  file_->Close();
}

void
OutputService::
fillDataframe(const DataFrame& dataframe)
{
  clearPanel();
  signal_event_ = dataframe.events[0];
  panel_id_ = dataframe.id;
  panel_layer_ = dataframe.layer;
  panel_subdet_ = dataframe.subdet;
  modules_n_ = dataframe.modules_n;
  for(unsigned ibx=0; ibx<kbunches; ibx++)
  {
    events_[ibx] = dataframe.events[ibx];
    events_type_[ibx] = dataframe.event_types[ibx];
  }
  for(unsigned id=0; id<kdatasize; id++)
  {
    tc_mipPt_[id] = dataframe.data_mipPt[id];
    tc_pt_[id] = dataframe.data_pt[id];
  }
  panel_tree_->Fill();
}

void
OutputService::
fillSignal(const SignalParticle& particle)
{
  clearSignal();
  event_ = particle.event();
  gen_index_ = particle.index();
  gen_id_ = particle.id();
  gen_pt_ = particle.lorentzVector().Pt();
  gen_eta_ = particle.lorentzVector().Eta();
  gen_phi_ = particle.lorentzVector().Phi();
  gen_energy_ = particle.lorentzVector().E();
  const auto& hits = particle.getSelectedHits();
  const unsigned third_per_module = 3;
  const unsigned cell_per_third = 16;
  for(const auto& hit : hits)
  {
    hits_panel_.emplace_back(hit.panelid);
	//    hits_subdet_.emplace_back(hit.subdet);
    unsigned cell_id = hit.cell + hit.third*cell_per_third + hit.module*cell_per_third*third_per_module;
    hits_tc_.emplace_back(cell_id);
    hits_eta_.emplace_back(hit.eta);
    hits_phi_.emplace_back(hit.phi);
    hits_pt_.emplace_back(hit.pt);
    hits_simenergy_.emplace_back(hit.simenergy);
  }
  signal_tree_->Fill();
}

void
OutputService::
clearPanel()
{
  signal_event_ = 0;
  panel_id_ = 0;
  panel_layer_ = 0;
  panel_subdet_ = 0;
  modules_n_ = 0;
  for(unsigned ibx=0; ibx<kbunches; ibx++)
  {
    events_[ibx] = 0;
    events_type_[ibx] = 0;
  }
  for(unsigned id=0; id<kdatasize; id++)
  {
    tc_mipPt_[id] = 0.;
    tc_pt_[id] = 0.;
  }
}

void
OutputService::
clearSignal()
{
  event_ = 0;
  gen_index_ = 0;
  gen_id_ = 0;
  gen_pt_ = 0.;
  gen_eta_ = 0.;
  gen_phi_ = 0.;
  gen_energy_ = 0.;
  hits_panel_.clear();
  hits_subdet_.clear();
  hits_tc_.clear();
  hits_eta_.clear();
  hits_phi_.clear();
  hits_pt_.clear();
  hits_simenergy_.clear();
}


