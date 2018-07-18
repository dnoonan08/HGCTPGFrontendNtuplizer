
#include <iostream>
#include <fstream>
#include "HGCTPG/FrontendNtuplizer/interface/Geometry.h"


const std::set<unsigned> Geometry::empty_modules = {};

Geometry::
Geometry(const std::string& panel_geometry)
{
  std::ifstream panel_geometry_file(panel_geometry);
  if(!panel_geometry_file.is_open())
  {
    throw std::string("Cannot open module to panel mapping file \n");
  }
  short module   = 0;
  short panel  = 0;
  for(; panel_geometry_file>>module>>panel; )
  {
    panel_to_modules_[panel].emplace(module);
  }
  panel_geometry_file.close();
  // Store the index of the modules in the panels
  for(const auto& panel_modules : panel_to_modules_)
  {
    panel_size_[panel_modules.first] = panel_modules.second.size();
    unsigned index = 0;
    for(const auto& module : panel_modules.second)
    {
      module_index_[module] = index;
      index++;
    }
  }
}



const std::set<unsigned>& 
Geometry::
getModulesInPanel(unsigned panel) const
{
  const auto& itr = panel_to_modules_.find(panel);
  if(itr==panel_to_modules_.end()) return empty_modules;
  return itr->second;
}

int
Geometry::
getModuleIndex(unsigned module) const
{
	//	std::cout << "-----------------" << std::endl;
	//	std::cout << module << std::endl;
	const auto& itr = module_index_.find(module);
	if(itr==module_index_.end()) {
		// std::cout << "NOTFOUND" << std::endl;
		return -1;
	}
	//	std::cout << itr->second << std::endl;
	return itr->second;
}

unsigned
Geometry::
getPanelSize(unsigned panel) const
{
  const auto& itr = panel_size_.find(panel);
  if(itr==panel_size_.end()) return 0;
  return itr->second;
}
