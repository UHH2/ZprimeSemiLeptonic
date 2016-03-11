#pragma once

#include <string>

#include <UHH2/core/include/Event.h>

#include <UHH2/common/include/TTbarGen.h>

class weightcalc_topptREWGT {

 public:
  explicit weightcalc_topptREWGT(uhh2::Context&, const std::string&, const float, const float);
  virtual ~weightcalc_topptREWGT() {}

  virtual float weight(const uhh2::Event&, const std::string&) const;

 protected:
  uhh2::Event::Handle<TTbarGen> h_ttbargen_;
  float a_, b_;
};
