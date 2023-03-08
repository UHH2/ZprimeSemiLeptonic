#include "UHH2/ZprimeSemiLeptonic/include/TopTagScaleFactor.h"

using namespace uhh2;
using namespace std;

TopTagScaleFactor::TopTagScaleFactor(uhh2::Context & ctx){
  h_gentops = ctx.get_handle<vector<GenTop>>("HadronicTop");
  h_toptaggedjets = ctx.get_handle<vector<TopJet>>("DeepAK8TopTags");

  h_toptagsf = ctx.declare_event_output<float>("weight_toptagsf");
  h_toptagsf_corr_up = ctx.declare_event_output<float>("weight_toptagsf_corr_up");
  h_toptagsf_corr_down = ctx.declare_event_output<float>("weight_toptagsf_corr_down");
  h_toptagsf_uncorr_up = ctx.declare_event_output<float>("weight_toptagsf_uncorr_up");
  h_toptagsf_uncorr_down = ctx.declare_event_output<float>("weight_toptagsf_uncorr_down");

  TString path = "/nfs/dust/cms/user/matthies/KseniaAndHenrik/SF_ak8_t__MDdeepak8__2023-03-06/";

  const Year & year = extract_year(ctx);
  TString year_tag;
  if(year == Year::isUL16preVFP) year_tag = "UL16preVFP";
  else if(year == Year::isUL16postVFP) year_tag = "UL16postVFP";
  else if(year == Year::isUL17) year_tag = "UL17";
  else if(year == Year::isUL18) year_tag = "UL18";
  else throw runtime_error("TopTagScaleFactor: no valid year selected");

  TFile *f = TFile::Open(path + "scale_factors_obs_" + year_tag + ".root");
  tgae_fullymerged_tot = (TGraphAsymmErrors*) f->Get(("FullyMerged_" + year_tag + "_tot").Data());
  tgae_fullymerged_corr = (TGraphAsymmErrors*) f->Get(("FullyMerged_" + year_tag + "_corr").Data());
  tgae_fullymerged_uncorr  = (TGraphAsymmErrors*) f->Get(("FullyMerged_" + year_tag + "_uncorr").Data());
  tgae_semimerged_tot = (TGraphAsymmErrors*) f->Get(("SemiMerged_" + year_tag + "_tot").Data());
  tgae_semimerged_corr = (TGraphAsymmErrors*) f->Get(("SemiMerged_" + year_tag + "_corr").Data());
  tgae_semimerged_uncorr = (TGraphAsymmErrors*) f->Get(("SemiMerged_" + year_tag + "_uncorr").Data());
  tgae_notmerged_tot = (TGraphAsymmErrors*) f->Get(("NotMerged_" + year_tag + "_tot").Data());
  tgae_notmerged_corr = (TGraphAsymmErrors*) f->Get(("NotMerged_" + year_tag + "_corr").Data());
  tgae_notmerged_uncorr = (TGraphAsymmErrors*) f->Get(("NotMerged_" + year_tag + "_uncorr").Data());
  f->Close();
}

TopTagScaleFactor::EMergeCategory TopTagScaleFactor::identifyMergeCategory_AK8(std::vector<GenTop> & gentops, const TopJet & taggedjet){
  if(gentops.size() == 0){
    throw std::domain_error("The provided scale factors are not supposed to be applied on MC not containing top quarks");
  }
  EMergeCategory result = EMergeCategory::isNotMerged;
  for(auto gentop : gentops){
    Int_t n_matched = 0;
    if(deltaR(gentop.get_b(), taggedjet) < 0.8) n_matched++;
    if(deltaR(gentop.get_q1(), taggedjet) < 0.8) n_matched++;
    if(deltaR(gentop.get_q2(), taggedjet) < 0.8) n_matched++;
    if(n_matched == 3){
      result = EMergeCategory::isFullyMerged;
      break;
    }
    if(n_matched == 2) result = EMergeCategory::isSemiMerged;
  }
  return result;
}

void TopTagScaleFactor::getSF(double jet_pt, EMergeCategory category){
  if(category == EMergeCategory::isFullyMerged){
    UInt_t bin = 0;
    Double_t x;
    Double_t y;
    tgae_fullymerged_tot->GetPoint(bin, x, y);
    const Double_t min_jet_pt = x - tgae_fullymerged_tot->GetErrorXlow(bin);
    if(jet_pt < min_jet_pt) std::cerr << "No scale factor for such low jet pT available. Will set scale factor to 1 with zero uncertainty." << std::endl;
    while(!(jet_pt >= x - tgae_fullymerged_tot->GetErrorXlow(bin) && jet_pt < x + tgae_fullymerged_tot->GetErrorXhigh(bin))){
      ++bin;
      tgae_fullymerged_tot->GetPoint(bin, x, y);
      if(bin + 1 >= (UInt_t) tgae_fullymerged_tot->GetN()) break;
    }
    weight_toptagsf *= y;
    weight_toptagsf_corr_up *= (y + tgae_fullymerged_corr->GetErrorYhigh(bin));
    weight_toptagsf_corr_down *= (y - tgae_fullymerged_corr->GetErrorYlow(bin));
    weight_toptagsf_uncorr_up *= (y + tgae_fullymerged_uncorr->GetErrorYhigh(bin));
    weight_toptagsf_uncorr_down *= (y - tgae_fullymerged_uncorr->GetErrorYlow(bin));
  }
  else if(category == EMergeCategory::isSemiMerged){
    UInt_t bin = 0;
    Double_t x;
    Double_t y;
    tgae_semimerged_tot->GetPoint(bin, x, y);
    const Double_t min_jet_pt = x - tgae_semimerged_tot->GetErrorXlow(bin);
    if(jet_pt < min_jet_pt) std::cerr << "No scale factor for such low jet pT available. Will set scale factor to 1 with zero uncertainty." << std::endl;
    while(!(jet_pt >= x - tgae_semimerged_tot->GetErrorXlow(bin) && jet_pt < x + tgae_semimerged_tot->GetErrorXhigh(bin))){
      ++bin;
      tgae_semimerged_tot->GetPoint(bin, x, y);
      if(bin + 1 >= (UInt_t) tgae_semimerged_tot->GetN()) break;
    }
    weight_toptagsf *= y;
    weight_toptagsf_corr_up *= (y + tgae_semimerged_corr->GetErrorYhigh(bin));
    weight_toptagsf_corr_down *= (y - tgae_semimerged_corr->GetErrorYlow(bin));
    weight_toptagsf_uncorr_up *= (y + tgae_semimerged_uncorr->GetErrorYhigh(bin));
    weight_toptagsf_uncorr_down *= (y - tgae_semimerged_uncorr->GetErrorYlow(bin));
  }
  else if(category == EMergeCategory::isNotMerged){
    UInt_t bin = 0;
    Double_t x;
    Double_t y;
    tgae_notmerged_tot->GetPoint(bin, x, y);
    const Double_t min_jet_pt = x - tgae_notmerged_tot->GetErrorXlow(bin);
    if(jet_pt < min_jet_pt) std::cerr << "No scale factor for such low jet pT available. Will set scale factor to 1 with zero uncertainty." << std::endl;
    while(!(jet_pt >= x - tgae_notmerged_tot->GetErrorXlow(bin) && jet_pt < x + tgae_notmerged_tot->GetErrorXhigh(bin))){
      ++bin;
      tgae_notmerged_tot->GetPoint(bin, x, y);
      if(bin + 1 >= (UInt_t) tgae_notmerged_tot->GetN()) break;
    }
    weight_toptagsf *= y;
    weight_toptagsf_corr_up *= (y + tgae_notmerged_corr->GetErrorYhigh(bin));
    weight_toptagsf_corr_down *= (y - tgae_notmerged_corr->GetErrorYlow(bin));
    weight_toptagsf_uncorr_up *= (y + tgae_notmerged_uncorr->GetErrorYhigh(bin));
    weight_toptagsf_uncorr_down *= (y - tgae_notmerged_uncorr->GetErrorYlow(bin));
  }
  else throw runtime_error("TopTagScaleFactor: no valid category");
}

bool TopTagScaleFactor::process(Event &event){
  weight_toptagsf = 1.;
  weight_toptagsf_corr_up = 1.;
  weight_toptagsf_corr_down = 1.;
  weight_toptagsf_uncorr_up = 1.;
  weight_toptagsf_uncorr_down = 1.;

  if(event.isRealData || event.get(h_gentops).size() == 0){
    event.set(h_toptagsf, 1.);
    event.set(h_toptagsf_corr_up, 1.);
    event.set(h_toptagsf_corr_down, 1.);
    event.set(h_toptagsf_uncorr_up, 1.);
    event.set(h_toptagsf_uncorr_down, 1.);
    return false;
  }

  vector<GenTop> gentops = event.get(h_gentops);
  vector<TopJet> taggedjets = event.get(h_toptaggedjets);
  for(const auto & taggedjet : taggedjets){
    EMergeCategory category = identifyMergeCategory_AK8(gentops, taggedjet);
    getSF(taggedjet.pt(), category);
  }
  event.weight *= weight_toptagsf;
  event.set(h_toptagsf, weight_toptagsf);
  event.set(h_toptagsf_corr_up, weight_toptagsf_corr_up);
  event.set(h_toptagsf_corr_down, weight_toptagsf_corr_down);
  event.set(h_toptagsf_uncorr_up, weight_toptagsf_uncorr_up);
  event.set(h_toptagsf_uncorr_down, weight_toptagsf_uncorr_down);
  return true;
}
