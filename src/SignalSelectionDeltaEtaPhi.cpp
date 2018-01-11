#include <cmath>
#include "TVector2.h"
#include "SignalSelectionDeltaEtaPhi.h"


SignalSelectionDeltaEtaPhi::
SignalSelectionDeltaEtaPhi(const Parameters& pars):
  ISignalSelection(pars)
{
  delta_eta_ = pars.signal().hit_selection_parameters.at("delta_eta");
  delta_phi_ = pars.signal().hit_selection_parameters.at("delta_phi");
}

std::vector<Hit>
SignalSelectionDeltaEtaPhi::
selectHits(const std::vector<Hit>& hits) const
{
  std::vector<Hit> selected_hits;
  // Compute the vector sum
  TLorentzVector p4_sum;
  for(const auto& hit : hits)
  {
    double simpt = hit.simenergy/std::cosh(hit.eta);
    TLorentzVector p4;
    p4.SetPtEtaPhiM(simpt, hit.eta, hit.phi, 0.);
    p4_sum += p4;
  }
  // Select signal hits with a DeltaEta DeltaPhi cut
  // around the sum direction
  for(const auto& hit : hits)
  {
    double deta = hit.eta - p4_sum.Eta();
    double dphi = TVector2::Phi_mpi_pi(hit.phi - p4_sum.Phi());
    if(std::abs(deta)<delta_eta_ && std::abs(dphi)<delta_phi_)
    {
      selected_hits.push_back(hit);
    }
  }
  return selected_hits;
}
