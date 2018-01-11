
#include<fstream>
#include <iostream>
#include <iomanip>
#include <unordered_set>

#include "Packer.h"


Packer::
Packer(const Geometry& geometry):
  geometry_(&geometry)
{
}


std::vector<DataFrame>
Packer::
pack(const std::vector<Event>& events, const Event& event_0pu, const std::vector<SignalParticle>& signals_particles)
{
  if(events.size()>DataFrame::kbunches)
  {
    throw std::string("More agregated bunch crossings than the 10 supported by the dataframe");
  }
  std::vector<DataFrame> frames;
  // Loop on each set of signal trigger cells
  // corresponding to each gen particles
  for(const auto& signal_particle : signals_particles)
  {
    const auto& signal_hits = signal_particle.getHits();
    if(signal_hits.size()==0) continue;
    // First find all panels hit by the signal
    std::unordered_map<uint32_t, const Panel&> signal_panels;
    std::unordered_set<uint32_t> cells_found;
    for(const auto& hit : signal_hits)
    {
      unsigned panel_id = hit.panelid;
      if(panel_id>0)
      {
        const Panel& panel = event_0pu.getPanel(panel_id);
        signal_panels.emplace(panel_id, panel);
        cells_found.emplace(hit.detid);
      }
    }
    if(cells_found.size()<signal_hits.size())
    {
      std::cout<<"Warning: "<<signal_hits.size()-cells_found.size()<<" signal cell(s) not found in the events\n";
    }
    
    // Form one dataframe for each panel
    for(const auto& id_panel : signal_panels)
    {
      DataFrame frame;
      frame.id = id_panel.second.detid;
      frame.panel = id_panel.second.number;
      frame.layer = id_panel.second.layer;
      frame.modules_n = geometry_->getPanelSize(id_panel.second.number);
      if(frame.modules_n>DataFrame::kmodules)
      {
        throw std::string("More modules in panel than the 6 supported by the dataframe");
      }
      unsigned ievt = 0;
      for(const auto& event : events)
      {
        // std::cerr<<"Packing bx "<<ievt<<"\n";
        frame.events.at(ievt) = event.event();
        frame.event_types.at(ievt) = static_cast<unsigned>(event.type());
        unsigned frame_pointer_0 = ievt*DataFrame::ktriggercells*DataFrame::kmodules;
        // Retrieve cells in the panel
        const auto& cells = event.getCellsFromPanel(id_panel.first);
        for(uint32_t cell_id : cells)
        {
          // std::cerr<<"New cell "<<cell_id<<"\n";

          const TriggerCell& cell = event.getCell(cell_id);
          unsigned cell_module = geometry_->getModuleIndex(cell.module);
          unsigned cell_cell = (cell.cell & TriggerCell::kcell_mask);
          // std::cerr<<"Cell "<<cell.cell<<" -> "<<cell_cell<<"\n";
          cell_cell |= ((cell.third & TriggerCell::kthird_mask) << TriggerCell::kthird_shift);
          // std::cerr<<"Third "<<cell.third<<" -> "<<cell_cell<<"\n";
          if(cell_cell>DataFrame::ktriggercells)
          {
            throw std::string("More trigger cells in the module than the 48 supported by the dataframe");
          }
          unsigned frame_pointer = frame_pointer_0 + cell_module*DataFrame::ktriggercells + cell_cell;
          frame.data_mipPt.at(frame_pointer) = cell.mipPt;
          frame.data_pt.at(frame_pointer) = cell.pt;
          // std::cerr<<frame_pointer<<" = "<<cell.mipPt<<" "<<frame.data_mipPt.at(frame_pointer)<<"\n";
        }
        ievt++;
      }
      frames.emplace_back(std::move(frame));
      // std::cerr<<"=================================\n";
      // std::cerr<<"Panel "<<id_panel.first<<"\n";
      // std::cerr<<"=================================\n";
      // unsigned index = 0;
      // for(float data : frames.back().data_mipPt)
      // {
        // if(index%16==0) std::cerr<<"| ";
        // if(index%DataFrame::ktriggercells==0) std::cerr<<"\n";
        // if(index%(DataFrame::kmodules*DataFrame::ktriggercells)==0) std::cerr<<"\n";
        // std::cerr<<std::setprecision(0)<<std::fixed<<data<<" ";
        // index++;
      // }
      // std::cerr<<"\n";

    }
  }
  return frames;
}
