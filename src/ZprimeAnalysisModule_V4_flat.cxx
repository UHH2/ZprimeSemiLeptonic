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

//#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

using namespace std;
using namespace uhh2;

/*
██████  ███████ ███████ ██ ███    ██ ██ ████████ ██  ██████  ███    ██
██   ██ ██      ██      ██ ████   ██ ██    ██    ██ ██    ██ ████   ██
██   ██ █████   █████   ██ ██ ██  ██ ██    ██    ██ ██    ██ ██ ██  ██
██   ██ ██      ██      ██ ██  ██ ██ ██    ██    ██ ██    ██ ██  ██ ██
██████  ███████ ██      ██ ██   ████ ██    ██    ██  ██████  ██   ████
*/

class ZprimeAnalysisModule_V4_flat : public ModuleBASE {

public:
  explicit ZprimeAnalysisModule_V4_flat(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

protected:

  bool debug;
  
  // Cleaners (to make sure the pre-selection did everything right)
  std::unique_ptr<MuonCleaner> muon_cleaner;
  std::unique_ptr<ElectronCleaner> electron_cleaner;

  // Scale Factors -- Systematics
  unique_ptr<MCMuonScaleFactor> MuonID_module, MuonTrigger_module;
  //unique_ptr<MCElecScaleFactor> EleID_module, EleTrigger_module;

  // AnalysisModules
  unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, printer_genparticles, BTagWeight_module, TopPtReweight_module, MCScale_module;

  // Taggers
  unique_ptr<AK8PuppiTopTagger> TopTaggerPuppi;

  // Mass reconstruction
  unique_ptr<ZprimeCandidateBuilder> CandidateBuilder;

  // Chi2 discriminator
  unique_ptr<ZprimeChi2Discriminator> Chi2DiscriminatorZprime;
  unique_ptr<ZprimeCorrectMatchDiscriminator> CorrectMatchDiscriminatorZprime;

  // Selections
  unique_ptr<Selection> Trigger1_selection, Trigger2_selection, NMuon1_selection, NMuon2_selection, NElectron_selection, TwoDCut_selection, Jet1_selection, Jet2_selection, Met_selection, Chi2_selection, TTbarMatchable_selection, Chi2CandidateMatched_selection, ZprimeTopTag_selection, BlindData_selection;
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

  // Configuration
  bool isMC, ispuppi, islooserselection;
  string Sys_MuonID, Sys_MuonTrigger, Sys_PU, Sys_btag; //Sys_EleID, Sys_EleTrigger
  TString sample;
  int runnr_oldtriggers = 299368;

  bool is2016v2, is2016v3, is2017v2, is2018;
  bool isMuon, isElectron;

  bool isTT, isST, isDiboson, isDY, isWJets, isZprime_M500_W50, isZprime_M750_W75, isZprime_M1000_W100, isZprime_M1500_W150, isZprime_M2000_W200, isZprime_M2500_W250, isZprime_M3000_W300, isZprime_M3500_W350, isZprime_M4000_W400, isZprime_M5000_W500, isZprime_M6000_W600, isZprime_M7000_W700, isZprime_M8000_W800, isZprime_M9000_W900;

  TH1F* h0_TT;
  TH1F* h0_ST;
  TH1F* h0_Diboson;
  TH1F* h0_DY;
  TH1F* h0_WJets;
  TH1F* h0_Zprime_M500_W50;
  TH1F* h0_Zprime_M750_W75;
  TH1F* h0_Zprime_M1000_W100;
  TH1F* h0_Zprime_M1500_W150;
  TH1F* h0_Zprime_M2000_W200;
  TH1F* h0_Zprime_M2500_W250;
  TH1F* h0_Zprime_M3000_W300;
  TH1F* h0_Zprime_M3500_W350;
  TH1F* h0_Zprime_M4000_W400;
  TH1F* h0_Zprime_M5000_W500;
  TH1F* h0_Zprime_M6000_W600;
  TH1F* h0_Zprime_M7000_W700;
  TH1F* h0_Zprime_M8000_W800;
  TH1F* h0_Zprime_M9000_W900;

};

void ZprimeAnalysisModule_V4_flat::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    string mytag = tag + "_Skimming";
    mytag = tag+"_General";
    book_HFolder(mytag, new ZprimeSemiLeptonicHists(ctx,mytag));
    mytag = tag+"_Muons";
    book_HFolder(mytag, new MuonHists(ctx,mytag));
    mytag = tag+"_Electrons";
    book_HFolder(mytag, new ElectronHists(ctx,mytag));
    mytag = tag+"_Jets";
    book_HFolder(mytag, new JetHists(ctx,mytag));
    mytag = tag+"_Event";
    book_HFolder(mytag, new EventHists(ctx,mytag));
    mytag = tag+"_Generator";
    book_HFolder(mytag, new ZprimeSemiLeptonicGeneratorHists(ctx,mytag));
  }
}

void ZprimeAnalysisModule_V4_flat::fill_histograms(uhh2::Event& event, string tag){
  string mytag = tag + "_Skimming";
  mytag = tag+"_General";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Muons";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Electrons";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Jets";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Event";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Generator";
  HFolder(mytag)->fill(event);
}

/*
█  ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████
█ ██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█ ██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████
█ ██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█  ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

ZprimeAnalysisModule_V4_flat::ZprimeAnalysisModule_V4_flat(uhh2::Context& ctx){
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

  isTT = (ctx.get("dataset_version").find("TTTo") != std::string::npos);
  isST = (ctx.get("dataset_version").find("ST") != std::string::npos);
  isDiboson = (ctx.get("dataset_version").find("Diboson") != std::string::npos);
  isDY = (ctx.get("dataset_version").find("DY") != std::string::npos);
  isWJets = (ctx.get("dataset_version").find("WJets") != std::string::npos);
  isZprime_M500_W50 = (ctx.get("dataset_version").find("M500_W50") != std::string::npos);
  isZprime_M750_W75 = (ctx.get("dataset_version").find("M750_W75") != std::string::npos);
  isZprime_M1000_W100 = (ctx.get("dataset_version").find("M1000_W100") != std::string::npos);
  isZprime_M1500_W150 = (ctx.get("dataset_version").find("M1500_W150") != std::string::npos);
  isZprime_M2000_W200 = (ctx.get("dataset_version").find("M2000_W200") != std::string::npos);
  isZprime_M2500_W250 = (ctx.get("dataset_version").find("M2500_W250") != std::string::npos);
  isZprime_M3000_W300 = (ctx.get("dataset_version").find("M3000_W300") != std::string::npos);
  isZprime_M3500_W350 = (ctx.get("dataset_version").find("M3500_W350") != std::string::npos);
  isZprime_M4000_W400 = (ctx.get("dataset_version").find("M4000_W400") != std::string::npos);
  isZprime_M5000_W500 = (ctx.get("dataset_version").find("M5000_W500") != std::string::npos);
  isZprime_M6000_W600 = (ctx.get("dataset_version").find("M6000_W600") != std::string::npos);
  isZprime_M7000_W700 = (ctx.get("dataset_version").find("M7000_W700") != std::string::npos);
  isZprime_M8000_W800 = (ctx.get("dataset_version").find("M8000_W800") != std::string::npos);
  isZprime_M9000_W900 = (ctx.get("dataset_version").find("M9000_W900") != std::string::npos);


  // Important selection values
  islooserselection = (ctx.get("is_looser_selection") == "true");
  double muon_pt(55.);
  double elec_pt(80.);
  double jet1_pt(150.);
  double jet2_pt(50.);
  double chi2_max(30.);
  double mtt_blind(3000.);
  int nmuon_min1, nmuon_max1;
  int nmuon_min2, nmuon_max2;
  int nele_min, nele_max;
  string trigger1,trigger2;
  double MET_cut, HT_lep_cut;
  isMuon = false; isElectron = false;
  if(ctx.get("channel") == "muon") isMuon = true;
  if(ctx.get("channel") == "electron") isElectron = true;

  if(isMuon){//semileptonic muon channel
    trigger1 = "HLT_Mu50_v*";
    if(is2016v2 || is2016v3)
      //trigger2 = "HLT_TkMu50_v*";
      trigger2 = "HLT_Mu50_v*"; //TkMu path does not exist in 2017/2018 and RunB 2016
    else
      trigger2 = "HLT_Mu50_v*"; //TkMu path does not exist in 2017/2018
    nmuon_min1 = 1, nmuon_max1 = -1;
    nmuon_min2 = 1, nmuon_max2 = 1;
    nele_min = 0; nele_max = 0;
    MET_cut = 50;
    jet1_pt = 150.;
    HT_lep_cut = 150;
  }
  if(isElectron){//semileptonic electron channel
    nmuon_min1 = 0; nmuon_max1 = 0;
    nmuon_min2 = 0; nmuon_max2 = 0;
    nele_min = 1; nele_max = 1;
    trigger1 = "HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v*";
    trigger2 = "HLT_Ele115_CaloIdVT_GsfTrkIdT_v*";
    MET_cut = 120;
    jet1_pt = 185.;
    HT_lep_cut = 0;
  }

 
  double TwoD_dr = 0.4, TwoD_ptrel = 25.;
  if(islooserselection){
    jet1_pt = 100.;
    TwoD_dr = 0.2;
    TwoD_ptrel = 10.;
  }
  const MuonId muonID(PtEtaCut(muon_pt, 2.4));
  const ElectronId electronID(PtEtaSCCut(elec_pt, 2.5));

  

  Sys_MuonID = ctx.get("Sys_MuonID");
  Sys_MuonTrigger = ctx.get("Sys_MuonTrigger");
//  Sys_EleID = ctx.get("Sys_EleID");
//  Sys_EleTrigger = ctx.get("Sys_EleTrigger");
  Sys_PU = ctx.get("Sys_PU");
  Sys_btag = ctx.get("Sys_BTagSF");

  BTag::algo btag_algo = BTag::DEEPJET;
  BTag::wp btag_wp_tight = BTag::WP_TIGHT;
  JetId id_btag = BTag(btag_algo, btag_wp_tight);

  double a_toppt = 0.0615; // par a TopPt Reweighting
  double b_toppt = -0.0005; // par b TopPt Reweighting 

  // Modules
  printer_genparticles.reset(new GenParticlesPrinter(ctx));
  muon_cleaner.reset(new MuonCleaner(muonID));
  electron_cleaner.reset(new ElectronCleaner(electronID));
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  //BTagWeight_module.reset(new MCBTagDiscriminantReweighting(ctx, btag_algo, "jets", Sys_btag));
  TopPtReweight_module.reset(new TopPtReweight(ctx, a_toppt, b_toppt));
  MCScale_module.reset(new MCScaleVariation(ctx));


  if((is2016v3 || is2016v2) && isMuon){
    MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_16/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root", "MC_NUM_TightID_DEN_genTracks_PAR_pt_eta", 0., "MuonID", true, Sys_MuonID));
    MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_16/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu50_OR_IsoTkMu50_PtEtaBins", 0.5, "MuonTrigger", true, Sys_MuonTrigger));
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
  }

  // Selection modules
  Trigger1_selection.reset(new TriggerSelection(trigger1));
  Trigger2_selection.reset(new TriggerSelection(trigger2));
  NMuon1_selection.reset(new NMuonSelection(nmuon_min1, nmuon_max1));
  NMuon2_selection.reset(new NMuonSelection(nmuon_min2, nmuon_max2));
  NElectron_selection.reset(new NElectronSelection(nele_min, nele_max));
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
  TopTaggerPuppi.reset(new AK8PuppiTopTagger(ctx));

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
  vector<string> histogram_tags = {"Weights", "Weights_MuonID", "Weights_PU", "Weights_Lumi", "Weights_TopPt", "Weights_MCScale", "Muon1", "TriggerMuon", "Muon2", "Electron1", "TriggerEle", "TwoDCut", "Jet1", "Jet2", "MET", "HTlep", "NNInputsBeforeReweight", "NNInputsAfterReweight", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction", "Btags2", "Btags1","TopJetBtagSubjet"};
  book_histograms(ctx, histogram_tags);

  // TTbar
  TFile *f_TT = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.TTbar.root");
  h0_TT   = (TH1F*) f_TT->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_TT->SetDirectory(0);

  // ST
  TFile *f_ST = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ST.root");
  h0_ST   = (TH1F*) f_ST->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_ST->SetDirectory(0);

  // ST
  TFile *f_Diboson = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.Diboson.root");
  h0_Diboson   = (TH1F*) f_Diboson->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Diboson->SetDirectory(0);

  // DY
  TFile *f_DY = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.DY.root");
  h0_DY   = (TH1F*) f_DY->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_DY->SetDirectory(0);

  // WJets
  TFile *f_WJets = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.WJets.root");
  h0_WJets   = (TH1F*) f_WJets->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_WJets->SetDirectory(0);

  // Zprime M500_W50
  TFile *f_Zprime_M500_W50 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M500_W50_2018.root");
  h0_Zprime_M500_W50   = (TH1F*) f_Zprime_M500_W50->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M500_W50->SetDirectory(0);

  // Zprime M750_W75
  TFile *f_Zprime_M750_W75 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M750_W75_2018.root");
  h0_Zprime_M750_W75   = (TH1F*) f_Zprime_M750_W75->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M750_W75->SetDirectory(0);

  // Zprime M1000_W100
  TFile *f_Zprime_M1000_W100 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M1000_W100_2018.root");
  h0_Zprime_M1000_W100   = (TH1F*) f_Zprime_M1000_W100->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M1000_W100->SetDirectory(0);

  // Zprime M1500_W150
  TFile *f_Zprime_M1500_W150 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M1500_W150_2018.root");
  h0_Zprime_M1500_W150   = (TH1F*) f_Zprime_M1500_W150->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M1500_W150->SetDirectory(0);

  // Zprime M2000_W200
  TFile *f_Zprime_M2000_W200 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M2000_W200_2018.root");
  h0_Zprime_M2000_W200   = (TH1F*) f_Zprime_M2000_W200->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M2000_W200->SetDirectory(0);
 
  // Zprime M2500_W250
  TFile *f_Zprime_M2500_W250 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M2500_W250_2018.root");
  h0_Zprime_M2500_W250   = (TH1F*) f_Zprime_M2500_W250->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M2500_W250->SetDirectory(0);
  
  // Zprime M3000_W300
  TFile *f_Zprime_M3000_W300 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M3000_W300_2018.root");
  h0_Zprime_M3000_W300   = (TH1F*) f_Zprime_M3000_W300->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M3000_W300->SetDirectory(0);
  
  // Zprime M3500_W350
  TFile *f_Zprime_M3500_W350 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M3500_W350_2018.root");
  h0_Zprime_M3500_W350   = (TH1F*) f_Zprime_M3500_W350->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M3500_W350->SetDirectory(0);
  
  // Zprime M4000_W400
  TFile *f_Zprime_M4000_W400 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M4000_W400_2018.root");
  h0_Zprime_M4000_W400   = (TH1F*) f_Zprime_M4000_W400->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M4000_W400->SetDirectory(0);
  
  // Zprime M5000_W500
  TFile *f_Zprime_M5000_W500 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M5000_W500_2018.root");
  h0_Zprime_M5000_W500   = (TH1F*) f_Zprime_M5000_W500->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M5000_W500->SetDirectory(0);
  
  // Zprime M6000_W600
  TFile *f_Zprime_M6000_W600 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M6000_W600_2018.root");
  h0_Zprime_M6000_W600   = (TH1F*) f_Zprime_M6000_W600->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M6000_W600->SetDirectory(0);
  
  // Zprime M7000_W700
  TFile *f_Zprime_M7000_W700 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M7000_W700_2018.root");
  h0_Zprime_M7000_W700   = (TH1F*) f_Zprime_M7000_W700->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M7000_W700->SetDirectory(0);
  
  // Zprime M8000_W800
  TFile *f_Zprime_M8000_W800 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M8000_W800_2018.root");
  h0_Zprime_M8000_W800   = (TH1F*) f_Zprime_M8000_W800->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M8000_W800->SetDirectory(0);
  
  // Zprime M9000_W900
  TFile *f_Zprime_M9000_W900 = new TFile("/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_2018/Analysis_2810_vars/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.ZprimeToTT_M9000_W900_2018.root");
  h0_Zprime_M9000_W900   = (TH1F*) f_Zprime_M9000_W900->Get("NNInputsBeforeReweight_General/NN_M_tt");
  h0_Zprime_M9000_W900->SetDirectory(0);

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeAnalysisModule_V4_flat::process(uhh2::Event& event){

  if(debug)   cout << "++++++++++++ NEW EVENT ++++++++++++++" << endl;
  if(debug)   cout<<" run.event: "<<event.run<<". "<<event.event<<endl;
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
  // Printing
  // if(!event.isRealData) printer_genparticles->process(event);

  // TODO Apply things that should've been done in the pre-selection already... Fix pre-selection and then remove these steps
  if(isMuon) muon_cleaner->process(event);
  if(isElectron) electron_cleaner->process(event);
  if(debug)  cout<<"Muon and Electron cleaner ok"<<endl;


  if(!HEM_selection->passes(event)){
    if(!isMC) return false;
    else event.weight = event.weight*(1-0.64774715284); // calculated following instructions ar https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2018Analysis
  }

  // Run top-tagging
  TopTaggerPuppi->process(event);
  if(debug) cout<<"Top Tagger ok"<<endl;
  
  fill_histograms(event, "Weights");

  // Weight modules
  if(isMuon){
    MuonID_module->process(event);
    if(debug)  cout<<"MuonID ok"<<endl;
  }
  fill_histograms(event, "Weights_MuonID");
 // if(isElectron){
 //   EleID_module->process(event);
 //   if(debug)  cout<<"EleID ok"<<endl;
 // }
  PUWeight_module->process(event);
  if(debug)  cout<<"PUWeight ok"<<endl;
  fill_histograms(event, "Weights_PU");

  LumiWeight_module->process(event);
  if(debug)  cout<<"LumiWeight ok"<<endl;
  fill_histograms(event, "Weights_Lumi");

  TopPtReweight_module->process(event);
  fill_histograms(event, "Weights_TopPt");

  MCScale_module->process(event);
  fill_histograms(event, "Weights_MCScale");
 
  //BTagWeight_module->process(event);
 
  if(!(Trigger1_selection->passes(event)|| Trigger2_selection->passes(event))) return false;
  if(isMuon){
    if(!NMuon1_selection->passes(event)) return false;
    fill_histograms(event, "Muon1");
    MuonTrigger_module->process_onemuon(event, 0);
    fill_histograms(event, "TriggerMuon");
    if(!NMuon2_selection->passes(event)) return false;
    fill_histograms(event, "Muon2");
  }
  if(isElectron){
    if(!NElectron_selection->passes(event)) return false;
    fill_histograms(event, "Electron1");
    //EleTrigger_module->process(event);
    //fill_histograms(event, "TriggerEle");
  }
  if((event.muons->size()+event.electrons->size()) != 1) return false; //veto events without leptons or with too many 
  if(debug) cout<<"N leptons ok: Nelectrons="<<event.electrons->size()<<" Nmuons="<<event.muons->size()<<endl;
  if(!TwoDCut_selection->passes(event)) return false;
  fill_histograms(event, "TwoDCut");

  // Here, the Zprime must be reconstructed (we ensured to have >= 2 AK4 jets, >= 1 muon)
  // Only consider well-separated AK4 jets
  // //FixME: 
  // for(const TopJet & chsjet : *event.topjets){
  //   int n_separatedjets = 0;
  //   for(unsigned int k = 0; k < event.jets->size(); k++){
  //     if(deltaR(event.jets->at(k), chsjet) > 1.2) n_separatedjets++;
  //   }
  //   //    cout<<"n_separatedjets = "<<n_separatedjets<<endl;
  //   if(n_separatedjets<1) return false;
  // }

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

  if(!Jet2_selection->passes(event)) return false;
  if(debug) cout<<"Jet2_selection is ok"<<endl;
  fill_histograms(event, "Jet2");

  // MET selection
  if(!met_sel->passes(event)) return false;
  if(debug) cout<<"MET is ok"<<endl;
  fill_histograms(event, "MET");
  if(isMuon){
    if(!htlep_sel->passes(event)) return false;
    fill_histograms(event, "HTlep");
    if(debug) cout<<"HTlep is ok"<<endl;
  }

  //  Variables for NN 
  //Variables_module->process(event);
  fill_histograms(event, "NNInputsBeforeReweight");

  // Reweight inputs for flattening
  double weight_flat=1.0;
  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
  if(is_zprime_reconstructed_chi2){
    ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);
    float Mtt = BestZprimeCandidate->Zprime_v4().M();

    if(isTT){
    weight_flat = 1.0/(h0_TT->GetBinContent(h0_TT->GetXaxis()->FindBin(Mtt)));
    }
    if(isST){
    weight_flat = 1.0/(h0_ST->GetBinContent(h0_ST->GetXaxis()->FindBin(Mtt)));
    }
    if(isDiboson){
    weight_flat = 1.0/(h0_Diboson->GetBinContent(h0_Diboson->GetXaxis()->FindBin(Mtt)));
    }
    if(isDY){
    weight_flat = 1.0/(h0_DY->GetBinContent(h0_DY->GetXaxis()->FindBin(Mtt)));
    }
    if(isWJets){
    weight_flat = 1.0/(h0_WJets->GetBinContent(h0_WJets->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M500_W50){
    weight_flat = 1.0/(h0_Zprime_M500_W50->GetBinContent(h0_Zprime_M500_W50->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M750_W75){
    weight_flat = 1.0/(h0_Zprime_M750_W75->GetBinContent(h0_Zprime_M750_W75->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M1000_W100){
    weight_flat = 1.0/(h0_Zprime_M1000_W100->GetBinContent(h0_Zprime_M1000_W100->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M1500_W150){
    weight_flat = 1.0/(h0_Zprime_M1500_W150->GetBinContent(h0_Zprime_M1500_W150->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M2000_W200){
    weight_flat = 1.0/(h0_Zprime_M2000_W200->GetBinContent(h0_Zprime_M2000_W200->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M2500_W250){
    weight_flat = 1.0/(h0_Zprime_M2500_W250->GetBinContent(h0_Zprime_M2500_W250->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M3000_W300){
    weight_flat = 1.0/(h0_Zprime_M3000_W300->GetBinContent(h0_Zprime_M3000_W300->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M3500_W350){
    weight_flat = 1.0/(h0_Zprime_M3500_W350->GetBinContent(h0_Zprime_M3500_W350->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M4000_W400){
    weight_flat = 1.0/(h0_Zprime_M4000_W400->GetBinContent(h0_Zprime_M4000_W400->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M5000_W500){
    weight_flat = 1.0/(h0_Zprime_M5000_W500->GetBinContent(h0_Zprime_M5000_W500->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M6000_W600){
    weight_flat = 1.0/(h0_Zprime_M6000_W600->GetBinContent(h0_Zprime_M6000_W600->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M7000_W700){
    weight_flat = 1.0/(h0_Zprime_M7000_W700->GetBinContent(h0_Zprime_M7000_W700->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M8000_W800){
    weight_flat = 1.0/(h0_Zprime_M8000_W800->GetBinContent(h0_Zprime_M8000_W800->GetXaxis()->FindBin(Mtt)));
    }
    if(isZprime_M9000_W900){
    weight_flat = 1.0/(h0_Zprime_M9000_W900->GetBinContent(h0_Zprime_M9000_W900->GetXaxis()->FindBin(Mtt)));
    }

  }
  event.weight = weight_flat;
   
  Variables_module->process(event);
  fill_histograms(event, "NNInputsAfterReweight");

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeAnalysisModule_V4_flat)
