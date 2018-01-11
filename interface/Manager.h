#ifndef __Manager_h__
#define __Manager_h__

#include <memory>
#include "TRandom3.h"
#include "Packer.h"
#include "InputService.h"
#include "OutputService.h"
#include "Parameters.h"
#include "Geometry.h"
#include "ISignalSelection.h"

class Manager 
{
  public:
    Manager(const Parameters&);
    ~Manager() {};

    void run();
    

  private:
    void fillEventMap();

    std::unordered_map<int, unsigned> event_to_entry_signal_0pu_;
    Parameters params_;
    InputService input_signal_;
    InputService input_signal_0pu_;
    InputService input_background_;
    OutputService output_;
    Geometry geometry_;
    Packer packer_;
    TRandom3 random_;
    std::unique_ptr<ISignalSelection> signal_selection_;
};

#endif
