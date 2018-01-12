#ifndef __HGCTPG_FrontendNtuplizer_Geometry_h__
#define __HGCTPG_FrontendNtuplizer_Geometry_h__

#include <unordered_map>
#include <set>

class Geometry
{
  public:
    static const std::set<unsigned> empty_modules;

  public:
    Geometry(const std::string&);
    ~Geometry() {};

    const std::set<unsigned>& getModulesInPanel(unsigned) const;
    int getModuleIndex(unsigned) const;
    unsigned getPanelSize(unsigned) const;
    
  private:
    std::unordered_map<unsigned, std::set<unsigned>> panel_to_modules_;
    std::unordered_map<unsigned, int> module_index_;
    std::unordered_map<unsigned, unsigned> panel_size_;
};


#endif
