#include <cmath>
#include <iostream>
#include "TVector2.h"
#include "HGCTPG/FrontendNtuplizer/interface/SignalSelectionDeltaR.h"


SignalSelectionDeltaR::
SignalSelectionDeltaR(const Parameters& pars):
  ISignalSelection(pars)
{
  delta_R_ = pars.signal().hit_selection_parameters.at("delta_R");
}

std::vector<Hit>
SignalSelectionDeltaR::
selectHits(const std::vector<Hit>& hits, TLorentzVector gen_particle) const
{
  std::vector<Hit> selected_hits;
  // Compute the vector sum
  // TLorentzVector p4_sum;
  // for(const auto& hit : hits)
  // {
  //   double simpt = hit.simenergy/std::cosh(hit.eta);
  //   TLorentzVector p4;
  //   p4.SetPtEtaPhiM(simpt, hit.eta, hit.phi, 0.);
  //   p4_sum += p4;
  // }
  // Select signal hits with a DeltaEta DeltaPhi cut
  // around the sum direction
  for(const auto& hit : hits)
  {
    double deta = hit.eta - gen_particle.Eta();
    double dphi = TVector2::Phi_mpi_pi(hit.phi - gen_particle.Phi());
	//	std::cout << std::sqrt(deta*deta+dphi*dphi) < delta_R_ << std::endl;
	if (std::sqrt(deta*deta+dphi*dphi) < delta_R_){
	  selected_hits.push_back(hit);
	}
  }
  return selected_hits;
}
