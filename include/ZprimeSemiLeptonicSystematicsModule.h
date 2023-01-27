#pragma once

#include <UHH2/ZprimeSemiLeptonic/include/ElecTriggerSF.h>
#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicHists.h>

class ZprimeSemiLeptonicSystematicsModule: public ModuleBASE {
public:
  explicit ZprimeSemiLeptonicSystematicsModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

private:
  bool is_MC, isDifferentPDFSet;
  TString dataset_version;
  vector<TString> v_systs, v_syst_handlenames, v_variations, v_mcscale_vars, v_psscales, v_psscale_handlenames;
  vector<string> v_nominal_dirtags, v_syst_dirtags, v_mcscale_dirtags, v_psscale_dirtags, v_pdf_dirtags;
  uhh2::Event::Handle<float> eventweight_nominal;
  vector<uhh2::Event::Handle<float>> v_systhandles_nominal, v_systhandles_var, v_mcscalehandles, v_psscalehandles;
  uhh2::Event::Handle<bool> h_ttIsReconstructed;
};
