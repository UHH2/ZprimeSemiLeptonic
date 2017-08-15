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

class TTbarLJSkimmingModule : public ModuleBASE {

 public:
  explicit TTbarLJSkimmingModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:

  // cleaners
  std::unique_ptr<MuonCleaner>     muoSR_cleaner;
  std::unique_ptr<ElectronCleaner> eleSR_cleaner;

  std::unique_ptr<TopJetCorrector> topjet_corrector;
  std::unique_ptr<GenericTopJetCorrector> toppuppijet_corrector;

  std::unique_ptr<JetCleaner>                      jet_IDcleaner;
  //split corrections by run periods 
  std::unique_ptr<JetCorrector>                    jet_corrector, jet_corrector_BCD, jet_corrector_EFearly, jet_corrector_FlateG, jet_corrector_H;
  std::unique_ptr<GenericJetResolutionSmearer>     jetER_smearer;
  //split cleaners by run periods 
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> jetlepton_cleaner, JLC_BCD, JLC_EFearly, JLC_FlateG, JLC_H;
  //  std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner, JLC_BCD, JLC_EFearly, JLC_FlateG, JLC_H;//TEST

  std::unique_ptr<JetCleaner>                      jet_cleaner1;
  std::unique_ptr<JetCleaner>                      jet_cleaner2;
  std::unique_ptr<TopJetCleaner>                  topjet_IDcleaner;
  std::unique_ptr<SubJetCorrector>             topjet_subjet_corrector, topjet_subjet_corrector_BCD, topjet_subjet_corrector_EF, topjet_subjet_corrector_G, topjet_subjet_corrector_H;
  std::unique_ptr<GenericJetResolutionSmearer> topjetER_smearer;
  //  std::unique_ptr<TopJetLeptonDeltaRCleaner>   topjetlepton_cleaner;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> topjetlepton_cleaner;
  std::unique_ptr<TopJetCleaner>               topjet_cleaner;

  std::unique_ptr<TopJetCleaner>               toppuppijet_IDcleaner;
  std::unique_ptr<GenericSubJetCorrector>      toppuppijet_subjet_corrector, toppuppijet_subjet_corrector_BCD, toppuppijet_subjet_corrector_EF, toppuppijet_subjet_corrector_G, toppuppijet_subjet_corrector_H;
  std::unique_ptr<GenericJetResolutionSmearer> toppuppijetER_smearer;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> toppuppijetlepton_cleaner;
  std::unique_ptr<TopJetCleaner>               toppuppijet_cleaner;

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel;
  //  std::unique_ptr<uhh2::AndSelection> metantifilters_sel;

  std::unique_ptr<uhh2::Selection> genmttbar_sel;
  std::unique_ptr<uhh2::Selection> genflavor_sel;

  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> twodcut_sel;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  uhh2::Event::Handle<TTbarGen> h_ttbar_gen;

  //run numbers for different jet corrections
  const int runnr_BCD = 276811;
  const int runnr_EF = 278802;
  const int runnr_G = 280385;
  bool isMC;

  Event::Handle<float> tt_TMVA_response;// response of TMVA method, dummy value at this step
  Event::Handle<float> wjets_TMVA_response;     // response of TMVA method, dummy value at this step
  Event::Handle<float> H_Rec_chi2;     
  Event::Handle<float>    h_lep1__pTrel_jet_norm;     //11                                                                                                            
  Event::Handle<float>    h_ht_met_lep_norm;          //12                                                                                                            
  Event::Handle<float>    h_jet1_csv;                //13                                                                                                             
  Event::Handle<float>    h_jet2_csv;                //14                                                                                                             
  Event::Handle<float>    h_DRpt;                     //15                                                                                                            
  Event::Handle<float>    h_njets;                    //16                                                                                                            
  Event::Handle<float>    h_jet1_m;                  //17                                                                                                             
  Event::Handle<float>    h_jet2_m;                  //18                                                                                                             
  Event::Handle<float>    h_lep1__minDR_norm;   //19                                                                                                                  
  Event::Handle<float> h_s33;                      

  bool isQCDstudy;
  std::unique_ptr<Hists> lumihists;
  std::string METcollection;
  //Runnumbers for applying different corrections
  constexpr static int s_runnr_BCD     = 276811; //up to this one, including this one
  constexpr static int s_runnr_EFearly = 278802; //up to this one, EXCLUDING this one
  constexpr static int s_runnr_Fearly  = 278802; //up to this one, EXCLUDING this one
  constexpr static int s_runnr_FlateG  = 280385; //up to this one, including this one

};

TTbarLJSkimmingModule::TTbarLJSkimmingModule(uhh2::Context& ctx){

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
    eleID  = ElectronID_Spring16_tight_noIso;
    //    eleID = ElectronID_MVAGeneralPurpose_Spring16_loose; //The best signal/bkg performance in 2016  
    //    eleID = ElectronID_HEEP_RunII_25ns; //TEST
    //    eleID = ElectronID_Spring16_medium_noIso;         
    use_miniiso = false;
    jet1_pt = 50.;
    jet2_pt =  20.;

    //    MET     =  50.;
    MET     =   0.;
    HT_lep  =   0.;
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
    eleID = ElectronID_MVAGeneralPurpose_Spring16_loose;
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
      eleID = ElectronID_MVAGeneralPurpose_Spring16_tight;                                                      
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
      eleID = ElectronID_MVAGeneralPurpose_Spring16_loose;
      use_miniiso = false;
      jet1_pt = 0.;
      jet2_pt = 0.; 
      MET     = 50.;
      // MET     = 0.;
      HT_lep  = 0.;
      twod1 = _twod1;
      twod2 = _twod2;
    }       
    else throw std::runtime_error("TTbarLJSkimmingModule::TTbarLJSkimmingModule -- undefined \"keyword\" argument in .xml configuration file: "+keyword);
  }
  ////

  //// COMMON MODULES

  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  /* MET filters */
  metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
  metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices");
  metfilters_sel->add<TriggerSelection>("globalTightHalo2016Filter", "Flag_globalTightHalo2016Filter");
  metfilters_sel->add<TriggerSelection>("HBHENoiseFilter", "Flag_HBHENoiseFilter");
  metfilters_sel->add<TriggerSelection>("HBHENoiseIsoFilter", "Flag_HBHENoiseIsoFilter");
  metfilters_sel->add<TriggerSelection>("EcalDeadCellTriggerPrimitiveFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter");
  //  metfilters_sel->add<TriggerSelection>("eeBadScFilter", "Flag_eeBadScFilter");
  metfilters_sel->add<TriggerSelection>("chargedHadronTrackResolutionFilter", "Flag_chargedHadronTrackResolutionFilter"); 
  metfilters_sel->add<TriggerSelection>("muonBadTrackFilter", "Flag_muonBadTrackFilter");
  

  /**********************************/
  
  /* GEN M-ttbar selection [TTbar MC "0.<M^{gen}_{ttbar}(GeV)<700.] */
  const std::string ttbar_gen_label("ttbargen");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));
  h_ttbar_gen = ctx.get_handle<TTbarGen>   (ttbar_gen_label);

  if(ctx.get("dataset_version") == "TTbar_Mtt0000to0700") genmttbar_sel.reset(new MttbarGenSelection( 0., 700.));
  else                                                    genmttbar_sel.reset(new uhh2::AndSelection(ctx));
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

  //// OBJ CLEANING
  //  const     MuonId muoSR(AndId<Muon>    (PtEtaCut  (muon_pt   , 2.1), MuonIDMedium()));
  const     MuonId muoSR(AndId<Muon>    (PtEtaCut  (muon_pt   , 2.1), MuonIDTight()));//temporary switch to TightID due to problems with MediumID in 2016 data
  //  const     MuonId muoSR(AndId<Muon>    (PtEtaCut  (muon_pt   , 2.1), MuonIDLoose()));//temporary switch to LooseID due to problems with MediumID in 2016 data
  const ElectronId eleSR(AndId<Electron>(PtEtaSCCut(ele_pt, 2.5), eleID));
  //  const ElectronId eleSR(PtEtaSCCut(ele_pt, 2.5));//TEST: WITHOUT ELECTRON ID (for denominator of electron ID studies)
  muoSR_cleaner.reset(new     MuonCleaner(muoSR));
  eleSR_cleaner.reset(new ElectronCleaner(eleSR));
  //

  //  const JetId jetID(JetPFID(JetPFID::WP_LOOSE));
  const JetId jetID(JetPFID(JetPFID::WP_TIGHT));

  std::vector<std::string> JEC_AK4, JEC_AK8;
  std::vector<std::string> JEC_corr,       JEC_corr_BCD,       JEC_corr_EFearly,       JEC_corr_FlateG,       JEC_corr_H,      JEC_corr_MC_FlateGH;
  std::vector<std::string> JEC_AK4_Puppi, JEC_AK8_Puppi, JEC_corr_BCD_Puppi, JEC_corr_EFearly_Puppi, JEC_corr_FlateG_Puppi, JEC_corr_H_Puppi;
  if(isMC){
    JEC_AK4 = JERFiles::Summer16_23Sep2016_V4_L123_AK4PFchs_MC;
    JEC_AK8 = JERFiles::Summer16_23Sep2016_V4_L123_AK8PFchs_MC;
    JEC_corr = JERFiles::Summer16_23Sep2016_V4_L123_AK4PFchs_MC;

    JEC_AK4_Puppi = JERFiles::Summer16_23Sep2016_V4_L123_AK4PFPuppi_MC;
    JEC_AK8_Puppi = JERFiles::Summer16_23Sep2016_V4_L123_AK8PFPuppi_MC;
  }
  else {
    JEC_AK4 = JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFchs_DATA;
    JEC_AK8 = JERFiles::Summer16_23Sep2016_V4_H_L123_AK8PFchs_DATA;
    JEC_corr = JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFchs_DATA;  //ReReco Data + Moriond17 MC
    JEC_corr_BCD          = JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFchs_DATA;
    JEC_corr_EFearly      = JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFchs_DATA;
    JEC_corr_FlateG       = JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFchs_DATA;
    JEC_corr_H            = JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFchs_DATA;

    JEC_AK4_Puppi = JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFPuppi_DATA;
    JEC_AK8_Puppi = JERFiles::Summer16_23Sep2016_V4_H_L123_AK8PFPuppi_DATA;
    JEC_corr_BCD_Puppi          = JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFPuppi_DATA;
    JEC_corr_EFearly_Puppi      = JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFPuppi_DATA;
    JEC_corr_FlateG_Puppi       = JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFPuppi_DATA;
    JEC_corr_H_Puppi            = JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFPuppi_DATA;
  }

  jet_IDcleaner.reset(new JetCleaner(ctx, jetID));
  if(!isMC){
    jet_corrector_BCD.reset(new JetCorrector(ctx, JEC_corr_BCD));
    jet_corrector_EFearly.reset(new JetCorrector(ctx, JEC_corr_EFearly));
    jet_corrector_FlateG.reset(new JetCorrector(ctx, JEC_corr_FlateG));
    jet_corrector_H.reset(new JetCorrector(ctx, JEC_corr_H));
    JLC_BCD.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_corr_BCD));
    JLC_EFearly.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_corr_EFearly));
    JLC_FlateG.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_corr_FlateG));
    JLC_H.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_corr_H));
    /*    JLC_BCD.reset(new JetLeptonCleaner(ctx, JEC_corr_BCD));
    JLC_EFearly.reset(new JetLeptonCleaner(ctx, JEC_corr_EFearly));
    JLC_FlateG.reset(new JetLeptonCleaner(ctx, JEC_corr_FlateG));
    JLC_H.reset(new JetLeptonCleaner(ctx, JEC_corr_H));*/
    topjet_subjet_corrector_BCD.reset(new SubJetCorrector(ctx, JEC_corr_BCD));
    topjet_subjet_corrector_EF.reset(new SubJetCorrector(ctx, JEC_corr_EFearly));
    topjet_subjet_corrector_G.reset(new SubJetCorrector(ctx, JEC_corr_FlateG));
    topjet_subjet_corrector_H.reset(new SubJetCorrector(ctx, JEC_corr_H));

    toppuppijet_subjet_corrector_BCD.reset(new GenericSubJetCorrector(ctx, JEC_corr_BCD, "toppuppijets"));
    toppuppijet_subjet_corrector_EF.reset(new GenericSubJetCorrector(ctx, JEC_corr_EFearly, "toppuppijets"));
    toppuppijet_subjet_corrector_G.reset(new GenericSubJetCorrector(ctx, JEC_corr_FlateG, "toppuppijets"));
    toppuppijet_subjet_corrector_H.reset(new GenericSubJetCorrector(ctx, JEC_corr_H, "toppuppijets"));

  }
  if(isMC){
    jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
    jetlepton_cleaner.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4));
    //    jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JEC_AK4));//TEST
    jetER_smearer.reset(new GenericJetResolutionSmearer(ctx));
    topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
    topjet_subjet_corrector.reset(new SubJetCorrector(ctx, JEC_AK4));
    ctx.declare_event_input<std::vector<Particle> >(ctx.get("TopJetCollectionGEN"), "topjetsGEN");
    topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "topjets", "topjetsGEN", false));

    toppuppijet_corrector.reset(new GenericTopJetCorrector(ctx, JEC_AK8_Puppi, "toppuppijets"));
    toppuppijet_subjet_corrector.reset(new GenericSubJetCorrector(ctx, JEC_AK4, "toppuppijets"));
    toppuppijetER_smearer.reset(new GenericJetResolutionSmearer(ctx, "toppuppijets", "topjetsGEN", false));

  }
 
  jet_cleaner1.reset(new JetCleaner(ctx, 15., 3.0));
  jet_cleaner2.reset(new JetCleaner(ctx, 30., 2.4));

  topjet_IDcleaner.reset(new TopJetCleaner(ctx, jetID, "topjets"));
  topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
  //topjet_subjet_corrector.reset(new SubJetCorrector(ctx, JEC_AK4)); //ToDo
  topjetlepton_cleaner.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK8, "topjets"));
  topjet_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4))));

  toppuppijet_IDcleaner.reset(new TopJetCleaner(ctx, jetID, "toppuppijets"));
  toppuppijet_corrector.reset(new GenericTopJetCorrector(ctx, JEC_AK8_Puppi, "toppuppijets"));
  toppuppijetlepton_cleaner.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK8, "toppuppijets"));
  toppuppijet_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4)), "toppuppijets"));
  //// EVENT SELECTION
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));

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

  // tt_TMVA_response = ctx.declare_event_output<float>("TMVA_response");
  // wjets_TMVA_response = ctx.declare_event_output<float>("WJets_TMVA_response");
  // H_Rec_chi2 = ctx.declare_event_output<float>("H_Rec_chi2");     
  // //W+Jets MVA related                                                                                                                                                
  // h_s33             = ctx.declare_event_output<float>("s33");                                                                                                         
  // //h_jet2_pt          = ctx.declare_event_output<float>          ("jet2_pt");  
  // h_ht_met_lep_norm   = ctx.declare_event_output<float>          ("ht_met_lep_norm");
  // h_jet1_csv         = ctx.declare_event_output<float>           ("jet1_csv");
  // h_jet2_csv         = ctx.declare_event_output<float>           ("jet2_csv");
  // h_njets             = ctx.declare_event_output<float>             ("njets");
  // h_DRpt              = ctx.declare_event_output<float>           ("DRpt");
  // h_lep1__pTrel_jet_norm = ctx.declare_event_output<float>         ("lep1__pTrel_jet_norm");
  // h_jet1_m         = ctx.declare_event_output<float>("jet1_m");                                                                           
  // //  h_lep1__minDR_norm = ctx.declare_event_output<float>("lep1__minDR_jet");
  // h_lep1__minDR_norm = ctx.declare_event_output<float>("lep1__minDR_norm");
  // h_jet2_m         = ctx.declare_event_output<float>("jet2_m");
}

bool TTbarLJSkimmingModule::process(uhh2::Event& event){
 //  std::cout<<" -------------------------- "<<std::endl;
 //  std::cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " <<std::endl;
 // std::cout<<"####BEGIN N_ele = "<<event.electrons->size()<<" N_muo = "<<event.muons->size()<<" N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<" met = "<<event.met->pt()<<" raw_met = "<<event.met->uncorr_v4().Pt()<<std::endl;

  // event.set(tt_TMVA_response,-100);//fill with dummy value
  // event.set(wjets_TMVA_response, -100);//fill with dummy value 
  // event.set(H_Rec_chi2,-100);                                                                                                                                         
  // event.set(h_jet1_m,-100);                                                                                                                                           
  // event.set(h_jet1_csv,-100);                                                                                                                                         
  // event.set(h_jet2_m,-100);                                                                                                                                           
  // event.set(h_jet2_csv,-100);                                                                                                                                         
  // event.set(h_njets,-100);                                                                                                                                            
  // event.set(h_ht_met_lep_norm,-100);                                                                                                                                  
  // event.set(h_lep1__pTrel_jet_norm,-100);                                                                                                                             
  // event.set(h_lep1__minDR_norm,-100);                                                                                                                                 
  // event.set(h_s33,-100);                                                                                                                                              
  // event.set(h_DRpt,-100);                                                                                                                                               
  // event.set(h_jet1pt_chi2,0);                                                                                                                                      
  // event.set(h_mttbar_chi2,0);            
  //// COMMON MODULES

  /* CMS-certified luminosity sections */
  if(event.isRealData){
    if(!lumi_sel->passes(event)) return false;
    lumihists->fill(event);
  }

  /* MET filters  */
  if(!metfilters_sel->passes(event)) return false;
  //  if(metantifilters_sel->passes(event)) return false;
 
  ////
  if(!event.isRealData){

    /* GEN M-ttbar selection */
    ttgenprod->process(event);
    if(!genmttbar_sel->passes(event)) return false;

    /* GEN ME quark-flavor selection */
    if(!genflavor_sel->passes(event)) return false;
    //    std::cout<<"genflavor_sel OK!"<<std::endl;
  }

  

  //// LEPTON selection

  muoSR_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  eleSR_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);
  //const bool pass_lep1 = (event.electrons->size() == 1);
  const bool pass_lep1 = ((event.muons->size() >= 1) || (event.electrons->size() >= 1));
  if(!pass_lep1) return false;
  HFolder("lep1")->fill(event);
  ////

 
  //// JET selection
  jet_IDcleaner->process(event);
  //  std::cout<<"####After jet_IDcleaner, N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<std::endl;

  if(event.isRealData){
    bool apply_BCD = false;
    bool apply_EFearly = false;
    bool apply_FlateG = false;
    bool apply_H = false;
    bool apply_global = false;
    if(event.run <= s_runnr_BCD)  apply_BCD = true;
    else if(event.run < s_runnr_EFearly) apply_EFearly = true; //< is correct, not <=
    else if(event.run <= s_runnr_FlateG) apply_FlateG = true; 
    else if(event.run > s_runnr_FlateG) apply_H = true;
    else throw std::runtime_error("run number not covered by if-statements in process-routine.");

    if(apply_BCD+apply_EFearly+apply_FlateG+apply_H+apply_global != 1) throw std::runtime_error("In TestModule.cxx: Sum of apply_* when applying JECs is not == 1. Fix this.");

    //apply proper JECs
    if(apply_BCD){
      bool jlc_sw =  JLC_BCD->process(event);
      jet_corrector_BCD->process(event);
      jet_corrector_BCD->correct_met(event);
      //    bool jlc_sw =  JLC_BCD->process(event); //TEST JLC order
      topjet_subjet_corrector_BCD->process(event);
      toppuppijet_subjet_corrector_BCD->process(event);
    }
    if(apply_EFearly){
      bool jlc_sw = JLC_EFearly->process(event);
      jet_corrector_EFearly->process(event);
      jet_corrector_EFearly->correct_met(event);
      //bool jlc_sw =  JLC_BCD->process(event); //TEST JLC order
      topjet_subjet_corrector_EF->process(event);
      toppuppijet_subjet_corrector_EF->process(event);
    }
    if(apply_FlateG){
      bool jlc_sw = JLC_FlateG->process(event);
      jet_corrector_FlateG->process(event);
      jet_corrector_FlateG->correct_met(event);
      // bool jlc_sw =  JLC_BCD->process(event); //TEST JLC order
      topjet_subjet_corrector_G->process(event);
      toppuppijet_subjet_corrector_G->process(event);
    }
    if(apply_H){
      bool jlc_sw = JLC_H->process(event);
      jet_corrector_H->process(event);
      jet_corrector_H->correct_met(event);
      //    bool jlc_sw =  JLC_BCD->process(event); //TEST JLC order
      topjet_subjet_corrector_H->process(event);
      toppuppijet_subjet_corrector_H->process(event);
    }
  }
  else{ //MC
    bool jlc_sw = jetlepton_cleaner->process(event); //TEST without JLC
    jet_corrector->process(event);
    //Apply JER to all jet collections
    if(jetER_smearer.get()) jetER_smearer->process(event);  
    //correct MET only AFTER smearing the jets
    jet_corrector->correct_met(event);
    topjet_subjet_corrector->process(event);
    toppuppijet_subjet_corrector->process(event);
  }
  //  std::cout<<"####After JLC, N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<std::endl;
  jet_cleaner1->process(event);
  sort_by_pt<Jet>(*event.jets);
  //  std::cout<<"####After jet_cleaner1, N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<std::endl;
  
  /* lepton-2Dcut variables */
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

  //  if(!pass_twodcut){};//place holder

  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);
  //  std::cout<<"####After jet_cleaner2, N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<std::endl;

  topjet_IDcleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

  topjetlepton_cleaner->process(event);
  topjet_corrector->process(event);
  //  topjet_subjet_corrector->process(event);
  if(topjetER_smearer.get()) topjetER_smearer->process(event);
  topjet_cleaner->process(event);

  //toppuppijet_IDcleaner->process(event);
  toppuppijetlepton_cleaner->process(event);
  toppuppijet_corrector->process(event);
  if(toppuppijetER_smearer.get()) toppuppijetER_smearer->process(event);
  toppuppijet_cleaner->process(event);

  sort_by_pt<TopJet>(*event.topjets);
  sort_by_pt<TopJet>(*event.toppuppijets);

  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  HFolder("jet2")->fill(event);

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  HFolder("jet1")->fill(event);
  ////


  //// MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  HFolder("met")->fill(event);
  ////

  //// HT_lep selection
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  HFolder("htlep")->fill(event);
  ////
  
  //// LEPTON-2Dcut selection
  if(!pass_twodcut) return false;
  HFolder("twodcut")->fill(event);
  ////

  /* GEN matching for the electron ID studies */
  if(!event.isRealData){
    const auto& ttgen = event.get(h_ttbar_gen);
    if(ttgen.IsSemiLeptonicDecay()){
      //    GenParticle lep =  ttgen.ChargedLepton();
      for(auto& ele : *event.electrons){
	double dR_gen_rec_lep = uhh2::deltaR(ele, ttgen.ChargedLepton()); //<0.1
	double pt_diff = fabs(ele.pt()-ttgen.ChargedLepton().pt())/ttgen.ChargedLepton().pt(); //<0.3
	if(dR_gen_rec_lep<0.1 && pt_diff<0.3 && (ttgen.ChargedLepton().charge()*ele.charge())>0 && fabs(ttgen.ChargedLepton().pdgId())==11){
	  HFolder("lep_eff_sig")->fill(event);
	}
	else
	  HFolder("lep_eff_bkg")->fill(event);
      }
    }
    else
      HFolder("lep_eff_bkg")->fill(event);
  }
    // std::cout<<"####END N_ele = "<<event.electrons->size()<<" N_muo = "<<event.muons->size()<<" N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<" met = "<<event.met->pt()<<" raw_met = "<<event.met->uncorr_v4().Pt()<<std::endl;
    // std::cout<<""<<std::endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TTbarLJSkimmingModule)
