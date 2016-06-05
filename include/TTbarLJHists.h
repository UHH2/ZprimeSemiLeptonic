#pragma once

#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/common/include/TopJetIds.h>

#include <string>

class TTbarLJHists : public HistsBASE {

 public:
  explicit TTbarLJHists(uhh2::Context&, const std::string&);
  explicit TTbarLJHists(uhh2::Context&, const std::string&, const TopJetId&, const float);

  virtual void fill(const uhh2::Event&) override;

 protected:
  TopJetId tjet_ID_;
  float    tjet_minDR_jet_;

  virtual void init() override;

 private:
  TH1F* TMVA_response;
  uhh2::Event::Handle<float> tt_tmva_response;

};
