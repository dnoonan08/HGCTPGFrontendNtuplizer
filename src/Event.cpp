#include <iostream>
#include "Event.h"

const std::set<uint32_t> Event::empty_cells = {};

Event::
Event(Type type, unsigned event):
  type_(type),
  event_(event)
{
}


void
Event::
fill(
    const Panel& panel,
    const std::vector<TriggerCell>& trigger_cells
    )
{
  panels_.emplace(panel.detid, panel);
  auto& tcs = panel_to_cells_[panel.detid];
  for(const auto& tc : trigger_cells)
  {
    trigger_cells_.emplace(tc.detid, tc);
    // fill maps between trigger cells and panels
    cell_to_panel_.emplace(tc.detid, panel.detid);
    tcs.emplace(tc.detid);
  }
}

uint32_t
Event::
getPanelFromCell(uint32_t id) const
{
  const auto& itr = cell_to_panel_.find(id);
  if(itr==cell_to_panel_.end())
  {
    // for(const auto& cell_panel : cell_to_panel_)
    // {
      // std::cerr<<"      "<<cell_panel.first<<" -> "<<cell_panel.second<<"\n";
    // }
    return 0;
  }
  // std::cerr<<" TOTO "<<itr->second<<"\n";
  return itr->second;
}

const std::set<uint32_t>&
Event::
getCellsFromPanel(uint32_t id) const
{
  const auto& itr = panel_to_cells_.find(id);
  if(itr==panel_to_cells_.end()) return empty_cells;
  return itr->second;
}


bool
Event::
containsCell(uint32_t id) const
{
  const auto& itr = trigger_cells_.find(id);
  if(itr==trigger_cells_.end()) return false;
  return true;
}

bool
Event::
containsPanel(uint32_t id) const
{
  const auto& itr = panels_.find(id);
  if(itr==panels_.end()) return false;
  return true;
}

const TriggerCell&
Event::
getCell(uint32_t id) const
{
  const auto& itr = trigger_cells_.find(id);
  if(itr==trigger_cells_.end())
  {
    throw std::string("Trigger cell not existing in event");
  }
  return itr->second;
}

const Panel&
Event::
getPanel(uint32_t id) const
{
  const auto& itr = panels_.find(id);
  if(itr==panels_.end())
  {
    throw std::string("Panel not existing in event");
  }
  return itr->second;
}
