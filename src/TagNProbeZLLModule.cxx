#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/CommonModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>

#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_elec.h>

class TagNProbeZLLModule: public AnalysisModule {

 public:
  explicit TagNProbeZLLModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

  enum lepton { muon, elec };
  lepton channel_;

 private:    
  // cleaners
  std::unique_ptr<MuonCleaner>     muo_cleaner;
  std::unique_ptr<ElectronCleaner> ele_cleaner;

  std::unique_ptr<JetCleaner>                      jet_IDcleaner;
  std::unique_ptr<JetCorrector>                    jet_corrector;
  std::unique_ptr<GenericJetResolutionSmearer>     jetER_smearer;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> jetlepton_cleaner;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt015_eta3p0;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt020_eta3p0;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt025_eta3p0;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt030_eta2p4;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt050_eta2p4;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt070_eta2p4;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt100_eta2p4;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt150_eta2p4;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt200_eta2p4;
  std::unique_ptr<JetCleaner>           jet_cleaner__pt250_eta2p4;

  // selections
  std::unique_ptr<Selection>    lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel;
  std::unique_ptr<AndSelection> lep2_sel;
  std::unique_ptr<Selection>    jet2_sel;
  std::unique_ptr<Selection>    jet1_sel;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  std::unique_ptr<uhh2::Selection> genmttbar_sel;

  //// Data/MC scale factors
  std::unique_ptr<uhh2::AnalysisModule> pileupSF;

  std::unique_ptr<uhh2::AnalysisModule> muonID_SF;

  std::unique_ptr<weightcalc_elecID>  elecIDSF;
//!!  std::unique_ptr<weightcalc_elecHLT> elecHLTSF;
  ////

  // Tag-N-Probe variables
  Event::Handle<float> h_MCweight;

  std::vector<std::string> HLT_paths_;
  std::unordered_map<std::string, Event::Handle<bool>> h_HLT;

  Event::Handle<int>   h_run;
  Event::Handle<int>   h_lumi_block;
  Event::Handle<int>   h_event;
  Event::Handle<int>   h_pvN;

  Event::Handle<float> h_MET__pt;
  Event::Handle<float> h_MET__phi;

  Event::Handle<int>   h_jetN__pt015_eta3p0;
  Event::Handle<int>   h_jetN__pt020_eta3p0;
  Event::Handle<int>   h_jetN__pt025_eta3p0;
  Event::Handle<int>   h_jetN__pt030_eta2p4;
  Event::Handle<int>   h_jetN__pt050_eta2p4;
  Event::Handle<int>   h_jetN__pt070_eta2p4;
  Event::Handle<int>   h_jetN__pt100_eta2p4;
  Event::Handle<int>   h_jetN__pt150_eta2p4;
  Event::Handle<int>   h_jetN__pt200_eta2p4;
  Event::Handle<int>   h_jetN__pt250_eta2p4;

  Event::Handle<float> h_ZLL__M;
  Event::Handle<float> h_ZLL__pt;
  Event::Handle<float> h_ZLL__eta;
  Event::Handle<float> h_ZLL__phi;

  Event::Handle<int>   h_TAG__charge;
  Event::Handle<float> h_TAG__M;
  Event::Handle<float> h_TAG__pt;
  Event::Handle<float> h_TAG__eta;
  Event::Handle<float> h_TAG__etaSC;
  Event::Handle<float> h_TAG__phi;
  Event::Handle<float> h_TAG__pfIso_rhoEA;
  Event::Handle<float> h_TAG__pfIso_dbeta;
  Event::Handle<float> h_TAG__pfMINIIso_dbeta;
  Event::Handle<float> h_TAG__minDR_pt015_eta3p0;
  Event::Handle<float> h_TAG__minDR_pt020_eta3p0;
  Event::Handle<float> h_TAG__minDR_pt025_eta3p0;
  Event::Handle<float> h_TAG__minDR_pt030_eta2p4;
  Event::Handle<float> h_TAG__minDR_pt050_eta2p4;
  Event::Handle<float> h_TAG__pTrel_pt015_eta3p0;
  Event::Handle<float> h_TAG__pTrel_pt020_eta3p0;
  Event::Handle<float> h_TAG__pTrel_pt025_eta3p0;
  Event::Handle<float> h_TAG__pTrel_pt030_eta2p4;
  Event::Handle<float> h_TAG__pTrel_pt050_eta2p4;
  Event::Handle<bool>  h_TAG__MuonIDLoose;
  Event::Handle<bool>  h_TAG__MuonIDMedium;
  Event::Handle<bool>  h_TAG__MuonIDTight;
  Event::Handle<bool>  h_TAG__ElecIDcutbasedL;
  Event::Handle<bool>  h_TAG__ElecIDcutbasedM;
  Event::Handle<bool>  h_TAG__ElecIDcutbasedT;
  Event::Handle<bool>  h_TAG__ElecIDmvaNonTrigL;
  Event::Handle<bool>  h_TAG__ElecIDmvaNonTrigT;
  Event::Handle<bool>  h_TAG__ElecIDmvaTrigL;
  Event::Handle<bool>  h_TAG__ElecIDmvaTrigT;

  Event::Handle<int>   h_PRO__charge;
  Event::Handle<float> h_PRO__M;
  Event::Handle<float> h_PRO__pt;
  Event::Handle<float> h_PRO__eta;
  Event::Handle<float> h_PRO__etaSC;
  Event::Handle<float> h_PRO__phi;
  Event::Handle<float> h_PRO__pfIso_rhoEA;
  Event::Handle<float> h_PRO__pfIso_dbeta;
  Event::Handle<float> h_PRO__pfMINIIso_dbeta;
  Event::Handle<float> h_PRO__minDR_pt015_eta3p0;
  Event::Handle<float> h_PRO__minDR_pt020_eta3p0;
  Event::Handle<float> h_PRO__minDR_pt025_eta3p0;
  Event::Handle<float> h_PRO__minDR_pt030_eta2p4;
  Event::Handle<float> h_PRO__minDR_pt050_eta2p4;
  Event::Handle<float> h_PRO__pTrel_pt015_eta3p0;
  Event::Handle<float> h_PRO__pTrel_pt020_eta3p0;
  Event::Handle<float> h_PRO__pTrel_pt025_eta3p0;
  Event::Handle<float> h_PRO__pTrel_pt030_eta2p4;
  Event::Handle<float> h_PRO__pTrel_pt050_eta2p4;
  Event::Handle<bool>  h_PRO__MuonIDLoose;
  Event::Handle<bool>  h_PRO__MuonIDMedium;
  Event::Handle<bool>  h_PRO__MuonIDTight;
  Event::Handle<bool>  h_PRO__ElecIDcutbasedL;
  Event::Handle<bool>  h_PRO__ElecIDcutbasedM;
  Event::Handle<bool>  h_PRO__ElecIDcutbasedT;
  Event::Handle<bool>  h_PRO__ElecIDmvaNonTrigL;
  Event::Handle<bool>  h_PRO__ElecIDmvaNonTrigT;
  Event::Handle<bool>  h_PRO__ElecIDmvaTrigL;
  Event::Handle<bool>  h_PRO__ElecIDmvaTrigT;
};

TagNProbeZLLModule::TagNProbeZLLModule(uhh2::Context& ctx){

  //// CONFIGURATION

  const std::string channel(ctx.get("channel", ""));
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else throw std::runtime_error("undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);

  const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string keyword(ctx.get("keyword", ""));

  MuonId muoID;
  ElectronId eleID;

  if(keyword == "ID"){

    muoID = PtEtaCut  (50., 2.1);
    eleID = PtEtaSCCut(50., 2.5);
  }
  else if(keyword == "twodcut"){

    muoID = AndId<Muon>    (PtEtaCut  (50., 2.1), MuonIDMedium());
    eleID = AndId<Electron>(PtEtaSCCut(50., 2.5), ElectronID_Spring15_25ns_tight_noIso);
  }
  else throw std::runtime_error("TagNProbeZLLModule::TagNProbeZLLModule -- undefined value for \"keyword\" configuration parameter: "+keyword);

  ////

  //// COMMON MODULES

  /* CMS-certified luminosity sections */
  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  /* MET filters (MINIAOD flags) */
  metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
  metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices");
  metfilters_sel->add<TriggerSelection>("HBHENoiseFilter", "Flag_HBHENoiseFilter");
  metfilters_sel->add<TriggerSelection>("HBHENoiseIsoFilter", "Flag_HBHENoiseIsoFilter");
  metfilters_sel->add<TriggerSelection>("CSCTightHalo2015Filter", "Flag_CSCTightHalo2015Filter");
  metfilters_sel->add<TriggerSelection>("EcalDeadCellTriggerPrimitiveFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter");
  metfilters_sel->add<TriggerSelection>("eeBadScFilter", "Flag_eeBadScFilter");
  metfilters_sel->add<TriggerSelection>("chargedHadronTrackResolutionFilter", "Flag_chargedHadronTrackResolutionFilter"); 
  metfilters_sel->add<TriggerSelection>("muonBadTrackFilter", "Flag_muonBadTrackFilter");
  /**********************************/

  ////

  //// OBJ CLEANING
  muo_cleaner.reset(new MuonCleaner    (muoID));
  ele_cleaner.reset(new ElectronCleaner(eleID));

  const JetId jetID(JetPFID(JetPFID::WP_LOOSE));

  std::vector<std::string> JEC_AK4;
  if(isMC){

    JEC_AK4 = JERFiles::Fall15_25ns_L123_AK4PFchs_MC;
  }
  else {

    JEC_AK4 = JERFiles::Fall15_25ns_L123_AK4PFchs_DATA;
  }

  jet_IDcleaner.reset(new JetCleaner(ctx, jetID));
  jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
  if(isMC) jetER_smearer.reset(new GenericJetResolutionSmearer(ctx));
  jetlepton_cleaner.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4));
  jet_cleaner__pt015_eta3p0.reset(new JetCleaner(ctx,  15., 3.0));
  jet_cleaner__pt020_eta3p0.reset(new JetCleaner(ctx,  20., 3.0));
  jet_cleaner__pt025_eta3p0.reset(new JetCleaner(ctx,  25., 3.0));
  jet_cleaner__pt030_eta2p4.reset(new JetCleaner(ctx,  30., 2.4));
  jet_cleaner__pt050_eta2p4.reset(new JetCleaner(ctx,  50., 2.4));
  jet_cleaner__pt070_eta2p4.reset(new JetCleaner(ctx,  70., 2.4));
  jet_cleaner__pt100_eta2p4.reset(new JetCleaner(ctx, 100., 2.4));
  jet_cleaner__pt150_eta2p4.reset(new JetCleaner(ctx, 150., 2.4));
  jet_cleaner__pt200_eta2p4.reset(new JetCleaner(ctx, 200., 2.4));
  jet_cleaner__pt250_eta2p4.reset(new JetCleaner(ctx, 250., 2.4));
  ////

  //// EVENT SELECTION
  lep2_sel.reset(new AndSelection(ctx));
  if(channel_ == muon){
    lep2_sel->add<NMuonSelection>    ("muoN == 2", 2, 2);
    lep2_sel->add<NElectronSelection>("eleN == 0", 0, 0);
  }
  else if(channel_ == elec){
    lep2_sel->add<NMuonSelection>    ("muoN == 0", 0, 0);
    lep2_sel->add<NElectronSelection>("eleN == 2", 2, 2);
  }

  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut( 50., 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(100., 2.4))));
  //

  const std::string ttbar_gen_label("ttbargen");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  if(ctx.get("dataset_version") == "TTbar_Mtt0000to0700") genmttbar_sel.reset(new MttbarGenSelection( 0., 700.));
  else                                                    genmttbar_sel.reset(new uhh2::AndSelection(ctx));
  ////

  //// Data/MC scale factors

  //pileup
  pileupSF.reset(new MCPileupReweight(ctx));

  // muon-ID
  const std::string& muonID_SFac    = ctx.get("muonID_SF_file");
  const std::string& muonID_directory    = ctx.get("muonID_SF_directory");

  muonID_SF.reset(new MCMuonScaleFactor(ctx, muonID_SFac, muonID_directory, 1.0, "ID"));
  //

  // elec-ID
  const std::string& elecID_SFac    = ctx.get("elecID_SF_file");
  const std::string& elecID_hist    = ctx.get("elecID_SF_hist");

  elecIDSF.reset(new weightcalc_elecID(ctx, "electrons", elecID_SFac, elecID_hist, 0.00));
  //

  ////

  //// TNP VARS
  ctx.undeclare_all_event_output();


  //if(isMC){

  //   HLT_paths_ = std::vector<std::string>({
  //     "HLT_Ele20WP60_Ele8_Mass55",
  //     "HLT_Ele25WP60_SC4_Mass55",
  //     "HLT_Ele27_WP85_Gsf",
  //     "HLT_Ele27_eta2p1_WP75_Gsf",
  //     "HLT_Ele27_eta2p1_WP85_Gsf_HT200",
  //     "HLT_Ele32_eta2p1_WP75_Gsf",
  //     "HLT_Ele105_CaloIdVT_GsfTrkIdT",
  //     "HLT_Mu40_TkMu11",
  //     "HLT_IsoMu17_eta2p1",
  //     "HLT_IsoMu24_eta2p1",
  //     "HLT_IsoMu27",
  //     "HLT_Mu45_eta2p1",
  //     "HLT_Mu50",
  //     "HLT_PFHT900",
  //     "HLT_PFHT800Emu",
  //   });
  // }
  // else {

  HLT_paths_ = std::vector<std::string>({
      "HLT_Ele30WP60_SC4_Mass55",
      "HLT_Ele30WP60_Ele8_Mass55",
      "HLT_Ele27_eta2p1_WPLoose_Gsf",
      "HLT_Ele27_eta2p1_WPLoose_Gsf_HT200",
      "HLT_Ele27_eta2p1_WPLoose_Gsf",
      "HLT_Ele27_eta2p1_WPTight_Gsf",
      "HLT_Ele32_eta2p1_WPTight_Gsf",
      "HLT_Mu40_TkMu11",
      "HLT_IsoMu17_eta2p1",
      "HLT_IsoMu27",
      "HLT_Mu45_eta2p1",
      "HLT_Mu50",
      "HLT_PFHT800",
      "HLT_PFHT800Emu",
  });
  // }
    
  for(const auto& p : HLT_paths_) h_HLT[p] = ctx.declare_event_output<bool>(p);

  h_MCweight                = ctx.declare_event_output<float> ("MCweight");

  h_run                     = ctx.declare_event_output<int>("run");
  h_lumi_block              = ctx.declare_event_output<int>("lumi_block");
  h_event                   = ctx.declare_event_output<int>("event");

  h_pvN                     = ctx.declare_event_output<int>  ("pvN");

  h_MET__pt                 = ctx.declare_event_output<float>("MET__pt");
  h_MET__phi                = ctx.declare_event_output<float>("MET__phi");

  h_jetN__pt015_eta3p0      = ctx.declare_event_output<int>("jetN__pt015_eta3p0");
  h_jetN__pt020_eta3p0      = ctx.declare_event_output<int>("jetN__pt020_eta3p0");
  h_jetN__pt025_eta3p0      = ctx.declare_event_output<int>("jetN__pt025_eta3p0");
  h_jetN__pt030_eta2p4      = ctx.declare_event_output<int>("jetN__pt030_eta2p4");
  h_jetN__pt050_eta2p4      = ctx.declare_event_output<int>("jetN__pt050_eta2p4");
  h_jetN__pt070_eta2p4      = ctx.declare_event_output<int>("jetN__pt070_eta2p4");
  h_jetN__pt100_eta2p4      = ctx.declare_event_output<int>("jetN__pt100_eta2p4");
  h_jetN__pt150_eta2p4      = ctx.declare_event_output<int>("jetN__pt150_eta2p4");
  h_jetN__pt200_eta2p4      = ctx.declare_event_output<int>("jetN__pt200_eta2p4");
  h_jetN__pt250_eta2p4      = ctx.declare_event_output<int>("jetN__pt250_eta2p4");

  h_ZLL__M                  = ctx.declare_event_output<float>("ZLL__M");
  h_ZLL__pt                 = ctx.declare_event_output<float>("ZLL__pt");
  h_ZLL__eta                = ctx.declare_event_output<float>("ZLL__eta");
  h_ZLL__phi                = ctx.declare_event_output<float>("ZLL__phi");

  h_TAG__charge             = ctx.declare_event_output<int>  ("TAG__charge");
  h_TAG__M                  = ctx.declare_event_output<float>("TAG__M");
  h_TAG__pt                 = ctx.declare_event_output<float>("TAG__pt");
  h_TAG__eta                = ctx.declare_event_output<float>("TAG__eta");
  h_TAG__etaSC              = ctx.declare_event_output<float>("TAG__etaSC");
  h_TAG__phi                = ctx.declare_event_output<float>("TAG__phi");
  h_TAG__pfIso_rhoEA        = ctx.declare_event_output<float>("TAG__pfIso_rhoEA");
  h_TAG__pfIso_dbeta        = ctx.declare_event_output<float>("TAG__pfIso_dbeta");
  h_TAG__pfMINIIso_dbeta    = ctx.declare_event_output<float>("TAG__pfMINIIso_dbeta");
  h_TAG__minDR_pt015_eta3p0 = ctx.declare_event_output<float>("TAG__minDR_pt015_eta3p0");
  h_TAG__minDR_pt020_eta3p0 = ctx.declare_event_output<float>("TAG__minDR_pt020_eta3p0");
  h_TAG__minDR_pt025_eta3p0 = ctx.declare_event_output<float>("TAG__minDR_pt025_eta3p0");
  h_TAG__minDR_pt030_eta2p4 = ctx.declare_event_output<float>("TAG__minDR_pt030_eta2p4");
  h_TAG__minDR_pt050_eta2p4 = ctx.declare_event_output<float>("TAG__minDR_pt050_eta2p4");
  h_TAG__pTrel_pt015_eta3p0 = ctx.declare_event_output<float>("TAG__pTrel_pt015_eta3p0");
  h_TAG__pTrel_pt020_eta3p0 = ctx.declare_event_output<float>("TAG__pTrel_pt020_eta3p0");
  h_TAG__pTrel_pt025_eta3p0 = ctx.declare_event_output<float>("TAG__pTrel_pt025_eta3p0");
  h_TAG__pTrel_pt030_eta2p4 = ctx.declare_event_output<float>("TAG__pTrel_pt030_eta2p4");
  h_TAG__pTrel_pt050_eta2p4 = ctx.declare_event_output<float>("TAG__pTrel_pt050_eta2p4");
  h_TAG__MuonIDLoose        = ctx.declare_event_output<bool> ("TAG__MuonIDLoose");
  h_TAG__MuonIDMedium       = ctx.declare_event_output<bool> ("TAG__MuonIDMedium");
  h_TAG__MuonIDTight        = ctx.declare_event_output<bool> ("TAG__MuonIDTight");
  h_TAG__ElecIDcutbasedL    = ctx.declare_event_output<bool> ("TAG__ElecIDcutbasedL");
  h_TAG__ElecIDcutbasedM    = ctx.declare_event_output<bool> ("TAG__ElecIDcutbasedM");
  h_TAG__ElecIDcutbasedT    = ctx.declare_event_output<bool> ("TAG__ElecIDcutbasedT");
  h_TAG__ElecIDmvaNonTrigL  = ctx.declare_event_output<bool> ("TAG__ElecIDmvaNonTrigL");
  h_TAG__ElecIDmvaNonTrigT  = ctx.declare_event_output<bool> ("TAG__ElecIDmvaNonTrigT");
  h_TAG__ElecIDmvaTrigL     = ctx.declare_event_output<bool> ("TAG__ElecIDmvaTrigL");
  h_TAG__ElecIDmvaTrigT     = ctx.declare_event_output<bool> ("TAG__ElecIDmvaTrigT");

  h_PRO__charge             = ctx.declare_event_output<int>  ("PRO__charge");
  h_PRO__M                  = ctx.declare_event_output<float>("PRO__M");
  h_PRO__pt                 = ctx.declare_event_output<float>("PRO__pt");
  h_PRO__eta                = ctx.declare_event_output<float>("PRO__eta");
  h_PRO__etaSC              = ctx.declare_event_output<float>("PRO__etaSC");
  h_PRO__phi                = ctx.declare_event_output<float>("PRO__phi");
  h_PRO__pfIso_rhoEA        = ctx.declare_event_output<float>("PRO__pfIso_rhoEA");
  h_PRO__pfIso_dbeta        = ctx.declare_event_output<float>("PRO__pfIso_dbeta");
  h_PRO__pfMINIIso_dbeta    = ctx.declare_event_output<float>("PRO__pfMINIIso_dbeta");
  h_PRO__minDR_pt015_eta3p0 = ctx.declare_event_output<float>("PRO__minDR_pt015_eta3p0");
  h_PRO__minDR_pt020_eta3p0 = ctx.declare_event_output<float>("PRO__minDR_pt020_eta3p0");
  h_PRO__minDR_pt025_eta3p0 = ctx.declare_event_output<float>("PRO__minDR_pt025_eta3p0");
  h_PRO__minDR_pt030_eta2p4 = ctx.declare_event_output<float>("PRO__minDR_pt030_eta2p4");
  h_PRO__minDR_pt050_eta2p4 = ctx.declare_event_output<float>("PRO__minDR_pt050_eta2p4");
  h_PRO__pTrel_pt015_eta3p0 = ctx.declare_event_output<float>("PRO__pTrel_pt015_eta3p0");
  h_PRO__pTrel_pt020_eta3p0 = ctx.declare_event_output<float>("PRO__pTrel_pt020_eta3p0");
  h_PRO__pTrel_pt025_eta3p0 = ctx.declare_event_output<float>("PRO__pTrel_pt025_eta3p0");
  h_PRO__pTrel_pt030_eta2p4 = ctx.declare_event_output<float>("PRO__pTrel_pt030_eta2p4");
  h_PRO__pTrel_pt050_eta2p4 = ctx.declare_event_output<float>("PRO__pTrel_pt050_eta2p4");
  h_PRO__MuonIDLoose        = ctx.declare_event_output<bool> ("PRO__MuonIDLoose");
  h_PRO__MuonIDMedium       = ctx.declare_event_output<bool> ("PRO__MuonIDMedium");
  h_PRO__MuonIDTight        = ctx.declare_event_output<bool> ("PRO__MuonIDTight");
  h_PRO__ElecIDcutbasedL    = ctx.declare_event_output<bool> ("PRO__ElecIDcutbasedL");
  h_PRO__ElecIDcutbasedM    = ctx.declare_event_output<bool> ("PRO__ElecIDcutbasedM");
  h_PRO__ElecIDcutbasedT    = ctx.declare_event_output<bool> ("PRO__ElecIDcutbasedT");
  h_PRO__ElecIDmvaNonTrigL  = ctx.declare_event_output<bool> ("PRO__ElecIDmvaNonTrigL");
  h_PRO__ElecIDmvaNonTrigT  = ctx.declare_event_output<bool> ("PRO__ElecIDmvaNonTrigT");
  h_PRO__ElecIDmvaTrigL     = ctx.declare_event_output<bool> ("PRO__ElecIDmvaTrigL");
  h_PRO__ElecIDmvaTrigT     = ctx.declare_event_output<bool> ("PRO__ElecIDmvaTrigT");
  ////
}

bool TagNProbeZLLModule::process(uhh2::Event& event){

  if(!event.isRealData){

    ttgenprod->process(event);
    if(!genmttbar_sel->passes(event)) return false;
  }

  //// COMMON MODULES

  /* CMS-certified luminosity sections */
  if(event.isRealData && !lumi_sel->passes(event)) return false;

  /* MET filters #1 */
  if(!metfilters_sel->passes(event)) return false;

  ////

  //// Data/MC scale factors

  float w_elecIDSF_ct(1.);

  if(!event.isRealData){

    // pileup
    pileupSF->process(event);
    //

    // muon-ID
    muonID_SF->process(event);

    //

    // elec-ID
    w_elecIDSF_ct = 1.00;//!!elecIDSF->weight(event, "CT");
    //

    if(channel_ == elec) event.weight *= w_elecIDSF_ct;
    //
  }
  ////

  //// LEPTON selection
  muo_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  ele_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  const bool pass_lep2 = lep2_sel->passes(event);
  if(!pass_lep2) return false;
  ////

  //// JET selection
  jet_IDcleaner->process(event);
  jet_corrector->process(event);
  if(jetER_smearer.get()) jetER_smearer->process(event);
  jetlepton_cleaner->process(event);

  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  ////

  /* TAG and PROBE assignment */
  const Particle *tag(0), *pro(0);

  if(channel_ == muon){

    if(event.muons->size() != 2) throw std::runtime_error("TagNProbeZLLModule::process -- logic error: incorrect number of muons (!=2)");

    for(const auto& muo : *event.muons){

      if(muo.get_bool(Muon::tight) && (muo.relIso() < .1)){ tag = &muo; break; }
    }

    if(!tag) return false;

    pro = (tag == &event.muons->at(0)) ? &event.muons->at(1) : &event.muons->at(0);
  }
  else if(channel_ == elec){

    if(event.electrons->size() != 2) throw std::runtime_error("TagNProbeZLLModule::process -- logic error: incorrect number of electrons (!=2)");

    for(const auto& ele : *event.electrons){

      if(ElectronID_Spring15_25ns_tight(ele, event)){ tag = &ele; break; }
    }

    if(!tag) return false;

    pro = (tag == &event.electrons->at(0)) ? &event.electrons->at(1) : &event.electrons->at(0);
  }

  if(!tag) throw std::runtime_error("TagNProbeZLLModule::process -- logic error: assignment of TAG charged lepton failed");
  if(!pro) throw std::runtime_error("TagNProbeZLLModule::process -- logic error: assignment of PROBE charged lepton failed");
  /****************************/

  /* add TnP vars to output ntuple */

  // global vars
  event.set(h_MCweight, event.weight);

  for(const auto& p : HLT_paths_) event.set(h_HLT.at(p), bool(trigger_bit(event, p+"_v*")));

  event.set(h_run       , event.run);
  event.set(h_lumi_block, event.luminosityBlock);
  event.set(h_event     , event.event);

  event.set(h_pvN     , event.pvs->size());

  event.set(h_MET__pt , event.met->pt());
  event.set(h_MET__phi, event.met->phi());
  //

  float tag__minDR_pt015_eta3p0(-1.), pro__minDR_pt015_eta3p0(-1.);
  float tag__pTrel_pt015_eta3p0(-1.), pro__pTrel_pt015_eta3p0(-1.);

  jet_cleaner__pt015_eta3p0->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt015_eta3p0, event.jets->size());

  std::tie(tag__minDR_pt015_eta3p0, tag__pTrel_pt015_eta3p0) = drmin_pTrel(*tag, *event.jets);
  std::tie(pro__minDR_pt015_eta3p0, pro__pTrel_pt015_eta3p0) = drmin_pTrel(*pro, *event.jets);
  //

  float tag__minDR_pt020_eta3p0(-1.), pro__minDR_pt020_eta3p0(-1.);
  float tag__pTrel_pt020_eta3p0(-1.), pro__pTrel_pt020_eta3p0(-1.);

  jet_cleaner__pt020_eta3p0->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt020_eta3p0, event.jets->size());

  std::tie(tag__minDR_pt020_eta3p0, tag__pTrel_pt020_eta3p0) = drmin_pTrel(*tag, *event.jets);
  std::tie(pro__minDR_pt020_eta3p0, pro__pTrel_pt020_eta3p0) = drmin_pTrel(*pro, *event.jets);
  //

  float tag__minDR_pt025_eta3p0(-1.), pro__minDR_pt025_eta3p0(-1.);
  float tag__pTrel_pt025_eta3p0(-1.), pro__pTrel_pt025_eta3p0(-1.);

  jet_cleaner__pt025_eta3p0->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt025_eta3p0, event.jets->size());

  std::tie(tag__minDR_pt025_eta3p0, tag__pTrel_pt025_eta3p0) = drmin_pTrel(*tag, *event.jets);
  std::tie(pro__minDR_pt025_eta3p0, pro__pTrel_pt025_eta3p0) = drmin_pTrel(*pro, *event.jets);
  //

  float tag__minDR_pt030_eta2p4(-1.), pro__minDR_pt030_eta2p4(-1.);
  float tag__pTrel_pt030_eta2p4(-1.), pro__pTrel_pt030_eta2p4(-1.);

  jet_cleaner__pt030_eta2p4->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt030_eta2p4, event.jets->size());

  std::tie(tag__minDR_pt030_eta2p4, tag__pTrel_pt030_eta2p4) = drmin_pTrel(*tag, *event.jets);
  std::tie(pro__minDR_pt030_eta2p4, pro__pTrel_pt030_eta2p4) = drmin_pTrel(*pro, *event.jets);
  //

  float tag__minDR_pt050_eta2p4(-1.), pro__minDR_pt050_eta2p4(-1.);
  float tag__pTrel_pt050_eta2p4(-1.), pro__pTrel_pt050_eta2p4(-1.);

  jet_cleaner__pt050_eta2p4->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt050_eta2p4, event.jets->size());

  std::tie(tag__minDR_pt050_eta2p4, tag__pTrel_pt050_eta2p4) = drmin_pTrel(*tag, *event.jets);
  std::tie(pro__minDR_pt050_eta2p4, pro__pTrel_pt050_eta2p4) = drmin_pTrel(*pro, *event.jets);
  //

  jet_cleaner__pt070_eta2p4->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt070_eta2p4, event.jets->size());
  //

  jet_cleaner__pt100_eta2p4->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt100_eta2p4, event.jets->size());
  //

  jet_cleaner__pt150_eta2p4->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt150_eta2p4, event.jets->size());
  //

  jet_cleaner__pt200_eta2p4->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt200_eta2p4, event.jets->size());
  //

  jet_cleaner__pt250_eta2p4->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt250_eta2p4, event.jets->size());
  //

  float tag__etaSC(-999.), tag__pfIso_rhoEA(-1.), tag__pfIso_dbeta(-1.), tag__pfMINIIso_dbeta(-1.);
  float pro__etaSC(-999.), pro__pfIso_rhoEA(-1.), pro__pfIso_dbeta(-1.), pro__pfMINIIso_dbeta(-1.);

  bool tag__MuonIDLoose      (false), pro__MuonIDLoose      (false);
  bool tag__MuonIDMedium     (false), pro__MuonIDMedium     (false);
  bool tag__MuonIDTight      (false), pro__MuonIDTight      (false);
  bool tag__ElecIDcutbasedL  (false), pro__ElecIDcutbasedL  (false);
  bool tag__ElecIDcutbasedM  (false), pro__ElecIDcutbasedM  (false);
  bool tag__ElecIDcutbasedT  (false), pro__ElecIDcutbasedT  (false);
  bool tag__ElecIDmvaNonTrigL(false), pro__ElecIDmvaNonTrigL(false);
  bool tag__ElecIDmvaNonTrigT(false), pro__ElecIDmvaNonTrigT(false);
  bool tag__ElecIDmvaTrigL   (false), pro__ElecIDmvaTrigL   (false);
  bool tag__ElecIDmvaTrigT   (false), pro__ElecIDmvaTrigT   (false);

  if(channel_ == muon){

    tag__pfIso_dbeta = ((Muon*) tag)->relIso();
    pro__pfIso_dbeta = ((Muon*) pro)->relIso();

    tag__pfMINIIso_dbeta = Muon_pfMINIIso(*((Muon*) tag), event, "delta-beta");
    pro__pfMINIIso_dbeta = Muon_pfMINIIso(*((Muon*) pro), event, "delta-beta");

    tag__MuonIDLoose  = ((Muon*) tag)->get_bool(Muon::loose);
    tag__MuonIDMedium = ((Muon*) tag)->get_bool(Muon::medium);
    tag__MuonIDTight  = ((Muon*) tag)->get_bool(Muon::tight);

    pro__MuonIDLoose  = ((Muon*) pro)->get_bool(Muon::loose);
    pro__MuonIDMedium = ((Muon*) pro)->get_bool(Muon::medium);
    pro__MuonIDTight  = ((Muon*) pro)->get_bool(Muon::tight);
  }
  else if(channel_ == elec){

    tag__etaSC = ((Electron*) tag)->supercluster_eta();
    pro__etaSC = ((Electron*) pro)->supercluster_eta();

    tag__pfIso_rhoEA = ((Electron*) tag)->relIsorho(event.rho);
    pro__pfIso_rhoEA = ((Electron*) pro)->relIsorho(event.rho);

    tag__pfIso_dbeta = ((Electron*) tag)->relIsodb();
    pro__pfIso_dbeta = ((Electron*) pro)->relIsodb();

    tag__pfMINIIso_dbeta = Electron_pfMINIIso(*((Electron*) tag), event, "delta-beta");
    pro__pfMINIIso_dbeta = Electron_pfMINIIso(*((Electron*) pro), event, "delta-beta");

    tag__ElecIDcutbasedL   = ElectronID_Spring15_25ns_loose_noIso    (*((Electron*) tag), event);
    tag__ElecIDcutbasedM   = ElectronID_Spring15_25ns_medium_noIso   (*((Electron*) tag), event);
    tag__ElecIDcutbasedT   = ElectronID_Spring15_25ns_tight_noIso    (*((Electron*) tag), event);
    tag__ElecIDmvaNonTrigL = ElectronID_MVAnotrig_Spring15_25ns_loose(*((Electron*) tag), event);
    tag__ElecIDmvaNonTrigT = ElectronID_MVAnotrig_Spring15_25ns_tight(*((Electron*) tag), event);
    tag__ElecIDmvaTrigL    = false;
    tag__ElecIDmvaTrigT    = false;

    pro__ElecIDcutbasedL   = ElectronID_Spring15_25ns_loose_noIso    (*((Electron*) pro), event);
    pro__ElecIDcutbasedM   = ElectronID_Spring15_25ns_medium_noIso   (*((Electron*) pro), event);
    pro__ElecIDcutbasedT   = ElectronID_Spring15_25ns_tight_noIso    (*((Electron*) pro), event);
    pro__ElecIDmvaNonTrigL = ElectronID_MVAnotrig_Spring15_25ns_loose(*((Electron*) pro), event);
    pro__ElecIDmvaNonTrigT = ElectronID_MVAnotrig_Spring15_25ns_tight(*((Electron*) pro), event);
    pro__ElecIDmvaTrigL    = false;
    pro__ElecIDmvaTrigT    = false;
  }

  /* ZLL */
  event.set(h_ZLL__M  , (tag->v4()+pro->v4()).M());
  event.set(h_ZLL__pt , (tag->v4()+pro->v4()).Pt());
  event.set(h_ZLL__eta, (tag->v4()+pro->v4()).Eta());
  event.set(h_ZLL__phi, (tag->v4()+pro->v4()).Phi());

  /* TAG */
  event.set(h_TAG__charge            , int(tag->charge()));
  event.set(h_TAG__M                 , tag->v4().M());
  event.set(h_TAG__pt                , tag->v4().Pt());
  event.set(h_TAG__eta               , tag->v4().Eta());
  event.set(h_TAG__etaSC             , tag__etaSC);
  event.set(h_TAG__phi               , tag->v4().Phi());
  event.set(h_TAG__pfIso_rhoEA       , tag__pfIso_rhoEA);
  event.set(h_TAG__pfIso_dbeta       , tag__pfIso_dbeta);
  event.set(h_TAG__pfMINIIso_dbeta   , tag__pfMINIIso_dbeta);
  event.set(h_TAG__minDR_pt015_eta3p0, tag__minDR_pt015_eta3p0);
  event.set(h_TAG__minDR_pt020_eta3p0, tag__minDR_pt020_eta3p0);
  event.set(h_TAG__minDR_pt025_eta3p0, tag__minDR_pt025_eta3p0);
  event.set(h_TAG__minDR_pt030_eta2p4, tag__minDR_pt030_eta2p4);
  event.set(h_TAG__minDR_pt050_eta2p4, tag__minDR_pt050_eta2p4);
  event.set(h_TAG__pTrel_pt015_eta3p0, tag__pTrel_pt015_eta3p0);
  event.set(h_TAG__pTrel_pt020_eta3p0, tag__pTrel_pt020_eta3p0);
  event.set(h_TAG__pTrel_pt025_eta3p0, tag__pTrel_pt025_eta3p0);
  event.set(h_TAG__pTrel_pt030_eta2p4, tag__pTrel_pt030_eta2p4);
  event.set(h_TAG__pTrel_pt050_eta2p4, tag__pTrel_pt050_eta2p4);
  event.set(h_TAG__MuonIDLoose       , tag__MuonIDLoose);
  event.set(h_TAG__MuonIDMedium      , tag__MuonIDMedium);
  event.set(h_TAG__MuonIDTight       , tag__MuonIDTight);
  event.set(h_TAG__ElecIDcutbasedL   , tag__ElecIDcutbasedL);
  event.set(h_TAG__ElecIDcutbasedM   , tag__ElecIDcutbasedM);
  event.set(h_TAG__ElecIDcutbasedT   , tag__ElecIDcutbasedT);
  event.set(h_TAG__ElecIDmvaNonTrigL , tag__ElecIDmvaNonTrigL);
  event.set(h_TAG__ElecIDmvaNonTrigT , tag__ElecIDmvaNonTrigT);
  event.set(h_TAG__ElecIDmvaTrigL    , tag__ElecIDmvaTrigL);
  event.set(h_TAG__ElecIDmvaTrigT    , tag__ElecIDmvaTrigT);

  /* PROBE */
  event.set(h_PRO__charge            , int(pro->charge()));
  event.set(h_PRO__M                 , pro->v4().M());
  event.set(h_PRO__pt                , pro->v4().Pt());
  event.set(h_PRO__eta               , pro->v4().Eta());
  event.set(h_PRO__etaSC             , pro__etaSC);
  event.set(h_PRO__phi               , pro->v4().Phi());
  event.set(h_PRO__pfIso_rhoEA       , pro__pfIso_rhoEA);
  event.set(h_PRO__pfIso_dbeta       , pro__pfIso_dbeta);
  event.set(h_PRO__pfMINIIso_dbeta   , pro__pfMINIIso_dbeta);
  event.set(h_PRO__minDR_pt015_eta3p0, pro__minDR_pt015_eta3p0);
  event.set(h_PRO__minDR_pt020_eta3p0, pro__minDR_pt020_eta3p0);
  event.set(h_PRO__minDR_pt025_eta3p0, pro__minDR_pt025_eta3p0);
  event.set(h_PRO__minDR_pt030_eta2p4, pro__minDR_pt030_eta2p4);
  event.set(h_PRO__minDR_pt050_eta2p4, pro__minDR_pt050_eta2p4);
  event.set(h_PRO__pTrel_pt015_eta3p0, pro__pTrel_pt015_eta3p0);
  event.set(h_PRO__pTrel_pt020_eta3p0, pro__pTrel_pt020_eta3p0);
  event.set(h_PRO__pTrel_pt025_eta3p0, pro__pTrel_pt025_eta3p0);
  event.set(h_PRO__pTrel_pt030_eta2p4, pro__pTrel_pt030_eta2p4);
  event.set(h_PRO__pTrel_pt050_eta2p4, pro__pTrel_pt050_eta2p4);
  event.set(h_PRO__MuonIDLoose       , pro__MuonIDLoose);
  event.set(h_PRO__MuonIDMedium      , pro__MuonIDMedium);
  event.set(h_PRO__MuonIDTight       , pro__MuonIDTight);
  event.set(h_PRO__ElecIDcutbasedL   , pro__ElecIDcutbasedL);
  event.set(h_PRO__ElecIDcutbasedM   , pro__ElecIDcutbasedM);
  event.set(h_PRO__ElecIDcutbasedT   , pro__ElecIDcutbasedT);
  event.set(h_PRO__ElecIDmvaNonTrigL , pro__ElecIDmvaNonTrigL);
  event.set(h_PRO__ElecIDmvaNonTrigT , pro__ElecIDmvaNonTrigT);
  event.set(h_PRO__ElecIDmvaTrigL    , pro__ElecIDmvaTrigL);
  event.set(h_PRO__ElecIDmvaTrigT    , pro__ElecIDmvaTrigT);
  ///

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TagNProbeZLLModule)
