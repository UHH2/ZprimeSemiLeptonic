#pragma once

#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>
#include <UHH2/core/include/Selection.h>
#include <UHH2/common/include/ObjectIdUtils.h>

class EffyJetTTAGHists: public HistsBASE {

 public:
  explicit EffyJetTTAGHists(uhh2::Context&, const std::string&, const TopJetId&, const float);
  virtual void fill(const uhh2::Event&) override;

 protected:
  TopJetId ttagID_;
  std::unique_ptr<uhh2::Selection> ttagevt_sel;
  float minDR_ttag_jet_;
  float maxDR_tjet_gentop_;

  virtual void init() override;
};
