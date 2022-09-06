#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <TLorentzVector.h>

class ZprimeSemiLeptonicEleHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicEleHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();

  TH1F *N_ele, *pt_ele, *eta_ele, *phi_ele;

  TH1F *pt_ele_lowpt, *pt_ele_midpt, *pt_ele_highpt, *eta_ele_lowpt, *eta_ele_midpt, *eta_ele_highpt, *phi_ele_lowpt, *phi_ele_midpt, *phi_ele_highpt;

  virtual ~ZprimeSemiLeptonicEleHists();
};
