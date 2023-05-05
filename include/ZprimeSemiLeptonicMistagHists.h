#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>


class ZprimeSemiLeptonicMistagHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicMistagHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();
  bool is_mc, ishotvr, isdeepAK8;


TH1F *N_AK8jets_pt200, *pt_AK8jets_pt200, *pt_AK8jet1_pt200, *eta_AK8jets_pt200, *eta_AK8jet1_pt200, *phi_AK8jets_pt200, *phi_AK8jet1_pt200, *mSD_AK8jets_pt200, *mSD_AK8jet1_pt200, *tau21_AK8jets_pt200, *tau21_AK8jet1_pt200, *tau32_AK8jets_pt200, *tau32_AK8jet1_pt200;

TH1F *N_AK8Topjets_pt200, *pt_AK8Topjets_pt200, *pt_AK8Topjet1_pt200, *eta_AK8Topjets_pt200, *eta_AK8Topjet1_pt200, *phi_AK8Topjets_pt200, *phi_AK8Topjet1_pt200, *mSD_AK8Topjets_pt200, *mSD_AK8Topjet1_pt200, *tau21_AK8Topjets_pt200, *tau21_AK8Topjet1_pt200, *tau32_AK8Topjets_pt200, *tau32_AK8Topjet1_pt200;

TH1F *N_AK8Lightjets_pt200, *pt_AK8Lightjets_pt200, *pt_AK8Lightjet1_pt200, *eta_AK8Lightjets_pt200, *eta_AK8Lightjet1_pt200, *phi_AK8Lightjets_pt200, *phi_AK8Lightjet1_pt200, *mSD_AK8Lightjets_pt200, *mSD_AK8Lightjet1_pt200, *tau21_AK8Lightjets_pt200, *tau21_AK8Lightjet1_pt200, *tau32_AK8Lightjets_pt200, *tau32_AK8Lightjet1_pt200;


TH1F *N_AK8jets, *pt_AK8jets, *pt_AK8jet1, *eta_AK8jets, *eta_AK8jet1, *phi_AK8jets, *phi_AK8jet1, *mSD_AK8jets, *mSD_AK8jet1, *tau21_AK8jets, *tau21_AK8jet1, *tau32_AK8jets, *tau32_AK8jet1;

TH1F *N_AK8Topjets, *pt_AK8Topjets, *pt_AK8Topjet1, *eta_AK8Topjets, *eta_AK8Topjet1, *phi_AK8Topjets, *phi_AK8Topjet1, *mSD_AK8Topjets, *mSD_AK8Topjet1, *tau21_AK8Topjets, *tau21_AK8Topjet1, *tau32_AK8Topjets, *tau32_AK8Topjet1;

TH1F *N_AK8Lightjets, *pt_AK8Lightjets, *pt_AK8Lightjet1, *eta_AK8Lightjets, *eta_AK8Lightjet1, *phi_AK8Lightjets, *phi_AK8Lightjet1, *mSD_AK8Lightjets, *mSD_AK8Lightjet1, *tau21_AK8Lightjets, *tau21_AK8Lightjet1, *tau32_AK8Lightjets, *tau32_AK8Lightjet1;


TH1F *N_AK8jets_tagged, *pt_AK8jets_tagged, *pt_AK8jet1_tagged, *eta_AK8jets_tagged, *eta_AK8jet1_tagged, *phi_AK8jets_tagged, *phi_AK8jet1_tagged, *mSD_AK8jets_tagged, *mSD_AK8jet1_tagged, *tau21_AK8jets_tagged, *tau21_AK8jet1_tagged, *tau32_AK8jets_tagged, *tau32_AK8jet1_tagged;

TH1F *N_AK8Topjets_tagged, *pt_AK8Topjets_tagged, *pt_AK8Topjet1_tagged, *eta_AK8Topjets_tagged, *eta_AK8Topjet1_tagged, *phi_AK8Topjets_tagged, *phi_AK8Topjet1_tagged, *mSD_AK8Topjets_tagged, *mSD_AK8Topjet1_tagged, *tau21_AK8Topjets_tagged, *tau21_AK8Topjet1_tagged, *tau32_AK8Topjets_tagged, *tau32_AK8Topjet1_tagged;

TH1F *N_AK8Lightjets_tagged, *pt_AK8Lightjets_tagged, *pt_AK8Lightjet1_tagged, *eta_AK8Lightjets_tagged, *eta_AK8Lightjet1_tagged, *phi_AK8Lightjets_tagged, *phi_AK8Lightjet1_tagged, *mSD_AK8Lightjets_tagged, *mSD_AK8Lightjet1_tagged, *tau21_AK8Lightjets_tagged, *tau21_AK8Lightjet1_tagged, *tau32_AK8Lightjets_tagged, *tau32_AK8Lightjet1_tagged;

  uhh2::Event::Handle< std::vector<TopJet> > h_AK8TopTags;
  virtual ~ZprimeSemiLeptonicMistagHists();
};
