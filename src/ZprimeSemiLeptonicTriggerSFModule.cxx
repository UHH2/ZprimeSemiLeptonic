#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>
#include <UHH2/common/include/PrintingModules.h>

#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>
#include <UHH2/common/include/LuminosityHists.h>
#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/TopPtReweight.h>
#include <UHH2/common/include/CommonModules.h>
#include <UHH2/common/include/LeptonScaleFactors.h>
#include <UHH2/common/include/PSWeights.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicEleHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicCHSMatchHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

using namespace std;
using namespace uhh2;

class ZprimeSemiLeptonicTriggerSFModule : public AnalysisModule {

public:
  explicit ZprimeSemiLeptonicTriggerSFModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

protected:

  Event::Handle<double>h_pt;
  Event::Handle<double>h_eta;
  Event::Handle<double>h_weight;
  Event::Handle<bool>h_passed;
  Event::Handle<int>h_run;
  Event::Handle<int>h_lumi;
  Event::Handle<int>h_eventnr;

  // Configuration
  bool debug = false;
  bool isMC, ishotvr, isdeepAK8;
  bool isUL16preVFP, isUL16postVFP, isUL17, isUL18;
  string Sys_PU, Prefiring_direction; // Sys_TopPt_a, Sys_TopPt_b;
  TString year;
  TString sample;

  TH2F *ratio_hist_muon;

  std::unique_ptr<Hists> h_pass, h_all;
  std::unique_ptr<Hists> h_EleHists_pass, h_EleHists_all;

  // scale factors
  std::unique_ptr<AnalysisModule> sf_muon_iso_low, sf_muon_id_low, sf_muon_id_high, sf_muon_trigger_low, sf_muon_trigger_high;
  std::unique_ptr<AnalysisModule> sf_muon_iso_low_dummy, sf_muon_id_dummy, sf_muon_trigger_dummy;
  std::unique_ptr<AnalysisModule> sf_ele_id_low, sf_ele_id_high, sf_ele_reco;
  std::unique_ptr<AnalysisModule> sf_ele_id_dummy, sf_ele_reco_dummy;
  std::unique_ptr<MuonRecoSF> sf_muon_reco;
  std::unique_ptr<AnalysisModule> sf_btagging;

  // AnalysisModules
  std::unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, TopPtReweight_module, MCScale_module;
  std::unique_ptr<AnalysisModule> NLOCorrections_module;

  // Selections
  std::unique_ptr<Selection> Trigger_ele_A_selection, Trigger_ele_B_selection, Trigger_ph_A_selection;
  std::unique_ptr<Selection> HEM_selection;

};

ZprimeSemiLeptonicTriggerSFModule::ZprimeSemiLeptonicTriggerSFModule(uhh2::Context& ctx){

  if(debug) cout << "Get Year ... " << endl;
  isUL16preVFP  = (ctx.get("dataset_version").find("UL16preVFP")  != std::string::npos);
  isUL16postVFP = (ctx.get("dataset_version").find("UL16postVFP") != std::string::npos);
  isUL17        = (ctx.get("dataset_version").find("UL17")        != std::string::npos);
  isUL18        = (ctx.get("dataset_version").find("UL18")        != std::string::npos);
  if(isUL16preVFP) year = "UL16preVFP";
  if(isUL16postVFP) year = "UL16postVFP";
  if(isUL17) year = "UL17";
  if(isUL18) year = "UL18";

  isMC = (ctx.get("dataset_type") == "MC");
  ishotvr = (ctx.get("is_hotvr") == "true");
  isdeepAK8 = (ctx.get("is_deepAK8") == "true");
  TString mode = "hotvr";
  if(isdeepAK8) mode = "deepAK8";
  string tmp = ctx.get("dataset_version");
  sample = tmp;

  if(debug) cout << "Declare Output ... " << endl;
  ctx.undeclare_all_event_output();
  h_eta = ctx.declare_event_output<double>("eta");
  h_pt = ctx.declare_event_output<double>("pt");
  h_weight = ctx.declare_event_output<double>("weight");
  h_passed = ctx.declare_event_output<bool>("passed");
  h_run = ctx.declare_event_output<int>("run");
  h_lumi = ctx.declare_event_output<int>("lumi");
  h_eventnr = ctx.declare_event_output<int>("eventnr");

  if(debug) cout << "Define Trigger ... " << endl;

  string trigger_ele_A, trigger_ele_B;
  string trigger_ph_A;

  trigger_ele_B = "HLT_Ele115_CaloIdVT_GsfTrkIdT_v*";
  if(isUL16preVFP || isUL16postVFP){
    trigger_ele_A = "HLT_Ele27_WPTight_Gsf_v*";
  }
  if(isUL17){
    trigger_ele_A = "HLT_Ele35_WPTight_Gsf_v*";
  }
  if(isUL18){
    trigger_ele_A = "HLT_Ele32_WPTight_Gsf_v*";
  }
  if(isUL16preVFP || isUL16postVFP){
    trigger_ph_A = "HLT_Photon175_v*";
  }
  else{
    trigger_ph_A = "HLT_Photon200_v*";
  }

  Trigger_ele_A_selection.reset(new TriggerSelection(trigger_ele_A));
  Trigger_ele_B_selection.reset(new TriggerSelection(trigger_ele_B));
  Trigger_ph_A_selection.reset(new TriggerSelection(trigger_ph_A));

  h_pass.reset(new ElectronHists(ctx, "pass_Elec"));
  h_all.reset(new ElectronHists(ctx, "all_Elec"));
  h_EleHists_pass.reset(new ZprimeSemiLeptonicEleHists(ctx, "pass_EleHists"));
  h_EleHists_all.reset(new ZprimeSemiLeptonicEleHists(ctx, "all_EleHists"));

  Sys_PU = ctx.get("Sys_PU");
  Prefiring_direction = ctx.get("Sys_prefiring");
  // Sys_TopPt_a = ctx.get("Systematic_TopPt_a");
  // Sys_TopPt_b = ctx.get("Systematic_TopPt_b");

  // double a_toppt = 0.0615; // par a TopPt Reweighting
  // double b_toppt = -0.0005; // par b TopPt Reweighting

  // Modules
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  //TopPtReweight_module.reset(new TopPtReweighting(ctx, a_toppt, b_toppt, Sys_TopPt_a, Sys_TopPt_b, ""));
  MCScale_module.reset(new MCScaleVariation(ctx));
  NLOCorrections_module.reset(new NLOCorrections(ctx));

  // b-tagging SFs
  sf_btagging.reset(new MCBTagDiscriminantReweighting(ctx, BTag::algo::DEEPJET, "CHS_matched"));

  // set lepton scale factors: see UHH2/common/include/LeptonScaleFactors.h
  sf_muon_iso_low.reset(new uhh2::MuonIsoScaleFactors(ctx, Muon::Selector::PFIsoTight, Muon::Selector::CutBasedIdTight, true));
  sf_muon_id_low.reset(new uhh2::MuonIdScaleFactors(ctx, Muon::Selector::CutBasedIdTight, true));
  sf_muon_id_high.reset(new uhh2::MuonIdScaleFactors(ctx, Muon::Selector::CutBasedIdGlobalHighPt, true));
  sf_muon_trigger_low.reset(new uhh2::MuonTriggerScaleFactors(ctx, false, true));
  sf_muon_trigger_high.reset(new uhh2::MuonTriggerScaleFactors(ctx, true, false));
  sf_muon_reco.reset(new MuonRecoSF(ctx));
  sf_ele_id_low.reset(new uhh2::ElectronIdScaleFactors(ctx, Electron::tag::mvaEleID_Fall17_iso_V2_wp80, true));
  sf_ele_id_high.reset(new uhh2::ElectronIdScaleFactors(ctx, Electron::tag::mvaEleID_Fall17_noIso_V2_wp80, true));
  sf_ele_reco.reset(new uhh2::ElectronRecoScaleFactors(ctx, false, true));

  // dummies (needed to aviod set value errors)
  sf_muon_iso_low_dummy.reset(new uhh2::MuonIsoScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, boost::none, true));
  sf_muon_id_dummy.reset(new uhh2::MuonIdScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, true));
  sf_muon_trigger_dummy.reset(new uhh2::MuonTriggerScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, boost::none, true));
  sf_ele_id_dummy.reset(new uhh2::ElectronIdScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, true));
  sf_ele_reco_dummy.reset(new uhh2::ElectronRecoScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, true));

  HEM_selection.reset(new HEMSelection(ctx));

  if(isMC){
    TString sample_name = "";
    vector<string> names  = {"ST", "WJets", "DY", "QCD","ALP_ttbar_signal", "ALP_ttbar_interference", "HscalarToTTTo1L1Nu2J_m365_w36p5_res", "HscalarToTTTo1L1Nu2J_m400_w40p0_res", "HscalarToTTTo1L1Nu2J_m500_w50p0_res", "HscalarToTTTo1L1Nu2J_m600_w60p0_res", "HscalarToTTTo1L1Nu2J_m800_w80p0_res", "HscalarToTTTo1L1Nu2J_m1000_w100p0_res", "HscalarToTTTo1L1Nu2J_m365_w36p5_int", "HscalarToTTTo1L1Nu2J_m400_w40p0_int", "HscalarToTTTo1L1Nu2J_m500_w50p0_int", "HscalarToTTTo1L1Nu2J_m600_w60p0_int", "HscalarToTTTo1L1Nu2J_m800_w80p0_int", "HscalarToTTTo1L1Nu2J_m1000_w100p0_int", "HpseudoToTTTo1L1Nu2J_m365_w36p5_res", "HpseudoToTTTo1L1Nu2J_m400_w40p0_res", "HpseudoToTTTo1L1Nu2J_m500_w50p0_res", "HpseudoToTTTo1L1Nu2J_m600_w60p0_res", "HpseudoToTTTo1L1Nu2J_m800_w80p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res", "HpseudoToTTTo1L1Nu2J_m365_w36p5_int", "HpseudoToTTTo1L1Nu2J_m400_w40p0_int", "HpseudoToTTTo1L1Nu2J_m500_w50p0_int", "HpseudoToTTTo1L1Nu2J_m600_w60p0_int", "HpseudoToTTTo1L1Nu2J_m800_w80p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int", "HscalarToTTTo1L1Nu2J_m365_w91p25_res", "HscalarToTTTo1L1Nu2J_m400_w100p0_res", "HscalarToTTTo1L1Nu2J_m500_w125p0_res", "HscalarToTTTo1L1Nu2J_m600_w150p0_res", "HscalarToTTTo1L1Nu2J_m800_w200p0_res", "HscalarToTTTo1L1Nu2J_m1000_w250p0_res", "HscalarToTTTo1L1Nu2J_m365_w91p25_int", "HscalarToTTTo1L1Nu2J_m400_w100p0_int", "HscalarToTTTo1L1Nu2J_m500_w125p0_int", "HscalarToTTTo1L1Nu2J_m600_w150p0_int", "HscalarToTTTo1L1Nu2J_m800_w200p0_int", "HscalarToTTTo1L1Nu2J_m1000_w250p0_int", "HpseudoToTTTo1L1Nu2J_m365_w91p25_res", "HpseudoToTTTo1L1Nu2J_m400_w100p0_res", "HpseudoToTTTo1L1Nu2J_m500_w125p0_res", "HpseudoToTTTo1L1Nu2J_m600_w150p0_res", "HpseudoToTTTo1L1Nu2J_m800_w200p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res", "HpseudoToTTTo1L1Nu2J_m365_w91p25_int", "HpseudoToTTTo1L1Nu2J_m400_w100p0_int", "HpseudoToTTTo1L1Nu2J_m500_w125p0_int", "HpseudoToTTTo1L1Nu2J_m600_w150p0_int", "HpseudoToTTTo1L1Nu2J_m800_w200p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int", "HscalarToTTTo1L1Nu2J_m365_w9p125_res", "HscalarToTTTo1L1Nu2J_m400_w10p0_res", "HscalarToTTTo1L1Nu2J_m500_w12p5_res", "HscalarToTTTo1L1Nu2J_m600_w15p0_res", "HscalarToTTTo1L1Nu2J_m800_w20p0_res", "HscalarToTTTo1L1Nu2J_m1000_w25p0_res", "HscalarToTTTo1L1Nu2J_m365_w9p125_int", "HscalarToTTTo1L1Nu2J_m400_w10p0_int", "HscalarToTTTo1L1Nu2J_m500_w12p5_int", "HscalarToTTTo1L1Nu2J_m600_w15p0_int", "HscalarToTTTo1L1Nu2J_m800_w20p0_int", "HscalarToTTTo1L1Nu2J_m1000_w25p0_int", "HpseudoToTTTo1L1Nu2J_m365_w9p125_res", "HpseudoToTTTo1L1Nu2J_m400_w10p0_res", "HpseudoToTTTo1L1Nu2J_m500_w12p5_res", "HpseudoToTTTo1L1Nu2J_m600_w15p0_res", "HpseudoToTTTo1L1Nu2J_m800_w20p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res", "HpseudoToTTTo1L1Nu2J_m365_w9p125_int", "HpseudoToTTTo1L1Nu2J_m400_w10p0_int", "HpseudoToTTTo1L1Nu2J_m500_w12p5_int", "HpseudoToTTTo1L1Nu2J_m600_w15p0_int", "HpseudoToTTTo1L1Nu2J_m800_w20p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int", "RSGluonToTT_M-500", "RSGluonToTT_M-1000", "RSGluonToTT_M-1500", "RSGluonToTT_M-2000", "RSGluonToTT_M-2500", "RSGluonToTT_M-3000", "RSGluonToTT_M-3500", "RSGluonToTT_M-4000", "RSGluonToTT_M-4500", "RSGluonToTT_M-5000", "RSGluonToTT_M-5500", "RSGluonToTT_M-6000", "ZPrimeToTT_M400_W40", "ZPrimeToTT_M500_W50", "ZPrimeToTT_M600_W60", "ZPrimeToTT_M700_W70", "ZPrimeToTT_M800_W80", "ZPrimeToTT_M900_W90", "ZPrimeToTT_M1000_W100", "ZPrimeToTT_M1200_W120", "ZPrimeToTT_M1400_W140", "ZPrimeToTT_M1600_W160", "ZPrimeToTT_M1800_W180", "ZPrimeToTT_M2000_W200", "ZPrimeToTT_M2500_W250", "ZPrimeToTT_M3000_W300", "ZPrimeToTT_M3500_W350", "ZPrimeToTT_M4000_W400", "ZPrimeToTT_M4500_W450", "ZPrimeToTT_M5000_W500", "ZPrimeToTT_M6000_W600", "ZPrimeToTT_M7000_W700", "ZPrimeToTT_M8000_W800", "ZPrimeToTT_M9000_W900", "ZPrimeToTT_M400_W120", "ZPrimeToTT_M500_W150", "ZPrimeToTT_M600_W180", "ZPrimeToTT_M700_W210", "ZPrimeToTT_M800_W240", "ZPrimeToTT_M900_W270", "ZPrimeToTT_M1000_W300", "ZPrimeToTT_M1200_W360", "ZPrimeToTT_M1400_W420", "ZPrimeToTT_M1600_W480", "ZPrimeToTT_M1800_W540", "ZPrimeToTT_M2000_W600", "ZPrimeToTT_M2500_W750", "ZPrimeToTT_M3000_W900", "ZPrimeToTT_M3500_W1050", "ZPrimeToTT_M4000_W1200", "ZPrimeToTT_M4500_W1350", "ZPrimeToTT_M5000_W1500", "ZPrimeToTT_M6000_W1800", "ZPrimeToTT_M7000_W2100", "ZPrimeToTT_M8000_W2400", "ZPrimeToTT_M9000_W2700", "ZPrimeToTT_M400_W4", "ZPrimeToTT_M500_W5", "ZPrimeToTT_M600_W6", "ZPrimeToTT_M700_W7", "ZPrimeToTT_M800_W8", "ZPrimeToTT_M900_W9", "ZPrimeToTT_M1000_W10", "ZPrimeToTT_M1200_W12", "ZPrimeToTT_M1400_W14", "ZPrimeToTT_M1600_W16", "ZPrimeToTT_M1800_W18", "ZPrimeToTT_M2000_W20", "ZPrimeToTT_M2500_W25", "ZPrimeToTT_M3000_W30", "ZPrimeToTT_M3500_W35", "ZPrimeToTT_M4000_W40", "ZPrimeToTT_M4500_W45", "ZPrimeToTT_M5000_W50", "ZPrimeToTT_M6000_W60", "ZPrimeToTT_M7000_W70", "ZPrimeToTT_M8000_W80", "ZPrimeToTT_M9000_W90"};

    for(unsigned int i=0; i<names.size(); i++){
      if( ctx.get("dataset_version").find(names.at(i)) != std::string::npos ) sample_name = names.at(i);
    }
    if( (ctx.get("dataset_version").find("TTToHadronic") != std::string::npos) || (ctx.get("dataset_version").find("TTToSemiLeptonic") != std::string::npos) || (ctx.get("dataset_version").find("TTTo2L2Nu") != std::string::npos) ) sample_name = "TTbar";
    if( (ctx.get("dataset_version").find("WW") != std::string::npos) || (ctx.get("dataset_version").find("ZZ") != std::string::npos) || (ctx.get("dataset_version").find("WZ") != std::string::npos) ) sample_name = "Diboson";

    TFile* f_btag2Dsf_muon = new TFile("/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/files_BTagSF/customBtagSF_muon_"+year+".root");
    ratio_hist_muon = (TH2F*)f_btag2Dsf_muon->Get("N_Jets_vs_HT_" + sample_name);
    ratio_hist_muon->SetDirectory(0);
  }
}


bool ZprimeSemiLeptonicTriggerSFModule::process(uhh2::Event& event){
  if(debug) cout << " ------------------------------------------- " << endl;
  if(debug) cout << " ----------------- NewEvent ---------------- " << endl;
  if(debug) cout << " ------------------------------------------- " << endl;
  if(debug) cout << event.event << endl;

  if(!HEM_selection->passes(event)){
    if(!isMC) return false;
    else event.weight = event.weight*(1-0.64774715284); // calculated following instructions ar https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2018Analysis
  }
  PUWeight_module->process(event);
  LumiWeight_module->process(event);
  //TopPtReweight_module->process(event);
  MCScale_module->process(event);
  if (isMC) {
    if (Prefiring_direction == "nominal") event.weight *= event.prefiringWeight;
    else if (Prefiring_direction == "up") event.weight *= event.prefiringWeightUp;
    else if (Prefiring_direction == "down") event.weight *= event.prefiringWeightDown;
  }

  double muon_pt_high(55.);
  bool muon_is_low = false;
  bool muon_is_high = false;

  vector<Muon>* muons = event.muons;
  for(unsigned int i=0; i<muons->size(); i++){
    if(event.muons->at(i).pt()<=muon_pt_high){
      muon_is_low = true;
    }else{
      muon_is_high = true;
    }
  }
  sort_by_pt<Muon>(*event.muons);

  double electron_pt_high(120.);
  bool ele_is_low = false;
  bool ele_is_high = false;

  vector<Electron>* electrons = event.electrons;
  for(unsigned int i=0; i<electrons->size(); i++){
    if(event.electrons->at(i).pt()<=electron_pt_high){
      ele_is_low = true;
    }else{
      ele_is_high = true;
    }
  }
  sort_by_pt<Electron>(*event.electrons);

  if(muon_is_low){
    sf_muon_iso_low->process(event);
    sf_muon_id_low->process(event);
  }else{
    sf_muon_iso_low_dummy->process(event);
  }

  if(muon_is_high){
    sf_muon_id_high->process(event);
  }

  if(ele_is_low){
    sf_ele_id_low->process(event);
  }
  else if(ele_is_high){
    sf_ele_id_high->process(event);
  }

  sf_muon_reco->process(event);
  sf_ele_reco->process(event);

  if(muon_is_low){
    sf_muon_trigger_low->process(event);
  }
  if(muon_is_high){
    sf_muon_trigger_high->process(event);
  }

  sf_btagging->process(event);

  // apply custom SF to correct for BTag SF shape effects on NJets/HT
  if(isMC){
    float custom_sf;

    vector<Jet>* jets = event.jets;
    int Njets = jets->size();
    double st_jets = 0.;
    for(const auto & jet : *jets) st_jets += jet.pt();
    custom_sf = ratio_hist_muon->GetBinContent( ratio_hist_muon->GetXaxis()->FindBin(Njets), ratio_hist_muon->GetYaxis()->FindBin(st_jets) );

    event.weight *= custom_sf;
  }
  NLOCorrections_module->process(event);

  // fill hists with all events
  h_all->fill(event);
  h_EleHists_all->fill(event);

  // HERE FILL PT AND ETA HISTS FOR PASSING AND NOT PASSING ELEC TRIGGER
  if(debug) cout << "Start Fill ... " << endl;
  bool passed_elec_trigger = false;

  if(ele_is_low){
    passed_elec_trigger = Trigger_ele_A_selection->passes(event);
  }
  if(ele_is_high){
    if(isMC && (isUL16preVFP || isUL16postVFP || isUL18) ){
      passed_elec_trigger = (Trigger_ele_A_selection->passes(event) || Trigger_ele_B_selection->passes(event) || Trigger_ph_A_selection->passes(event));
    }
    if(isMC && isUL17){
      float runB_ele = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      if(runB_ele <= 0.1158){ // in RunB (below runnumb 299329) Ele115 does not exist, use Ele35 instead. To apply randomly in MC if random numb < RunB percetage (11.58%, calculated by Christopher Matthies)
        passed_elec_trigger = (Trigger_ele_A_selection->passes(event) || Trigger_ph_A_selection->passes(event));
      }else{
        passed_elec_trigger = (Trigger_ele_A_selection->passes(event) || Trigger_ele_B_selection->passes(event) || Trigger_ph_A_selection->passes(event));
      }
    }
    if(!isMC && (isUL16preVFP || isUL16postVFP || isUL18) ){
      passed_elec_trigger = (Trigger_ele_A_selection->passes(event) || Trigger_ele_B_selection->passes(event)|| Trigger_ph_A_selection->passes(event));
    }else if(!isMC && isUL17){
      if(event.run <= 299329){
        passed_elec_trigger = (Trigger_ele_A_selection->passes(event) || Trigger_ph_A_selection->passes(event));
      }else{
        passed_elec_trigger = (Trigger_ele_A_selection->passes(event) || Trigger_ele_B_selection->passes(event)|| Trigger_ph_A_selection->passes(event));
      }
    }

  }

  if(debug) cout << "Set after Trigger pass... " << endl;
  event.set(h_pt, event.electrons->at(0).pt());
  event.set(h_eta, event.electrons->at(0).eta());
  event.set(h_weight, event.weight);
  event.set(h_passed, passed_elec_trigger);

  int run = 0;
  int lumi = 0;
  int eventnr = 0;

  if(!isMC){
    run = event.run;
    lumi = event.luminosityBlock;
    eventnr = event.event;
  }

  if(debug) cout << "Set run info ... " << endl;
  event.set(h_run, run);
  event.set(h_lumi, lumi);
  event.set(h_eventnr, eventnr);

  if(passed_elec_trigger){
    // fill pass histograms
    h_pass->fill(event);
    h_EleHists_pass->fill(event);
  }

  if(debug) cout << "Event done ... " << endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeSemiLeptonicTriggerSFModule)
