#ifndef __HGCTPG_FrontendNtuplizer_SignalSelectionDeltaEtaPhi_h__
#define __HGCTPG_FrontendNtuplizer_SignalSelectionDeltaEtaPhi_h__

#include "HGCTPG/FrontendNtuplizer/interface/ISignalSelection.h"

class SignalSelectionDeltaEtaPhi : public ISignalSelection
{
  public:
    SignalSelectionDeltaEtaPhi(const Parameters&);

    virtual std::vector<Hit> selectHits(const std::vector<Hit>&) const override final;

  private:
    float delta_eta_;
    float delta_phi_;
};

#endif
