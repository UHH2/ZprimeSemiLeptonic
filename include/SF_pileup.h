#pragma once

#include <string>

#include <TFile.h>
#include <TH1F.h>

#include <UHH2/core/include/Event.h>

class weightcalc_pileup {

 public:
  explicit weightcalc_pileup(const std::string&, const std::string&, const std::string& h_pu_DATA="pileup", const std::string& h_pu_MC="pileup");

  virtual ~weightcalc_pileup();

  virtual float weight(const uhh2::Event&) const;

 protected:
  TFile* f_pileupDATA_;
  TFile* f_pileupMC_;

  TH1F* h_pileupDATA_;
  TH1F* h_pileupMC_;
};
