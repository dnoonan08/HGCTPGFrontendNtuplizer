#ifndef __HGCTPG_FrontendNtuplizer_InputService_h__
#define __HGCTPG_FrontendNtuplizer_InputService_h__


#include <vector>
#include <string>
#include <memory>

#include "TChain.h"
#include "HGCTPG/FrontendNtuplizer/interface/Event.h"
#include "HGCTPG/FrontendNtuplizer/interface/SignalParticle.h"
#include "HGCTPG/FrontendNtuplizer/interface/Geometry.h"


class InputService
{
  public:
    InputService(const std::vector<std::string>&, const std::string&, bool, Event::Type, std::string, double);
    ~InputService() {};

    unsigned events() {return tree_.GetEntries();}
    void read(unsigned);
    Event buildEvent();
    std::vector<SignalParticle> buildSignal(const Event&, const Geometry&);


  private:
    // std::unique_ptr<TChain> tree_;
    TChain tree_;
    bool read_signal_;
    Event::Type type_;
	std::string genType_;
	double genJetThreshold_;

    // tree branches
    unsigned event_;
    // gen particles
    int gen_n_;
    std::vector<int>   *gen_id_ = nullptr;
    std::vector<int>   *gen_status_ = nullptr;
    std::vector<float> *gen_energy_ = nullptr;
    std::vector<float> *gen_pt_ = nullptr;
    std::vector<float> *gen_eta_ = nullptr;
    std::vector<float> *gen_phi_ = nullptr;

    // gen jets
    int genjet_n_;
    std::vector<float> *genjet_energy_ = nullptr;
    std::vector<float> *genjet_pt_ = nullptr;
    std::vector<float> *genjet_eta_ = nullptr;
    std::vector<float> *genjet_phi_ = nullptr;

    // trigger cells
    int tc_n_ ;
    std::vector<uint32_t> *tc_id_ = nullptr;
	std::vector<uint32_t> *tc_subdet_ = nullptr;
    std::vector<float> *tc_eta_ = nullptr;
    std::vector<float> *tc_phi_ = nullptr;
    std::vector<float> *tc_pt_ = nullptr;
    std::vector<float> *tc_mipPt_ = nullptr;
    std::vector<float> *tc_simenergy_ = nullptr;
    // panels
    int panel_n_ ;
    std::vector<uint32_t> *panel_id_ = nullptr;
    std::vector<int> *panel_zside_ = nullptr;
    std::vector<int> *panel_layer_ = nullptr;
    std::vector<int> *panel_subdet_ = nullptr;
    std::vector<int> *panel_sector_ = nullptr;
    std::vector<int> *panel_number_ = nullptr;
    std::vector<unsigned> *panel_tc_n_ = nullptr;
    std::vector<std::vector<uint32_t> > *panel_tc_id_ = nullptr;
    std::vector<std::vector<uint32_t> > *panel_tc_mod_ = nullptr;
    std::vector<std::vector<uint32_t> > *panel_tc_third_ = nullptr;
    std::vector<std::vector<uint32_t> > *panel_tc_cell_ = nullptr;
    std::vector<std::vector<float> > *panel_tc_mipPt_ = nullptr;
    std::vector<std::vector<float> > *panel_tc_pt_ = nullptr;

};

#endif
