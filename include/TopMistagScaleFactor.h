#pragma once

#include "TH1F.h"
#include "TFile.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"

class TopMistagScaleFactor: public uhh2::AnalysisModule{
public:
  explicit TopMistagScaleFactor(uhh2::Context & ctx);
  virtual bool process(uhh2::Event & event) override;

private:
  Year year;
  bool is_mc, ishotvr, isdeepAK8;
  float sf_value, sf_error;
  uhh2::Event::Handle< std::vector<TopJet>> h_AK8TopTags;
  float weight_topmistagsf = 1.;
  float weight_topmistagsf_up = 1.;
  float weight_topmistagsf_down = 1.;
  TH1F *hist;
  uhh2::Event::Handle<float> h_topmistagsf, h_topmistagsf_up, h_topmistagsf_down;
};
