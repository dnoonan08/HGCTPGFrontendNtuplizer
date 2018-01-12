#ifndef __HGCTPG_FrontendNtuplizer_Manager_h__
#define __HGCTPG_FrontendNtuplizer_Manager_h__

#include <memory>
#include "TRandom3.h"
#include "HGCTPG/FrontendNtuplizer/interface/Packer.h"
#include "HGCTPG/FrontendNtuplizer/interface/InputService.h"
#include "HGCTPG/FrontendNtuplizer/interface/OutputService.h"
#include "HGCTPG/FrontendNtuplizer/interface/Parameters.h"
#include "HGCTPG/FrontendNtuplizer/interface/Geometry.h"
#include "HGCTPG/FrontendNtuplizer/interface/ISignalSelection.h"

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
