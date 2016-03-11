#pragma once

#include <vector>

#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/GenParticle.h>

class weightcalc_WjetsREWGT {

 public:
  explicit weightcalc_WjetsREWGT();
  virtual ~weightcalc_WjetsREWGT() {}

  virtual float weight(const uhh2::Event&) const;

  virtual const GenParticle* genW(const std::vector<GenParticle>&) const;

  virtual float kfactor_QCD(const GenParticle&) const;
  virtual float kfactor_EWK(const GenParticle&) const;
};
