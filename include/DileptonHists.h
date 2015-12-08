#pragma once

#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/common/include/TopJetIds.h>

#include <string>

class DileptonHists : public HistsBASE {

 public:
  explicit DileptonHists(uhh2::Context&, const std::string&);

  virtual void fill(const uhh2::Event&) override;

 protected:
  virtual void init() override;
};
