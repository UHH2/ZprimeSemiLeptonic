#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <TLorentzVector.h>
#include "TH1F.h"
#include <string>
#include <math.h>
#include <sstream>
#include <iostream>

namespace uhh2 {

class ZprimeSemiLeptonicPDFHists: public uhh2::Hists {
  public:
    explicit ZprimeSemiLeptonicPDFHists(uhh2::Context&, const std::string&);
    virtual void fill(const uhh2::Event&) override;
    std::string hist_names[100];

  protected:
    bool is_mc;
    uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
    uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;
    uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;
    virtual ~ZprimeSemiLeptonicPDFHists();
};
}
