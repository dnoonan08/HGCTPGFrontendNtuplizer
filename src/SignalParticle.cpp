#include <iostream>
#include "HGCTPG/FrontendNtuplizer/interface/SignalParticle.h"
#include "HGCTPG/FrontendNtuplizer/interface/ISignalSelection.h"


SignalParticle::
SignalParticle(
    unsigned event, unsigned index,
    int id,
    float pt, float eta, float phi, float E
    ):
  event_(event),
  index_(index),
  id_(id)
{
  gen_particle_.SetPtEtaPhiE(pt, eta, phi, E);
}

void
SignalParticle::
addHit(const Hit& hit)
{
  hits_.emplace_back(hit);
}


const std::vector<Hit>& 
SignalParticle::
getSelectedHits() const 
{
  if(selected_hits_.size()==0) return hits_;
  else return selected_hits_;
}

void
SignalParticle::
applySelection(const std::unique_ptr<ISignalSelection>& sel)
{
	selected_hits_ = sel->selectHits(hits_, gen_particle_);
}
