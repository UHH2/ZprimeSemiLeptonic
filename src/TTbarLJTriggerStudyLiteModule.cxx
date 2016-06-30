#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>
#include <UHH2/common/include/CleaningModules.h>

#include <UHH2/common/include/MCWeight.h>
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
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/TopPtReweight.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJTriggerEffHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/DileptonHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/EffyTTbarRECOHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/SF_elec.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_ttagging.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_WjetsREWGT.h>

#include <TMVA/Tools.h>
#include <TMVA/Reader.h>
#include <TMVA/MethodCuts.h>

class TTbarLJTriggerStudyLiteModule : public ModuleBASE {

 public:
  explicit TTbarLJTriggerStudyLiteModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:
  enum lepton { muon, elec };
  lepton channel_;

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;

  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> trigger_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> triangc_sel;
  // cleaners
  std::unique_ptr<MuonCleaner>     muoSR_cleaner;
  std::unique_ptr<ElectronCleaner> eleSR_cleaner;
  ElectronId eleID = ElectronID_Spring15_25ns_tight_noIso;
  std::unique_ptr<JetCleaner>                      jet_IDcleaner;
  std::unique_ptr<JetCorrector>                    jet_corrector;
  std::unique_ptr<GenericJetResolutionSmearer>     jetER_smearer;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> jetlepton_cleaner;
  std::unique_ptr<JetCleaner>                      jet_cleaner1;
  std::unique_ptr<JetCleaner>                      jet_cleaner2;

  

  // std::unique_ptr<uhh2::Selection> ttagevt_sel;
  // std::unique_ptr<uhh2::Selection> topleppt_sel;
  // std::unique_ptr<uhh2::Selection> chi2_sel;

  // // ttbar reconstruction
  // std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  // std::unique_ptr<uhh2::AnalysisModule> reco_primlep;

  // std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag0;
  // std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag1;
  // std::unique_ptr<Chi2Discriminator>     ttbar_chi2__ttag0;
  // std::unique_ptr<Chi2DiscriminatorTTAG> ttbar_chi2__ttag1;

  // uhh2::Event::Handle<TTbarGen> h_ttbar_gen;
  // uhh2::Event::Handle<std::vector<ReconstructionHypothesis> > h_ttbar_hyps;

  float lep1_pt_;

  JetId btag_ID_;
  CSVBTag::wp b_working_point;

  bool use_ttagging_;
  TopJetId ttag_ID_;
  float    ttag_minDR_jet_;

  bool blind_DATA_;
  bool isTrigger_sel;
  bool store_PDF_weights_;

  //// Data/MC scale factors
  std::unique_ptr<weightcalc_elecID>  elecIDSF;

  std::unique_ptr<uhh2::AnalysisModule> pileupSF;
  std::unique_ptr<uhh2::AnalysisModule> muonID_SF;
  std::unique_ptr<uhh2::AnalysisModule> muonHLT_SF;

//!!  std::unique_ptr<weightcalc_elecHLT> elecHLTSF;

  // std::unique_ptr<uhh2::AnalysisModule> btagSF;
  // std::unique_ptr<Hists> h_btagMCeffi;

  // std::unique_ptr<weightcalc_ttagging> ttagSF_ct;
  // std::unique_ptr<weightcalc_ttagging> ttagSF_upL;
  // std::unique_ptr<weightcalc_ttagging> ttagSF_dnL;
  // std::unique_ptr<weightcalc_ttagging> ttagSF_upT;
  // std::unique_ptr<weightcalc_ttagging> ttagSF_dnT;

  // //std::unique_ptr<weightcalc_topptREWGT> topptREWGT;
  // std::unique_ptr<TopPtReweight> topptREWGT;
  // std::unique_ptr<weightcalc_WjetsREWGT> wjetsREWGT;
  // ////

  //// VARS

  // event
  Event::Handle<int>   h_run;
  Event::Handle<int>   h_lumi_block;
  Event::Handle<int>   h_event;
  Event::Handle<int>   h_pvN;
  Event::Handle<int>   h_muoN;
  Event::Handle<int>   h_eleN;
  // Event::Handle<int>   h_btagN;
  // Event::Handle<int>   h_ttagN;
  // Event::Handle<bool>  h_ttagevt;
  // Event::Handle<int>   h_ttgen;
  //

  // lepton
  Event::Handle<TLorentzVector> h_lep1;
  Event::Handle<int>            h_lep1__pdgID;
  Event::Handle<int>            h_lep1__charge;
  Event::Handle<float>          h_lep1__minDR_jet;
  Event::Handle<float>          h_lep1__pTrel_jet;

  Event::Handle<TLorentzVector> h_lep2;
  Event::Handle<int>            h_lep2__pdgID;
  Event::Handle<int>            h_lep2__charge;
  Event::Handle<float>          h_lep2__minDR_jet;
  Event::Handle<float>          h_lep2__pTrel_jet;
  //

  // jet
  Event::Handle<TLorentzVector> h_jet1;
  Event::Handle<TLorentzVector> h_jet2;

  // // MET
  // Event::Handle<TLorentzVector> h_MET;
  // Event::Handle<float>          h_MET__pz;
  // //

  // // ttbar reco hyp
  // Event::Handle<float>          h_rec_chi2;
  // Event::Handle<TLorentzVector> h_rec_tlep;
  // Event::Handle<TLorentzVector> h_rec_thad;
  // //

  // // weight
  // Event::Handle<float> h_wgtMC__GEN;

  // Event::Handle<float> h_wgtMC__elecIDSF_ct;
  // Event::Handle<float> h_wgtMC__elecIDSF_up;
  // Event::Handle<float> h_wgtMC__elecIDSF_dn;

  // Event::Handle<float> h_wgtMC__elecHLTSF_ct;
  // Event::Handle<float> h_wgtMC__elecHLTSF_up;
  // Event::Handle<float> h_wgtMC__elecHLTSF_dn;

  // Event::Handle<float> h_wgtMC__ttagSF_ct;
  // Event::Handle<float> h_wgtMC__ttagSF_upL;
  // Event::Handle<float> h_wgtMC__ttagSF_dnL;
  // Event::Handle<float> h_wgtMC__ttagSF_upT;
  // Event::Handle<float> h_wgtMC__ttagSF_dnT;

  // Event::Handle<float> h_wgtMC__muR_ct__muF_up;
  // Event::Handle<float> h_wgtMC__muR_ct__muF_dn;
  // Event::Handle<float> h_wgtMC__muR_up__muF_ct;
  // Event::Handle<float> h_wgtMC__muR_up__muF_up;
  // Event::Handle<float> h_wgtMC__muR_dn__muF_ct;
  // Event::Handle<float> h_wgtMC__muR_dn__muF_dn;

  // Event::Handle<float> h_wgtMC__topptREWGT_ct;
  // Event::Handle<float> h_wgtMC__topptREWGT_up;
  // Event::Handle<float> h_wgtMC__topptREWGT_dn;

  // Event::Handle<float> h_wgtMC__wjetsREWGT_ct;

  // Event::Handle<std::vector<float> > h_wgtMC__PDF;
  //

  // // vars in TTree for Homemade ttbar MVA
  // Event::Handle<float> tt_lep_pt;//lepton pt
  // Event::Handle<float> tt_lep_pt_err;//lepton pt error
  // Event::Handle<float> tt_lep_eta;//lepton eta
  // Event::Handle<float> tt_lep_eta_err;//lepton eta error
  // Event::Handle<float> tt_lep_phi;//lepton eta
  // Event::Handle<float> tt_lep_phi_err;//lepton eta error
  // Event::Handle<float> tt_lep_xy;// x^2+y^2 vertex of the lepton 
  // Event::Handle<float> tt_MwT;// Transversal mass
  // Event::Handle<float> tt_lep_fbrem;//fraction of energy loss due to bremsstrahlung. !cation: in 8TeV was well modeled only for |eta|<1.44
  // Event::Handle<float> tt_met_pt;//MET pt 
  // Event::Handle<float> tt_met_phi;//MET phi
  // Event::Handle<float> tt_ljet_pt;//jet pt (for the leading jet)
  // Event::Handle<float> tt_cjet_pt;//jet pt (for the close to lepton jet)
  // Event::Handle<float> tt_ljet_phi;//jet pt (for the leading jet)
  // Event::Handle<float> tt_cjet_phi;//jet pt (for the close to lepton jet)
  // Event::Handle<float> tt_ljet_eta;//jet pt (for the leading jet)
  // Event::Handle<float> tt_cjet_eta;//jet pt (for the close to lepton jet)
  // Event::Handle<float> tt_jet2_pt;
  // Event::Handle<float> tt_jet3_pt;
  // Event::Handle<float> tt_jet2_phi;
  // Event::Handle<float> tt_jet3_phi;
  // Event::Handle<float> tt_jet2_eta;
  // Event::Handle<float> tt_jet3_eta;
  // Event::Handle<float> tt_ljet_M; Event::Handle<float> tt_cjet_M;  Event::Handle<float> tt_jet2_M; Event::Handle<float> tt_jet3_M; //jet mass
  // Event::Handle<float> tt_lep_pt_ljet;// lepton Pt to the leading jet axis
  // Event::Handle<float> tt_lep_pt_cjet;// lepton Pt to the closest not leading jet axis
  // Event::Handle<float> tt_cjet_pt_ljet;// the closest not leading jet Pt to the leading jet axis
  // Event::Handle<float> tt_dR_cljet_ljet;//distance in eta-phi between close jet  and leading jet
  // Event::Handle<float> tt_dR_lep_cljet;// distance between lepton and the closest not leading jet in eta-phi
  // Event::Handle<float> tt_dR_lep_ljet;// distance between lepton and the leading jet in eta-phi
  // Event::Handle<float> tt_dPhi_lep_met;//distance in phi for MET to lepton  
  // Event::Handle<float> tt_dPhi_ljet_met;//distance in phi for MET to the leading jet
  // Event::Handle<float> tt_dPhi_cjet_met;//distance in phi for MET to the closest not leading jet to lepton 
  // Event::Handle<int> tt_lep_class;// rec.electron classification
  // Event::Handle<float> tt_ljet_CSV;//btagging: CombinedSecondaryVertex
  // Event::Handle<float> tt_cjet_CSV;//btagging: CombinedSecondaryVertex
  // Event::Handle<float> tt_jet2_CSV; Event::Handle<float> tt_jet3_CSV;
  // Event::Handle<float> tt_nJets;//number of jets
  // Event::Handle<float> tt_jets_pt;//sum of jets pt
  // //  Event::Handle<float> tt_chi2;//chi2 of ttbar decay reconstruction

  // //electron related variables (as for HEEP ID)
  // Event::Handle<float> tt_Nclusters;
  // Event::Handle<float> tt_full5x5_e1x5;
  // Event::Handle<float> tt_full5x5_e2x5Max;
  // Event::Handle<float> tt_full5x5_e5x5;
  // Event::Handle<float> tt_dEtaInSeed;
  // //electron related variables
  // Event::Handle<float> tt_dB;
  // Event::Handle<float> tt_sigmaIEtaIEta;
  // Event::Handle<float> tt_HoverE;
  // Event::Handle<float> tt_EoverPIn;
  // Event::Handle<float> tt_hcalOverEcal;
  // Event::Handle<float> tt_dr03TkSumPt;
  // Event::Handle<float> tt_effArea;
  // Event::Handle<float> tt_mvaNonTrigV0;
  // Event::Handle<float> tt_dEtaIn;
  // Event::Handle<float> tt_dPhiIn;
  // //top tagging variables
  // Event::Handle<float> tt_qjets_volatility;
  // Event::Handle<float> tt_tau1;
  // Event::Handle<float> tt_tau2;
  // Event::Handle<float> tt_tau3;
  // Event::Handle<float> tt_mvahiggsdiscr;
  // Event::Handle<float> tt_prunedmass;
  // Event::Handle<float> tt_softdropmass;

  // Event::Handle<float> tt_ev_weight;// event weight
  // Event::Handle<float> tt_mttbar;//ttbar rec inv. mass
  // Event::Handle<float> tt_mttbar_gen;//ttbar generated inv. mass

  // float met_pt, met_phi;//MET
  // float lep_pt, lep_eta, fabs_lep_eta, lep_phi;//lepton
  // float lep_pt_err, lep_eta_err, lep_phi_err;//lepton
  // float ljet_pt; float ljet_eta; float ljet_phi;//leading jet 
  // float cjet_pt; float cjet_eta; float cjet_phi;//close to the lepton jet (not leading)
  // float fjet2_pt; float fjet2_eta; float fjet2_phi;//leading jet 
  // float fjet3_pt; float fjet3_eta; float fjet3_phi;//leading jet 
  // float ljet_M, cjet_M, jet2_M, jet3_M;

  // float lep_xy; //x^2+y^2 vertex of the lepton
  // float lep_fbrem; 
  // float MwT;// Transversal mass
  // float lep_pt_ljet;// lepton Pt to the leading jet axis
  // float lep_pt_cjet;// lepton Pt to the closest not leading jet axis
  // float cjet_pt_ljet;// the leading jet Pt to the closest not leading jet axis
  // float dR_cljet_ljet;//distance in eta-phi between the closest jet and the leading jet 
  // float dR_lep_cljet;//distance in eta-phi for the closest not leading jet to lepton  
  // float dR_lep_ljet;//distance in eta-phi for the leading jet to lepton  
  // float dPhi_lep_met;//distance in phi for MET to lepton  
  // float dPhi_ljet_met;//distance in phi for MET to the leading jet
  // float dPhi_cjet_met;//distance in phi for MET to the closest not leading jet to lepton 
  // int lep_class;// rec.electron classification
  // float ljet_CSV;//btag: combinedSecondaryVertex
  // float cjet_CSV;//btag: combinedSecondaryVertex
  // float jet2_CSV,jet3_CSV;//btag: combinedSecondaryVertex
  // float jets_pt;//sum of jets pt
  // float ev_weight;

  // float rec_ttbar_M_; float gen_ttbar_M_;
  // float lep_Nclusters,lep_full5x5_e1x5,lep_full5x5_e2x5Max,lep_full5x5_e5x5,lep_dEtaInSeed;
  // // float log_ljet_pt, log_dR_cljet_ljet, log_dR_lep_cljet, log_lep_pt, jets_pt_to_lep_pt, lep_pt_ljet_to_lep_pt, log_met_pt_to_ljet_pt;
  // // float jets_pt_to_ljet_pt,  log_lep_xy_corr, log_ljet_CSV_ljet_pt;
  // float lep_dB, lep_sigmaIEtaIEta, lep_HoverE, lep_EoverPIn, lep_hcalOverEcal, lep_dr03TkSumPt, lep_effArea, lep_mvaNonTrigV0;
  // float lep_dEtaIn, lep_dPhiIn;
  // float top_qjets_volatility,top_tau1, top_tau2, top_tau3, top_mvahiggsdiscr, top_prunedmass, top_softdropmass;
  // float TMVA_response;
  Event::Handle<float> tt_TMVA_response;// response of TMVA method
  // std::unique_ptr<TMVA::Reader> reader;
  // TString methodName;
  // float varMVA[20];

  ////
};

TTbarLJTriggerStudyLiteModule::TTbarLJTriggerStudyLiteModule(uhh2::Context& ctx){

  //// CONFIGURATION
  const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else {

    std::string log("TTbarLJTriggerStudyLiteModule::TTbarLJTriggerStudyLiteModule -- ");
    log += "TTbarLJTriggerStudyLiteModule::TTbarLJTriggerStudyLiteModule -- invalid argument for 'channel' key in xml file (must be 'muon' or 'elec'): \""+channel+"\"";

    throw std::runtime_error(log);
  }

  use_ttagging_ = true;

  blind_DATA_ = ((ctx.get("dataset_version").find("BLINDED") != std::string::npos) && (ctx.get("dataset_type") == "DATA") && !isMC);
  isTrigger_sel = ((ctx.get("dataset_version").find("HLT") != std::string::npos) && (ctx.get("dataset_type") == "DATA") );
  const std::string& store_PDF_weights = ctx.get("store_PDF_weights", "");
  if     (store_PDF_weights == "true")  store_PDF_weights_ = true;
  else if(store_PDF_weights == "false") store_PDF_weights_ = false;
  else {

    std::string log("TTbarLJTriggerStudyLiteModule::TTbarLJTriggerStudyLiteModule -- ");
    log += "invalid argument for 'store_PDF_weights' key in xml file (must be 'true' or 'false'): \""+store_PDF_weights+"\"";

    throw std::runtime_error(log);
  }
  //

  const std::string& keyword = ctx.get("keyword");

  float jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);
  bool triangul_cut(false);
  //  bool topleppt_cut(false);

  if(keyword == "T0_v01" || keyword == "T1_v01"){

    if     (keyword == "T0_v01") use_ttagging_ = false;
    else if(keyword == "T1_v01") use_ttagging_ = true;

    if(channel_ == muon){

      lep1_pt_ =   50.;

      jet1_pt  = 150.;
      jet2_pt  =  50.;

      MET      =  50.;
      HT_lep   = 150.;

      triangul_cut = false;
      //      topleppt_cut = false;
    }
    else if(channel_ == elec){

      lep1_pt_ =   50.;

      jet1_pt  = 250.;
      jet2_pt  =  70.;

      MET      = 120.;
      HT_lep   =   0.;

      // jet1_pt  = 0.;
      // jet2_pt  = 0.;

      // MET      =   0.;
      // HT_lep   =   0.;

      triangul_cut = false;
      //      topleppt_cut = false;
    }
  }
  else if(keyword == "T0_v02" || keyword == "T1_v02"){

    if     (keyword == "T0_v02") use_ttagging_ = false;
    else if(keyword == "T1_v02") use_ttagging_ = true;

    if(channel_ == muon){

      lep1_pt_ =   0.;

      jet1_pt  = 150.;
      jet2_pt  =  50.;

      MET      =  50.;
      HT_lep   = 150.;

      triangul_cut = false;
      //      topleppt_cut = false;
    }
    else if(channel_ == elec){

      lep1_pt_ = 110.;

      jet1_pt  = 150.;
      jet2_pt  =  50.;

      MET      = 100.;
      HT_lep   =   0.;

      triangul_cut = false;
      //      topleppt_cut = false;
    }
  }
  else if(keyword == "T0_v03" || keyword == "T1_v03"){

    if     (keyword == "T0_v03") use_ttagging_ = false;
    else if(keyword == "T1_v03") use_ttagging_ = true;

    if(channel_ == muon){

      lep1_pt_ =   0.;

      jet1_pt  = 250.;
      jet2_pt  =  70.;

      MET      = 120.;
      HT_lep   =   0.;

      triangul_cut = false;
      //      topleppt_cut = false;
    }
    else if(channel_ == elec){

      throw std::runtime_error("TTbarLJTriggerStudyLiteModule::TTbarLJTriggerStudyLiteModule -- undefined working-point for \""+keyword+"\" in \"elec\" channel");
    }
  }
  else if(keyword == "T0_v04" || keyword == "T1_v04"){

    if     (keyword == "T0_v04") use_ttagging_ = false;
    else if(keyword == "T1_v04") use_ttagging_ = true;

    if(channel_ == muon){

      throw std::runtime_error("TTbarLJTriggerStudyLiteModule::TTbarLJTriggerStudyLiteModule -- undefined working-point for \""+keyword+"\" in \"muon\" channel");
    }
    else if(channel_ == elec){

      lep1_pt_ =   0.;

      jet1_pt  = 250.;
      jet2_pt  =  70.;

      MET      =  120.;
      HT_lep   =   0.;

      triangul_cut = false;
      //      topleppt_cut = false;
    }
  }
  else throw std::runtime_error("TTbarLJTriggerStudyLiteModule::TTbarLJTriggerStudyLiteModule -- undefined \"keyword\" argument in .xml configuration file: "+keyword);
  //

  ////

  //// COMMON MODULES

  /* CMS-certified luminosity sections */
  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  /**********************************/

  ////

  //// OBJ CLEANING
  const     MuonId muoSR(AndId<Muon>    (PtEtaCut  (lep1_pt_   , 2.1), MuonIDMedium()));
  const ElectronId eleSR(AndId<Electron>(PtEtaSCCut(lep1_pt_, 2.5), eleID));
  muoSR_cleaner.reset(new     MuonCleaner(muoSR));
  eleSR_cleaner.reset(new ElectronCleaner(eleSR));
  const JetId jetID(JetPFID(JetPFID::WP_LOOSE));

  std::vector<std::string> JEC_AK4, JEC_AK8;
  if(isMC){
    JEC_AK4 = JERFiles::Spring16_25ns_L123_AK4PFchs_MC;
    JEC_AK8 = JERFiles::Spring16_25ns_L123_AK8PFchs_MC;
  }
  else {
    JEC_AK4 = JERFiles::Spring16_25ns_L123_AK4PFchs_DATA;
    JEC_AK8 = JERFiles::Spring16_25ns_L123_AK8PFchs_DATA;
  }

  jet_IDcleaner.reset(new JetCleaner(ctx, jetID));
  jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
  if(isMC) jetER_smearer.reset(new GenericJetResolutionSmearer(ctx));
  jetlepton_cleaner.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4));
  jet_cleaner1.reset(new JetCleaner(ctx, 15., 3.0));
  jet_cleaner2.reset(new JetCleaner(ctx, 30., 2.4));


  //// EVENT SELECTION
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));

  const std::string& trigger = ctx.get("trigger", "NULL");
  if(trigger != "NULL") trigger_sel.reset(new TriggerSelection(trigger));
  else                  trigger_sel.reset(new uhh2::AndSelection(ctx));

  met_sel  .reset(new METCut  (MET   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));

  if(triangul_cut){

    if     (channel_ == elec) triangc_sel.reset(new TriangularCuts(M_PI/2., (M_PI/2.)/75.));
    else if(channel_ == muon) triangc_sel.reset(new uhh2::AndSelection(ctx));
  }
  else triangc_sel.reset(new uhh2::AndSelection(ctx));
  ////

  // /* b-tagging */
  // const std::string& btag_wp = ctx.get("btag_wp");

  // if     (btag_wp == "CSVL") btag_ID_ = CSVBTag(CSVBTag::WP_LOOSE);
  // else if(btag_wp == "CSVM") btag_ID_ = CSVBTag(CSVBTag::WP_MEDIUM);
  // else if(btag_wp == "CSVT") btag_ID_ = CSVBTag(CSVBTag::WP_TIGHT);

  // if     (btag_wp == "CSVL") b_working_point = CSVBTag::WP_LOOSE;
  // else if(btag_wp == "CSVM") b_working_point = CSVBTag::WP_MEDIUM;
  // else if(btag_wp == "CSVT") b_working_point = CSVBTag::WP_TIGHT;

  // h_btagMCeffi.reset(new BTagMCEfficiencyHists(ctx,"chi2__BTAG",b_working_point));

  /*************/

  // /* t-tagging */
  // const std::string& ttag_wp = ctx.get("ttag_wp");

  // ttag_ID_ = TopTagID_SoftDrop(ttag_wp);
  // ttag_minDR_jet_ = 1.2;

  // ttagevt_sel.reset(new TopTagEventSelection(ttag_ID_, ttag_minDR_jet_));
  // /*************/

  // //// TTBAR KINEMATICAL RECO

  // const std::string ttbar_gen_label ("ttbargen");
  // const std::string ttbar_hyps_label("TTbarReconstruction");
  // const std::string ttbar_chi2_label("Chi2");

  // ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));
  // h_ttbar_gen = ctx.get_handle<TTbarGen>   (ttbar_gen_label);

  // reco_primlep.reset(new PrimaryLepton(ctx));

  // ttbar_reco__ttag0.reset(new HighMassTTbarReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label));
  // ttbar_reco__ttag1.reset(new        TopTagReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label, ttag_ID_, ttag_minDR_jet_));

  // ttbar_chi2__ttag0.reset(new Chi2Discriminator(ctx, ttbar_hyps_label));
  // ttbar_chi2__ttag0->set_Mtlep_mean (175.);
  // ttbar_chi2__ttag0->set_Mtlep_sigma( 19.);
  // ttbar_chi2__ttag0->set_Mthad_mean (177.);
  // ttbar_chi2__ttag0->set_Mthad_sigma( 16.);

  // ttbar_chi2__ttag1.reset(new Chi2DiscriminatorTTAG(ctx, ttbar_hyps_label));
  // ttbar_chi2__ttag1->set_Mtlep_mean (175.);
  // ttbar_chi2__ttag1->set_Mtlep_sigma( 19.);
  // ttbar_chi2__ttag1->set_Mthad_mean (173.);
  // ttbar_chi2__ttag1->set_Mthad_sigma( 15.);
  // ttbar_chi2__ttag1->use_subjet_mass(false);

  // h_ttbar_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis> >(ttbar_hyps_label);
  // ////

  // if(topleppt_cut){

  //   if     (channel_ == elec) topleppt_sel.reset(new LeptonicTopPtCut(ctx, 140., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label));
  //   else if(channel_ == muon) topleppt_sel.reset(new uhh2::AndSelection(ctx));
  // }
  // else topleppt_sel.reset(new uhh2::AndSelection(ctx));

  // chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., 30., ttbar_hyps_label, ttbar_chi2_label));
  // //  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label)); //TEST no chi2 for QCD studies

  //// HISTS

  std::vector<std::string> htags_1({

    "jet2",
    "jet1",
    "trigger",
    "met",
    "htlep",
    "triangc",
      //    "topleppt",
  });

  for(const auto& tag : htags_1){

    book_HFolder(tag, new TTbarLJTriggerEffHists(ctx, tag, ttag_ID_, ttag_minDR_jet_));
  }
  //

  std::vector<std::string> htags_2({

    "kine",
    // "kine__t0b0",
    // "kine__t0b1",
    // "kine__t0b2",
    // "kine__t1b0",
    // "kine__t1b1",
    // "kine__t1b2",

  });

  for(const auto& tag : htags_2){

    book_HFolder(tag          , new TTbarLJTriggerEffHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
    //    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  }
  //

  // std::vector<std::string> htags_4({
  //   "Final",
  // });

  // for(const auto& tag : htags_4){

  //   book_HFolder(tag          , new TTbarLJTriggerEffHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
  //   //    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  // }

  ////

  //// Data/MC scale factors

  //

  // muon-ID
  const std::string& muonID_SFac    = ctx.get("muonID_SF_file");
  const std::string& muonID_directory    = ctx.get("muonID_SF_directory");


  // muon-HLT
  const std::string& muonHLT_SFac   = ctx.get("muonHLT_SF_file");
  const std::string& muonHLT_directory   = ctx.get("muonHLT_SF_directory");


  // elec-ID
  const std::string& elecID_SFac    = ctx.get("elecID_SF_file");
  const std::string& elecID_hist    = ctx.get("elecID_SF_hist");

  elecIDSF.reset(new weightcalc_elecID(ctx, "electrons", elecID_SFac, elecID_hist, 0.00));
  //

//!!  // elec-HLT
//!!  const std::string& elecHLT_SFac   = ctx.get("elecHLT_SF_file");
//!!  const std::string& elecHLT_hist   = ctx.get("elecHLT_SF_hist");
//!!
//!!  elecHLTSF.reset(new weightcalc_elecHLT(ctx, "electrons", elecHLT_SFac, elecHLT_hist, 0.005));
//!!  //


  // // t-tagging
  // const std::string& ttag_SFac_file = ctx.get("ttag_SFs");
  // const std::string& ttag_effy_file = ctx.get("ttag_eff");
  // const std::string& ttag_effyL     = ctx.get("ttag_eff__jetL");
  // const std::string& ttag_effyT     = ctx.get("ttag_eff__jetT");

  // ttagSF_ct .reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));

  // ttagSF_upL.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "UP", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));
  // ttagSF_dnL.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "DN", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));

  // ttagSF_upT.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "UP", ttag_effy_file, ttag_effyL, ttag_effyT));
  // ttagSF_dnT.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "DN", ttag_effy_file, ttag_effyL, ttag_effyT));
  // //

  // // top-pt reweighting
  // if(ctx.get("dataset_version").find("TTbar") != std::string::npos || ctx.get("dataset_version").find("TTBar") != std::string::npos){
  //   //    std::cout<<"Set top pt reweighting!"<<std::endl;
  //   topptREWGT.reset(new TopPtReweight(ctx, 0.156, -0.00137, ttbar_gen_label, "wgtMC__topptREWGT_ct"));
  // }
  // //

  // // W+jets reweighting (NLO/LO k-factors)
  // if(ctx.get("dataset_version").find("WJets") != std::string::npos){
  //   wjetsREWGT.reset(new weightcalc_WjetsREWGT());
  // }
  //

  ////

  //// VARS
  ctx.undeclare_all_event_output();

  //pileup (define it after undeclaring all other variables to keep the weights in the output)
  pileupSF.reset(new MCPileupReweight(ctx));

  //muon ID scale factors
  muonID_SF.reset(new MCMuonScaleFactor(ctx, muonID_SFac, muonID_directory, 1.0, "ID"));
  muonHLT_SF.reset(new MCMuonScaleFactor(ctx, muonHLT_SFac, muonHLT_directory, 0.5, "HLT"));

  // //b-tagging scale factors
  // btagSF.reset(new MCBTagScaleFactor(ctx, b_working_point));

  // event
  h_run             = ctx.declare_event_output<int>("run");
  h_lumi_block      = ctx.declare_event_output<int>("lumi_block");
  h_event           = ctx.declare_event_output<int>("event");

  h_pvN             = ctx.declare_event_output<int>("pvN");

  h_muoN            = ctx.declare_event_output<int>("muoN");
  h_eleN            = ctx.declare_event_output<int>("eleN");

  // h_btagN           = ctx.declare_event_output<int>("btagN");
  // h_ttagN           = ctx.declare_event_output<int>("ttagN");

  // h_ttagevt         = ctx.declare_event_output<bool>("ttagevt");

  // h_ttgen           = ctx.declare_event_output<int>("ttgen");
  // //

  // lepton
  h_lep1            = ctx.declare_event_output<TLorentzVector>("lep1");
  h_lep1__pdgID     = ctx.declare_event_output<int>           ("lep1__pdgID");
  h_lep1__charge    = ctx.declare_event_output<int>           ("lep1__charge");
  h_lep1__minDR_jet = ctx.declare_event_output<float>         ("lep1__minDR_jet");
  h_lep1__pTrel_jet = ctx.declare_event_output<float>         ("lep1__pTrel_jet");

  h_lep2            = ctx.declare_event_output<TLorentzVector>("lep2");
  h_lep2__pdgID     = ctx.declare_event_output<int>           ("lep2__pdgID");
  h_lep2__charge    = ctx.declare_event_output<int>           ("lep2__charge");
  h_lep2__minDR_jet = ctx.declare_event_output<float>         ("lep2__minDR_jet");
  h_lep2__pTrel_jet = ctx.declare_event_output<float>         ("lep2__pTrel_jet");
  //

  // jet
  h_jet1            = ctx.declare_event_output<TLorentzVector>("jet1");
  h_jet2            = ctx.declare_event_output<TLorentzVector>("jet2");
  //

  //Dummy TMVA response
  tt_TMVA_response            = ctx.declare_event_output<float>("TMVA_response");

}

bool TTbarLJTriggerStudyLiteModule::process(uhh2::Event& event){
  //  std::cout<<" --- New event! --- "<<std::endl;
  event.set(tt_TMVA_response, 0);
  //// COMMON MODULES


  // if(!event.isRealData){

  //   ttgenprod->process(event);
  // }

  /* CMS-certified luminosity sections */
  if(event.isRealData){

    if(!lumi_sel->passes(event)) return false;
  }

  ////

  //// Data/MC scale factors

  //  float w_GEN(1.);
  //  float w_elecIDSF_ct(1.) , w_elecIDSF_up(1.) , w_elecIDSF_dn(1.);
  //  float w_elecHLTSF_ct(1.), w_elecHLTSF_up(1.), w_elecHLTSF_dn(1.);
  //float w_ttagSF_ct(1.), w_ttagSF_upL(1.), w_ttagSF_dnL(1.), w_ttagSF_upT(1.), w_ttagSF_dnT(1.);
  // float w_muR_ct__muF_up(1.), w_muR_ct__muF_dn(1.), w_muR_up__muF_ct(1.), w_muR_up__muF_up(1.), w_muR_dn__muF_ct(1.), w_muR_dn__muF_dn(1.);
  // float w_topptREWGT_up(1.), w_topptREWGT_dn(1.); //w_topptREWGT_ct(1.);
  // float w_wjetsREWGT_ct(1.);
  //  std::vector<float> w_PDF;
  //  w_PDF.clear();

  //pileup
  pileupSF->process(event);

  // // b-tagging
  // btagSF->process(event);

  // muon-ID
  muonID_SF->process(event);

  // muon-HLT
  muonHLT_SF->process(event);


  // if(!event.isRealData){

  //   //    w_GEN = event.weight;
  
  //   //

  //   // // elec-ID
  //   // w_elecIDSF_ct  = elecIDSF->weight(event, "CT");
  //   // w_elecIDSF_up  = elecIDSF->weight(event, "UP");
  //   // w_elecIDSF_dn  = elecIDSF->weight(event, "DN");
  //   //

  //   // // elec-HLT
  //   // w_elecHLTSF_ct = 0.99;//!!elecHLTSF->weight(event, "CT");
  //   // w_elecHLTSF_up = 1.01;//!!elecHLTSF->weight(event, "UP");
  //   // w_elecHLTSF_dn = 0.97;//!!elecHLTSF->weight(event, "DN");
  //   // //

  //   // // elec-HLT
  //   // w_elecHLTSF_ct = 1.0;//!!elecHLTSF->weight(event, "CT");
  //   // w_elecHLTSF_up = 1.0;//!!elecHLTSF->weight(event, "UP");
  //   // w_elecHLTSF_dn = 1.0;//!!elecHLTSF->weight(event, "DN");
  //   // //


  //   // // t-tagging
  //   // w_ttagSF_ct    = ttagSF_ct ->weight(event);

  //   // w_ttagSF_upL   = ttagSF_upL->weight(event);
  //   // w_ttagSF_dnL   = ttagSF_dnL->weight(event);

  //   // w_ttagSF_upT   = ttagSF_upT->weight(event);
  //   // w_ttagSF_dnT   = ttagSF_dnT->weight(event);
  //   // //

  //   // // Renormalization/Factorization scales
  //   // if(event.genInfo){

  //   //   if(event.genInfo->systweights().size() >= 9){

  //   //     if(event.genInfo->originalXWGTUP()){

  //   //       w_muR_ct__muF_up = (event.genInfo->systweights().at(1) / event.genInfo->originalXWGTUP());
  //   //       w_muR_ct__muF_dn = (event.genInfo->systweights().at(2) / event.genInfo->originalXWGTUP());
  //   //       w_muR_up__muF_ct = (event.genInfo->systweights().at(3) / event.genInfo->originalXWGTUP());
  //   //       w_muR_up__muF_up = (event.genInfo->systweights().at(4) / event.genInfo->originalXWGTUP());
  //   //       w_muR_dn__muF_ct = (event.genInfo->systweights().at(6) / event.genInfo->originalXWGTUP());
  //   //       w_muR_dn__muF_dn = (event.genInfo->systweights().at(8) / event.genInfo->originalXWGTUP());

  //   //       if(store_PDF_weights_){

  //   //         for(unsigned int i=9; i<event.genInfo->systweights().size(); ++i){

  //   //           const float pdf_w(event.genInfo->systweights().at(i) / event.genInfo->originalXWGTUP());
  //   //           w_PDF.push_back(pdf_w);
  //   //         }
  //   //       }
  //   //     }
  //   //   }
  //   // }

  //   // // top-pt reweighting
  //   // if(topptREWGT.get()){
  //   //   //      std::cout<<"aw!"<<std::endl;
  //   //   topptREWGT->process(event);
  //   //   float w_topptREWGT_ct = event.get(h_wgtMC__topptREWGT_ct);
  //   //   //      std::cout<<w_topptREWGT_ct<<std::endl;
  //   //   //apply twice the shift as uncertainty
  //   //   w_topptREWGT_dn = w_topptREWGT_ct*w_topptREWGT_ct;
  //   //   w_topptREWGT_up = 1;
  //   //   //
  //   // }
  //   // //  


  //   // // W+jets reweighting
  //   // if(wjetsREWGT.get()) w_wjetsREWGT_ct = wjetsREWGT->weight(event);
  //   // //

  //   // central weight (histograms)
  //   //    event.weight *= w_ttagSF_ct;
  //   //

  //   //    if(channel_ == elec) event.weight *= w_elecIDSF_ct;
  // }
  // //

  ////

  //// LEPTON SELECTION
  muoSR_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  eleSR_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  // // OF lepton veto
  // bool pass_lepV(0);
  // if     (channel_ == muon) pass_lepV = ((event.muons->size() == 0));//at least 1 muon 
  // else if(channel_ == elec) pass_lepV = ((event.electrons->size() == 0));//at least 1 electron
  // if(!pass_lepV) return false;
  // //

  // lepton multiplicity
  int lepN(-1);
  if     (channel_ == muon) lepN = int(event.muons    ->size());
  else if(channel_ == elec) lepN = int(event.electrons->size());
  //  if(!(lepN >= 1)) return false;
  if(!(lepN == 1)) return false;
  //
  
  //di-lepton selection
  bool pass_dilep(0);
  if(channel_ == muon) pass_dilep = (event.electrons->size()==1);
  if(channel_ == elec) pass_dilep = (event.muons->size()==1);
  if(!pass_dilep) return false;
  //  std::cout<<" MuonN = "<<event.muons->size()<<" ElecN = "<<event.electrons->size()<<std::endl;
  // // pt-leading lepton selection
  const Particle* lep1 = leading_lepton(event);
  if(!(lep1->pt() > lep1_pt_)) return false;
  // // //

  // // ////

  // // //// JET selectionjet_IDcleaner->process(event);
  jet_corrector->process(event);
  if(jetER_smearer.get()) jetER_smearer->process(event);
  jetlepton_cleaner->process(event);
  jet_cleaner1->process(event);
  sort_by_pt<Jet>(*event.jets);

  const int jet_n = event.jets->size();
  if(jet_n<2) return false;
  // /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  if(lepN == 1) HFolder("jet2")->fill(event);

  // /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  if(lepN == 1) HFolder("jet1")->fill(event);

  // // ////
  if(isTrigger_sel){
  // //// HLT selection
  const bool pass_trigger = trigger_sel->passes(event);
  // //  if(!pass_trigger) return false;
  if(!pass_trigger && event.isRealData) return false; //apply only on data
  // //  else std::cout<<"Passed trigger!!! "<<std::endl;
  if(lepN == 1) HFolder("trigger")->fill(event);
  // ////
  }

  // //if(channel_ == elec) event.weight *= w_elecHLTSF_ct;

  // // // //TEST: no  MET, HT_lep, TRIANGULAR-CUTS cuts for QCD studies

  // // //// MET selection
  // const bool pass_met = met_sel->passes(event);
  // if(!pass_met) return false;
  // if(lepN == 1) HFolder("met")->fill(event);
  // // ////

  // // //// HT_lep selection
  // const bool pass_htlep = htlep_sel->passes(event);
  // if(!pass_htlep) return false;
  // if(lepN == 1) HFolder("htlep")->fill(event);
  // // ////

  // // //// TRIANGULAR-CUTS selection
  // const bool pass_triangc = triangc_sel->passes(event);
  // if(!pass_triangc) return false;
  // if(lepN == 1) HFolder("triangc")->fill(event);
  // // ////

  // // // //--------------------------------------------------------------------

  // //// TTBAR KIN RECO

  // /* TOPTAG-EVENT boolean */
  // const bool pass_ttagevt = ttagevt_sel->passes(event) && use_ttagging_;

  // const std::string ttag_posx = (pass_ttagevt ? "t1" : "t0");
  // /************************/

  // reco_primlep->process(event);

  // if(!pass_ttagevt){ ttbar_reco__ttag0->process(event); ttbar_chi2__ttag0->process(event); }
  // else             { ttbar_reco__ttag1->process(event); ttbar_chi2__ttag1->process(event); }

  //  std::vector<ReconstructionHypothesis>& ttbar_hyps = event.get(h_ttbar_hyps);

  ////

  //// LEPTONIC-TOP pt selection
  // const bool pass_topleppt = topleppt_sel->passes(event);
  //  if(!pass_topleppt) return false; TEST
  //if(lepN == 1) HFolder("topleppt")->fill(event);
  ////

  //// FINAL selection

  // /* ttagN counters */
  // int ttagN(0);
  // for(const auto& tj : *event.topjets) if(ttag_ID_(tj, event)) ++ttagN;

  // //TEST
  // top_qjets_volatility = -100; top_tau1 = -100; top_tau2 = -100; top_tau3 = -100; 
  // top_mvahiggsdiscr = -100; top_prunedmass = -100; top_softdropmass = -100;
  // if(ttagN>0){
  //   for(const auto& tj : *event.topjets){
  //     top_qjets_volatility = tj.qjets_volatility();
  //     top_tau1 = tj.tau1();
  //     top_tau2 = tj.tau2();
  //     top_tau3 = tj.tau3();
  //     top_mvahiggsdiscr = tj.mvahiggsdiscr();
  //     top_prunedmass = tj.prunedmass();
  //     top_softdropmass = tj.softdropmass();
  //   }
  // }
  // event.set(tt_qjets_volatility,top_qjets_volatility); 
  // event.set(tt_tau1,top_tau1); 
  // event.set(tt_tau2,top_tau2); 
  // event.set(tt_tau3,top_tau3); 
  // event.set(tt_mvahiggsdiscr,top_mvahiggsdiscr); 
  // event.set(tt_prunedmass,top_prunedmass); 
  // event.set(tt_softdropmass,top_softdropmass); 

  //TEST for QCD studies
  // veto on 2-ttag events
  //  if(!(ttagN <= 1)) return false; TEST

  /******************/

  // /* btagN counters */
  // int jetbtagN(0), subjbtagN(0);

  // if(!pass_ttagevt){

  //   for(const auto& j : *event.jets) if(btag_ID_(j, event)) ++jetbtagN;
  // }
  // else {

  //   const ReconstructionHypothesis* ttbar_hyp = get_best_hypothesis(ttbar_hyps, "Chi2");

  //   const TopJet* thad = ttbar_hyp->tophad_topjet_ptr();

  //   for(const auto& j : thad->subjets()) if(btag_ID_(j, event)) ++subjbtagN;

  //   for(const auto& j : *event.jets){

  //     if(!(uhh2::deltaR(*thad, j) > ttag_minDR_jet_)) continue;
  //     if(btag_ID_(j, event)) ++jetbtagN;
  //   }
  // }

  // // const int btagN = jetbtagN + subjbtagN;
  // const int btagN = 0;//TEST
  // const std::string btag_posx = (btagN >= 2 ? "b2" : (btagN >= 1 ? "b1" : "b0"));
  // /******************/

  // // /* CHI2 selection */
  // const bool pass_chi2 = true; //TEST
  // const std::string chi2_posx = pass_chi2 ? "chi2" : "antichi2";
  // const bool pass_chi2 = chi2_sel->passes(event);
  // //  std::cout<<"pass_chi2 = "<<pass_chi2<<std::endl;
  // const std::string chi2_posx = pass_chi2 ? "chi2" : "antichi2";
  // /******************/

  // /* DATA blinding */
  // if(blind_DATA_){

  //   if(lepN == 1 && pass_chi2){

  //     const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");

  //     const float rec_ttbar_M((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());

  //     if(!( rec_ttbar_M < 2000. )) return false;
  //   }
  // }
  // /*****************/

  /* KINE plots */
  if(lepN == 1){

    HFolder("kine")       ->fill(event);
    //    HFolder("kine__ttbar")->fill(event);

    // HFolder("kine__"+ttag_posx+btag_posx)          ->fill(event);
    //    HFolder("kine__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
  }
  /**************/
  //  std::cout<<" KINE plots DONE!"<<std::endl;
  // /* CHI2 plots */
  // if(lepN == 1){

  //   HFolder(chi2_posx)          ->fill(event);
  //   //    HFolder(chi2_posx+"__ttbar")->fill(event);

  //   HFolder(chi2_posx+"__"+ttag_posx+btag_posx)          ->fill(event);
  //   //    HFolder(chi2_posx+"__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
    
  //   if(pass_chi2 && !event.isRealData){
  //     h_btagMCeffi->fill(event);
  //   }
    
  // }
  // else if(lepN == 2){

  //   bool l2_ossf(false);
  //   if     (channel_ == muon) l2_ossf = ((event.muons    ->at(0).charge() * event.muons    ->at(1).charge()) == -1);
  //   else if(channel_ == elec) l2_ossf = ((event.electrons->at(0).charge() * event.electrons->at(1).charge()) == -1);

  //   if(l2_ossf && chi2_posx == "chi2"){

  //     HFolder(chi2_posx+"_L2")          ->fill(event);
  //     HFolder(chi2_posx+"_L2"+"__dilep")->fill(event);
  //     //      HFolder(chi2_posx+"_L2"+"__ttbar")->fill(event);

  //     HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx)          ->fill(event);
  //     HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx+"__dilep")->fill(event);
  //     //      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
  //   }
  // }
  // /**************/
  // //  std::cout<<" CHI2 plots DONE!"<<std::endl;
  // ////

  //// VARS

  // event
  event.set(h_run       , event.run);
  event.set(h_lumi_block, event.luminosityBlock);
  event.set(h_event     , event.event);

  event.set(h_pvN  , event.pvs->size());

  event.set(h_muoN , event.muons    ->size());
  event.set(h_eleN , event.electrons->size());

  // event.set(h_btagN, btagN);
  // event.set(h_ttagN, ttagN);

  // event.set(h_ttagevt, pass_ttagevt);

  // int ttgen_decay(-1);
  // if(!event.isRealData){

  //   const auto& ttgen = event.get(h_ttbar_gen);

  //   if     (ttgen.DecayChannel() == TTbarGen::e_notfound) ttgen_decay = -1;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_had     ) ttgen_decay = 00;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_ehad    ) ttgen_decay = 01;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_muhad   ) ttgen_decay = 02;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_tauhad  ) ttgen_decay = 03;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_ee      ) ttgen_decay = 11;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_emu     ) ttgen_decay = 12;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_etau    ) ttgen_decay = 13;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_mumu    ) ttgen_decay = 22;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_mutau   ) ttgen_decay = 23;
  //   else if(ttgen.DecayChannel() == TTbarGen::e_tautau  ) ttgen_decay = 33;
  // }

  // event.set(h_ttgen, ttgen_decay);
  // //

  // jet
  if(!(event.jets->size() >= 2)) throw std::runtime_error("TTbarLJTriggerStudyLiteModule::process -- logic error: jet multiplicity < 2 ("+std::to_string(event.jets->size())+")");

  TLorentzVector jet1__p4(event.jets->at(0).v4().Px(), event.jets->at(0).v4().Py(), event.jets->at(0).v4().Pz(), event.jets->at(0).v4().E());
  TLorentzVector jet2__p4(event.jets->at(1).v4().Px(), event.jets->at(1).v4().Py(), event.jets->at(1).v4().Pz(), event.jets->at(1).v4().E());

  event.set(h_jet1           , jet1__p4);
  event.set(h_jet2           , jet2__p4);

 
  
  // event.set(tt_nJets,jet_n);
  // //leading jet
  // const Jet* jet1 = &event.jets->at(0);
  // ljet_pt = jet1->pt();
  // event.set(tt_ljet_pt, ljet_pt);
  // ljet_phi = jet1->phi();     ljet_eta = jet1->eta();
  // event.set(tt_ljet_phi, ljet_phi);     event.set(tt_ljet_eta, ljet_eta);
  // ljet_CSV = jet1->btag_combinedSecondaryVertexMVA();
  // event.set(tt_ljet_CSV,ljet_CSV);
  // ljet_M = jet1->v4().M();
  // event.set(tt_ljet_M, ljet_M);

  // if(jet_n>1){
  //   const Jet* jet2 =  &event.jets->at(1);
  //   fjet2_pt = jet2->pt(); fjet2_eta = jet2->eta(); fjet2_phi = jet2->phi();
  //   jet2_M = jet2->v4().M();
  //   jet2_CSV = jet2->btag_combinedSecondaryVertexMVA();
  //   //    std::cout<<"jet2_CSV = "<<jet2_CSV<<std::endl;
  // }
  // if(jet_n>2){
  //   const Jet* jet3 =  &event.jets->at(2);                                                                                              
  //   fjet3_pt = jet3->pt(); fjet3_eta = jet3->eta(); fjet3_phi = jet3->phi(); 
  //   jet3_M = jet3->v4().M();                        
  //   jet3_CSV = jet3->btag_combinedSecondaryVertexMVA();        
  // }
  // event.set(tt_jet2_pt,fjet2_pt); event.set(tt_jet2_phi,fjet2_phi); event.set(tt_jet2_eta,fjet2_eta);
  // event.set(tt_jet3_pt,fjet3_pt); event.set(tt_jet3_phi,fjet3_phi); event.set(tt_jet3_eta,fjet3_eta); 
  // event.set(tt_jet2_M,jet2_M); event.set(tt_jet3_M,jet3_M);
  // event.set(tt_jet2_CSV,jet2_CSV); 
  // //  std::cout<<"one more time ... jet2_CSV = "<<jet2_CSV<<std::endl;
  // event.set(tt_jet3_CSV,jet3_CSV);
  // //

  // // MET
  //  event.set(h_MET, TLorentzVector(event.met->v4().Px(), event.met->v4().Py(), event.met->v4().Pz(), event.met->v4().P()));
  // met_pt = event.met->pt();
  // event.set(tt_met_pt, met_pt); 
  // met_phi = event.met->phi();
  // event.set(tt_met_phi, met_phi); 
  // //

  // // //----------------------------------
  // //  std::cout<<"set bunch of vars in TTree, part1"<<std::endl;
  // // lepton
  const Particle* lep2(0);
  // if(lepN == 2){
  //   if     (channel_ == muon) lep2 = &((lep1 == &event.muons    ->at(0)) ? event.muons    ->at(1) : event.muons    ->at(0));
  //   else if(channel_ == elec) lep2 = &((lep1 == &event.electrons->at(0)) ? event.electrons->at(1) : event.electrons->at(0));
  // }

  if     (channel_ == muon) lep2 = &event.electrons->at(0);
  else if(channel_ == elec) lep2 = &event.muons    ->at(0);

  TLorentzVector lep1__p4(0.,0.,0.,0.), lep2__p4(0.,0.,0.,0.);
  int   lep1__pdgID(0), lep1__charge(0), lep2__pdgID(0), lep2__charge(0);
  float lep1__minDR_jet(-1.), lep1__pTrel_jet(-1.), lep2__minDR_jet(-1.), lep2__pTrel_jet(-1.);
  if(channel_ == muon){

    lep1__pdgID     = lep1->charge() * -13;
    lep1__charge    = lep1->charge();
    lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());

    if(lep2){

      lep2__pdgID     = lep2->charge() * -11;
      lep2__charge    = lep2->charge();
      lep2__p4        = TLorentzVector(lep2->v4().Px(), lep2->v4().Py(), lep2->v4().Pz(), lep2->v4().E());
    }
    //    std::cout<<"set bunch of vars in TTree, part2 (muon)"<<std::endl;
  }
  else if(channel_ == elec){

    lep1__pdgID     = lep1->charge() * -11;
    lep1__charge    = lep1->charge();
    lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());

    if(lep2){

      lep2__pdgID     = lep2->charge() * -13;
      lep2__charge    = lep2->charge();
      lep2__p4        = TLorentzVector(lep2->v4().Px(), lep2->v4().Py(), lep2->v4().Pz(), lep2->v4().E());
    }


    // //Set variables for MVA ------------
    // lep_class = ((Electron*)lep1)->Class();
    // lep_pt = lep1->pt(); lep_eta = lep1->eta(); fabs_lep_eta = fabs(lep_eta); lep_phi = lep1->phi();
    // lep_pt_err = ((Electron*)lep1)->ptError(); lep_eta_err = ((Electron*)lep1)->etaError(); lep_phi_err = ((Electron*)lep1)->phiError();
    // lep_xy = hypot(((Electron*)lep1)->gsfTrack_vx(),((Electron*)lep1)->gsfTrack_vy());
    // lep_fbrem = ((Electron*)lep1)->fbrem();//f_brem = (Pin-Pout)/Pin where Pin, Pout - electron momentum in and out of the tracker

    // lep_Nclusters = ((Electron*)lep1)->Nclusters();
    // lep_full5x5_e1x5 = ((Electron*)lep1)->full5x5_e1x5();
    // lep_full5x5_e2x5Max = ((Electron*)lep1)->full5x5_e2x5Max();
    // lep_full5x5_e5x5 = ((Electron*)lep1)->full5x5_e5x5();
    // lep_dEtaInSeed = ((Electron*)lep1)->dEtaInSeed();
    // lep_dB = ((Electron*)lep1)->dB(); 
    // lep_sigmaIEtaIEta = ((Electron*)lep1)->sigmaIEtaIEta(); 
    // lep_HoverE = ((Electron*)lep1)->HoverE(); 
    // lep_EoverPIn = ((Electron*)lep1)->EoverPIn(); 
    // lep_hcalOverEcal = ((Electron*)lep1)->hcalOverEcal(); 
    // lep_dr03TkSumPt = ((Electron*)lep1)->dr03TkSumPt(); 
    // lep_effArea = ((Electron*)lep1)->effArea(); 
    // lep_mvaNonTrigV0 = ((Electron*)lep1)->mvaNonTrigV0();
    // lep_dEtaIn = ((Electron*)lep1)->dEtaIn();
    // lep_dPhiIn = ((Electron*)lep1)->dPhiIn();

    // //the closest to lepton jet
    // // find jet with smallest angle to lepton (the closest jet to lepton)
    // int jet_pos = 0;
    // dR_lep_cljet = 1e7;
    // jets_pt = (&event.jets->at(0))->pt();
    // for(int i=1; i<jet_n; i++){//skip leading jet
    //   const Particle* jeti =  &event.jets->at(i);
    //   jets_pt += jeti->pt();
    //   float dR_current = uhh2::deltaR(*lep1, *jeti);
    //   if(dR_lep_cljet>dR_current){// min distance in eta-phi
    // 	dR_lep_cljet = dR_current;      
    // 	jet_pos = i;
    //   }
    // }
   
    // const Jet*  jet0 =  &event.jets->at(jet_pos); 
    // cjet_pt = jet0->pt();
    // cjet_phi = jet0->phi(); cjet_eta = jet0->eta();
    // dR_lep_ljet = uhh2::deltaR(*lep1, *jet1);
    // lep_pt_ljet = pTrel(*lep1, jet1);
    // dR_cljet_ljet = uhh2::deltaR(*jet0, *jet1);
    // dPhi_lep_met = uhh2::deltaPhi(*event.met, *lep1);
    // MwT = sqrt(2*fabs(lep_pt*met_pt*(1-cos(fabs(dPhi_lep_met)))));
    // dPhi_ljet_met = uhh2::deltaPhi(*event.met,*jet1);
    // dPhi_cjet_met = uhh2::deltaPhi(*event.met,*jet0);
    // lep_pt_cjet = pTrel(*lep1, jet0);
    // cjet_pt_ljet = pTrel(*jet0, jet1);// the closest not leading jet Pt to the leading jet axis
    // cjet_M = jet0->v4().M();
    // cjet_CSV = jet0->btag_combinedSecondaryVertexMVA();       

    // //    std::cout<<"set bunch of vars in TTree, part2 (elec)"<<std::endl; 
  }

  // event.set(tt_lep_class, lep_class);
  // event.set(tt_lep_pt, lep_pt);   event.set(tt_lep_eta, lep_eta); event.set(tt_lep_phi, lep_phi);
  // event.set(tt_lep_pt_err, lep_pt_err); event.set(tt_lep_eta_err, lep_eta_err); event.set(tt_lep_phi_err, lep_phi_err);
  // event.set(tt_lep_xy,lep_xy);
  // event.set(tt_lep_fbrem,lep_fbrem);
  // event.set(tt_Nclusters,lep_Nclusters);   
  // event.set(tt_full5x5_e1x5,lep_full5x5_e1x5);
  // event.set(tt_full5x5_e2x5Max,lep_full5x5_e2x5Max);
  // event.set(tt_full5x5_e5x5,lep_full5x5_e5x5);
  // event.set(tt_dEtaInSeed,lep_dEtaInSeed);
  // event.set(tt_dB, lep_dB);
  // event.set(tt_sigmaIEtaIEta,lep_sigmaIEtaIEta);
  // event.set(tt_HoverE, lep_HoverE);
  // event.set(tt_EoverPIn, lep_EoverPIn);
  // event.set(tt_hcalOverEcal, lep_hcalOverEcal);
  // event.set(tt_dr03TkSumPt, lep_dr03TkSumPt);
  // event.set(tt_effArea, lep_effArea);
  // event.set(tt_mvaNonTrigV0, lep_mvaNonTrigV0);
  // event.set(tt_dEtaIn, lep_dEtaIn);
  // event.set(tt_dPhiIn, lep_dPhiIn);

  // event.set(tt_dR_lep_cljet, dR_lep_cljet); 
  // event.set(tt_jets_pt,jets_pt);
  // event.set(tt_cjet_pt,cjet_pt);
  // event.set(tt_cjet_phi,cjet_phi); event.set(tt_cjet_eta,cjet_eta);
  // event.set(tt_dR_lep_ljet, dR_lep_ljet); 
  // event.set(tt_lep_pt_ljet, lep_pt_ljet);
  // event.set(tt_dR_cljet_ljet, dR_cljet_ljet);
  // event.set(tt_MwT,MwT);
  // event.set(tt_dPhi_lep_met,dPhi_lep_met);
  // event.set(tt_dPhi_ljet_met,dPhi_ljet_met);
  // event.set(tt_dPhi_cjet_met,dPhi_cjet_met);
  // event.set(tt_cjet_pt_ljet,cjet_pt_ljet);
  // event.set(tt_lep_pt_cjet,lep_pt_cjet);
  // event.set(tt_cjet_M, cjet_M);
  // event.set(tt_cjet_CSV,cjet_CSV);


  event.set(h_lep1           , lep1__p4);
  event.set(h_lep1__pdgID    , lep1__pdgID);
  event.set(h_lep1__charge   , lep1__charge);
  event.set(h_lep1__minDR_jet, lep1__minDR_jet);
  event.set(h_lep1__pTrel_jet, lep1__pTrel_jet);

  event.set(h_lep2           , lep2__p4);
  event.set(h_lep2__pdgID    , lep2__pdgID);
  event.set(h_lep2__charge   , lep2__charge);
  event.set(h_lep2__minDR_jet, lep2__minDR_jet);
  event.set(h_lep2__pTrel_jet, lep2__pTrel_jet);
  //

  // //  std::cout<<"set bunch of vars in TTree"<<std::endl;
  // // ttbar reco hyp
  // const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");
  // if(!rec_ttbar) throw std::runtime_error("TTbarLJTriggerStudyLiteModule::process -- logic error: ttbar reconstruction hypothesis (\"get_best_hypothesis\", discr=Chi2) not found");

  // // const float MET__pz = rec_ttbar->neutrino_v4().Pz();
  // event.set(h_MET__pz, -1);

  // // const float rec_chi2 = rec_ttbar->discriminator("Chi2");
  // event.set(h_rec_chi2, -1);

  // // const LorentzVector tlep(rec_ttbar->toplep_v4());
  // // const LorentzVector thad(rec_ttbar->tophad_v4());

  // // event.set(h_rec_tlep, TLorentzVector(tlep.Px(), tlep.Py(), tlep.Pz(), tlep.E()));
  // // event.set(h_rec_thad, TLorentzVector(thad.Px(), thad.Py(), thad.Pz(), thad.E()));
  // // //
  // event.set(h_rec_tlep,  TLorentzVector(0,0,0,0)); event.set(h_rec_thad,TLorentzVector(0, 0, 0, 0));

  // // weight
  // event.set(h_wgtMC__GEN         , w_GEN);

  // event.set(h_wgtMC__elecIDSF_ct , w_elecIDSF_ct);
  // event.set(h_wgtMC__elecIDSF_up , w_elecIDSF_up);
  // event.set(h_wgtMC__elecIDSF_dn , w_elecIDSF_dn);

  // event.set(h_wgtMC__elecHLTSF_ct, w_elecHLTSF_ct);
  // event.set(h_wgtMC__elecHLTSF_up, w_elecHLTSF_up);
  // event.set(h_wgtMC__elecHLTSF_dn, w_elecHLTSF_dn);

  // event.set(h_wgtMC__ttagSF_ct  , w_ttagSF_ct );
  // event.set(h_wgtMC__ttagSF_upL , w_ttagSF_upL);
  // event.set(h_wgtMC__ttagSF_dnL , w_ttagSF_dnL);
  // event.set(h_wgtMC__ttagSF_upT , w_ttagSF_upT);
  // event.set(h_wgtMC__ttagSF_dnT , w_ttagSF_dnT);

  // event.set(h_wgtMC__muR_ct__muF_up, w_muR_ct__muF_up);
  // event.set(h_wgtMC__muR_ct__muF_dn, w_muR_ct__muF_dn);
  // event.set(h_wgtMC__muR_up__muF_ct, w_muR_up__muF_ct);
  // event.set(h_wgtMC__muR_up__muF_up, w_muR_up__muF_up);
  // event.set(h_wgtMC__muR_dn__muF_ct, w_muR_dn__muF_ct);
  // event.set(h_wgtMC__muR_dn__muF_dn, w_muR_dn__muF_dn);

  // if(!topptREWGT.get())
  //   event.set(h_wgtMC__topptREWGT_ct , 1.);

  // event.set(h_wgtMC__topptREWGT_up , w_topptREWGT_up);
  // event.set(h_wgtMC__topptREWGT_dn , w_topptREWGT_dn);

  // event.set(h_wgtMC__wjetsREWGT_ct , w_wjetsREWGT_ct);

  // event.set(h_wgtMC__PDF, std::move(w_PDF));
  // //

  // ////

  // // const ReconstructionHypothesis* rec_ttbar_ = get_best_hypothesis(ttbar_hyps, "Chi2");
  // // rec_ttbar_M_ = ((rec_ttbar_->top_v4()+rec_ttbar_->antitop_v4()).M());
  // //  event.set(tt_mttbar,rec_ttbar_M_);
  // event.set(tt_mttbar,-1);

  //   if(channel_ == elec){
  // varMVA[0] = lep_pt/rec_ttbar_M_;
  // varMVA[1] = fabs(lep_eta);
  // varMVA[2] = lep_eta_err;
  // varMVA[3] = lep_pt_err;
  // varMVA[4] = lep_full5x5_e5x5;
  // varMVA[5] = lep_dB;
  // varMVA[6] = fabs(lep_dPhiIn);
  // varMVA[7] = fabs(lep_dEtaInSeed);
  // varMVA[8] = lep_hcalOverEcal;
  // varMVA[9] = lep_dr03TkSumPt;
  // varMVA[10] = lep_effArea;
  // varMVA[11] = lep1__minDR_jet;
  // varMVA[12] = fabs(ljet_eta);
  // varMVA[13] = ljet_CSV;
  // varMVA[14] = fabs(fjet2_eta);
  // varMVA[15] = fjet2_pt/rec_ttbar_M_;
  // varMVA[16] = jet2_CSV;
  // varMVA[17] = met_pt/MwT;
  // varMVA[18] = ttagN;
  // varMVA[19] = btagN;
  
  // // if(ljet_CSV<-1. || lep_pt_err>1000.) 
  // //    return false; // do NOT use unphysical data
  // TMVA_response = reader->EvaluateMVA(methodName);
  // //  if(TMVA_response<0.5) return false; //BDTG_DATADriven_MET40_20vars
  // event.set(tt_TMVA_response, TMVA_response);
  // //std::cout<<"TMVA_response = "<<TMVA_response<<std::endl;
  //   }
  // // if(!pass_chi2) 
  // //   return false;

  // //  if(TMVA_response<0.9) return false; //MLP

  //   //    std::cout<<"event.weight = "<<event.weight<<std::endl;
  // event.set(tt_ev_weight,event.weight);
  // if(!event.isRealData){
  //   const TTbarGen* ttbargen(0);
  //   const auto& ttgen = event.get(h_ttbar_gen);
  //   ttbargen = &ttgen;
  //   LorentzVector gen_ttbar = ttbargen->Top().v4()+ttbargen->Antitop().v4();
  //   gen_ttbar_M_ = gen_ttbar.M();
  // }
  // event.set(tt_mttbar_gen,gen_ttbar_M_);


  //  HFolder("Final")->fill(event);
  //  HFolder("Final__ttbar")->fill(event);

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TTbarLJTriggerStudyLiteModule)
