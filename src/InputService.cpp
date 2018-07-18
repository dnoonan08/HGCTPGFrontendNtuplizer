#include <iostream>


#include "TLorentzVector.h"
#include "HGCTPG/FrontendNtuplizer/interface/InputService.h"


InputService::
InputService(
    const std::vector<std::string>& file_list,
    const std::string& tree_name,
    bool read_signal,
    Event::Type type,
	std::string genType,
	double genJetThreshold
    ):
  tree_(tree_name.c_str()),
  read_signal_(read_signal),
  type_(type),
  genType_(genType),
  genJetThreshold_(genJetThreshold)
{
  // tree_.SetDirectory(0);
  for(const auto& f : file_list)
  {
    tree_.Add(f.c_str());
  }
  tree_.SetBranchStatus("*", 0);
  tree_.SetBranchStatus("event", 1);
  tree_.SetBranchStatus("panel_n", 1);
  tree_.SetBranchStatus("panel_id", 1);
  tree_.SetBranchStatus("panel_zside", 1);
  tree_.SetBranchStatus("panel_layer", 1);
  tree_.SetBranchStatus("panel_subdet", 1);
  tree_.SetBranchStatus("panel_sector", 1);
  tree_.SetBranchStatus("panel_number", 1);
  tree_.SetBranchStatus("panel_tc_n", 1);
  tree_.SetBranchStatus("panel_tc_id", 1);
  tree_.SetBranchStatus("panel_tc_mod", 1);
  tree_.SetBranchStatus("panel_tc_third", 1);
  tree_.SetBranchStatus("panel_tc_cell", 1);
  tree_.SetBranchStatus("panel_tc_mipPt", 1);
  tree_.SetBranchStatus("panel_tc_pt", 1);

  tree_.SetBranchAddress("event", &event_);
  tree_.SetBranchAddress("panel_n", &panel_n_);
  tree_.SetBranchAddress("panel_id", &panel_id_);
  tree_.SetBranchAddress("panel_zside", &panel_zside_);
  tree_.SetBranchAddress("panel_layer", &panel_layer_);
  tree_.SetBranchAddress("panel_subdet", &panel_subdet_);
  tree_.SetBranchAddress("panel_sector", &panel_sector_);
  tree_.SetBranchAddress("panel_number", &panel_number_);
  tree_.SetBranchAddress("panel_tc_n", &panel_tc_n_);
  tree_.SetBranchAddress("panel_tc_id", &panel_tc_id_);
  tree_.SetBranchAddress("panel_tc_mod", &panel_tc_mod_);
  tree_.SetBranchAddress("panel_tc_third", &panel_tc_third_);
  tree_.SetBranchAddress("panel_tc_cell", &panel_tc_cell_);
  tree_.SetBranchAddress("panel_tc_mipPt", &panel_tc_mipPt_);
  tree_.SetBranchAddress("panel_tc_pt", &panel_tc_pt_);

  if(read_signal_)
  {
    tree_.SetBranchStatus("gen_n", 1);
    tree_.SetBranchStatus("gen_id", 1);
    tree_.SetBranchStatus("gen_status", 1);
    tree_.SetBranchStatus("gen_energy", 1);
    tree_.SetBranchStatus("gen_pt", 1);
    tree_.SetBranchStatus("gen_eta", 1);
    tree_.SetBranchStatus("gen_phi", 1);

    tree_.SetBranchAddress("gen_n", &gen_n_);
    tree_.SetBranchAddress("gen_id", &gen_id_);
    tree_.SetBranchAddress("gen_status", &gen_status_);
    tree_.SetBranchAddress("gen_energy", &gen_energy_);
    tree_.SetBranchAddress("gen_pt", &gen_pt_);
    tree_.SetBranchAddress("gen_eta", &gen_eta_);
    tree_.SetBranchAddress("gen_phi", &gen_phi_);

	if (genType=="genJet"){
		tree_.SetBranchStatus("genjet_n", 1);
		tree_.SetBranchStatus("genjet_energy", 1);
		tree_.SetBranchStatus("genjet_pt", 1);
		tree_.SetBranchStatus("genjet_eta", 1);
		tree_.SetBranchStatus("genjet_phi", 1);

		tree_.SetBranchAddress("genjet_n", &genjet_n_);
		tree_.SetBranchAddress("genjet_energy", &genjet_energy_);
		tree_.SetBranchAddress("genjet_pt", &genjet_pt_);
		tree_.SetBranchAddress("genjet_eta", &genjet_eta_);
		tree_.SetBranchAddress("genjet_phi", &genjet_phi_);
	}

    tree_.SetBranchStatus("tc_n", 1);
    tree_.SetBranchStatus("tc_eta", 1);
    tree_.SetBranchStatus("tc_phi", 1);
    tree_.SetBranchStatus("tc_pt", 1);
    tree_.SetBranchStatus("tc_id", 1);
    tree_.SetBranchStatus("tc_subdet", 1);
    tree_.SetBranchStatus("tc_mipPt", 1);
    tree_.SetBranchStatus("tc_simenergy", 1);

    tree_.SetBranchAddress("tc_n", &tc_n_);
    tree_.SetBranchAddress("tc_eta", &tc_eta_);
    tree_.SetBranchAddress("tc_phi", &tc_phi_);
    tree_.SetBranchAddress("tc_pt", &tc_pt_);
    tree_.SetBranchAddress("tc_id", &tc_id_);
    tree_.SetBranchAddress("tc_subdet", &tc_subdet_);
    tree_.SetBranchAddress("tc_mipPt", &tc_mipPt_);
    tree_.SetBranchAddress("tc_simenergy", &tc_simenergy_);
  }
  
}


void
InputService::
read(unsigned entry)
{
  tree_.GetEntry(entry);
}


Event
InputService::
buildEvent()
{
  Event event(type_, event_);
  for(int p=0; p<panel_n_; p++)
  {
    // fill panel data
    uint32_t panel_id = panel_id_->at(p);
    Panel panel;
    panel.detid = panel_id;
    panel.zside = panel_zside_->at(p);
    panel.layer = panel_layer_->at(p);
    panel.subdet = panel_subdet_->at(p);
    panel.sector = panel_sector_->at(p);
    panel.number = panel_number_->at(p);
    std::vector<TriggerCell> trigger_cells;
    for(unsigned c=0; c<panel_tc_n_->at(p); c++)
    {
      // fill trigger cell data
      uint32_t triggercell_id = panel_tc_id_->at(p).at(c);
      TriggerCell triggercell;
      triggercell.detid = triggercell_id;
      triggercell.mipPt = panel_tc_mipPt_->at(p).at(c);
      triggercell.pt = panel_tc_pt_->at(p).at(c);
      triggercell.module = panel_tc_mod_->at(p).at(c);
      triggercell.third = panel_tc_third_->at(p).at(c);
      triggercell.cell = panel_tc_cell_->at(p).at(c);
      trigger_cells.emplace_back(triggercell);
    }
    event.fill(panel, trigger_cells);
  }
  return event;
}


std::vector<SignalParticle>
InputService::
buildSignal(const Event& event, const Geometry& geometry)
{
  // Build trigger cell 4-vectors and split them in positive / negative sides
  std::vector<std::pair<Hit, TLorentzVector>> trigger_cells_side_plus;
  std::vector<std::pair<Hit, TLorentzVector>> trigger_cells_side_minus;
  for(int itc=0; itc<tc_n_; itc++)
  {
    // select only trigger cells which contain sim hits
    // and not in the BH
	  //	  if(tc_simenergy_->at(itc)>0. && tc_subdet_->at(itc)!=5)
	  if(tc_simenergy_->at(itc)>0.)
    {
      if(tc_eta_->at(itc)>0)
      {

        trigger_cells_side_plus.emplace_back(std::make_pair(
              Hit(),
              TLorentzVector()
              ));
        uint32_t panel_id = event.getPanelFromCell(tc_id_->at(itc));
        const TriggerCell& cell = event.getCell(tc_id_->at(itc));
        unsigned cell_module = geometry.getModuleIndex(cell.module);
        trigger_cells_side_plus.back().first.detid = tc_id_->at(itc);
        trigger_cells_side_plus.back().first.panelid = panel_id;
        trigger_cells_side_plus.back().first.eta = tc_eta_->at(itc);
        trigger_cells_side_plus.back().first.phi = tc_phi_->at(itc);
        trigger_cells_side_plus.back().first.pt = tc_pt_->at(itc);
        trigger_cells_side_plus.back().first.simenergy = tc_simenergy_->at(itc);
        trigger_cells_side_plus.back().first.subdet = tc_subdet_->at(itc);
        trigger_cells_side_plus.back().first.module = cell_module;
        trigger_cells_side_plus.back().first.third = cell.third;
        trigger_cells_side_plus.back().first.cell = cell.cell;

        trigger_cells_side_plus.back().second.SetPtEtaPhiM(
            tc_pt_->at(itc),
            tc_eta_->at(itc),
            tc_phi_->at(itc),
            0
            );
      }
      else
      {
        trigger_cells_side_minus.emplace_back(std::make_pair(
              Hit(),
              TLorentzVector()
              ));
        uint32_t panel_id = event.getPanelFromCell(tc_id_->at(itc));
        const TriggerCell& cell = event.getCell(tc_id_->at(itc));
        unsigned cell_module = geometry.getModuleIndex(cell.module);
        trigger_cells_side_minus.back().first.detid = tc_id_->at(itc);
        trigger_cells_side_minus.back().first.panelid = panel_id;
        trigger_cells_side_minus.back().first.eta = tc_eta_->at(itc);
        trigger_cells_side_minus.back().first.phi = tc_phi_->at(itc);
        trigger_cells_side_minus.back().first.pt = tc_pt_->at(itc);
        trigger_cells_side_minus.back().first.simenergy = tc_simenergy_->at(itc);
        trigger_cells_side_minus.back().first.subdet = tc_subdet_->at(itc);
        trigger_cells_side_minus.back().first.module = cell_module;
        trigger_cells_side_minus.back().first.third = cell.third;
        trigger_cells_side_minus.back().first.cell = cell.cell;

        trigger_cells_side_minus.back().second.SetPtEtaPhiM(
            tc_pt_->at(itc),
            tc_eta_->at(itc),
            tc_phi_->at(itc),
            0
            );
      }
    }
  }
  // Associate trigger cells to gen particles
  std::vector<SignalParticle> signal_particles;
  if (genType_!="genJet"){
    for(int ig=0; ig<gen_n_; ig++)
    {
      // stable particle in the endcaps
      if(gen_status_->at(ig)==1 && 
          std::abs(gen_eta_->at(ig))>1.6 &&
          std::abs(gen_eta_->at(ig))<2.9
          )
      {
        SignalParticle particle(
            event_,
            ig,
            gen_id_->at(ig),
            gen_pt_->at(ig),
            gen_eta_->at(ig),
            gen_phi_->at(ig),
            gen_energy_->at(ig)
            );
        if(particle.lorentzVector().Eta()>0)
        {
          for(const auto& id_p : trigger_cells_side_plus)
          {
            particle.addHit(id_p.first);
          }
        }
        else
        {
          for(const auto& id_p : trigger_cells_side_minus)
          {
            particle.addHit(id_p.first);
          }
        }
        signal_particles.emplace_back(particle);
      }
    }
  }
  else {
    for(int ig=0; ig<genjet_n_; ig++)
    {
      // stable particle in the endcaps
      if( std::abs(genjet_eta_->at(ig))>1.6 &&
          std::abs(genjet_eta_->at(ig))<2.9 && 
		  genjet_pt_->at(ig) > genJetThreshold_
          )
      {
        SignalParticle particle(
            event_,
            ig,			
			0,
            genjet_pt_->at(ig),
            genjet_eta_->at(ig),
            genjet_phi_->at(ig),
            genjet_energy_->at(ig)
            );
        if(particle.lorentzVector().Eta()>0)
        {
          for(const auto& id_p : trigger_cells_side_plus)
          {
            particle.addHit(id_p.first);
          }
        }
        else
        {
          for(const auto& id_p : trigger_cells_side_minus)
          {
            particle.addHit(id_p.first);
          }
        }
        signal_particles.emplace_back(particle);
      }
    }
  }
  return signal_particles;
}
