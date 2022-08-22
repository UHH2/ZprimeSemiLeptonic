#include <UHH2/ZprimeSemiLeptonic/include/ElecTriggerSF.h>

uhh2::ElecTriggerSF::ElecTriggerSF(uhh2::Context & ctx, std::string var_, TString pe, TString year): var(var_) {

  is_Muon = ctx.get("channel") == "muon";

  h_ele_weight      = ctx.declare_event_output<float>("weight_sfelec_trigger");
  h_ele_weight_up   = ctx.declare_event_output<float>("weight_sfelec_trigger_up");
  h_ele_weight_down = ctx.declare_event_output<float>("weight_sfelec_trigger_down");

  pteta = pe;
  if(pteta != "pt" && pteta != "eta" && pteta != "eta_ptbins"){
    cout << "Warning: You should select 'pt', 'eta' or 'eta_ptbins' for ElecTriggerSF class" << endl;
    return;
  }

  auto dataset_type = ctx.get("dataset_type");
  isMC = dataset_type == "MC";
  if (!isMC) {
    cout << "Warning: MCElecScaleFactor will not have an effect on "
    <<" this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
    return;
  }

  TString dir = "/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/files_EleTrigger/";
  TString filename = dir + "ElecTriggerSF"+year+".root";
  TFile *file = new TFile(filename);

  TString histname = "Central";
  TString histUp = "Up";
  TString histDown = "Down";
  if(var == "up")        histname = "Up";
  else if(var == "down") histname = "Down";

  // for the options pt and eta the low and high histograms are exactly the same
  // its just to make it easier to code
  if(pteta == "pt"){
    cout << "ElecTriggerSF: You selected the pt dependent SF: " << histname << endl;
    h_sf_lo = (TH1F*)file->Get(histname+"_pt");
    h_sf_me = (TH1F*)file->Get(histname+"_pt");
    h_sf_hi = (TH1F*)file->Get(histname+"_pt");

    h_sf_lo_up = (TH1F*)file->Get(histUp+"_pt");
    h_sf_me_up = (TH1F*)file->Get(histUp+"_pt");
    h_sf_hi_up = (TH1F*)file->Get(histUp+"_pt");

    h_sf_lo_down = (TH1F*)file->Get(histDown+"_pt");
    h_sf_me_down = (TH1F*)file->Get(histDown+"_pt");
    h_sf_hi_down = (TH1F*)file->Get(histDown+"_pt");
  }
  else if(pteta == "eta"){
    cout << "ElecTriggerSF: You selected the eta dependent SF: " << histname << endl;
    h_sf_lo = (TH1F*)file->Get(histname+"_eta");
    h_sf_me = (TH1F*)file->Get(histname+"_eta");
    h_sf_hi = (TH1F*)file->Get(histname+"_eta");

    h_sf_lo_up = (TH1F*)file->Get(histUp+"_eta");
    h_sf_me_up = (TH1F*)file->Get(histUp+"_eta");
    h_sf_hi_up = (TH1F*)file->Get(histUp+"_eta");

    h_sf_lo_down = (TH1F*)file->Get(histDown+"_eta");
    h_sf_me_down = (TH1F*)file->Get(histDown+"_eta");
    h_sf_hi_down = (TH1F*)file->Get(histDown+"_eta");
  }
  else{
    cout << "ElecTriggerSF: You selected the eta (pt bins) dependent SF: " << histname << endl;
    h_sf_lo = (TH1F*)file->Get(histname+"_eta_lowpt");
    h_sf_me = (TH1F*)file->Get(histname+"_eta_midpt");
    h_sf_hi = (TH1F*)file->Get(histname+"_eta_highpt");

    h_sf_lo_up = (TH1F*)file->Get(histUp+"_eta_lowpt");
    h_sf_me_up = (TH1F*)file->Get(histUp+"_eta_midpt");
    h_sf_hi_up = (TH1F*)file->Get(histUp+"_eta_highpt");

    h_sf_lo_down = (TH1F*)file->Get(histDown+"_eta_lowpt");
    h_sf_me_down = (TH1F*)file->Get(histDown+"_eta_midpt");
    h_sf_hi_down = (TH1F*)file->Get(histDown+"_eta_highpt");
  }
}

bool uhh2::ElecTriggerSF::process(uhh2::Event & event){

  if(is_Muon || event.isRealData || event.electrons->size() < 1){
    event.set(h_ele_weight, 1.);
    event.set(h_ele_weight_up, 1.);
    event.set(h_ele_weight_down, 1.);
    return true;
  }

  if(!isMC) return true;
  if(pteta != "pt" && pteta != "eta" && pteta != "eta_ptbins") return false;

  if(event.electrons->size() < 1) return false;
  double pt = event.electrons->at(0).pt();
  double eta = event.electrons->at(0).eta();
  double UsedVariable;
  if(pteta == "pt") UsedVariable = pt;
  else              UsedVariable = eta;

  // do not set SF if electron out of range
  // this can happen if recsel is not passed
  /**
  if(fabs(eta) > 2.4 || pt < 55){
    event.set(h_ele_weight, 1.);
    event.set(h_ele_weight_up, 1.);
    event.set(h_ele_weight_down, 1.);
    return true;
  }
  **/

  int bin = 0;
  double sf = 1.0; double sf_up = 0.0; double sf_down = 0.0;
  if(pt < 120){
    bin = h_sf_lo->GetXaxis()->FindBin(UsedVariable);
    sf = h_sf_lo->GetBinContent(bin);
    sf_up = h_sf_lo_up->GetBinContent(bin);
    sf_down = h_sf_lo_down->GetBinContent(bin);
  }
  else if(pt > 120 && pt < 200){
    bin = h_sf_me->GetXaxis()->FindBin(UsedVariable);
    sf = h_sf_me->GetBinContent(bin);
    sf_up = h_sf_me_up->GetBinContent(bin);
    sf_down = h_sf_me_down->GetBinContent(bin);
  }
  else if(pt > 200){
    bin = h_sf_hi->GetXaxis()->FindBin(UsedVariable);
    sf = h_sf_hi->GetBinContent(bin);
    sf_up = h_sf_hi_up->GetBinContent(bin);
    sf_down = h_sf_hi_down->GetBinContent(bin);
  }

  event.set(h_ele_weight, sf);
  event.set(h_ele_weight_up, sf_up);
  event.set(h_ele_weight_down, sf_down);

  if (var == "up") {
    event.weight *= sf_up;
  } else if (var == "down") {
    event.weight *= sf_down;
  } else {
    event.weight *= sf;
  }

  return true;
}
