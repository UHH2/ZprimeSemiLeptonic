#pragma once

#include "TGraphAsymmErrors.h"
#include "TFile.h"

#include "UHH2/common/include/Utils.h"

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/HOTVR/include/HadronicTop.h"

class TopTagScaleFactor: public uhh2::AnalysisModule {
public:
  explicit TopTagScaleFactor(uhh2::Context & ctx);
  virtual bool process(uhh2::Event & event) override;
  enum class EMergeCategory{
    isFullyMerged,
    isSemiMerged,
    isNotMerged
  };

private:
  void getSF(double jet_pt, EMergeCategory category);
  EMergeCategory identifyMergeCategory_AK8(std::vector<GenTop> & gentops, const TopJet & tagged_jet);
  Year year;
  uhh2::Event::Handle<std::vector<GenTop>> h_gentops;
  uhh2::Event::Handle<std::vector<TopJet>> h_toptaggedjets;
  float weight_toptagsf = 1.;
  float weight_toptagsf_corr_up = 1.;
  float weight_toptagsf_corr_down = 1.;
  float weight_toptagsf_uncorr_up = 1.;
  float weight_toptagsf_uncorr_down = 1.;
  TGraphAsymmErrors *tgae_fullymerged_tot, *tgae_fullymerged_corr, *tgae_fullymerged_uncorr;
  TGraphAsymmErrors *tgae_semimerged_tot, *tgae_semimerged_corr, *tgae_semimerged_uncorr;
  TGraphAsymmErrors *tgae_notmerged_tot, *tgae_notmerged_corr, *tgae_notmerged_uncorr;
  uhh2::Event::Handle<float> h_toptagsf, h_toptagsf_corr_up, h_toptagsf_corr_down, h_toptagsf_uncorr_up, h_toptagsf_uncorr_down;
};
