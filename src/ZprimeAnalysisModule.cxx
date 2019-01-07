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

#include <UHH2/common/include/TTbarGen.h>
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

class ZprimeAnalysisModule : public ModuleBASE {

public:
  explicit ZprimeAnalysisModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

protected:

  // Cleaners (to make sure the pre-selection did everything right)
  std::unique_ptr<MuonCleaner> muon_cleaner;

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
  unique_ptr<Selection> Trigger1_selection, Trigger2_selection, Trigger3_selection, NMuon1_selection, NMuon2_selection, NElectron_selection, TwoDCut_selection, Jet1_selection, Jet2_selection, STlepPlusMet_selection, Chi2_selection, TTbarMatchable_selection, Chi2CandidateMatched_selection, ZprimeTopTag_selection, BlindData_selection;

  //Handles
  Event::Handle<bool> h_is_zprime_reconstructed_chi2, h_is_zprime_reconstructed_correctmatch;

  // Configuration
  bool isMC, ispuppi;
  string Sys_MuonID, Sys_MuonTrigger, Sys_PU;
  TString sample;
  int runnr_oldtriggers = 299368;
};

void ZprimeAnalysisModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
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

void ZprimeAnalysisModule::fill_histograms(uhh2::Event& event, string tag){
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

ZprimeAnalysisModule::ZprimeAnalysisModule(uhh2::Context& ctx){

  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }

  // Important selection values
  double muon_pt(55.);
  double jet1_pt(150.);
  double jet2_pt(50.);
  double stlep_plus_met(150.);
  double chi2_max(30.);
  double mtt_blind(3000.);
  int nmuon_min1 = 1, nmuon_max1 = -1;
  int nmuon_min2 = 1, nmuon_max2 = 1;
  int nele_min = 0  , nele_max = 0;
  string trigger1 = "HLT_Mu50_v*";
  string trigger2 = "HLT_OldMu100_v*";
  string trigger3 = "HLT_TkMu100_v*";
  double TwoD_dr = 0.4, TwoD_ptrel = 25.;
  const MuonId muonID(PtEtaCut(muon_pt, 2.4));


  // Configuration
  isMC = (ctx.get("dataset_type") == "MC");
  ispuppi = (ctx.get("is_puppi") == "true");
  TString mode = "chs";
  if(ispuppi) mode = "puppi";
  string tmp = ctx.get("dataset_version");
  sample = tmp;
  Sys_MuonID = ctx.get("Sys_MuonID");
  Sys_MuonTrigger = ctx.get("Sys_MuonTrigger");
  Sys_PU = ctx.get("Sys_PU");

  // Modules
  printer_genparticles.reset(new GenParticlesPrinter(ctx));
  muon_cleaner.reset(new MuonCleaner(muonID));
  MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/reimersa/CMSSW_9_4_1/src/UHH2/common/data/MuonID_94X_RunBCDEF_SF_ID.root", "NUM_HighPtID_DEN_genTracks_pair_newTuneP_probe_pt_abseta", 0., "HighPtID", true, Sys_MuonID));
  MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/reimersa/CMSSW_9_4_1/src/UHH2/common/data/MuonTrigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "Mu50_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger", true, Sys_MuonTrigger));

  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  CSVWeight_module.reset(new MCCSVv2ShapeSystematic(ctx, "jets","central","iterativefit","","MCCSVv2ShapeSystematic"));

  // Selection modules
  Trigger1_selection.reset(new TriggerSelection(trigger1));
  Trigger2_selection.reset(new TriggerSelection(trigger2));
  Trigger3_selection.reset(new TriggerSelection(trigger3));
  NMuon1_selection.reset(new NMuonSelection(nmuon_min1, nmuon_max1));
  NMuon2_selection.reset(new NMuonSelection(nmuon_min2, nmuon_max2));
  NElectron_selection.reset(new NElectronSelection(nele_min, nele_max));
  TwoDCut_selection.reset(new TwoDCut(TwoD_dr, TwoD_ptrel));
  Jet1_selection.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  Jet2_selection.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  STlepPlusMet_selection.reset(new STlepPlusMetCut(stlep_plus_met, -1.));
  Chi2_selection.reset(new Chi2Cut(ctx, 0., chi2_max));
  TTbarMatchable_selection.reset(new TTbarSemiLepMatchableSelection());
  Chi2CandidateMatched_selection.reset(new Chi2CandidateMatchedSelection(ctx));
  ZprimeTopTag_selection.reset(new ZprimeTopTagSelection(ctx));
  BlindData_selection.reset(new BlindDataSelection(ctx, mtt_blind));

  // Taggers
  TopTaggerPuppi.reset(new AK8PuppiTopTagger(ctx));

  // Zprime candidate builder
  CandidateBuilder.reset(new ZprimeCandidateBuilder(ctx, mode));

  // Zprime discriminators
  Chi2DiscriminatorZprime.reset(new ZprimeChi2Discriminator(ctx));
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  CorrectMatchDiscriminatorZprime.reset(new ZprimeCorrectMatchDiscriminator(ctx));
  h_is_zprime_reconstructed_correctmatch = ctx.get_handle<bool>("is_zprime_reconstructed_correctmatch");

  // Book histograms
  vector<string> histogram_tags = {"Weights", "Muon1", "Trigger", "Muon2", "Electron1", "TwoDCut", "Jet1", "Jet2", "STlepPlusMet", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction"};
  book_histograms(ctx, histogram_tags);
}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeAnalysisModule::process(uhh2::Event& event){

  // cout << "++++++++++++ NEW EVENT ++++++++++++++" << endl;

  // Initialize reco flags with false
  event.set(h_is_zprime_reconstructed_chi2, false);
  event.set(h_is_zprime_reconstructed_correctmatch, false);

  // Printing
  // if(!event.isRealData) printer_genparticles->process(event);

  // TODO Apply things that should've been done in the pre-selection already... Fix pre-selection and then remove these steps
  muon_cleaner->process(event);

  // Weight modules
  LumiWeight_module->process(event);
  PUWeight_module->process(event);
  CSVWeight_module->process(event);
  MuonID_module->process(event);

  // Run top-tagging
  TopTaggerPuppi->process(event);
  fill_histograms(event, "Weights");

  if(!NMuon1_selection->passes(event)) return false;
  fill_histograms(event, "Muon1");

  // if(isMC || (!isMC && event.run >= runnr_oldtriggers)){
  //   if(!(Trigger1_selection->passes(event) || Trigger2_selection->passes(event) || Trigger3_selection->passes(event))) return false;
  // }
  // else{
  //   if(!(Trigger1_selection->passes(event))) return false;
  // }
  if(!(Trigger1_selection->passes(event))) return false;
  MuonTrigger_module->process_onemuon(event, 0);
  fill_histograms(event, "Trigger");

  if(!NMuon2_selection->passes(event)) return false;
  fill_histograms(event, "Muon2");

  if(!NElectron_selection->passes(event)) return false;
  fill_histograms(event, "Electron1");

  if(!TwoDCut_selection->passes(event)) return false;
  fill_histograms(event, "TwoDCut");

  // Here, the Zprime must be reconstructed (we ensured to have >= 2 AK4 jets, >= 1 muon)
  CandidateBuilder->process(event);
  Chi2DiscriminatorZprime->process(event);
  CorrectMatchDiscriminatorZprime->process(event);

  if(sample.Contains("_blinded")){
    if(!BlindData_selection->passes(event)) return false;
  }

  if(!Jet1_selection->passes(event)) return false;
  fill_histograms(event, "Jet1");

  if(!Jet2_selection->passes(event)) return false;
  fill_histograms(event, "Jet2");

  if(!STlepPlusMet_selection->passes(event)) return false;
  fill_histograms(event, "STlepPlusMet");

  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "MatchableBeforeChi2Cut");
  else fill_histograms(event, "NotMatchableBeforeChi2Cut");

  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatchBeforeChi2Cut");
  else fill_histograms(event, "NotCorrectMatchBeforeChi2Cut");

  if(!Chi2_selection->passes(event)) return false;
  fill_histograms(event, "Chi2");

  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "Matchable");
  else fill_histograms(event, "NotMatchable");

  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatch");
  else fill_histograms(event, "NotCorrectMatch");

  if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "TopTagReconstruction");
  else fill_histograms(event, "NotTopTagReconstruction");







  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeAnalysisModule)
