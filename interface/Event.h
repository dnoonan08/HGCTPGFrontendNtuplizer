#ifndef __HGCTPG_FrontendNtuplizer_Event_h__
#define __HGCTPG_FrontendNtuplizer_Event_h__

#include <unordered_map>
#include <set>
#include <vector>


struct TriggerCell
{
  const static unsigned kcell_mask = 0xF;
  const static unsigned kcell_shift = 0;
  const static unsigned kthird_mask = 0x3;
  const static unsigned kthird_shift = 4;

  TriggerCell() {};
  uint32_t detid;
  float mipPt;
  float pt;
  unsigned module;
  unsigned third;
  unsigned cell;
};


struct Panel
{
  Panel() {};
  uint32_t detid;
  int zside;
  int sector;
  int layer;
  int number;
};


class Event
{
  public:
    enum class Type {Background, Signal};
    static const std::set<uint32_t> empty_cells;

  public:
    Event(Type, unsigned);
    ~Event() {};

    void fill(const Panel&, const std::vector<TriggerCell>&);

    int event() const {return event_;}
    Type type() const {return type_;}
    uint32_t getPanelFromCell(uint32_t) const;
    const std::set<uint32_t>& getCellsFromPanel(uint32_t) const;
    bool containsCell(uint32_t) const;
    bool containsPanel(uint32_t) const;
    const TriggerCell& getCell(uint32_t) const;
    const Panel& getPanel(uint32_t) const;

  private:
    Type type_;
    int event_;
    std::unordered_map<uint32_t, uint32_t> cell_to_panel_;
    std::unordered_map<uint32_t, std::set<uint32_t>> panel_to_cells_;
    std::unordered_map<uint32_t, TriggerCell> trigger_cells_;
    std::unordered_map<uint32_t, Panel> panels_;

};

#endif
