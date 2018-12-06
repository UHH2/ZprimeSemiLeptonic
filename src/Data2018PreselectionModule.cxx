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
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/EventHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicPreselectionHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>

using namespace std;

class Data2018PreselectionModule : public ModuleBASE {

public:
  explicit Data2018PreselectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

protected:

  // Corrections
  std::unique_ptr<JetCorrector>                    jet_corrector_B, jet_corrector_C, jet_corrector_DE, jet_corrector_F, jet_corrector_MC;
  std::unique_ptr<TopJetCorrector>                 topjet_corrector_B, topjet_corrector_C, topjet_corrector_DE, topjet_corrector_F, topjet_corrector_MC;
  std::unique_ptr<GenericTopJetCorrector>          topjet_puppi_corrector_B, topjet_puppi_corrector_C, topjet_puppi_corrector_DE, topjet_puppi_corrector_F, topjet_puppi_corrector_MC;
  std::unique_ptr<SubJetCorrector>                 topjet_subjet_corrector_B, topjet_subjet_corrector_C, topjet_subjet_corrector_DE, topjet_subjet_corrector_F, topjet_subjet_corrector_MC;
  std::unique_ptr<GenericSubJetCorrector>          topjet_puppi_subjet_corrector_B, topjet_puppi_subjet_corrector_C, topjet_puppi_subjet_corrector_DE, topjet_puppi_subjet_corrector_F, topjet_puppi_subjet_corrector_MC;

  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> JLC_B, JLC_C, JLC_DE, JLC_F, JLC_MC;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> TopJLC_B, TopJLC_C, TopJLC_DE, TopJLC_F, TopJLC_MC;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> TopJLC_puppi_B, TopJLC_puppi_C, TopJLC_puppi_DE, TopJLC_puppi_F, TopJLC_puppi_MC;

  std::unique_ptr<GenericJetResolutionSmearer>     JER_smearer;
  std::unique_ptr<GenericJetResolutionSmearer>     TopJER_smearer;
  std::unique_ptr<GenericJetResolutionSmearer>     TopJER_puppi_smearer;


  // Cleaners
  std::unique_ptr<MuonCleaner>                     muon_cleaner;

  std::unique_ptr<JetCleaner>                      jet_IDcleaner, jet_cleaner;
  std::unique_ptr<TopJetCleaner>                   topjet_IDcleaner, topjet_cleaner, topjet_puppi_IDcleaner, topjet_puppi_cleaner;



  // Selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  // std::unique_ptr<uhh2::AndSelection> metfilters_sel;

  std::unique_ptr<uhh2::Selection> jet_sel;
  std::unique_ptr<uhh2::Selection> muon_sel;
  std::unique_ptr<uhh2::Selection> trigger1_sel;
  std::unique_ptr<uhh2::Selection> trigger2_sel;

  bool isMC, ispuppi;
  TString mode, year;

  std::unique_ptr<Hists> lumihists;
  TString METcollection;


  // Runnumbers for applying different corrections
  constexpr static int s_runnr_B = 299329; //up to this one, including this one
  constexpr static int s_runnr_C = 302029; //up to this one, including this one
  constexpr static int s_runnr_DE = 304826; //up to this one, including this one
  constexpr static int s_runnr_F = 306462; //up to this one, including this one

};

void Data2018PreselectionModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    string mytag = tag+"_General";
    book_HFolder(mytag, new ZprimeSemiLeptonicPreselectionHists(ctx,mytag));
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

void Data2018PreselectionModule::fill_histograms(uhh2::Event& event, string tag){
  string mytag = tag+"_General";
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


Data2018PreselectionModule::Data2018PreselectionModule(uhh2::Context& ctx){

  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }

  //// CONFIGURATION
  const TString METcollection = ctx.get("METName");
  const bool isMC = (ctx.get("dataset_type") == "MC");
  const bool ispuppi = (ctx.get("is_puppi") == "true");
  cout << "Is this running on puppi: " << ispuppi << endl;

  const string tmp = ctx.get("triggermode");
  mode = tmp;
  if(mode != "Iso" && mode != "NonIso" && mode != "Comb") throw runtime_error("Invalid triggermode specified in xml file.");

  const string tmp2 = ctx.get("year");
  year = tmp2;
  if(year != "2016" && year != "2017" && year != "2018") throw runtime_error("Invalid year specified in xml file.");

  // ElectronId eleID = ElectronID_Fall17_tight;
  MuonId muID;
  if(mode == "Iso" || mode == "Comb") muID = AndId<Muon>(MuonID(Muon::CutBasedIdTight), MuonIso(0.15));
  else muID = MuonID(Muon::CutBasedIdGlobalHighPt);
  double muon_pt = -1.;
  if(mode == "Iso" || mode == "Comb") muon_pt = 30.;
  else muon_pt = 55.;
  double jet_pt(30.);

  string triggername1, triggername2;
  if(year == "2018"){
    triggername1 = "HLT_IsoMu27_v*";
    triggername2 = triggername1;
  }
  else if(year == "2017"){
    triggername1 = "HLT_IsoMu27_v*";
    triggername2 = triggername1;
  }
  else{
    triggername1 = "HLT_IsoMu24_v*";
    triggername2 = "HLT_IsoTkMu24_v*";
  }


  // COMMON MODULES


  // // MET filters
  // metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
  // if(!isMC){
  //   metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices");
  //   metfilters_sel->add<TriggerSelection>("globalTightHalo2016Filter", "Flag_globalTightHalo2016Filter");
  //   metfilters_sel->add<TriggerSelection>("HBHENoiseFilter", "Flag_HBHENoiseFilter");
  //   metfilters_sel->add<TriggerSelection>("HBHENoiseIsoFilter", "Flag_HBHENoiseIsoFilter");
  //   metfilters_sel->add<TriggerSelection>("EcalDeadCellTriggerPrimitiveFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter");
  //   if(!isMC)  metfilters_sel->add<TriggerSelection>("eeBadScFilter", "Flag_eeBadScFilter");
  //   metfilters_sel->add<TriggerSelection>("chargedHadronTrackResolutionFilter", "Flag_chargedHadronTrackResolutionFilter");
  //   metfilters_sel->add<TriggerSelection>("muonBadTrackFilter", "Flag_muonBadTrackFilter");
  // }

  ////

  // Cleaning: Mu, Ele, Jets
  const MuonId muonID(AndId<Muon>(PtEtaCut(muon_pt, 2.4), muID));
  // const ElectronId electronID(AndId<Electron>(PtEtaSCCut(electron_pt, 2.4), eleID));
  const JetId jetID(JetPFID(JetPFID::WP_TIGHT));


  muon_cleaner.reset(new MuonCleaner(muonID));
  // electron_cleaner.reset(new ElectronCleaner(electronID));
  jet_IDcleaner.reset(new JetCleaner(ctx, jetID));
  jet_cleaner.reset(new JetCleaner(ctx, jet_pt, 2.4));
  topjet_IDcleaner.reset(new TopJetCleaner(ctx, jetID, "topjets"));
  topjet_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4)), "topjets"));
  topjet_puppi_IDcleaner.reset(new TopJetCleaner(ctx, jetID, "toppuppijets"));
  topjet_puppi_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4)), "toppuppijets"));

  // Jet energy corrections
  std::vector<std::string> JEC_AK4_MC, JEC_AK8_MC, JEC_AK4_MC_Puppi, JEC_AK8_MC_Puppi;
  std::vector<std::string> JEC_AK4_B,       JEC_AK4_C,       JEC_AK4_DE,       JEC_AK4_F;
  std::vector<std::string> JEC_AK4_B_Puppi, JEC_AK4_C_Puppi, JEC_AK4_DE_Puppi, JEC_AK4_F_Puppi;
  std::vector<std::string> JEC_AK8_B,       JEC_AK8_C,       JEC_AK8_DE,       JEC_AK8_F;
  std::vector<std::string> JEC_AK8_B_Puppi, JEC_AK8_C_Puppi, JEC_AK8_DE_Puppi, JEC_AK8_F_Puppi;

  JEC_AK4_B       = JERFiles::Fall17_17Nov2017_V32_B_L123_AK4PFchs_DATA;
  JEC_AK4_C       = JERFiles::Fall17_17Nov2017_V32_C_L123_AK4PFchs_DATA;
  JEC_AK4_DE       = JERFiles::Fall17_17Nov2017_V32_DE_L123_AK4PFchs_DATA;
  JEC_AK4_F       = JERFiles::Fall17_17Nov2017_V32_F_L123_AK4PFchs_DATA;
  JEC_AK4_MC       = JERFiles::Fall17_17Nov2017_V32_L123_AK4PFchs_MC;

  JEC_AK8_B       = JERFiles::Fall17_17Nov2017_V32_B_L123_AK8PFchs_DATA;
  JEC_AK8_C       = JERFiles::Fall17_17Nov2017_V32_C_L123_AK8PFchs_DATA;
  JEC_AK8_DE       = JERFiles::Fall17_17Nov2017_V32_DE_L123_AK8PFchs_DATA;
  JEC_AK8_F       = JERFiles::Fall17_17Nov2017_V32_F_L123_AK8PFchs_DATA;
  JEC_AK8_MC       = JERFiles::Fall17_17Nov2017_V32_L123_AK8PFchs_MC;

  JEC_AK4_B_Puppi = JERFiles::Fall17_17Nov2017_V32_B_L123_AK4PFPuppi_DATA;
  JEC_AK4_C_Puppi = JERFiles::Fall17_17Nov2017_V32_C_L123_AK4PFPuppi_DATA;
  JEC_AK4_DE_Puppi = JERFiles::Fall17_17Nov2017_V32_DE_L123_AK4PFPuppi_DATA;
  JEC_AK4_F_Puppi = JERFiles::Fall17_17Nov2017_V32_F_L123_AK4PFPuppi_DATA;
  JEC_AK4_MC_Puppi = JERFiles::Fall17_17Nov2017_V32_L123_AK4PFPuppi_MC;

  JEC_AK8_B_Puppi = JERFiles::Fall17_17Nov2017_V32_B_L123_AK8PFPuppi_DATA;
  JEC_AK8_C_Puppi = JERFiles::Fall17_17Nov2017_V32_C_L123_AK8PFPuppi_DATA;
  JEC_AK8_DE_Puppi = JERFiles::Fall17_17Nov2017_V32_DE_L123_AK8PFPuppi_DATA;
  JEC_AK8_F_Puppi = JERFiles::Fall17_17Nov2017_V32_F_L123_AK8PFPuppi_DATA;
  JEC_AK8_MC_Puppi = JERFiles::Fall17_17Nov2017_V32_L123_AK8PFPuppi_MC;

  if(!ispuppi){
    jet_corrector_B.reset(new JetCorrector(ctx,             JEC_AK4_B));
    jet_corrector_C.reset(new JetCorrector(ctx,             JEC_AK4_C));
    jet_corrector_DE.reset(new JetCorrector(ctx,            JEC_AK4_DE));
    jet_corrector_F.reset(new JetCorrector(ctx,             JEC_AK4_F));
    jet_corrector_MC.reset(new JetCorrector(ctx,            JEC_AK4_MC));
  }
  else{
    jet_corrector_B.reset(new JetCorrector(ctx,             JEC_AK4_B_Puppi));
    jet_corrector_C.reset(new JetCorrector(ctx,             JEC_AK4_C_Puppi));
    jet_corrector_DE.reset(new JetCorrector(ctx,            JEC_AK4_DE_Puppi));
    jet_corrector_F.reset(new JetCorrector(ctx,             JEC_AK4_F_Puppi));
    jet_corrector_MC.reset(new JetCorrector(ctx,            JEC_AK4_MC_Puppi));
  }

  topjet_corrector_B.reset(new TopJetCorrector(ctx,       JEC_AK8_B));
  topjet_corrector_C.reset(new TopJetCorrector(ctx,       JEC_AK8_C));
  topjet_corrector_DE.reset(new TopJetCorrector(ctx,      JEC_AK8_DE));
  topjet_corrector_F.reset(new TopJetCorrector(ctx,       JEC_AK8_F));
  topjet_corrector_MC.reset(new TopJetCorrector(ctx,      JEC_AK8_MC));

  topjet_puppi_corrector_B.reset(new GenericTopJetCorrector(ctx,  JEC_AK8_B_Puppi, "toppuppijets"));
  topjet_puppi_corrector_C.reset(new GenericTopJetCorrector(ctx,  JEC_AK8_C_Puppi, "toppuppijets"));
  topjet_puppi_corrector_DE.reset(new GenericTopJetCorrector(ctx, JEC_AK8_DE_Puppi, "toppuppijets"));
  topjet_puppi_corrector_F.reset(new GenericTopJetCorrector(ctx,  JEC_AK8_F_Puppi, "toppuppijets"));
  topjet_puppi_corrector_MC.reset(new GenericTopJetCorrector(ctx, JEC_AK8_MC_Puppi, "toppuppijets"));

  topjet_subjet_corrector_B.reset(new SubJetCorrector(ctx,               JEC_AK4_B));
  topjet_subjet_corrector_C.reset(new SubJetCorrector(ctx,               JEC_AK4_C));
  topjet_subjet_corrector_DE.reset(new SubJetCorrector(ctx,              JEC_AK4_DE));
  topjet_subjet_corrector_F.reset(new SubJetCorrector(ctx,               JEC_AK4_F));
  topjet_subjet_corrector_MC.reset(new SubJetCorrector(ctx,              JEC_AK4_MC));

  topjet_puppi_subjet_corrector_B.reset(new GenericSubJetCorrector(ctx,  JEC_AK4_B_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_C.reset(new GenericSubJetCorrector(ctx,  JEC_AK4_C_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_DE.reset(new GenericSubJetCorrector(ctx, JEC_AK4_DE_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_F.reset(new GenericSubJetCorrector(ctx,  JEC_AK4_F_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_MC.reset(new GenericSubJetCorrector(ctx, JEC_AK4_MC_Puppi, "toppuppijets"));

  if(!ispuppi){
    JLC_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_B));
    JLC_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_C));
    JLC_DE.reset(new JetLeptonCleaner_by_KEYmatching(ctx,          JEC_AK4_DE));
    JLC_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_F));
    JLC_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,          JEC_AK4_MC));
  }
  else{
    JLC_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_B_Puppi));
    JLC_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_C_Puppi));
    JLC_DE.reset(new JetLeptonCleaner_by_KEYmatching(ctx,          JEC_AK4_DE_Puppi));
    JLC_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_F_Puppi));
    JLC_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,          JEC_AK4_MC_Puppi));
  }

  TopJLC_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,        JEC_AK8_B, "topjets"));
  TopJLC_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,        JEC_AK8_C, "topjets"));
  TopJLC_DE.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8_DE, "topjets"));
  TopJLC_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,        JEC_AK8_F, "topjets"));
  TopJLC_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8_MC, "topjets"));

  TopJLC_puppi_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,  JEC_AK8_B_Puppi, "toppuppijets"));
  TopJLC_puppi_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,  JEC_AK8_C_Puppi, "toppuppijets"));
  TopJLC_puppi_DE.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK8_DE_Puppi, "toppuppijets"));
  TopJLC_puppi_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,  JEC_AK8_F_Puppi, "toppuppijets"));
  TopJLC_puppi_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK8_MC_Puppi, "toppuppijets"));

  if(isMC){
    ctx.declare_event_input<std::vector<Particle> >(ctx.get("TopJetCollectionGEN"), "topjetsGEN");
    if(!ispuppi) JER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERSmearing::SF_13TeV_Fall17_V3, "Fall17_V3_MC_PtResolution_AK4PFchs.txt"));
    else JER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERSmearing::SF_13TeV_Fall17_V3, "Fall17_V3_MC_PtResolution_AK4PFPuppi.txt"));
    TopJER_smearer.reset(new GenericJetResolutionSmearer(ctx, "topjets", "topjetsGEN", JERSmearing::SF_13TeV_Fall17_V3, "Fall17_V3_MC_PtResolution_AK8PFchs.txt"));
    TopJER_puppi_smearer.reset(new GenericJetResolutionSmearer(ctx, "toppuppijets", "topjetsGEN", JERSmearing::SF_13TeV_Fall17_V3, "Fall17_V3_MC_PtResolution_AK8PFPuppi.txt"));
  }


  //// EVENT SELECTION
  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));
  jet_sel.reset(new NJetSelection(2, -1));
  muon_sel.reset(new NMuonSelection(1, 1));
  trigger1_sel.reset(new TriggerSelection(triggername1));
  trigger2_sel.reset(new TriggerSelection(triggername2));


  // Book histograms
  vector<string> histogram_tags = {"Input", "Lumiselection", "Muon1", "JetCleaner", "TopjetCleaner", "Jet1", "MuonTrigger"};
  book_histograms(ctx, histogram_tags);


  lumihists.reset(new LuminosityHists(ctx, "lumi"));
}








bool Data2018PreselectionModule::process(uhh2::Event& event){


  fill_histograms(event, "Input");
  // Lumi selection
  if(event.isRealData){
    if(!lumi_sel->passes(event)) return false;
    lumihists->fill(event);
  }
  fill_histograms(event, "Lumiselection");

  // MET filters
  // if(!metfilters_sel->passes(event)) return false;
  // fill_histograms(event, "Metfilters");)) return false;



  //// LEPTON selection
  muon_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  fill_histograms(event, "Muon1");


  //// JET selection
  jet_IDcleaner->process(event);

  if(event.isRealData){
    bool apply_B = false;
    bool apply_C = false;
    bool apply_DE = false;
    bool apply_F = false;
    if(event.run <= s_runnr_B)  apply_B = true;
    else if(event.run <= s_runnr_C) apply_C = true;
    else if(event.run <= s_runnr_DE) apply_DE = true;
    else if(event.run <= s_runnr_F) apply_F = true;
    else throw std::runtime_error("run number not covered by if-statements in process-routine.");

    if(apply_B+apply_C+apply_DE+apply_F != 1) throw std::runtime_error("In Data2018PreselectionModule.cxx: Sum of apply_* when applying JECs is not == 1. Fix this.");

    //apply proper JECs
    if(apply_B){
      JLC_B->process(event);
      TopJLC_B->process(event);
      TopJLC_puppi_B->process(event);
      jet_corrector_B->process(event);
      topjet_corrector_B->process(event);
      topjet_puppi_corrector_B->process(event);
      jet_corrector_B->correct_met(event);
      topjet_subjet_corrector_B->process(event);
      topjet_puppi_subjet_corrector_B->process(event);
    }
    if(apply_C){
      JLC_C->process(event);
      TopJLC_C->process(event);
      TopJLC_puppi_C->process(event);
      jet_corrector_C->process(event);
      topjet_corrector_C->process(event);
      topjet_puppi_corrector_C->process(event);
      jet_corrector_C->correct_met(event);
      topjet_subjet_corrector_C->process(event);
      topjet_puppi_subjet_corrector_C->process(event);
    }
    if(apply_DE){
      JLC_DE->process(event);
      TopJLC_DE->process(event);
      TopJLC_puppi_DE->process(event);
      jet_corrector_DE->process(event);
      topjet_corrector_DE->process(event);
      topjet_puppi_corrector_DE->process(event);
      jet_corrector_DE->correct_met(event);
      topjet_subjet_corrector_DE->process(event);
      topjet_puppi_subjet_corrector_DE->process(event);
    }
    if(apply_F){
      JLC_F->process(event);
      TopJLC_F->process(event);
      TopJLC_puppi_F->process(event);
      jet_corrector_F->process(event);
      topjet_corrector_F->process(event);
      topjet_puppi_corrector_F->process(event);
      jet_corrector_F->correct_met(event);
      topjet_subjet_corrector_F->process(event);
      topjet_puppi_subjet_corrector_F->process(event);
    }
  }
  else{ //MC
    JLC_MC->process(event);
    TopJLC_MC->process(event);
    TopJLC_puppi_MC->process(event);
    jet_corrector_MC->process(event);
    topjet_corrector_MC->process(event);
    topjet_puppi_corrector_MC->process(event);
    if(JER_smearer.get()) JER_smearer->process(event);
    if(TopJER_smearer.get()) TopJER_smearer->process(event);
    if(TopJER_puppi_smearer.get()) TopJER_puppi_smearer->process(event);
    jet_corrector_MC->correct_met(event);
    topjet_subjet_corrector_MC->process(event);
    topjet_puppi_subjet_corrector_MC->process(event);
  }

  jet_cleaner->process(event);
  sort_by_pt<Jet>(*event.jets);
  fill_histograms(event, "JetCleaner");

  topjet_IDcleaner->process(event);
  topjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

  topjet_puppi_IDcleaner->process(event);
  topjet_puppi_cleaner->process(event);
  sort_by_pt<TopJet>(*event.toppuppijets);
  fill_histograms(event, "TopjetCleaner");

  // 2 jet selection
  if(!jet_sel->passes(event)) return false;
  fill_histograms(event, "Jet1");

  // Muon trigger
  if(!(trigger1_sel->passes(event) || trigger2_sel->passes(event))) return false;
  fill_histograms(event, "MuonTrigger");


  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(Data2018PreselectionModule)
