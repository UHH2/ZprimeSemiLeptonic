#pragma once

#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/common/include/TopJetIds.h>

#include <string>

class TTbarLJTriggerEffHists : public HistsBASE {

 public:
  explicit TTbarLJTriggerEffHists(uhh2::Context&, const std::string&);
  explicit TTbarLJTriggerEffHists(uhh2::Context&, const std::string&, const TopJetId&, const float);

  virtual void fill(const uhh2::Event&) override;

 protected:

  virtual void init() override;

};
