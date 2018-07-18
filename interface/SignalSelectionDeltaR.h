#ifndef __HGCTPG_FrontendNtuplizer_SignalSelectionDeltaR_h__
#define __HGCTPG_FrontendNtuplizer_SignalSelectionDeltaR_h__

#include "HGCTPG/FrontendNtuplizer/interface/ISignalSelection.h"
#include "TLorentzVector.h"

class SignalSelectionDeltaR : public ISignalSelection
{
  public:
    SignalSelectionDeltaR(const Parameters&);

    virtual std::vector<Hit> selectHits(const std::vector<Hit>&, TLorentzVector gen_particle) const override final;

  private:
    float delta_R_;
};

#endif
