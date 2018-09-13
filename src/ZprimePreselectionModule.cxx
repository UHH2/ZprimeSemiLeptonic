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

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHistsSkimming.h>

using namespace std;

class ZprimePreselectionModule : public ModuleBASE {

 public:
  explicit ZprimePreselectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:

  // Corrections
  std::unique_ptr<JetCorrector>                    jet_corrector_B, jet_corrector_C, jet_corrector_D, jet_corrector_E, jet_corrector_F, jet_corrector_MC;
  std::unique_ptr<TopJetCorrector>                 topjet_corrector_B, topjet_corrector_C, topjet_corrector_D, topjet_corrector_E, topjet_corrector_F, topjet_corrector_MC;
  std::unique_ptr<GenericTopJetCorrector>          topjet_puppi_corrector_B, topjet_puppi_corrector_C, topjet_puppi_corrector_D, topjet_puppi_corrector_E, topjet_puppi_corrector_F, topjet_puppi_corrector_MC;
  std::unique_ptr<SubJetCorrector>                 topjet_subjet_corrector_B, topjet_subjet_corrector_C, topjet_subjet_corrector_D, topjet_subjet_corrector_E, topjet_subjet_corrector_F, topjet_subjet_corrector_MC;
  std::unique_ptr<GenericSubJetCorrector>          topjet_puppi_subjet_corrector_B, topjet_puppi_subjet_corrector_C, topjet_puppi_subjet_corrector_D, topjet_puppi_subjet_corrector_E, topjet_puppi_subjet_corrector_F, topjet_puppi_subjet_corrector_MC;

  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> JLC_B, JLC_C, JLC_D, JLC_E, JLC_F, JLC_MC;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> TopJLC_B, TopJLC_C, TopJLC_D, TopJLC_E, TopJLC_F, TopJLC_MC;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> TopJLC_puppi_B, TopJLC_puppi_C, TopJLC_puppi_D, TopJLC_puppi_E, TopJLC_puppi_F, TopJLC_puppi_MC;

  std::unique_ptr<JetResolutionSmearer>            JER_smearer;
  std::unique_ptr<GenericJetResolutionSmearer>     TopJER_smearer;
  std::unique_ptr<GenericJetResolutionSmearer>     TopJER_puppi_smearer;


  // Cleaners
  std::unique_ptr<MuonCleaner>                     muoSR_cleaner;
  std::unique_ptr<ElectronCleaner>                 eleSR_cleaner;

  std::unique_ptr<JetCleaner>                      jet_IDcleaner, jet_cleaner1, jet_cleaner2;
  std::unique_ptr<TopJetCleaner>                   topjet_IDcleaner, topjet_cleaner, topjet_puppi_IDcleaner, topjet_puppi_cleaner;



  // Selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel;

  std::unique_ptr<uhh2::Selection> genflavor_sel;

  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> twodcut_sel;

  bool isMC, isQCDstudy;    

  std::unique_ptr<Hists> lumihists;
  std::string METcollection;


  // Runnumbers for applying different corrections
  constexpr static int s_runnr_B = 299329; //up to this one, including this one
  constexpr static int s_runnr_C = 302029; //up to this one, including this one
  constexpr static int s_runnr_D = 303434; //up to this one, including this one
  constexpr static int s_runnr_E = 304826; //up to this one, including this one
  constexpr static int s_runnr_F = 306462; //up to this one, including this one

};

ZprimePreselectionModule::ZprimePreselectionModule(uhh2::Context& ctx){

  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }
  
  //// CONFIGURATION
 const std::string& _METcollection = ctx.get("METName");
 METcollection = _METcollection;
  const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string& keyword = ctx.get("keyword");
  const float& _twod1 = string2double(ctx.get("twod1"))*0.1;
  const float& _twod2 = string2double(ctx.get("twod2"));

  ElectronId eleID;
  float ele_pt(-1.),muon_pt(-1.), jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);
  bool use_miniiso(false);
  float twod1(0.4),twod2(40.);
  if(keyword == "v01"){ // Cut-based aka 2015
    isQCDstudy = false;
    //    isQCDstudy = true;//TEST JLC
    ele_pt = 50.;
    //    ele_pt = 0.;
    muon_pt = 55.;
    eleID  = ElectronID_Fall17_tight_noIso;
    //    eleID = ElectronID_MVAGeneralPurpose_Spring16_loose; //The best signal/bkg performance in 2016  
    //    eleID = ElectronID_HEEP_RunII_25ns; //TEST
    //    eleID = ElectronID_Spring16_medium_noIso;         
    use_miniiso = false;
    jet1_pt = 50.;
    jet2_pt =  20.;

    //    MET     =  50.;
    MET     =   0.;
    HT_lep  =   0.;
    twod1 = _twod1;
    twod2 = _twod2;
  }
  else {
    if(keyword == "v02"){ //Skimming for ElecID_MVA_loose
      //    isQCDstudy = true;
    isQCDstudy = false;
    ele_pt = 50.;
    muon_pt = 0.;
    //  eleID  = ElectronID_Spring15_25ns_tight_noIso;
    //    eleID = ElectronID_MVAnotrig_Spring15_25ns_veryloose;//TEST
    //    eleID = ElectronID_MVAnotrig_Spring15_25ns_loose; //TEST 
    //    eleID  = ElectronID_Spring15_25ns_tight_noIso;
    // eleID  = ElectronID_Spring16_tight_noIso;
    eleID = ElectronID_MVA_Fall17_loose_iso;
    use_miniiso = false;
    jet1_pt =   0.;
    jet2_pt =   0.;
    MET     =   50.;
    // MET     =   0.;

    HT_lep  =   0.;
    }
    else if(keyword == "v03"){ //Skimming for ElecID_MVA_tight
      isQCDstudy = false;
      ele_pt = 50.;     
      muon_pt = 50.;
      eleID = ElectronID_MVA_Fall17_loose_iso;
      use_miniiso = false;
      jet1_pt = 50.;
      jet2_pt = 20.; 
      MET     = 50.;
      // MET     = 0.;
      HT_lep  = 0.;
    }        
    else if(keyword == "v04"){ //Skimming for ElecID_cut_tight
      //      isQCDstudy = true;
      isQCDstudy = false;
      ele_pt = 50.;     
      muon_pt = 50.;
      //      eleID = ElectronID_Spring16_tight_noIso;                                                  
      eleID = ElectronID_Spring16_tight;                                                  
      use_miniiso = false;
      jet1_pt = 50.;
      jet2_pt = 20.; 
      MET     = 50.;
      // MET     = 0.;
      HT_lep  = 0.;
    }
    else if(keyword == "v05"){ //Skimming for ElecID_cut_loose_noIso
      isQCDstudy = true;
      ele_pt = 50.;     
      muon_pt = 0.;
      eleID = ElectronID_Spring16_loose_noIso;                                                  
      use_miniiso = false;
      jet1_pt = 0.;
      jet2_pt = 0.; 
      MET     = 50.;
      // MET     = 0.;
      HT_lep  = 0.;
    }
    else if(keyword == "v06"){ //Skimming for ElecID_cut_medium_noIso
      isQCDstudy = true;
      ele_pt = 50.;     
      muon_pt = 0.;
      eleID = ElectronID_Spring16_medium_noIso;                                                  
      use_miniiso = false;
      jet1_pt = 50.;
      jet2_pt = 20.; 
      //      MET     = 50.;
      MET     = 0.;
      HT_lep  = 0.;
    }
    else if(keyword == "v07"){ //Skimming for ElecID_cut_medium_noIso
      isQCDstudy = true;
      ele_pt = 50.;     
      muon_pt = 0.;
      // eleID = ElectronID_Spring16_medium_noIso;                                                  
      use_miniiso = false;
      jet1_pt = 0.;
      jet2_pt = 0.; 
      MET     = 50.;
      // MET     = 0.;
      HT_lep  = 0.;
    }
    else if(keyword == "v061"){ //Skimming for ElecID_cut_medium_noIso
      isQCDstudy = false;
      ele_pt = 50.;     
      muon_pt = 0.;
      eleID = ElectronID_Spring16_medium_noIso;                                                  
      use_miniiso = false;
      jet1_pt = 0.;
      jet2_pt = 0.; 
      MET     = 50.;
      // MET     = 0.;
      HT_lep  = 0.;
      twod1 = _twod1;
      twod2 = _twod2;
    }
    else if(keyword == "v021"){ //Skimming for ElecID_MVA_loose                                                                                             
      //      isQCDstudy = true;
      isQCDstudy = false;
      ele_pt = 50.;     
      muon_pt = 0.;
      eleID = ElectronID_MVA_Fall17_loose_iso;
      use_miniiso = false;
      jet1_pt = 0.;
      jet2_pt = 0.; 
      MET     = 50.;
      // MET     = 0.;
      HT_lep  = 0.;
      twod1 = _twod1;
      twod2 = _twod2;
    }       
    else throw std::runtime_error("ZprimePreselectionModule::ZprimePreselectionModule -- undefined \"keyword\" argument in .xml configuration file: "+keyword);
  }
  ////

  //// COMMON MODULES

  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  /* MET filters */
  metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
  if(!isMC){
    metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices");
    metfilters_sel->add<TriggerSelection>("globalTightHalo2016Filter", "Flag_globalTightHalo2016Filter");
    metfilters_sel->add<TriggerSelection>("HBHENoiseFilter", "Flag_HBHENoiseFilter");
    metfilters_sel->add<TriggerSelection>("HBHENoiseIsoFilter", "Flag_HBHENoiseIsoFilter");
    metfilters_sel->add<TriggerSelection>("EcalDeadCellTriggerPrimitiveFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter");
    if(!isMC)  metfilters_sel->add<TriggerSelection>("eeBadScFilter", "Flag_eeBadScFilter");
    metfilters_sel->add<TriggerSelection>("chargedHadronTrackResolutionFilter", "Flag_chargedHadronTrackResolutionFilter"); 
    metfilters_sel->add<TriggerSelection>("muonBadTrackFilter", "Flag_muonBadTrackFilter");
  }
  

  /******************************************************************/

  /* GEN Flavor selection [W+jets flavor-splitting] */
  if(ctx.get("dataset_version").find("WJets") != std::string::npos){

    if     (ctx.get("dataset_version").find("__B") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("b"));
    else if(ctx.get("dataset_version").find("__C") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("c"));
    else if(ctx.get("dataset_version").find("__L") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("l"));

    else genflavor_sel.reset(new uhh2::AndSelection(ctx));
  }
  else genflavor_sel.reset(new uhh2::AndSelection(ctx));
  /**************************************************/

  ////

  // Cleaning: Mu, Ele, Jets
  const MuonId muoSR(AndId<Muon>(PtEtaCut(muon_pt, 2.4), MuonID(Muon::CutBasedIdTight)));//temporary switch to TightID due to problems with MediumID in 2016 data
  const ElectronId eleSR(AndId<Electron>(PtEtaSCCut(ele_pt, 2.5), eleID));
  const JetId jetID(JetPFID(JetPFID::WP_TIGHT));


  muoSR_cleaner.reset(new MuonCleaner(muoSR));
  eleSR_cleaner.reset(new ElectronCleaner(eleSR));
  jet_IDcleaner.reset(new JetCleaner(ctx, jetID));
  jet_cleaner1.reset(new JetCleaner(ctx, 15., 3.0));
  jet_cleaner2.reset(new JetCleaner(ctx, 30., 2.4));
  topjet_IDcleaner.reset(new TopJetCleaner(ctx, jetID, "topjets"));
  topjet_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4)), "topjets"));
  topjet_puppi_IDcleaner.reset(new TopJetCleaner(ctx, jetID, "toppuppijets"));
  topjet_puppi_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4)), "toppuppijets"));

  // Jet energy corrections
  std::vector<std::string> JEC_AK4_MC, JEC_AK8_MC, JEC_AK4_MC_Puppi, JEC_AK8_MC_Puppi;
  std::vector<std::string> JEC_AK4_B,       JEC_AK4_C,       JEC_AK4_D,       JEC_AK4_E,       JEC_AK4_F;
  std::vector<std::string> JEC_AK4_B_Puppi, JEC_AK4_C_Puppi, JEC_AK4_D_Puppi, JEC_AK4_E_Puppi, JEC_AK4_F_Puppi;
  std::vector<std::string> JEC_AK8_B,       JEC_AK8_C,       JEC_AK8_D,       JEC_AK8_E,       JEC_AK8_F;
  std::vector<std::string> JEC_AK8_B_Puppi, JEC_AK8_C_Puppi, JEC_AK8_D_Puppi, JEC_AK8_E_Puppi, JEC_AK8_F_Puppi;

  JEC_AK4_B       = JERFiles::Fall17_17Nov2017_V6_B_L123_AK4PFchs_DATA;
  JEC_AK4_C       = JERFiles::Fall17_17Nov2017_V6_C_L123_AK4PFchs_DATA;
  JEC_AK4_D       = JERFiles::Fall17_17Nov2017_V6_D_L123_AK4PFchs_DATA;
  JEC_AK4_E       = JERFiles::Fall17_17Nov2017_V6_E_L123_AK4PFchs_DATA;
  JEC_AK4_F       = JERFiles::Fall17_17Nov2017_V6_F_L123_AK4PFchs_DATA;
  JEC_AK4_MC       = JERFiles::Fall17_17Nov2017_V6_L123_AK4PFchs_MC;

  JEC_AK8_B       = JERFiles::Fall17_17Nov2017_V6_B_L123_AK8PFchs_DATA;
  JEC_AK8_C       = JERFiles::Fall17_17Nov2017_V6_C_L123_AK8PFchs_DATA;
  JEC_AK8_D       = JERFiles::Fall17_17Nov2017_V6_D_L123_AK8PFchs_DATA;
  JEC_AK8_E       = JERFiles::Fall17_17Nov2017_V6_E_L123_AK8PFchs_DATA;
  JEC_AK8_F       = JERFiles::Fall17_17Nov2017_V6_F_L123_AK8PFchs_DATA;
  JEC_AK8_MC       = JERFiles::Fall17_17Nov2017_V6_L123_AK8PFchs_MC;

  JEC_AK4_B_Puppi = JERFiles::Fall17_17Nov2017_V6_B_L123_AK4PFPuppi_DATA;
  JEC_AK4_C_Puppi = JERFiles::Fall17_17Nov2017_V6_C_L123_AK4PFPuppi_DATA;
  JEC_AK4_D_Puppi = JERFiles::Fall17_17Nov2017_V6_D_L123_AK4PFPuppi_DATA;
  JEC_AK4_E_Puppi = JERFiles::Fall17_17Nov2017_V6_E_L123_AK4PFPuppi_DATA;
  JEC_AK4_F_Puppi = JERFiles::Fall17_17Nov2017_V6_F_L123_AK4PFPuppi_DATA;
  JEC_AK4_MC_Puppi = JERFiles::Fall17_17Nov2017_V6_L123_AK4PFPuppi_MC;

  JEC_AK8_B_Puppi = JERFiles::Fall17_17Nov2017_V6_B_L123_AK8PFPuppi_DATA;
  JEC_AK8_C_Puppi = JERFiles::Fall17_17Nov2017_V6_C_L123_AK8PFPuppi_DATA;
  JEC_AK8_D_Puppi = JERFiles::Fall17_17Nov2017_V6_D_L123_AK8PFPuppi_DATA;
  JEC_AK8_E_Puppi = JERFiles::Fall17_17Nov2017_V6_E_L123_AK8PFPuppi_DATA;
  JEC_AK8_F_Puppi = JERFiles::Fall17_17Nov2017_V6_F_L123_AK8PFPuppi_DATA;
  JEC_AK8_MC_Puppi = JERFiles::Fall17_17Nov2017_V6_L123_AK8PFPuppi_MC;

  jet_corrector_B.reset(new JetCorrector(ctx,             JEC_AK4_B));
  jet_corrector_C.reset(new JetCorrector(ctx,             JEC_AK4_C));
  jet_corrector_D.reset(new JetCorrector(ctx,             JEC_AK4_D));
  jet_corrector_E.reset(new JetCorrector(ctx,             JEC_AK4_E));
  jet_corrector_F.reset(new JetCorrector(ctx,             JEC_AK4_F));
  jet_corrector_MC.reset(new JetCorrector(ctx,            JEC_AK4_MC));

  topjet_corrector_B.reset(new TopJetCorrector(ctx,       JEC_AK8_B));
  topjet_corrector_C.reset(new TopJetCorrector(ctx,       JEC_AK8_C));
  topjet_corrector_D.reset(new TopJetCorrector(ctx,       JEC_AK8_D));
  topjet_corrector_E.reset(new TopJetCorrector(ctx,       JEC_AK8_E));
  topjet_corrector_F.reset(new TopJetCorrector(ctx,       JEC_AK8_F));
  topjet_corrector_MC.reset(new TopJetCorrector(ctx,      JEC_AK8_MC));

  topjet_puppi_corrector_B.reset(new GenericTopJetCorrector(ctx,  JEC_AK8_B_Puppi, "toppuppijets"));
  topjet_puppi_corrector_C.reset(new GenericTopJetCorrector(ctx,  JEC_AK8_C_Puppi, "toppuppijets"));
  topjet_puppi_corrector_D.reset(new GenericTopJetCorrector(ctx,  JEC_AK8_D_Puppi, "toppuppijets"));
  topjet_puppi_corrector_E.reset(new GenericTopJetCorrector(ctx,  JEC_AK8_E_Puppi, "toppuppijets"));
  topjet_puppi_corrector_F.reset(new GenericTopJetCorrector(ctx,  JEC_AK8_F_Puppi, "toppuppijets"));
  topjet_puppi_corrector_MC.reset(new GenericTopJetCorrector(ctx, JEC_AK8_MC_Puppi, "toppuppijets"));

  topjet_subjet_corrector_B.reset(new SubJetCorrector(ctx,               JEC_AK4_B));
  topjet_subjet_corrector_C.reset(new SubJetCorrector(ctx,               JEC_AK4_C));
  topjet_subjet_corrector_D.reset(new SubJetCorrector(ctx,               JEC_AK4_D));
  topjet_subjet_corrector_E.reset(new SubJetCorrector(ctx,               JEC_AK4_E));
  topjet_subjet_corrector_F.reset(new SubJetCorrector(ctx,               JEC_AK4_F));
  topjet_subjet_corrector_MC.reset(new SubJetCorrector(ctx,              JEC_AK4_MC));

  topjet_puppi_subjet_corrector_B.reset(new GenericSubJetCorrector(ctx,  JEC_AK4_B_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_C.reset(new GenericSubJetCorrector(ctx,  JEC_AK4_C_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_D.reset(new GenericSubJetCorrector(ctx,  JEC_AK4_D_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_E.reset(new GenericSubJetCorrector(ctx,  JEC_AK4_E_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_F.reset(new GenericSubJetCorrector(ctx,  JEC_AK4_F_Puppi, "toppuppijets"));
  topjet_puppi_subjet_corrector_MC.reset(new GenericSubJetCorrector(ctx, JEC_AK4_MC_Puppi, "toppuppijets"));

  JLC_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_B));
  JLC_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_C));
  JLC_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_D));
  JLC_E.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_E));
  JLC_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,           JEC_AK4_F));
  JLC_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,          JEC_AK4_MC));

  TopJLC_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,        JEC_AK8_B, "topjets"));
  TopJLC_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,        JEC_AK8_C, "topjets"));
  TopJLC_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx,        JEC_AK8_D, "topjets"));
  TopJLC_E.reset(new JetLeptonCleaner_by_KEYmatching(ctx,        JEC_AK8_E, "topjets"));
  TopJLC_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,        JEC_AK8_F, "topjets"));
  TopJLC_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8_MC, "topjets"));

  TopJLC_puppi_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,  JEC_AK8_B_Puppi, "toppuppijets"));
  TopJLC_puppi_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,  JEC_AK8_C_Puppi, "toppuppijets"));
  TopJLC_puppi_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx,  JEC_AK8_D_Puppi, "toppuppijets"));
  TopJLC_puppi_E.reset(new JetLeptonCleaner_by_KEYmatching(ctx,  JEC_AK8_E_Puppi, "toppuppijets"));
  TopJLC_puppi_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,  JEC_AK8_F_Puppi, "toppuppijets"));
  TopJLC_puppi_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK8_MC_Puppi, "toppuppijets"));

  if(isMC){
    ctx.declare_event_input<std::vector<Particle> >(ctx.get("TopJetCollectionGEN"), "topjetsGEN");
    JER_smearer.reset(new JetResolutionSmearer(ctx, JERSmearing::SF_13TeV_Summer16_25nsV1));
    TopJER_smearer.reset(new GenericJetResolutionSmearer(ctx, "topjets", "topjetsGEN", JERSmearing::SF_13TeV_Summer16_25nsV1, "Fall17_25nsV1_MC_PtResolution_AK8PFchs.txt"));
    TopJER_puppi_smearer.reset(new GenericJetResolutionSmearer(ctx, "toppuppijets", "topjetsGEN", JERSmearing::SF_13TeV_Summer16_25nsV1, "Fall17_25nsV1_MC_PtResolution_AK8PFPuppi.txt"));
  }

  
 







  //// EVENT SELECTION
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));

  met_sel  .reset(new METCut  (MET   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));

  if(use_miniiso) twodcut_sel.reset(new TwoDCut1(-1, 20.));
  //  else            twodcut_sel.reset(new TwoDCut1(.4, 40.));
  else            twodcut_sel.reset(new TwoDCut1(twod1, twod2));

  ////

  //// HISTS
  std::vector<std::string> htags_1({

    "lep1",
    "jet2",
    "jet1",
    "met",
    "htlep",
    "jetlepcleaning_before",
    "jetlepcleaning_after",
    "twodcut",
    "lep_eff_sig",
    "lep_eff_bkg"
  });

  for(const auto& tag : htags_1){

    //book_HFolder(tag, new TTbarLJHists(ctx, tag));
     book_HFolder(tag, new TTbarLJHistsSkimming(ctx,tag));
  }
  ////

  lumihists.reset(new LuminosityHists(ctx, "lumi"));
}








bool ZprimePreselectionModule::process(uhh2::Event& event){

  // Lumi selection
  if(event.isRealData){
    if(!lumi_sel->passes(event)) return false;
    lumihists->fill(event);
  }

  // MET filters
  if(!metfilters_sel->passes(event)) return false;
 
  // GEN ME quark-flavor selection
  if(!event.isRealData){
    if(!genflavor_sel->passes(event)) return false;
  }


  //// LEPTON selection

  muoSR_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  eleSR_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  const bool pass_lep1 = ((event.muons->size() >= 1) || (event.electrons->size() >= 1));
  if(!pass_lep1) return false;
  HFolder("lep1")->fill(event);
  ////

 
  //// JET selection
  jet_IDcleaner->process(event);

  if(event.isRealData){
    bool apply_B = false;
    bool apply_C = false;
    bool apply_D = false;
    bool apply_E = false;
    bool apply_F = false;
    if(event.run <= s_runnr_B)  apply_B = true;
    else if(event.run <= s_runnr_C) apply_C = true; //< is correct, not <=
    else if(event.run <= s_runnr_D) apply_D = true; 
    else if(event.run <= s_runnr_E) apply_E = true;
    else if(event.run <= s_runnr_F) apply_F = true;
    else throw std::runtime_error("run number not covered by if-statements in process-routine.");

    if(apply_B+apply_C+apply_D+apply_E+apply_F != 1) throw std::runtime_error("In ZprimePreselectionModule.cxx: Sum of apply_* when applying JECs is not == 1. Fix this.");
    HFolder("jetlepcleaning_before")->fill(event);
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
    if(apply_D){
      JLC_D->process(event); 
      TopJLC_D->process(event); 
      TopJLC_puppi_D->process(event); 
      jet_corrector_D->process(event);
      topjet_corrector_D->process(event);
      topjet_puppi_corrector_D->process(event);
      jet_corrector_D->correct_met(event);
      topjet_subjet_corrector_D->process(event);
      topjet_puppi_subjet_corrector_D->process(event);
    }
    if(apply_E){
      JLC_E->process(event); 
      TopJLC_E->process(event); 
      TopJLC_puppi_E->process(event); 
      jet_corrector_E->process(event);
      topjet_corrector_E->process(event);
      topjet_puppi_corrector_E->process(event);
      jet_corrector_E->correct_met(event);
      topjet_subjet_corrector_E->process(event);
      topjet_puppi_subjet_corrector_E->process(event);
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

  jet_cleaner1->process(event);
  sort_by_pt<Jet>(*event.jets);
  HFolder("jetlepcleaning_after")->fill(event);

  
  // Lepton-2Dcut variables
  const bool pass_twodcut = twodcut_sel->passes(event); {

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
  }

  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);

  topjet_IDcleaner->process(event);
  topjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

  topjet_puppi_IDcleaner->process(event);
  topjet_puppi_cleaner->process(event);
  sort_by_pt<TopJet>(*event.toppuppijets);

  // 1st AK4 jet selection
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  HFolder("jet1")->fill(event);

  // 2nd AK4 jet selection 
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  HFolder("jet2")->fill(event);

  // MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  HFolder("met")->fill(event);

  // ST_lep selection
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  HFolder("htlep")->fill(event);
  
  // Lepton-2Dcut selection
  if(!pass_twodcut) return false;
  HFolder("twodcut")->fill(event);

  // // GEN matching for the electron ID studies
  // if(!event.isRealData){
  //   const auto& ttgen = event.get(h_ttbar_gen);
  //   if(ttgen.IsSemiLeptonicDecay()){
  //     //    GenParticle lep =  ttgen.ChargedLepton();
  //     for(auto& ele : *event.electrons){
  // 	double dR_gen_rec_lep = uhh2::deltaR(ele, ttgen.ChargedLepton()); //<0.1
  // 	double pt_diff = fabs(ele.pt()-ttgen.ChargedLepton().pt())/ttgen.ChargedLepton().pt(); //<0.3
  // 	if(dR_gen_rec_lep<0.1 && pt_diff<0.3 && (ttgen.ChargedLepton().charge()*ele.charge())>0 && fabs(ttgen.ChargedLepton().pdgId())==11){
  // 	  HFolder("lep_eff_sig")->fill(event);
  // 	}
  // 	else
  // 	  HFolder("lep_eff_bkg")->fill(event);
  //     }
  //   }
  //   else
  //     HFolder("lep_eff_bkg")->fill(event);
  // }
    // std::cout<<"####END N_ele = "<<event.electrons->size()<<" N_muo = "<<event.muons->size()<<" N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<" met = "<<event.met->pt()<<" raw_met = "<<event.met->uncorr_v4().Pt()<<std::endl;
    // std::cout<<""<<std::endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimePreselectionModule)
