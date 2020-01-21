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

class ZprimeAnalysisModule_LooseCuts : public ModuleBASE {

public:
  explicit ZprimeAnalysisModule_LooseCuts(uhh2::Context&);
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

  // AnalysisModules
  unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, CSVWeight_module, printer_genparticles;

  // Taggers
  unique_ptr<AK8PuppiTopTagger> TopTaggerPuppi;

  // Mass reconstruction
  unique_ptr<ZprimeCandidateBuilder> CandidateBuilder;

  // Chi2 discriminator
  unique_ptr<ZprimeChi2Discriminator> Chi2DiscriminatorZprime;
  unique_ptr<ZprimeCorrectMatchDiscriminator> CorrectMatchDiscriminatorZprime;

  // Selections
  unique_ptr<Selection> Trigger1_selection, Trigger2_selection, NMuon1_selection, NMuon2_selection, NElectron_selection, Jet1_selection, Jet2_selection, Met_selection, Chi2_selection, TTbarMatchable_selection, Chi2CandidateMatched_selection, ZprimeTopTag_selection, BlindData_selection;
  unique_ptr<Selection> TwoDCut_selection;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<Selection> sel_1btag, sel_2btag;
  std::unique_ptr<Selection> TopJetBtagSubjet_selection;
  std::unique_ptr<Selection> HEM_selection;
  //Handles
  Event::Handle<bool> h_is_zprime_reconstructed_chi2, h_is_zprime_reconstructed_correctmatch;
  Event::Handle<float> h_chi2;   Event::Handle<float> h_weight;
  Event::Handle<float> h_MET;   Event::Handle<int> h_NPV;
  Event::Handle<float> h_lep1_pt; Event::Handle<float> h_lep1_eta; 
  Event::Handle<float> h_ak4jet1_pt; Event::Handle<float> h_ak4jet1_eta; 
  Event::Handle<float> h_ak8jet1_pt; Event::Handle<float> h_ak8jet1_eta; 
  Event::Handle<float> h_Mttbar; 
  Event::Handle<float> h_Lep_pt; 
  Event::Handle<float> h_Lep_eta; 
  Event::Handle<float> h_Lep_phi; 
  Event::Handle<float> h_Nu_pt; 
  Event::Handle<float> h_Nu_eta; 
  Event::Handle<float> h_Nu_phi; 
  Event::Handle<float> h_JetLep_pt; 
  Event::Handle<float> h_JetLep_eta; 
  Event::Handle<float> h_JetLep_phi; 
  Event::Handle<float> h_JetHadAK8_pt; 
  Event::Handle<float> h_JetHadAK8_eta; 
  Event::Handle<float> h_JetHadAK8_phi; 
  Event::Handle<float> h_JetHadAK4_1j_pt; 
  Event::Handle<float> h_JetHadAK4_1j_eta; 
  Event::Handle<float> h_JetHadAK4_1j_phi; 
  Event::Handle<float> h_N_AK4_HadJets; 
  Event::Handle<float> h_N_AK4_LepJets; 
  Event::Handle<float> h_JetHadAK4_2j_pt; 
  Event::Handle<float> h_JetHadAK4_2j_eta; 
  Event::Handle<float> h_JetHadAK4_2j_phi; 
  Event::Handle<float> h_TopLep_pt; 
  Event::Handle<float> h_TopLep_eta; 
  Event::Handle<float> h_TopLep_phi; 
  Event::Handle<float> h_TopHad_pt; 
  Event::Handle<float> h_TopHad_eta; 
  Event::Handle<float> h_TopHad_phi; 
  Event::Handle<float> h_TopHadOverLep_pt; 
  Event::Handle<float> h_DeltaR_j1j2_had; 
  Event::Handle<float> h_DeltaR_j1lep_j1had; 
  Event::Handle<float> h_DeltaR_j1_lep; 
  Event::Handle<float> h_DeltaR_j1_nu; 
  Event::Handle<float> h_DeltaR_tlep_thad; 
  Event::Handle<float> h_S11_lep; 
  Event::Handle<float> h_S12_lep; 
  Event::Handle<float> h_S13_lep; 
  Event::Handle<float> h_S22_lep; 
  Event::Handle<float> h_S23_lep; 
  Event::Handle<float> h_S33_lep; 
  Event::Handle<float> h_S11_had; 
  Event::Handle<float> h_S12_had; 
  Event::Handle<float> h_S13_had; 
  Event::Handle<float> h_S22_had; 
  Event::Handle<float> h_S23_had; 
  Event::Handle<float> h_S33_had; 

  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;

  // Configuration
  bool isMC, ispuppi, islooserselection;
  string Sys_MuonID, Sys_MuonTrigger, Sys_PU;
  TString sample;
  int runnr_oldtriggers = 299368;

  bool is2016v2, is2016v3, is2017v2, is2018;
  bool isMuon, isElectron;
};

void ZprimeAnalysisModule_LooseCuts::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    string mytag = tag + "_Skimming";
    // book_HFolder(mytag, new TTbarLJHistsSkimming(ctx,mytag));
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

void ZprimeAnalysisModule_LooseCuts::fill_histograms(uhh2::Event& event, string tag){
  string mytag = tag + "_Skimming";
  // HFolder(mytag)->fill(event);
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

ZprimeAnalysisModule_LooseCuts::ZprimeAnalysisModule_LooseCuts(uhh2::Context& ctx){
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

  // Important selection values
  islooserselection = (ctx.get("is_looser_selection") == "true");
  double muon_pt(55.);
  double elec_pt(80.);
  double jet1_pt(150.);
  double jet2_pt(50.);
  //  double stlep_plus_met(150.);
  double chi2_max(30.);
  double mtt_blind(3000.);
  int nmuon_min1, nmuon_max1;
  int nmuon_min2, nmuon_max2;
  int nele_min, nele_max;
  string trigger1,trigger2;// trigger3;
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
    MET_cut = 50;
    jet1_pt = 185.;
    HT_lep_cut = 0;
    //    trigger3 = "HLT\_Ele115_v*";
  }

 // Remove TwoD cut for DNN 
  double TwoD_dr = 0.4, TwoD_ptrel = 25.;
  if(islooserselection){
    jet1_pt = 100.;
    TwoD_dr = 0.2;
    TwoD_ptrel = 10.;
    //    stlep_plus_met = 100.;
  }
  const MuonId muonID(PtEtaCut(muon_pt, 2.4));
  const ElectronId electronID(PtEtaSCCut(elec_pt, 2.5));

  

  Sys_MuonID = ctx.get("Sys_MuonID");
  Sys_MuonTrigger = ctx.get("Sys_MuonTrigger");
  Sys_PU = ctx.get("Sys_PU");

  // Modules
  printer_genparticles.reset(new GenParticlesPrinter(ctx));
  muon_cleaner.reset(new MuonCleaner(muonID));
  electron_cleaner.reset(new ElectronCleaner(electronID));
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  CSVWeight_module.reset(new MCCSVv2ShapeSystematic(ctx, "jets","central","iterativefit","","MCCSVv2ShapeSystematic"));

  //if((is2016v3 || is2016v2) && isMuon){
  //  MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root", "MC_NUM_TightID_DEN_genTracks_PAR_pt_eta", 0., "MuonID", true, Sys_MuonID));
  //  MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu50_OR_IsoTkMu50_PtEtaBins", 0.5, "MuonTrigger", true, Sys_MuonTrigger));
  //}
  //if(is2017v2 || is2018){
  //  MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2017/MuonID_94X_RunBCDEF_SF_ID.root", "NUM_HighPtID_DEN_genTracks_pair_newTuneP_probe_pt_abseta", 0., "HighPtID", true, Sys_MuonID));
  //  MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2017/MuonTrigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "Mu50_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger", true, Sys_MuonTrigger));
  //}

  // Selection modules
  Trigger1_selection.reset(new TriggerSelection(trigger1));
  Trigger2_selection.reset(new TriggerSelection(trigger2));
  //  Trigger3_selection.reset(new TriggerSelection(trigger3));
  NMuon1_selection.reset(new NMuonSelection(nmuon_min1, nmuon_max1));
  NMuon2_selection.reset(new NMuonSelection(nmuon_min2, nmuon_max2));
  NElectron_selection.reset(new NElectronSelection(nele_min, nele_max));
  TwoDCut_selection.reset(new TwoDCut(TwoD_dr, TwoD_ptrel));
  Jet1_selection.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  Jet2_selection.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  //  STlepPlusMet_selection.reset(new STlepPlusMetCut(stlep_plus_met, -1.));
  met_sel.reset(new METCut  (MET_cut   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep_cut, uhh2::infinity));

  Chi2_selection.reset(new Chi2Cut(ctx, 0., chi2_max));
  TTbarMatchable_selection.reset(new TTbarSemiLepMatchableSelection());
  Chi2CandidateMatched_selection.reset(new Chi2CandidateMatchedSelection(ctx));
  ZprimeTopTag_selection.reset(new ZprimeTopTagSelection(ctx));
  BlindData_selection.reset(new BlindDataSelection(ctx, mtt_blind));

  HEM_selection.reset(new HEMSelection(ctx)); // HEM issue in 2017, veto on electron and jets

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
  //  h_chi2 = ctx.get_handle<float>("rec_chi2");
  h_chi2 = ctx.declare_event_output<float> ("rec_chi2");
  h_MET = ctx.declare_event_output<float> ("met_pt");
  h_Mttbar = ctx.declare_event_output<float> ("Mttbar");
  h_Lep_pt = ctx.declare_event_output<float> ("Lep_pt");
  h_Lep_eta = ctx.declare_event_output<float> ("Lep_eta");
  h_Lep_phi = ctx.declare_event_output<float> ("Lep_phi");
  h_Nu_pt = ctx.declare_event_output<float> ("Nu_pt");
  h_Nu_eta = ctx.declare_event_output<float> ("Nu_eta");
  h_Nu_phi = ctx.declare_event_output<float> ("Nu_phi");
  h_JetLep_pt = ctx.declare_event_output<float> ("JetLep_pt");
  h_JetLep_eta = ctx.declare_event_output<float> ("JetLep_eta");
  h_JetLep_phi = ctx.declare_event_output<float> ("JetLep_phi");
  h_JetHadAK8_pt = ctx.declare_event_output<float> ("JetHadAK8_pt");
  h_JetHadAK8_eta = ctx.declare_event_output<float> ("JetHadAK8_eta");
  h_JetHadAK8_phi = ctx.declare_event_output<float> ("JetHadAK8_phi");
  h_JetHadAK4_1j_pt = ctx.declare_event_output<float> ("JetHadAK4_1j_pt");
  h_JetHadAK4_1j_eta = ctx.declare_event_output<float> ("JetHadAK4_1j_eta");
  h_JetHadAK4_1j_phi = ctx.declare_event_output<float> ("JetHadAK4_1j_phi");
  h_N_AK4_HadJets = ctx.declare_event_output<float> ("N_AK4_HadJets");
  h_N_AK4_LepJets = ctx.declare_event_output<float> ("N_AK4_LepJets");
  h_JetHadAK4_2j_pt = ctx.declare_event_output<float> ("JetHadAK4_2j_pt");
  h_JetHadAK4_2j_eta = ctx.declare_event_output<float> ("JetHadAK4_2j_eta");
  h_JetHadAK4_2j_phi = ctx.declare_event_output<float> ("JetHadAK4_2j_phi");
  h_TopLep_pt = ctx.declare_event_output<float> ("TopLep_pt");
  h_TopLep_eta = ctx.declare_event_output<float> ("TopLep_eta");
  h_TopLep_phi = ctx.declare_event_output<float> ("TopLep_phi");
  h_TopHad_pt = ctx.declare_event_output<float> ("TopHad_pt");
  h_TopHad_eta = ctx.declare_event_output<float> ("TopHad_eta");
  h_TopHad_phi = ctx.declare_event_output<float> ("TopHad_phi");
  h_TopHadOverLep_pt = ctx.declare_event_output<float> ("TopHadOverLep_pt");
  h_DeltaR_j1j2_had = ctx.declare_event_output<float> ("DeltaR_j1j2_had");
  h_DeltaR_j1lep_j1had = ctx.declare_event_output<float> ("DeltaR_j1lep_j1had");
  h_DeltaR_j1_lep = ctx.declare_event_output<float> ("DeltaR_j1_lep");
  h_DeltaR_j1_nu = ctx.declare_event_output<float> ("DeltaR_j1_nu");
  h_DeltaR_tlep_thad = ctx.declare_event_output<float> ("DeltaR_tlep_thad");
  h_S11_lep = ctx.declare_event_output<float> ("S11_lep");
  h_S12_lep = ctx.declare_event_output<float> ("S12_lep");
  h_S13_lep = ctx.declare_event_output<float> ("S13_lep");
  h_S22_lep = ctx.declare_event_output<float> ("S22_lep");
  h_S23_lep = ctx.declare_event_output<float> ("S23_lep");
  h_S33_lep = ctx.declare_event_output<float> ("S33_lep");
  h_S11_had = ctx.declare_event_output<float> ("S11_had");
  h_S12_had = ctx.declare_event_output<float> ("S12_had");
  h_S13_had = ctx.declare_event_output<float> ("S13_had");
  h_S22_had = ctx.declare_event_output<float> ("S22_had");
  h_S23_had = ctx.declare_event_output<float> ("S23_had");
  h_S33_had = ctx.declare_event_output<float> ("S33_had");

  h_lep1_pt = ctx.declare_event_output<float> ("lep1_pt");
  h_lep1_eta = ctx.declare_event_output<float> ("lep1_eta");
  h_ak4jet1_pt = ctx.declare_event_output<float> ("ak4jet1_pt");
  h_ak4jet1_eta = ctx.declare_event_output<float> ("ak4jet1_eta");
  h_ak8jet1_pt = ctx.declare_event_output<float> ("ak8jet1_pt");
  h_ak8jet1_eta = ctx.declare_event_output<float> ("ak8jet1_eta");

  h_NPV = ctx.declare_event_output<int> ("NPV");
  h_weight = ctx.declare_event_output<float> ("weight");

  // btag 
  CSVBTag::wp btag_wp = CSVBTag::WP_TIGHT; // b-tag workingpoint
  JetId id_btag = CSVBTag(btag_wp);

  // DeepCSVBTag::wp btag_wp = DeepCSVBTag::WP_TIGHT; // b-tag workingpoint
  // JetId id_btag = DeepCSVBTag(btag_wp);

  // DeepJetBTag::wp btag_wp = DeepJetBTag::WP_TIGHT; // b-tag workingpoint
  // JetId id_btag = DeepJetBTag(btag_wp);

  sel_1btag.reset(new NJetSelection(1, 1, id_btag));
  sel_2btag.reset(new NJetSelection(2,-1, id_btag));


  TopJetBtagSubjet_selection.reset(new ZprimeBTagFatSubJetSelection(ctx));

  // Book histograms
  vector<string> histogram_tags = {"Weights", "Muon1", "Trigger", "Muon2", "Electron1", "TwoDCut", "Jet1", "Jet2", "MET", "HTlep", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction", "Btags2", "Btags1","TopJetBtagSubjet"};
  book_histograms(ctx, histogram_tags);
}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeAnalysisModule_LooseCuts::process(uhh2::Event& event){

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

  // Variables for NN
  event.set(h_Lep_pt,0);
  event.set(h_Lep_eta,0);
  event.set(h_Lep_phi,0);
  event.set(h_Nu_pt,0);
  event.set(h_Nu_eta,0);
  event.set(h_Nu_phi,0);
  event.set(h_JetLep_pt,0);
  event.set(h_JetLep_eta,0);
  event.set(h_JetLep_phi,0);
  event.set(h_JetHadAK8_pt,0);
  event.set(h_JetHadAK8_eta,0);
  event.set(h_JetHadAK8_phi,0);
  event.set(h_JetHadAK4_1j_pt,0);
  event.set(h_JetHadAK4_1j_eta,0);
  event.set(h_JetHadAK4_1j_phi,0);
  event.set(h_N_AK4_HadJets,0);
  event.set(h_N_AK4_LepJets,0);
  event.set(h_JetHadAK4_2j_pt,0);
  event.set(h_JetHadAK4_2j_eta,0);
  event.set(h_JetHadAK4_2j_phi,0);
  event.set(h_TopLep_pt,0);
  event.set(h_TopLep_eta,0);
  event.set(h_TopLep_phi,0);
  event.set(h_TopHad_pt,0);
  event.set(h_TopHad_eta,0);
  event.set(h_TopHad_phi,0);
  event.set(h_TopHadOverLep_pt,0);
  event.set(h_DeltaR_j1j2_had,0);
  event.set(h_DeltaR_j1lep_j1had,0);
  event.set(h_DeltaR_j1_lep,0);
  event.set(h_DeltaR_j1_nu,0);
  event.set(h_DeltaR_tlep_thad,0);
  event.set(h_S11_lep,0);
  event.set(h_S12_lep,0);
  event.set(h_S13_lep,0);
  event.set(h_S22_lep,0);
  event.set(h_S23_lep,0);
  event.set(h_S33_lep,0);
  event.set(h_S11_had,0);
  event.set(h_S12_had,0);
  event.set(h_S13_had,0);
  event.set(h_S22_had,0);
  event.set(h_S23_had,0);
  event.set(h_S33_had,0);
 
  // Printing
  // if(!event.isRealData) printer_genparticles->process(event);

  // TODO Apply things that should've been done in the pre-selection already... Fix pre-selection and then remove these steps
  if(isMuon) muon_cleaner->process(event);
  if(isElectron) electron_cleaner->process(event);
  if(debug)  cout<<"Muon and Electron cleaner ok"<<endl;
  if(isElectron && !HEM_selection->passes(event)) return false;
  // Weight modules
  LumiWeight_module->process(event);
  if(debug)  cout<<"LumiWeight ok"<<endl;
  // in fisrt round re-weighting is switched off
  PUWeight_module->process(event);
  //if(debug)  cout<<"PUWeight ok"<<endl;
  CSVWeight_module->process(event);
  //if(isMuon){
  //  MuonID_module->process(event);
  //  if(debug)  cout<<"MuonID ok"<<endl;
  //}
  // Run top-tagging
  TopTaggerPuppi->process(event);
  if(debug) cout<<"Top Tagger ok"<<endl;
  fill_histograms(event, "Weights");
 
  // if(isMC || (!isMC && event.run >= runnr_oldtriggers)){
  //   if(!(Trigger1_selection->passes(event) || Trigger2_selection->passes(event) || Trigger3_selection->passes(event))) return false;
  // }
  // else{
  //   if(!(Trigger1_selection->passes(event))) return false;
  // }
  if(!(Trigger1_selection->passes(event)|| Trigger2_selection->passes(event))) return false;
  if(isMuon){
    if(!NMuon1_selection->passes(event)) return false;
    fill_histograms(event, "Muon1");
//    MuonTrigger_module->process_onemuon(event, 0);
//    fill_histograms(event, "Trigger");
    if(!NMuon2_selection->passes(event)) return false;
    fill_histograms(event, "Muon2");
  }
  if(isElectron){
    if(!NElectron_selection->passes(event)) return false;
    fill_histograms(event, "Electron1");
  }
  //  if(event.electrons->size()<1 && event.muons->size()<1) return false; //veto events without leptons
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

  // if(!STlepPlusMet_selection->passes(event)) return false;
  // fill_histograms(event, "STlepPlusMet");

  // MET selection
  if(!met_sel->passes(event)) return false;
  if(debug) cout<<"MET is ok"<<endl;
  fill_histograms(event, "MET");
  if(isMuon){
    if(!htlep_sel->passes(event)) return false;
    fill_histograms(event, "HTlep");
    if(debug) cout<<"HTlep is ok"<<endl;
  }

  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "MatchableBeforeChi2Cut");
  else fill_histograms(event, "NotMatchableBeforeChi2Cut");
  if(debug) cout<<"TTbarMatchable_selection is ok"<<endl;

  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatchBeforeChi2Cut");
  else fill_histograms(event, "NotCorrectMatchBeforeChi2Cut");
  if(debug) cout<<"Chi2CandidateMatched_selection is ok"<<endl;

  if(!Chi2_selection->passes(event)) return false;
  fill_histograms(event, "Chi2");

  if(debug) cout<<"Chi2_selection is ok"<<endl;

  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "Matchable");
  else fill_histograms(event, "NotMatchable");
  if(debug) cout<<"TTbarMatchable_selection is ok"<<endl;

  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatch");
  else fill_histograms(event, "NotCorrectMatch");
  if(debug) cout<<"Chi2CandidateMatched_selection is ok"<<endl;

  if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "TopTagReconstruction");
  else fill_histograms(event, "NotTopTagReconstruction");
  if(debug) cout<<"ZprimeTopTag_selection is ok"<<endl;

  //Test with b-tagging
  if(sel_2btag->passes(event)) fill_histograms(event, "Btags2");
  if(sel_1btag->passes(event)) fill_histograms(event, "Btags1");
  if(debug) cout<<"Btags1 is ok"<<endl;
  if(TopJetBtagSubjet_selection->passes(event)) fill_histograms(event, "TopJetBtagSubjet");
  if(debug) cout<<"TopJetBtagSubjet_selection is ok"<<endl;

  //Fill some vars for monitoring and comparison
  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2); 
  if(is_zprime_reconstructed_chi2){
    ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);
    //    float chi2 = BestZprimeCandidate->discriminator("chi2_total");
    event.set(h_chi2,BestZprimeCandidate->discriminator("chi2_total"));
    event.set(h_Mttbar,BestZprimeCandidate->Zprime_v4().M());
    event.set(h_Lep_pt,BestZprimeCandidate->lepton().pt());
    event.set(h_Lep_eta,BestZprimeCandidate->lepton().eta());
    event.set(h_Lep_phi,BestZprimeCandidate->lepton().phi());
    event.set(h_Nu_pt,BestZprimeCandidate->neutrino_v4().pt());
    event.set(h_Nu_eta,BestZprimeCandidate->neutrino_v4().eta());
    event.set(h_Nu_phi,BestZprimeCandidate->neutrino_v4().phi());
    event.set(h_JetLep_pt,BestZprimeCandidate->jets_leptonic().at(0).pt());
    event.set(h_JetLep_eta,BestZprimeCandidate->jets_leptonic().at(0).eta());
    event.set(h_JetLep_phi,BestZprimeCandidate->jets_leptonic().at(0).phi());
    event.set(h_N_AK4_LepJets,BestZprimeCandidate->jets_leptonic().size());
   if(BestZprimeCandidate->is_toptag_reconstruction()){
   if(BestZprimeCandidate->jets_hadronic().size()>0){
       event.set(h_JetHadAK8_pt,BestZprimeCandidate->jets_hadronic().at(0).pt());
       event.set(h_JetHadAK8_eta,BestZprimeCandidate->jets_hadronic().at(0).eta());
       event.set(h_JetHadAK8_phi,BestZprimeCandidate->jets_hadronic().at(0).phi());
    }
    }
    else{
       event.set(h_N_AK4_HadJets,BestZprimeCandidate->jets_hadronic().size());
       if(BestZprimeCandidate->jets_hadronic().size()>=2){
          event.set(h_JetHadAK4_1j_pt,BestZprimeCandidate->jets_hadronic().at(0).pt());
          event.set(h_JetHadAK4_1j_eta,BestZprimeCandidate->jets_hadronic().at(0).eta());
          event.set(h_JetHadAK4_1j_phi,BestZprimeCandidate->jets_hadronic().at(0).phi());
          event.set(h_JetHadAK4_2j_pt,BestZprimeCandidate->jets_hadronic().at(1).pt());
          event.set(h_JetHadAK4_2j_eta,BestZprimeCandidate->jets_hadronic().at(1).eta());
          event.set(h_JetHadAK4_2j_phi,BestZprimeCandidate->jets_hadronic().at(1).phi());
          event.set(h_DeltaR_j1j2_had,deltaR(BestZprimeCandidate->jets_hadronic().at(0),BestZprimeCandidate->jets_hadronic().at(1)));
          event.set(h_DeltaR_j1lep_j1had,deltaR(BestZprimeCandidate->jets_leptonic().at(0),BestZprimeCandidate->jets_hadronic().at(0)));
       }
    }
    event.set(h_DeltaR_j1_lep,deltaR(BestZprimeCandidate->jets_leptonic().at(0),BestZprimeCandidate->lepton()));
    event.set(h_DeltaR_j1_nu,deltaR(BestZprimeCandidate->jets_leptonic().at(0),BestZprimeCandidate->neutrino_v4()));
    event.set(h_TopLep_pt,BestZprimeCandidate->top_leptonic_v4().pt());
    event.set(h_TopLep_eta,BestZprimeCandidate->top_leptonic_v4().eta());
    event.set(h_TopLep_phi,BestZprimeCandidate->top_leptonic_v4().phi());
    event.set(h_TopHad_pt,BestZprimeCandidate->top_hadronic_v4().pt());
    event.set(h_TopHad_eta,BestZprimeCandidate->top_hadronic_v4().eta());
    event.set(h_TopHad_phi,BestZprimeCandidate->top_hadronic_v4().phi());
    event.set(h_TopHadOverLep_pt,(BestZprimeCandidate->top_hadronic_v4().pt())/(BestZprimeCandidate->top_leptonic_v4().pt()));
    event.set(h_DeltaR_tlep_thad,deltaR(BestZprimeCandidate->top_leptonic_v4(),BestZprimeCandidate->top_hadronic_v4()));


  // Sphericity tensors jets leptonic side
    double s11_lep = -1., s12_lep = -1., s13_lep = -1., s22_lep = -1., s23_lep = -1., s33_lep = -1., mag_lep = -1.;
    for(const Particle jet : BestZprimeCandidate->jets_leptonic()){
      mag_lep += (jet.v4().Px()*jet.v4().Px()+jet.v4().Py()*jet.v4().Py()+jet.v4().Pz()*jet.v4().Pz());
      s11_lep += jet.v4().Px()*jet.v4().Px();
      s12_lep += jet.v4().Px()*jet.v4().Py();
      s13_lep += jet.v4().Px()*jet.v4().Pz();
      s22_lep += jet.v4().Py()*jet.v4().Py();
      s23_lep += jet.v4().Py()*jet.v4().Pz();
      s33_lep += jet.v4().Pz()*jet.v4().Pz();
    }

    s11_lep = s11_lep / mag_lep;
    s12_lep = s12_lep / mag_lep;
    s13_lep = s13_lep / mag_lep;
    s22_lep = s22_lep / mag_lep;
    s23_lep = s23_lep / mag_lep;
    s33_lep = s33_lep / mag_lep;

    event.set(h_S11_lep,s11_lep);
    event.set(h_S12_lep,s12_lep);
    event.set(h_S13_lep,s13_lep);
    event.set(h_S22_lep,s22_lep);
    event.set(h_S23_lep,s23_lep);
    event.set(h_S33_lep,s33_lep);

  // Sphericity tensors jets hadronic side
    double s11_had = -1., s12_had = -1., s13_had = -1., s22_had = -1., s23_had = -1., s33_had = -1., mag_had = -1.;
    for(const Particle jet : BestZprimeCandidate->jets_hadronic()){
      mag_had += (jet.v4().Px()*jet.v4().Px()+jet.v4().Py()*jet.v4().Py()+jet.v4().Pz()*jet.v4().Pz());
      s11_had += jet.v4().Px()*jet.v4().Px();
      s12_had += jet.v4().Px()*jet.v4().Py();
      s13_had += jet.v4().Px()*jet.v4().Pz();
      s22_had += jet.v4().Py()*jet.v4().Py();
      s23_had += jet.v4().Py()*jet.v4().Pz();
      s33_had += jet.v4().Pz()*jet.v4().Pz();
    }

    s11_had = s11_had / mag_had;
    s12_had = s12_had / mag_had;
    s13_had = s13_had / mag_had;
    s22_had = s22_had / mag_had;
    s23_had = s23_had / mag_had;
    s33_had = s33_had / mag_had;

    event.set(h_S11_had,s11_had);
    event.set(h_S12_had,s12_had);
    event.set(h_S13_had,s13_had);
    event.set(h_S22_had,s22_had);
    event.set(h_S23_had,s23_had);
    event.set(h_S33_had,s33_had);
  
  }

  if(debug) cout<<"Set ttbar reconstruction vars for monitoring"<<endl;

  event.set(h_weight,event.weight);
  event.set(h_MET,event.met->pt());
  if(isMuon){
    event.set(h_lep1_pt,event.muons->at(0).pt());
    event.set(h_lep1_eta,event.muons->at(0).eta());
  }
  if(isElectron){
    event.set(h_lep1_pt,event.electrons->at(0).pt());
    event.set(h_lep1_eta,event.electrons->at(0).eta());
  }
  if(event.jets->size()>0){
    event.set(h_ak4jet1_pt,event.jets->at(0).pt());
    event.set(h_ak4jet1_eta,event.jets->at(0).eta());
  }
  if(event.topjets->size()>0){
    event.set(h_ak8jet1_pt,event.topjets->at(0).pt());
    event.set(h_ak8jet1_eta,event.topjets->at(0).eta());
  }
  event.set(h_NPV,event.pvs->size());
  if(debug) cout<<"Set some vars for monitoring"<<endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeAnalysisModule_LooseCuts)
