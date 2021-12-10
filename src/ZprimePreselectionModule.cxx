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
#include <UHH2/common/include/JetCorrectionSets.h>
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
#include <UHH2/common/include/CommonModules.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
//#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicPreselectionHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>
//#include <UHH2/ZprimeSemiLeptonic/include/TopJetCorrections.h>
//#include <UHH2/ZprimeSemiLeptonic/include/TopPuppiJetCorrections.h>

#include "UHH2/HOTVR/include/HOTVRJetCorrectionModule.h"
                           
using namespace std;
using namespace uhh2;

class ZprimePreselectionModule : public ModuleBASE {

public:
  explicit ZprimePreselectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

protected:


  // Corrections
  std::unique_ptr<CommonModules> common;
  //std::unique_ptr<TopJetCorrections> topjetCorr;
  //std::unique_ptr<TopPuppiJetCorrections> toppuppijetCorr;
  std::unique_ptr<AnalysisModule> hotvrjetCorr; 

  // Cleaners
  std::unique_ptr<MuonCleaner>                     muon_cleaner_low, muon_cleaner_high;
  std::unique_ptr<ElectronCleaner>                 electron_cleaner_low, electron_cleaner_high;
  std::unique_ptr<JetCleaner>                      jet_IDcleaner, jet_cleaner1, jet_cleaner2;
  //std::unique_ptr<TopJetCleaner>                   topjet_puppi_IDcleaner, topjet_puppi_cleaner, topjet_IDcleaner, topjet_cleaner;
  std::unique_ptr<AnalysisModule>                  hotvrjet_cleaner;

  // Selections
  std::unique_ptr<uhh2::Selection> genflavor_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> met_sel;

  bool isMC, ispuppi, isHOTVR;
  string Sys_PU;

  std::unique_ptr<Hists> lumihists;
  TString METcollection;

  bool is2016v2, is2016v3, is2017v2, is2018;

};

void ZprimePreselectionModule::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    string mytag = tag+"_General";
    book_HFolder(mytag, new ZprimeSemiLeptonicPreselectionHists(ctx,mytag));
  }
}

void ZprimePreselectionModule::fill_histograms(uhh2::Event& event, string tag){
    string mytag = tag+"_General";
    HFolder(mytag)->fill(event);
}



ZprimePreselectionModule::ZprimePreselectionModule(uhh2::Context& ctx){

  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }

  //// CONFIGURATION
  const TString METcollection = ctx.get("METName");
  isMC = ctx.get("dataset_type") == "MC";
  ispuppi = (ctx.get("is_puppi") == "true");
  isHOTVR = (ctx.get("is_HOTVR") == "true");
  is2016v2 = (ctx.get("dataset_version").find("2016v2") != std::string::npos);
  is2016v3 = (ctx.get("dataset_version").find("2016v3") != std::string::npos);
  is2017v2 = (ctx.get("dataset_version").find("2017v2") != std::string::npos);
  is2018 = (ctx.get("dataset_version").find("2018") != std::string::npos);
  Sys_PU = ctx.get("Sys_PU");

  cout << "Is this running on puppi: " << ispuppi << endl;
  cout << "Is this running on HOTVR: " << isHOTVR << endl;


  ElectronId eleID_low; 
  MuonId muID_low;
  ElectronId eleID_high; 
  MuonId muID_high;

  if(is2017v2 || is2018){
    eleID_low = ElectronID_Fall17_tight;
    muID_low  = MuonID(Muon::CutBasedIdTight);
    eleID_high = ElectronID_Fall17_tight_noIso;
    muID_high  = MuonID(Muon::CutBasedIdGlobalHighPt);
  }
  if(is2016v2 || is2016v3){
    //eleID = ElectronID_Summer16_tight_noIso;//ToDo: compare cutBased without iso and MVA-based via wp in UHH2
    //muID      = MuonID(Muon::Highpt);
    eleID_low = ElectronID_Summer16_tight;
    muID_low  = MuonID(Muon::CutBasedIdTight); 
    eleID_high = ElectronID_Summer16_tight_noIso;
    muID_high  = MuonID(Muon::CutBasedIdTight); // see more muonIDs https://github.com/cms-sw/cmssw/blob/master/DataFormats/MuonReco/interface/Muon.h#L201
  }
  double electron_pt_low(35.);
  double muon_pt_low(30.);
  double electron_pt_high(120.);
  double muon_pt_high(55.);
  double jet1_pt(50.);
  double jet2_pt(20.);
  double MET(50.);



  // GEN Flavor selection [W+jets flavor-splitting] 
  if(ctx.get("dataset_version").find("WJets") != std::string::npos){

    if     (ctx.get("dataset_version").find("_B") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("b"));
    else if(ctx.get("dataset_version").find("_C") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("c"));
    else if(ctx.get("dataset_version").find("_L") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("l"));

    else genflavor_sel.reset(new uhh2::AndSelection(ctx));
  }
  else genflavor_sel.reset(new uhh2::AndSelection(ctx));


  // Cleaning: Mu, Ele, Jets
  const MuonId muonID_low(AndId<Muon>(PtEtaCut(muon_pt_low, 2.4), muID_low, MuonIso(0.15)));
  const ElectronId electronID_low(AndId<Electron>(PtEtaSCCut(electron_pt_low, 2.5), eleID_low));
  const MuonId muonID_high(AndId<Muon>(PtEtaCut(muon_pt_high, 2.4), muID_high));
  const ElectronId electronID_high(AndId<Electron>(PtEtaSCCut(electron_pt_high, 2.5), eleID_high));
  const JetPFID jetID_CHS(JetPFID::WP_TIGHT_CHS); 
  const JetPFID jetID_PUPPI(JetPFID::WP_TIGHT_PUPPI); 

  muon_cleaner_low.reset(new MuonCleaner(muonID_low));
  electron_cleaner_low.reset(new ElectronCleaner(electronID_low));
  muon_cleaner_high.reset(new MuonCleaner(muonID_high));
  electron_cleaner_high.reset(new ElectronCleaner(electronID_high));
  jet_IDcleaner.reset(new JetCleaner(ctx, jetID_PUPPI));
  jet_cleaner1.reset(new JetCleaner(ctx, 15., 3.0));
  jet_cleaner2.reset(new JetCleaner(ctx, 30., 2.4));
  //topjet_IDcleaner.reset(new TopJetCleaner(ctx, jetID_CHS, "topjets"));
  //topjet_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(200., 2.4)), "topjets"));
  //topjet_puppi_IDcleaner.reset(new TopJetCleaner(ctx, jetID_PUPPI, "toppuppijets"));
  //topjet_puppi_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(200., 2.4)), "toppuppijets"));
  hotvrjet_cleaner.reset(new TopJetCleaner(ctx, PtEtaCut(200., 2.5))); 
  

  // common modules
  common.reset(new CommonModules());
  common->switch_jetlepcleaner(true);
  common->disable_pvfilter();
  common->disable_jetpfidfilter();
  common->switch_jetPtSorter(true);
  common->switch_metcorrection(true);
//  common->set_muon_id(OrId<Muon>(AndId<Muon>(PtEtaCut(muon_pt_low, 2.4), muID_low), AndId<Muon>(PtEtaCut(muon_pt_high, 2.4), muID_high)));  
//  common->set_electron_id(OrId<Electron>(AndId<Electron>(PtEtaSCCut(electron_pt_low, 2.5), eleID_low), AndId<Electron>(PtEtaSCCut(electron_pt_high, 2.5), eleID_high)));  
  common->init(ctx, Sys_PU);

  //topjetCorr.reset(new TopJetCorrections());
  //topjetCorr->init(ctx);

  //toppuppijetCorr.reset(new TopPuppiJetCorrections());
  //toppuppijetCorr->init(ctx);

  hotvrjetCorr.reset(new HOTVRJetCorrectionModule(ctx));


  //// EVENT SELECTION
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  met_sel  .reset(new METCut  (MET   , uhh2::infinity));


  // Book histograms
  vector<string> histogram_tags = {"Input", "CommonModules", "MuonCleanerLowPt", "MuonCleanerHighPt","EleCleanerLowPt", "EleCleanerHighPt","Lepton1", "JetID", "JetCleaner1", "JetCleaner2", "TopjetCleaner", "Jet1", "Jet2", "MET"};
  book_histograms(ctx, histogram_tags);

  lumihists.reset(new LuminosityHists(ctx, "lumi"));
}


bool ZprimePreselectionModule::process(uhh2::Event& event){

double electron_pt_high(120.);
double muon_pt_high(55.);

  //cout<<"Getting started... "<<event.event<<endl;
  fill_histograms(event, "Input");

  bool commonResult = common->process(event);
  if (!commonResult) return false;
  //cout<<"Common Modules... "<<event.event<<endl;
  fill_histograms(event, "CommonModules");

  // CLEANER MUONS
  vector<Muon>* muons = event.muons;
  for(unsigned int i=0; i<muons->size(); i++){
    if(event.muons->at(i).pt()<=muon_pt_high){
    muon_cleaner_low->process(event);
    fill_histograms(event, "MuonCleanerLowPt");
    }else{
    muon_cleaner_high->process(event);
    fill_histograms(event, "MuonCleanerHighPt");
    }
  }
  sort_by_pt<Muon>(*event.muons);

  // CLEANER ELECTRONS
  vector<Electron>* electrons = event.electrons;
  for(unsigned int i=0; i<electrons->size(); i++){
    if(event.electrons->at(i).pt()<=electron_pt_high){
    electron_cleaner_low->process(event);
    fill_histograms(event, "EleCleanerLowPt");
    }else{
    electron_cleaner_high->process(event);
    fill_histograms(event, "EleCleanerHighPt");
    }
  }
  sort_by_pt<Electron>(*event.electrons);

  //if(ispuppi){
  //toppuppijetCorr->process(event);
  //}
  if(isHOTVR){
  hotvrjetCorr->process(event);
  }
  //if(!ispuppi && !isHOTVR){
  //topjetCorr->process(event);
  //}
  
  //cout<<"TopJEC_JLC ... "<<event.event<<endl;


  // GEN ME quark-flavor selection
  if(!event.isRealData){
    if(!genflavor_sel->passes(event)) return false;
  }

    //cout<<"GEN ME quark-flavor selection ... "<<event.event<<endl;

  const bool pass_lep1 = ((event.muons->size() >= 1) || (event.electrons->size() >= 1));
  if(!pass_lep1) return false;

  fill_histograms(event, "Lepton1");

  jet_IDcleaner->process(event);
  fill_histograms(event, "JetID");

  jet_cleaner1->process(event);
  sort_by_pt<Jet>(*event.jets);
  fill_histograms(event, "JetCleaner1");
  //cout<<"JetCleaner1 ... "<<event.event<<endl;

  // Lepton-2Dcut variables
  for(auto& muo : *event.muons){

    float    dRmin, pTrel;
    std::tie(dRmin, pTrel) = drmin_pTrel(muo, *event.jets);

    muo.set_tag(Muon::twodcut_dRmin, dRmin);
    muo.set_tag(Muon::twodcut_pTrel, pTrel);
  }

  for(auto& ele : *event.electrons){

    float    dRmin, pTrel;
    std::tie(dRmin, pTrel) = drmin_pTrel(ele, *event.jets);

    ele.set_tag(Electron::twodcut_dRmin, dRmin);
    ele.set_tag(Electron::twodcut_pTrel, pTrel);
  }


  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);
  fill_histograms(event, "JetCleaner2");
    //cout<<"JetCleaner2 ... "<<event.event<<endl;

  //topjet_IDcleaner->process(event);
  //topjet_cleaner->process(event);
  //sort_by_pt<TopJet>(*event.topjets);

  //topjet_puppi_IDcleaner->process(event);
  //topjet_puppi_cleaner->process(event);
  //sort_by_pt<TopJet>(*event.toppuppijets);

  hotvrjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

  fill_histograms(event, "TopjetCleaner");
    //cout<<"TopjetCleaner ... "<<event.event<<endl;

  // 1st AK4 jet selection
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  fill_histograms(event, "Jet1");

  // 2nd AK4 jet selection
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  fill_histograms(event, "Jet2");

  // MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  fill_histograms(event, "MET");

  return true;

}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimePreselectionModule)
