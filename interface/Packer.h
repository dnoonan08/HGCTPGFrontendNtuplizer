#ifndef __Packer_h__
#define __Packer_h__

#include <array>
#include <vector>
#include <unordered_map>

#include "Event.h"
#include "SignalParticle.h"
#include "Geometry.h"



struct DataFrame
{
  static const unsigned kbunches = 10;
  static const unsigned kmodules = 6;
  static const unsigned ktriggercells = 48;

  DataFrame():
    id(0),
    panel(0),
    layer(0),
    modules_n(0),
    events(),
    event_types(),
    data_mipPt(),
    data_pt()
  {}
  uint32_t id;
  unsigned panel;
  unsigned layer;
  unsigned modules_n;
  std::array<unsigned, kbunches> events;
  std::array<unsigned, kbunches> event_types;
  std::array<float, kbunches*kmodules*ktriggercells> data_mipPt;
  std::array<float, kbunches*kmodules*ktriggercells> data_pt;
};


class Packer
{

  public:
    Packer(const Geometry&);
    ~Packer() {};

    std::vector<DataFrame> pack(
        const std::vector<Event>&,
        const Event&,
        const std::vector<SignalParticle>&
        );

  private:
    const Geometry* geometry_;


};

#endif
