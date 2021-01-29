#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>
#include "UHH2/common/include/PrintingModules.h"

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
#include "UHH2/common/include/LuminosityHists.h"
#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/TopPtReweight.h>
#include <UHH2/common/include/CommonModules.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <UHH2/HOTVR/include/HadronicTop.h>
#include <UHH2/HOTVR/include/HOTVRScaleFactor.h>
#include <UHH2/HOTVR/include/HOTVRIds.h>

using namespace std;
using namespace uhh2;

/*
██████  ███████ ███████ ██ ███    ██ ██ ████████ ██  ██████  ███    ██
██   ██ ██      ██      ██ ████   ██ ██    ██    ██ ██    ██ ████   ██
██   ██ █████   █████   ██ ██ ██  ██ ██    ██    ██ ██    ██ ██ ██  ██
██   ██ ██      ██      ██ ██  ██ ██ ██    ██    ██ ██    ██ ██  ██ ██
██████  ███████ ██      ██ ██   ████ ██    ██    ██  ██████  ██   ████
*/

class ZprimeAnalysisModule : public ModuleBASE {

public:
  explicit ZprimeAnalysisModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

protected:

  bool debug;
  
  // Scale Factors -- Systematics
  unique_ptr<MCMuonScaleFactor> MuonID_module, MuonTrigger_module;
  unique_ptr<MCElecScaleFactor> EleID_module, EleTrigger_module;

  // AnalysisModules
  unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, BTagWeight_module, TopPtReweight_module, MCScale_module;

  // Taggers
  //unique_ptr<AK8PuppiTopTagger> TopTaggerPuppi;
  unique_ptr<HOTVRTopTagger> TopTaggerHOTVR;
  unique_ptr<AnalysisModule> hadronic_top;
  unique_ptr<AnalysisModule> sf_toptag;

  // Mass reconstruction
  unique_ptr<ZprimeCandidateBuilder> CandidateBuilder;

  // Chi2 discriminator
  unique_ptr<ZprimeChi2Discriminator> Chi2DiscriminatorZprime;
  unique_ptr<ZprimeCorrectMatchDiscriminator> CorrectMatchDiscriminatorZprime;

  // Selections
  unique_ptr<Selection> MuonVeto_selection, EleVeto_selection, NMuon1_LowPt_selection, NMuon1_HighPt_selection, NEle1_LowPt_selection, NEle1_HighPt_selection;
  unique_ptr<Selection> Trigger_mu_A_selection, Trigger_mu_B_selection, Trigger_mu_C_selection, Trigger_mu_D_selection;
  unique_ptr<Selection> Trigger_ele_A_selection, Trigger_ele_B_selection, Trigger_ph_A_selection;
  unique_ptr<Selection> TwoDCut_selection, Jet1_selection, Jet2_selection, Met_selection, Chi2_selection, TTbarMatchable_selection, Chi2CandidateMatched_selection, ZprimeTopTag_selection, BlindData_selection;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<Selection> sel_1btag, sel_2btag;
  std::unique_ptr<Selection> TopJetBtagSubjet_selection;
  std::unique_ptr<Selection> HEM_selection;

  // NN variables handles
  unique_ptr<Variables_NN> Variables_module;

  //Handles
  Event::Handle<bool> h_is_zprime_reconstructed_chi2, h_is_zprime_reconstructed_correctmatch;
  Event::Handle<float> h_chi2;   Event::Handle<float> h_weight;
  Event::Handle<float> h_MET;   Event::Handle<int> h_NPV;
  Event::Handle<float> h_lep1_pt; Event::Handle<float> h_lep1_eta; 
  Event::Handle<float> h_ak4jet1_pt; Event::Handle<float> h_ak4jet1_eta; 
  Event::Handle<float> h_ak8jet1_pt; Event::Handle<float> h_ak8jet1_eta; 
  Event::Handle<float> h_Mttbar; 

  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;


  // Lumi hists
  std::unique_ptr<Hists> lumihists_Weights_Init, lumihists_Weights_PU, lumihists_Weights_Lumi, lumihists_Weights_TopPt, lumihists_Weights_MCScale, lumihists_Muon1_LowPt, lumihists_Muon1_HighPt, lumihists_Ele1_LowPt, lumihists_Ele1_HighPt, lumihists_TriggerMuon, lumihists_TriggerEle, lumihists_TwoDCut_Muon, lumihists_TwoDCut_Ele, lumihists_Jet1, lumihists_Jet2, lumihists_MET, lumihists_HTlep, lumihists_Chi2;



  // Configuration
  bool isMC, ispuppi, islooserselection;
  string Sys_MuonID, Sys_MuonTrigger, Sys_PU, Sys_btag, Sys_EleID, Sys_EleTrigger;
  TString sample;
  int runnr_oldtriggers = 299368;

  bool is2016v2, is2016v3, is2017v2, is2018;
  bool isMuon, isElectron;
  bool isPhoton;
};

void ZprimeAnalysisModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    string mytag = tag + "_Skimming";
    mytag = tag+"_General";
    book_HFolder(mytag, new ZprimeSemiLeptonicHists(ctx,mytag));
  }
}

void ZprimeAnalysisModule::fill_histograms(uhh2::Event& event, string tag){
  string mytag = tag + "_Skimming";
  mytag = tag+"_General";
  HFolder(mytag)->fill(event);
}

/*
█  ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████
█ ██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█ ██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████
█ ██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█  ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

ZprimeAnalysisModule::ZprimeAnalysisModule(uhh2::Context& ctx){
  //  debug = true;
  debug = false;
  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }
  // Configuration
  isMC = (ctx.get("dataset_type") == "MC");
  ispuppi = (ctx.get("is_puppi") == "true");
  TString mode = "chs";
  if(ispuppi) mode = "puppi";
  string tmp = ctx.get("dataset_version");
  sample = tmp;
  is2016v2 = (ctx.get("dataset_version").find("2016v2") != std::string::npos);
  is2016v3 = (ctx.get("dataset_version").find("2016v3") != std::string::npos);
  is2017v2 = (ctx.get("dataset_version").find("2017v2") != std::string::npos);
  is2018 = (ctx.get("dataset_version").find("2018") != std::string::npos);

  isPhoton = (ctx.get("dataset_version").find("SinglePhoton") != std::string::npos);

  // Important selection values
  islooserselection = (ctx.get("is_looser_selection") == "true");
  double jet1_pt(50.);
  double jet2_pt(30.);
  double chi2_max(30.);
  double mtt_blind(3000.);
  string trigger_mu_A,trigger_mu_B,trigger_mu_C,trigger_mu_D;
  string trigger_ele_A,trigger_ele_B;
  string trigger_ph_A;
  double MET_cut, HT_lep_cut;
  isMuon = false; isElectron = false;
  if(ctx.get("channel") == "muon") isMuon = true;
  if(ctx.get("channel") == "electron") isElectron = true;

  if(isMuon){//semileptonic muon channel
    if(is2017v2)
     trigger_mu_A = "HLT_IsoMu24_v*";
    else
     trigger_mu_A = "HLT_IsoMu27_v*";
    trigger_mu_B = "HLT_IsoTkMu24_v*";
    trigger_mu_C = "HLT_Mu50_v*";
    trigger_mu_D = "HLT_TkMu50_v*";

    MET_cut = 50;
    HT_lep_cut = 0;
  }
  if(isElectron){//semileptonic electron channel
    if(is2016v2 || is2016v3)
     trigger_ele_A = "HLT_Ele27_WPTight_Gsf_v*";
    if(is2017v2)
     trigger_ele_A = "HLT_Ele35_WPTight_Gsf_v*";
    if(is2018)
     trigger_ele_A = "HLT_Ele32_WPTight_Gsf_v*";
    trigger_ele_B = "HLT_Ele115_CaloIdVT_GsfTrkIdT_v*"; 
    if(is2016v2 || is2016v3)
     trigger_ph_A = "HLT_Photon175_v*";
    else 
     trigger_ph_A = "HLT_Photon200_v*";
    MET_cut = 50;
    HT_lep_cut = 0;
  }

 
  double TwoD_dr = 0.4, TwoD_ptrel = 25.;
  if(islooserselection){
    jet1_pt = 100.;
    TwoD_dr = 0.2;
    TwoD_ptrel = 10.;
  }


  double electron_pt_low(35.);
  double muon_pt_low(30.);
  double electron_pt_high(120.);
  double muon_pt_high(55.);

  const MuonId muonID_low(PtEtaCut(muon_pt_low, 2.4));
  const ElectronId electronID_low(PtEtaSCCut(electron_pt_low, 2.5));
  const MuonId muonID_high(PtEtaCut(muon_pt_high, 2.4));
  const ElectronId electronID_high(PtEtaSCCut(electron_pt_high, 2.5));
  const TopJetId toptagID = AndId<TopJet>(HOTVRTopTag(0.8, 140.0, 220.0, 50.0), Tau32Groomed(0.56));

  Sys_MuonID = ctx.get("Sys_MuonID");
  Sys_MuonTrigger = ctx.get("Sys_MuonTrigger");
  Sys_EleID = ctx.get("Sys_EleID");
  Sys_EleTrigger = ctx.get("Sys_EleTrigger");
  Sys_PU = ctx.get("Sys_PU");
  Sys_btag = ctx.get("Sys_BTagSF");

  BTag::algo btag_algo = BTag::DEEPJET;
  BTag::wp btag_wp_tight = BTag::WP_TIGHT;
  JetId id_btag = BTag(btag_algo, btag_wp_tight);

  double a_toppt = 0.0615; // par a TopPt Reweighting
  double b_toppt = -0.0005; // par b TopPt Reweighting 

  // Modules
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  //BTagWeight_module.reset(new MCBTagDiscriminantReweighting(ctx, btag_algo, "jets", Sys_btag));
  //TopPtReweight_module.reset(new TopPtReweight(ctx, a_toppt, b_toppt,"","weight_ttbar",true));
  MCScale_module.reset(new MCScaleVariation(ctx));
  hadronic_top.reset(new HadronicTop(ctx));
  sf_toptag.reset(new HOTVRScaleFactor(ctx, toptagID, ctx.get("Sys_TopTag", "nominal"), "HadronicTop", "TopTagSF", "HOTVRTopTagSFs")); 

/*  if((is2016v3 || is2016v2) && isMuon){
    MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root", "MC_NUM_TightID_DEN_genTracks_PAR_pt_eta", 0., "MuonID", true, Sys_MuonID));
    MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu50_OR_IsoTkMu50_PtEtaBins", 0.5, "MuonTrigger", true, Sys_MuonTrigger));
  }
  if(is2017v2 && isMuon){
    MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_16/src/UHH2/common/data/2017/MuonID_94X_RunBCDEF_SF_ID.root", "NUM_HighPtID_DEN_genTracks_pair_newTuneP_probe_pt_abseta", 0., "HighPtID", true, Sys_MuonID));
    MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_16/src/UHH2/common/data/2017/MuonTrigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "Mu50_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger", true, Sys_MuonTrigger));
  }
  if(is2018 && isMuon){
    MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_16/src/UHH2/common/data/2018/Muon_ID_SF_RunABCD.root", "NUM_HighPtID_DEN_TrackerMuons_pair_newTuneP_probe_pt_abseta", 0., "HighPtID", true, Sys_MuonID));
    MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_16/src/UHH2/common/data/2018/Muon_Trigger_Eff_SF_AfterMuonHLTUpdate.root", "Mu50_OR_OldMu100_OR_TkMu100_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger", true, Sys_MuonTrigger));
//    EleID_module.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_16/src/UHH2/common/data/2018/2018_ElectronTight.root", 0., "TightID", Sys_EleID));
//    EleTrigger_module.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_16/src/UHH2/common/data/2018/SF_2018.root", 0.5, "Trigger", Sys_EleTrigger));
  }*/

  // Selection modules
  MuonVeto_selection.reset(new NMuonSelection(0, 0)); 
  EleVeto_selection.reset(new NElectronSelection(0, 0));
  NMuon1_LowPt_selection.reset(new NMuonSelection(1, 1, muonID_low));
  NMuon1_HighPt_selection.reset(new NMuonSelection(1, 1, muonID_high));
  NEle1_LowPt_selection.reset(new NElectronSelection(1, 1, electronID_low));
  NEle1_HighPt_selection.reset(new NElectronSelection(1, 1, electronID_high));

  Trigger_mu_A_selection.reset(new TriggerSelection(trigger_mu_A));
  Trigger_mu_B_selection.reset(new TriggerSelection(trigger_mu_B));
  Trigger_mu_C_selection.reset(new TriggerSelection(trigger_mu_C));
  Trigger_mu_D_selection.reset(new TriggerSelection(trigger_mu_D));

  Trigger_ele_A_selection.reset(new TriggerSelection(trigger_ele_A));
  Trigger_ele_B_selection.reset(new TriggerSelection(trigger_ele_B));
  Trigger_ph_A_selection.reset(new TriggerSelection(trigger_ph_A));


  TwoDCut_selection.reset(new TwoDCut(TwoD_dr, TwoD_ptrel));
  Jet1_selection.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  Jet2_selection.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  met_sel.reset(new METCut  (MET_cut   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep_cut, uhh2::infinity));

  Chi2_selection.reset(new Chi2Cut(ctx, 0., chi2_max));
  TTbarMatchable_selection.reset(new TTbarSemiLepMatchableSelection());
  Chi2CandidateMatched_selection.reset(new Chi2CandidateMatchedSelection(ctx));
  ZprimeTopTag_selection.reset(new ZprimeTopTagSelection(ctx));
  BlindData_selection.reset(new BlindDataSelection(ctx, mtt_blind));

  HEM_selection.reset(new HEMSelection(ctx)); // HEM issue in 2018, veto on leptons and jets

  Variables_module.reset(new Variables_NN(ctx)); // variables for NN

  // Taggers
  //TopTaggerPuppi.reset(new AK8PuppiTopTagger(ctx));
  TopTaggerHOTVR.reset(new HOTVRTopTagger(ctx));

  // Zprime candidate builder
  CandidateBuilder.reset(new ZprimeCandidateBuilder(ctx, mode));

  // Zprime discriminators
  Chi2DiscriminatorZprime.reset(new ZprimeChi2Discriminator(ctx));
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  CorrectMatchDiscriminatorZprime.reset(new ZprimeCorrectMatchDiscriminator(ctx));
  h_is_zprime_reconstructed_correctmatch = ctx.get_handle<bool>("is_zprime_reconstructed_correctmatch");
  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_chi2 = ctx.declare_event_output<float> ("rec_chi2");
  h_MET = ctx.declare_event_output<float> ("met_pt");
  h_Mttbar = ctx.declare_event_output<float> ("Mttbar");
  h_lep1_pt = ctx.declare_event_output<float> ("lep1_pt");
  h_lep1_eta = ctx.declare_event_output<float> ("lep1_eta");
  h_ak4jet1_pt = ctx.declare_event_output<float> ("ak4jet1_pt");
  h_ak4jet1_eta = ctx.declare_event_output<float> ("ak4jet1_eta");
  h_ak8jet1_pt = ctx.declare_event_output<float> ("ak8jet1_pt");
  h_ak8jet1_eta = ctx.declare_event_output<float> ("ak8jet1_eta");

  h_NPV = ctx.declare_event_output<int> ("NPV");
  h_weight = ctx.declare_event_output<float> ("weight");

  sel_1btag.reset(new NJetSelection(1, 1, id_btag));
  sel_2btag.reset(new NJetSelection(2,-1, id_btag));


  TopJetBtagSubjet_selection.reset(new ZprimeBTagFatSubJetSelection(ctx));

  // Book histograms
  vector<string> histogram_tags = {"Weights_Init", "Weights_PU", "Weights_Lumi", "Weights_TopPt", "Weights_MCScale", "Weights_HOTVR_SF", "Muon1_LowPt", "Muon1_HighPt", "Ele1_LowPt", "Ele1_HighPt", "TriggerMuon", "TriggerEle", "TwoDCut_Muon", "TwoDCut_Ele", "Jet1", "Jet2", "MET", "HTlep", "NNInputsBeforeReweight", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction", "Btags2", "Btags1","TopJetBtagSubjet"};
  book_histograms(ctx, histogram_tags);

  lumihists_Weights_Init.reset(new LuminosityHists(ctx, "Lumi_Weights_Init"));
  lumihists_Weights_PU.reset(new LuminosityHists(ctx, "Lumi_Weights_PU"));
  lumihists_Weights_Lumi.reset(new LuminosityHists(ctx, "Lumi_Weights_Lumi"));
  lumihists_Weights_TopPt.reset(new LuminosityHists(ctx, "Lumi_Weights_TopPt"));
  lumihists_Weights_MCScale.reset(new LuminosityHists(ctx, "Lumi_Weights_MCScale"));
  lumihists_Muon1_LowPt.reset(new LuminosityHists(ctx, "Lumi_Muon1_LowPt"));
  lumihists_Muon1_HighPt.reset(new LuminosityHists(ctx, "Lumi_Muon1_HighPt"));
  lumihists_Ele1_LowPt.reset(new LuminosityHists(ctx, "Lumi_Ele1_LowPt"));
  lumihists_Ele1_HighPt.reset(new LuminosityHists(ctx, "Lumi_Ele1_HighPt"));
  lumihists_TriggerMuon.reset(new LuminosityHists(ctx, "Lumi_TriggerMuon"));
  lumihists_TriggerEle.reset(new LuminosityHists(ctx, "Lumi_TriggerEle"));
  lumihists_TwoDCut_Muon.reset(new LuminosityHists(ctx, "Lumi_TwoDCut_Muon"));
  lumihists_TwoDCut_Ele.reset(new LuminosityHists(ctx, "Lumi_TwoDCut_Ele"));
  lumihists_Jet1.reset(new LuminosityHists(ctx, "Lumi_Jet1"));
  lumihists_Jet2.reset(new LuminosityHists(ctx, "Lumi_Jet2"));
  lumihists_MET.reset(new LuminosityHists(ctx, "Lumi_MET"));
  lumihists_HTlep.reset(new LuminosityHists(ctx, "Lumi_HTlep"));
  lumihists_Chi2.reset(new LuminosityHists(ctx, "Lumi_Chi2"));

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeAnalysisModule::process(uhh2::Event& event){


  if(debug)   cout << "++++++++++++ NEW EVENT ++++++++++++++" << endl;
  if(debug)   cout<<" run.event: "<<event.run<<". "<<event.event<<endl;
  //cout << "++++++++++++ NEW EVENT ++++++++++++++" << endl;
  //cout<<" run.event: "<<event.run<<". "<<event.event<<endl;
  //if(event.event != 500000) return false;
  // Initialize reco flags with false
  event.set(h_is_zprime_reconstructed_chi2, false);
  event.set(h_is_zprime_reconstructed_correctmatch, false);
  event.set(h_chi2,-100);
  event.set(h_MET,-100);
  event.set(h_Mttbar,-100);
  event.set(h_lep1_pt,-100);
  event.set(h_lep1_eta,-100);
  event.set(h_ak4jet1_pt,-100);
  event.set(h_ak4jet1_eta,-100);
  event.set(h_ak8jet1_pt,-100);
  event.set(h_ak8jet1_eta,-100);
  event.set(h_NPV,-100);
  event.set(h_weight,-100);


  if(!HEM_selection->passes(event)){
    if(!isMC) return false;
    else event.weight = event.weight*(1-0.64774715284); // calculated following instructions ar https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2018Analysis
  }

  // Run top-tagging
  //TopTaggerPuppi->process(event);
  TopTaggerHOTVR->process(event);
  if(debug) cout<<"Top Tagger ok"<<endl;
 
  // HOTVR TopTag SFs
  hadronic_top->process(event);
  sf_toptag->process(event);
  fill_histograms(event, "Weights_HOTVR_SF");
  
  fill_histograms(event, "Weights_Init");
  lumihists_Weights_Init->fill(event);

  // Lepton ID SF
  //if(isMuon){
  //  MuonID_module->process(event);
  //  if(debug)  cout<<"MuonID ok"<<endl;
  //}
  //if(isElectron){
  //  EleID_module->process(event);
  //  if(debug)  cout<<"EleID ok"<<endl;
  //}

  // Weight modules
  PUWeight_module->process(event);
  if(debug)  cout<<"PUWeight ok"<<endl;
  fill_histograms(event, "Weights_PU");
  lumihists_Weights_PU->fill(event);

  LumiWeight_module->process(event);
  if(debug)  cout<<"LumiWeight ok"<<endl;
  fill_histograms(event, "Weights_Lumi");
  lumihists_Weights_Lumi->fill(event);

//  TopPtReweight_module->process(event);
//  fill_histograms(event, "Weights_TopPt");
//  lumihists_Weights_TopPt->fill(event);

  MCScale_module->process(event);
  fill_histograms(event, "Weights_MCScale");
  lumihists_Weights_MCScale->fill(event);


  // Select exactly 1 muon or 1 electron
  bool muon_is_low = false;
  bool muon_is_high = false;
  bool ele_is_low = false;
  bool ele_is_high = false;

  if(isMuon){
     if(!EleVeto_selection->passes(event)) return false;
     if(!NMuon1_HighPt_selection->passes(event)){
       if(NMuon1_LowPt_selection->passes(event)){
         muon_is_low = true;
         fill_histograms(event, "Muon1_LowPt");
         lumihists_Muon1_LowPt->fill(event);
       }
     }
     else{
       muon_is_high = true;
       fill_histograms(event, "Muon1_HighPt");
         lumihists_Muon1_HighPt->fill(event);
     }
     if( !(muon_is_high || muon_is_low) ) return false;
  }
  if(isElectron){
     if(!MuonVeto_selection->passes(event)) return false;
     if(!NEle1_HighPt_selection->passes(event)){
       if(NEle1_LowPt_selection->passes(event)){
         ele_is_low = true;
         fill_histograms(event, "Ele1_LowPt");
         lumihists_Ele1_LowPt->fill(event);
       }
     }
     else{
       ele_is_high = true;
       fill_histograms(event, "Ele1_HighPt");
         lumihists_Ele1_HighPt->fill(event);
     }
     if( !(ele_is_high || ele_is_low) ) return false;
  }


  // Trigger MUON channel
  if(isMuon){
     // low pt
     if(muon_is_low){
        if(is2016v2 || is2016v3){
         if(!(Trigger_mu_A_selection->passes(event) || Trigger_mu_B_selection->passes(event))) return false;
        }
        else{
         if(!Trigger_mu_A_selection->passes(event)) return false;
        }
     }  
     // high pt
     if(muon_is_high){
        if(is2016v2 || is2016v3){ // 2016
           // DATA below runnumb
           if(!isMC && event.run < 274954){
            if(!Trigger_mu_C_selection->passes(event)) return false;
           }
           // DATA above runnumb & MC
           else{
            if(!(Trigger_mu_C_selection->passes(event) || Trigger_mu_D_selection->passes(event))) return false;
           }
        } // 2017 & 2018
        else{
         if(!Trigger_mu_C_selection->passes(event)) return false;
        }

     }
  fill_histograms(event, "TriggerMuon");
  lumihists_TriggerMuon->fill(event);
  }

  // Trigger ELECTRON channel
  if(isElectron){
     // low pt
     if(ele_is_low){
         if(!Trigger_ele_A_selection->passes(event)) return false;
     }
     // high pt
     if(ele_is_high){
        // MC
        if(isMC){
          if(!(Trigger_ele_B_selection->passes(event) || Trigger_ph_A_selection->passes(event))) return false;
        }else{
        //DATA 
            // 2016
            if(is2016v2 || is2016v3){
                if(isPhoton){ // photon stream
                    if(Trigger_ele_B_selection->passes(event) && !Trigger_ph_A_selection->passes(event)) return false;
                }else{ // electron stream
                   if(!Trigger_ele_B_selection->passes(event)) return false; 
                }
            }
            // 2017
            if(is2017v2){
              // below runnumb trigger Ele115 does not exist
              if(event.run < 299329){
                if(isPhoton){ // photon stream
                    if(Trigger_ele_A_selection->passes(event) && !Trigger_ph_A_selection->passes(event)) return false;
                }else{ // electron stream
                   if(!Trigger_ele_A_selection->passes(event)) return false; 
                }
              }else{ // above runnumb with Ele115
                if(isPhoton){ // photon stream
                    if(Trigger_ele_B_selection->passes(event) && !Trigger_ph_A_selection->passes(event)) return false;
                }else{ // electron stream
                   if(!Trigger_ele_B_selection->passes(event)) return false; 
                }
              }
            }
            // 2018 photon & electron together: EGamma DATA
            if(is2018){
               if(!(Trigger_ele_B_selection->passes(event)|| Trigger_ph_A_selection->passes(event))) return false;
            }

        }
     }
  fill_histograms(event, "TriggerEle");
  lumihists_TriggerEle->fill(event);
  } 


  // Lepton Trigger SF
  //if(isMuon){
  //  MuonTrigger_module->process_onemuon(event, 0);
  //  fill_histograms(event, "TriggerMuon");
  //}
  //if(isElectron){
  //  EleTrigger_module->process(event);
  //  fill_histograms(event, "TriggerEle");
  //} 



  if((event.muons->size()+event.electrons->size()) != 1) return false; //veto events without leptons or with too many 
  if(debug) cout<<"N leptons ok: Nelectrons="<<event.electrons->size()<<" Nmuons="<<event.muons->size()<<endl;

  if(isMuon && muon_is_high){
    if(!TwoDCut_selection->passes(event)) return false;
  }
  fill_histograms(event, "TwoDCut_Muon");
  lumihists_TwoDCut_Muon->fill(event);
  if(isElectron && ele_is_high){
    if(!TwoDCut_selection->passes(event)) return false;
  }
  fill_histograms(event, "TwoDCut_Ele");
  lumihists_TwoDCut_Ele->fill(event);

  CandidateBuilder->process(event);
  if(debug) cout<<"CandidateBuilder is ok"<<endl;
  Chi2DiscriminatorZprime->process(event);
  if(debug)  cout<<"Chi2DiscriminatorZprime is ok"<<endl;
  CorrectMatchDiscriminatorZprime->process(event);
  if(debug) cout<<"CorrectMatchDiscriminatorZprime is ok"<<endl;
  if(sample.Contains("_blinded")){
    if(!BlindData_selection->passes(event)) return false;
  }
  if(!Jet1_selection->passes(event)) return false;
  if(debug) cout<<"Jet1_selection is ok"<<endl;
  fill_histograms(event, "Jet1");
  lumihists_Jet1->fill(event);

  if(!Jet2_selection->passes(event)) return false;
  if(debug) cout<<"Jet2_selection is ok"<<endl;
  fill_histograms(event, "Jet2");
  lumihists_Jet2->fill(event);

  // MET selection
  if(!met_sel->passes(event)) return false;
  if(debug) cout<<"MET is ok"<<endl;
  fill_histograms(event, "MET");
  lumihists_MET->fill(event);
  if(isMuon){
    if(!htlep_sel->passes(event)) return false;
    fill_histograms(event, "HTlep");
    lumihists_HTlep->fill(event);
    if(debug) cout<<"HTlep is ok"<<endl;
  }

  // Variables for NN 
  Variables_module->process(event);
  fill_histograms(event, "NNInputsBeforeReweight");

//  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "MatchableBeforeChi2Cut");
//  else fill_histograms(event, "NotMatchableBeforeChi2Cut");
//  if(debug) cout<<"TTbarMatchable_selection is ok"<<endl;
//
//  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatchBeforeChi2Cut");
//  else fill_histograms(event, "NotCorrectMatchBeforeChi2Cut");
//  if(debug) cout<<"Chi2CandidateMatched_selection is ok"<<endl;
//
//  if(!Chi2_selection->passes(event)) return false;
//  fill_histograms(event, "Chi2");
//  lumihists_Chi2->fill(event);
//
//  if(debug) cout<<"Chi2_selection is ok"<<endl;
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////// Extra checks
//
//
//  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "Matchable");
//  else fill_histograms(event, "NotMatchable");
//  if(debug) cout<<"TTbarMatchable_selection is ok"<<endl;
//
//  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatch");
//  else fill_histograms(event, "NotCorrectMatch");
//  if(debug) cout<<"Chi2CandidateMatched_selection is ok"<<endl;
//
//  if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "TopTagReconstruction");
//  else fill_histograms(event, "NotTopTagReconstruction");
//  if(debug) cout<<"ZprimeTopTag_selection is ok"<<endl;
//
//  //Test with b-tagging
//  if(sel_2btag->passes(event)) fill_histograms(event, "Btags2");
//  if(sel_1btag->passes(event)) fill_histograms(event, "Btags1");
//  if(debug) cout<<"Btags1 is ok"<<endl;
//  if(TopJetBtagSubjet_selection->passes(event)) fill_histograms(event, "TopJetBtagSubjet");
//  if(debug) cout<<"TopJetBtagSubjet_selection is ok"<<endl;
//
//  //Fill some vars for monitoring and comparison
//  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2); 
//  if(is_zprime_reconstructed_chi2){
//    ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);
//    event.set(h_chi2,BestZprimeCandidate->discriminator("chi2_total"));
//    event.set(h_Mttbar,BestZprimeCandidate->Zprime_v4().M());
//  }
//  if(debug) cout<<"Set ttbar reconstruction vars for monitoring"<<endl;
//
//  event.set(h_weight,event.weight);
//  event.set(h_MET,event.met->pt());
//  if(isMuon){
//    event.set(h_lep1_pt,event.muons->at(0).pt());
//    event.set(h_lep1_eta,event.muons->at(0).eta());
//  }
//  if(isElectron){
//    event.set(h_lep1_pt,event.electrons->at(0).pt());
//    event.set(h_lep1_eta,event.electrons->at(0).eta());
//  }
//  if(event.jets->size()>0){
//    event.set(h_ak4jet1_pt,event.jets->at(0).pt());
//    event.set(h_ak4jet1_eta,event.jets->at(0).eta());
//  }
//  if(event.topjets->size()>0){
//    event.set(h_ak8jet1_pt,event.topjets->at(0).pt());
//    event.set(h_ak8jet1_eta,event.topjets->at(0).eta());
//  }
//  event.set(h_NPV,event.pvs->size());
//  if(debug) cout<<"Set some vars for monitoring"<<endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeAnalysisModule)
