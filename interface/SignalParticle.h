#ifndef __SignalParticle_h__
#define __SignalParticle_h__

#include <vector>
#include <memory>
#include "TLorentzVector.h"
// #include "ISignalSelection.h"

struct Hit
{
  const static unsigned kcell_mask = 0xF;
  const static unsigned kcell_shift = 0;
  const static unsigned kthird_mask = 0x3;
  const static unsigned kthird_shift = 4;

  Hit() {};
  uint32_t detid;
  uint32_t panelid;
  float eta;
  float phi;
  float pt;
  float simenergy;
  unsigned module;
  unsigned third;
  unsigned cell;
};

class ISignalSelection;

class SignalParticle
{
  public:
    SignalParticle(unsigned event, unsigned index,
        int id,
        float pt, float eta, float phi, float E);
    ~SignalParticle() {}; 

    void addHit(const Hit&);
    const std::vector<Hit>& getHits() const {return hits_;}
    const std::vector<Hit>& getSelectedHits() const ;
    const TLorentzVector& lorentzVector() const {return gen_particle_;}

    unsigned event() const {return event_;};
    unsigned index() const {return index_;};
    int id() const {return id_;};

    void applySelection(const std::unique_ptr<ISignalSelection>& sel);

  private:
    unsigned event_;
    unsigned index_;
    int id_;

    std::vector<Hit> hits_;
    std::vector<Hit> selected_hits_;
    TLorentzVector gen_particle_;

};

#endif
