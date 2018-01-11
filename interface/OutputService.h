#ifndef __OutputService_h__
#define __OutputService_h__


#include <vector>
#include <memory>

#include "TFile.h"
#include "TTree.h"
#include "Packer.h"
#include "SignalParticle.h"


class OutputService
{
  public:
    OutputService(const std::string&);
    ~OutputService();

    void fillDataframe(const DataFrame&);
    void fillSignal(const SignalParticle&);

  private:
    static const unsigned kbunches = DataFrame::kbunches;
    static const unsigned kdatasize = DataFrame::kbunches*DataFrame::kmodules*DataFrame::ktriggercells;

    std::unique_ptr<TFile> file_;
    TTree* panel_tree_; // the tree is owned by file_ and deleted when the file is closed
    TTree* signal_tree_; // the tree is owned by file_ and deleted when the file is closed

    // panel tree branches
    unsigned signal_event_;
    unsigned panel_id_;
    unsigned panel_layer_;
    unsigned modules_n_;
    unsigned events_[kbunches];
    unsigned events_type_[kbunches];
    float tc_mipPt_[kdatasize];
    float tc_pt_[kdatasize];
    // signal tree branches
    unsigned event_;
    unsigned gen_index_;
    int gen_id_;
    float gen_pt_;
    float gen_eta_;
    float gen_phi_;
    float gen_energy_;
    std::vector<uint32_t> hits_panel_;
    std::vector<uint32_t> hits_tc_;
    std::vector<float> hits_eta_;
    std::vector<float> hits_phi_;
    std::vector<float> hits_pt_;
    std::vector<float> hits_simenergy_;


    void clearPanel();
    void clearSignal();


};

#endif
