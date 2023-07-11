#include "UHH2/ZprimeSemiLeptonic/include/TopMistagScaleFactor.h"

using namespace std;
using namespace uhh2;

TopMistagScaleFactor::TopMistagScaleFactor(Context & ctx){
  // to be applied on MC only
  is_mc = ctx.get("dataset_type") == "MC";
  ishotvr = (ctx.get("is_hotvr") == "true");
  isdeepAK8 = (ctx.get("is_deepAK8") == "true");

  // input handles
  if(isdeepAK8){
    h_AK8TopTags = ctx.get_handle<vector<TopJet>>("DeepAK8TopTags");
  }else if(ishotvr){
    h_AK8TopTags = ctx.get_handle<vector<TopJet>>("HOTVRTopTags");
  }

  // output handles
  h_topmistagsf = ctx.declare_event_output<float>("weight_topmistagsf");
  h_topmistagsf_up = ctx.declare_event_output<float>("weight_topmistagsf_up");
  h_topmistagsf_down = ctx.declare_event_output<float>("weight_topmistagsf_down");

  // year
  const Year & year = extract_year(ctx);
  TString year_tag;
  if(year == Year::isUL16preVFP) year_tag = "UL16preVFP";
  else if(year == Year::isUL16postVFP) year_tag = "UL16postVFP";
  else if(year == Year::isUL17) year_tag = "UL17";
  else if(year == Year::isUL18) year_tag = "UL18";
  else throw runtime_error("TopTagScaleFactor: no valid year selected");


  // extract values from root file
  const TString base_file_path = (TString) getenv("CMSSW_BASE") + "/src/UHH2/ZprimeSemiLeptonic/data/";
  TFile *f = TFile::Open(base_file_path + "top_mistag_scale_factors.root");
  hist = (TH1F*) f->Get((TString) year_tag);
  sf_value = hist->GetBinContent(1);
  sf_error = hist->GetBinError(1);
  f->Close();
}

bool TopMistagScaleFactor::process(Event & event){
  weight_topmistagsf = 1.;
  weight_topmistagsf_up = 1.;
  weight_topmistagsf_down = 1.;

  vector<GenParticle>* genparticles = event.genparticles;
  vector<TopJet> AK8PuppiTopTags = event.get(h_AK8TopTags);

  if(event.isRealData || genparticles->size() == 0){
    event.set(h_topmistagsf, 1.);
    event.set(h_topmistagsf_up, 1.);
    event.set(h_topmistagsf_down, 1.);
    return false;
  }

  for(unsigned int l=0; l<AK8PuppiTopTags.size(); l++){
    double deltaR_min_tagged = 99;
    for(unsigned int k=0; k<genparticles->size(); ++k){
      if(abs(genparticles->at(k).pdgId()) == 6){
        double deltaR_top_tagged = deltaR(AK8PuppiTopTags.at(l),genparticles->at(k));
        if(deltaR_top_tagged < deltaR_min_tagged) deltaR_min_tagged = deltaR_top_tagged;
      }
    }
    if(deltaR_min_tagged > 0.4){
      weight_topmistagsf = sf_value;
      weight_topmistagsf_up = sf_value + sf_error;
      weight_topmistagsf_down = sf_value - sf_error;
    }
  }
  event.weight *= weight_topmistagsf;
  event.set(h_topmistagsf, weight_topmistagsf);
  event.set(h_topmistagsf_up, weight_topmistagsf_up);
  event.set(h_topmistagsf_down, weight_topmistagsf_down);
  return true;
}
