#ifndef __HGCTPG_FrontendNtuplizer_ISignalSelection_h__
#define __HGCTPG_FrontendNtuplizer_ISignalSelection_h__

#include <vector>
#include "HGCTPG/FrontendNtuplizer/interface/SignalParticle.h"
#include "HGCTPG/FrontendNtuplizer/interface/Parameters.h"


class ISignalSelection
{

  public:
    ISignalSelection(const Parameters&) {};
    virtual ~ISignalSelection() {};

    virtual std::vector<Hit> selectHits(const std::vector<Hit>&) const = 0;
};


#endif
