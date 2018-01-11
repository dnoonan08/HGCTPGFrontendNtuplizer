#ifndef __ISignalSelection_h__
#define __ISignalSelection_h__

#include <vector>
#include "SignalParticle.h"
#include "Parameters.h"


class ISignalSelection
{

  public:
    ISignalSelection(const Parameters&) {};
    virtual ~ISignalSelection() {};

    virtual std::vector<Hit> selectHits(const std::vector<Hit>&) const = 0;
};


#endif
