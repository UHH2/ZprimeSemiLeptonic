#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>


class ZprimeSemiLeptonicCHSMatchHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicCHSMatchHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();
  bool is_mc;

TH1F *N_jets, *pt_jet, *pt_jet1, *pt_jet2, *pt_jet3, *eta_jet, *eta_jet1, *eta_jet2, *eta_jet3, *phi_jet, *phi_jet1, *phi_jet2, *phi_jet3, *m_jet, *m_jet1, *m_jet2, *m_jet3, *bscore_jet, *bscore_jet1, *bscore_jet2, *bscore_jet3, *N_bJets_loose, *N_bJets_med, *N_bJets_tight;

TH1F *CHS_matched_N_jets, *CHS_matched_pt_jet, *CHS_matched_pt_jet1, *CHS_matched_pt_jet2, *CHS_matched_pt_jet3, *CHS_matched_eta_jet, *CHS_matched_eta_jet1, *CHS_matched_eta_jet2, *CHS_matched_eta_jet3, *CHS_matched_phi_jet, *CHS_matched_phi_jet1, *CHS_matched_phi_jet2, *CHS_matched_phi_jet3, *CHS_matched_m_jet, *CHS_matched_m_jet1, *CHS_matched_m_jet2, *CHS_matched_m_jet3, *CHS_matched_bscore_jet, *CHS_matched_bscore_jet1, *CHS_matched_bscore_jet2, *CHS_matched_bscore_jet3, *CHS_matched_N_bJets_loose, *CHS_matched_N_bJets_med, *CHS_matched_N_bJets_tight;

uhh2::Event::Handle< std::vector<Jet> > h_CHSjets_matched;
  virtual ~ZprimeSemiLeptonicCHSMatchHists();
};
