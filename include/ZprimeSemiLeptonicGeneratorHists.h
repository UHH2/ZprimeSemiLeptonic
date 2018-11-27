#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>


class ZprimeSemiLeptonicGeneratorHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicGeneratorHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();
  bool is_mc;

  TH1F   *M_Zprime, *M_Zprime_rebin, *M_Zprime_rebin2, *M_Zprime_rebin3, *M_ttbar, *M_ttbar_rebin, *M_ttbar_rebin2, *M_ttbar_rebin3, *M_top, *M_antitop, *Pt_Zprime, *Pt_ttbar, *Pt_top, *Pt_antitop;

  virtual ~ZprimeSemiLeptonicGeneratorHists();
};
