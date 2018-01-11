#ifndef __SignalSelectionDeltaEtaPhi_h__
#define __SignalSelectionDeltaEtaPhi_h__

#include "ISignalSelection.h"

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
