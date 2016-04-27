#pragma once

#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>

#include <UHH2/common/include/ObjectIdUtils.h>

class EffyJetBTAGHists: public HistsBASE {

 public:
  explicit EffyJetBTAGHists(uhh2::Context&, const std::string&, const TopJetId&, const float);
  virtual void fill(const uhh2::Event&) override;

 protected:
  bool check_subjets_;
  TopJetId ttagID_;
  float minDR_ttag_jet_;

  virtual void init() override;
};
