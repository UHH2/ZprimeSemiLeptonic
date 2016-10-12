#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

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
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/DileptonHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/EffyTTbarRECOHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/SF_elec.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_ttagging.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_WjetsREWGT.h>

#include <TMVA/Factory.h>
#include <TMVA/Tools.h>
#include <TMVA/Reader.h>



class BDTQCDVariableDumpModule : public ModuleBASE {

 public:
  explicit BDTQCDVariableDumpModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:
  enum lepton { muon, elec };
  lepton channel_;

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;

  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> trigger_sel;
  std::unique_ptr<uhh2::Selection> trigger2_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> triangc_sel;
  std::unique_ptr<uhh2::Selection> ttagevt_sel;
  std::unique_ptr<uhh2::Selection> topleppt_sel;
  std::unique_ptr<uhh2::Selection> chi2_sel;

  // ttbar reconstruction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  std::unique_ptr<uhh2::AnalysisModule> reco_primlep;

  std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag0;
  std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag1;
  std::unique_ptr<Chi2Discriminator>     ttbar_chi2__ttag0;
  std::unique_ptr<Chi2DiscriminatorTTAG> ttbar_chi2__ttag1;

  uhh2::Event::Handle<TTbarGen> h_ttbar_gen;
  uhh2::Event::Handle<std::vector<ReconstructionHypothesis> > h_ttbar_hyps;

  float lep1_pt_;
  float muo1_pt_max_, muo1_eta_max_;

  JetId btag_ID_;
  CSVBTag::wp b_working_point;

  bool use_ttagging_;
  TopJetId ttag_ID_;
  float    ttag_minDR_jet_;

  bool blind_DATA_;

  bool store_PDF_weights_;

  //// Data/MC scale factors
    std::unique_ptr<uhh2::AnalysisModule> elecID_SF;
    std::unique_ptr<uhh2::AnalysisModule> elecGsf_SF;
    
    std::unique_ptr<uhh2::AnalysisModule> pileupSF;
    std::unique_ptr<uhh2::AnalysisModule> muonID_SF;
    std::unique_ptr<uhh2::AnalysisModule> muonHLT_SF;
    std::unique_ptr<uhh2::AnalysisModule> muonHLT2_SF;
    std::unique_ptr<uhh2::AnalysisModule> muonTRK_SF;
//!!  std::unique_ptr<weightcalc_elecHLT> elecHLTSF;

  std::unique_ptr<uhh2::AnalysisModule> btagSF;
  std::unique_ptr<Hists> h_btagMCeffi;

  std::unique_ptr<weightcalc_ttagging> ttagSF_ct;
  std::unique_ptr<weightcalc_ttagging> ttagSF_upL;
  std::unique_ptr<weightcalc_ttagging> ttagSF_dnL;
  std::unique_ptr<weightcalc_ttagging> ttagSF_upT;
  std::unique_ptr<weightcalc_ttagging> ttagSF_dnT;

  //std::unique_ptr<weightcalc_topptREWGT> topptREWGT;
    std::unique_ptr<TopPtReweight> topptREWGT;
  std::unique_ptr<weightcalc_WjetsREWGT> wjetsREWGT;
  ////

    //For usage of run dependent muonHLT Effs
    double lumi_tot;
    double lumi1;
    double lumi2;
  //// VARS

  // event
  Event::Handle<int>   h_run;
  Event::Handle<int>   h_lumi_block;
  Event::Handle<int>   h_event;
  Event::Handle<int>   h_pvN;
  Event::Handle<int>   h_muoN;
  Event::Handle<int>   h_eleN;
  Event::Handle<int>   h_btagN;
  Event::Handle<int>   h_ttagN;
  Event::Handle<bool>  h_ttagevt;
  Event::Handle<int>   h_ttgen;
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
   // MET
  Event::Handle<TLorentzVector> h_MET;
  
  //

  // ttbar reco hyp
  Event::Handle<float>          h_rec_chi2;
  Event::Handle<TLorentzVector> h_rec_tlep;
  Event::Handle<TLorentzVector> h_rec_thad;
  //

  // weight
  Event::Handle<float> h_wgtMC__GEN;

  //dump variables after BDT QCD training
  float rec_ttbar_M_, lep_eta_err,  dPhi_lep_met,fjet2_pt,lep_pt, lep_eta, lep_pt_err, lep_full5x5_e5x5, lep_dB, lep_dPhiIn, lep_dEtaInSeed, lep_hcalOverEcal, lep_dr03TkSumPt, lep_effArea,  ljet_eta, ljet_CSV, fjet2_eta, fjet_pt, jet2_CSV, met_pt, MwT;
    float TMVA_response;
    Event::Handle<float> tt_TMVA_response;// response of TMVA method
    std::unique_ptr<TMVA::Reader> reader_qcd;
    TString methodName;
    float varMVA[20];       
  Event::Handle<float> h_lep_eta_err;
  //Event::Handle<float> h_dPhi_lep_met;
  Event::Handle<float> h_fjet2_pt;
  Event::Handle<float> h_lep_pt;
  Event::Handle<float> h_lep_eta;
  Event::Handle<float> h_lep_pt_err;
  Event::Handle<float> h_lep_full5x5_e5x5;
  Event::Handle<float> h_lep_dB;
  Event::Handle<float> h_lep_dPhiIn;
  Event::Handle<float> h_lep_dEtaInSeed;
  Event::Handle<float> h_lep_hcalOverEcal;
  Event::Handle<float> h_lep_dr03TkSumPt;
  Event::Handle<float> h_lep_effArea;
  Event::Handle<float> h_ljet_eta;
  Event::Handle<float> h_ljet_CSV;
  Event::Handle<float> h_fjet2_eta;
 // Event::Handle<float> h_fjet_pt;
  Event::Handle<float> h_jet2_CSV;
  Event::Handle<float> h_met_pt;
  //Event::Handle<float> h_MwT;




};

BDTQCDVariableDumpModule::BDTQCDVariableDumpModule(uhh2::Context& ctx){

  //// CONFIGURATION
  const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else {

    std::string log("TTbarLJAnalysisLiteBDTDumpVariablesModule::TTbarLJAnalysisLiteBDTDumpVariablesModule -- ");
    log += "TTbarLJAnalysisLiteBDTDumpVariablesModule::TTbarLJAnalysisLiteBDTDumpVariablesModule -- invalid argument for 'channel' key in xml file (must be 'muon' or 'elec'): \""+channel+"\"";

    throw std::runtime_error(log);
  }

  use_ttagging_ = true;

  blind_DATA_ = ((ctx.get("dataset_version").find("BLINDED") != std::string::npos) && (ctx.get("dataset_type") == "DATA") && !isMC);

  const std::string& store_PDF_weights = ctx.get("store_PDF_weights", "");
  if     (store_PDF_weights == "true")  store_PDF_weights_ = true;
  else if(store_PDF_weights == "false") store_PDF_weights_ = false;
  else {

    std::string log("TTbarLJAnalysisLiteBDTDumpVariablesModule::TTbarLJAnalysisLiteBDTDumpVariablesModule -- ");
    log += "invalid argument for 'store_PDF_weights' key in xml file (must be 'true' or 'false'): \""+store_PDF_weights+"\"";

    throw std::runtime_error(log);
  }
  //

  const std::string& keyword = ctx.get("keyword");

  float jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);
  bool triangul_cut(false);
  bool topleppt_cut(false);

  if(keyword == "T0_v01" || keyword == "T1_v01"){

    if     (keyword == "T0_v01") use_ttagging_ = false;
    else if(keyword == "T1_v01") use_ttagging_ = true;

    if(channel_ == muon){

      lep1_pt_ =   0.;

      jet1_pt  = 150.;
      jet2_pt  =  50.;

      MET      =  50.;
      HT_lep   = 150.;

      triangul_cut = false;
      topleppt_cut = false;
    }
    else if(channel_ == elec){

      lep1_pt_ =   0.;

      jet1_pt  = 150.;
      jet2_pt  =  70.;

      MET      =  50.;
      HT_lep   =   0.;

      triangul_cut = false;
      topleppt_cut = false;
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
      topleppt_cut = false;
    }
    else if(channel_ == elec){

      lep1_pt_ = 110.;

      jet1_pt  = 150.;
      jet2_pt  =  50.;

      MET      = 100.;
      HT_lep   =   0.;

      triangul_cut = false;
      topleppt_cut = false;
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
      topleppt_cut = false;
    }
    else if(channel_ == elec){

      throw std::runtime_error("TTbarLJAnalysisLiteBDTDumpVariablesModule::TTbarLJAnalysisLiteBDTDumpVariablesModule -- undefined working-point for \""+keyword+"\" in \"elec\" channel");
    }
  }
  else if(keyword == "T0_v04" || keyword == "T1_v04"){

    if     (keyword == "T0_v04") use_ttagging_ = false;
    else if(keyword == "T1_v04") use_ttagging_ = true;

    if(channel_ == muon){

      throw std::runtime_error("TTbarLJAnalysisLiteBDTDumpVariablesModule::TTbarLJAnalysisLiteBDTDumpVariablesModule -- undefined working-point for \""+keyword+"\" in \"muon\" channel");
    }
    else if(channel_ == elec){

      lep1_pt_ =   0.;

      jet1_pt  = 250.;
      jet2_pt  =  70.;

      MET      =  50.;
      HT_lep   =   0.;

      triangul_cut = false;
      topleppt_cut = false;
    }
  }
  else throw std::runtime_error("TTbarLJAnalysisLiteBDTDumpVariablesModule::TTbarLJAnalysisLiteBDTDumpVariablesModule -- undefined \"keyword\" argument in .xml configuration file: "+keyword);
  //

  ////

  //// COMMON MODULES

  /* CMS-certified luminosity sections */
  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  /**********************************/

  ////

  //// OBJ CLEANING
  ////

  //// EVENT SELECTION
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));

  const std::string& trigger = ctx.get("trigger", "NULL");
  if(trigger != "NULL") trigger_sel.reset(new TriggerSelection(trigger));
  else                  trigger_sel.reset(new uhh2::AndSelection(ctx));

  met_sel  .reset(new METCut  (0   , 5000));
  htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));

  if(triangul_cut){

    if     (channel_ == elec) triangc_sel.reset(new TriangularCuts(M_PI/2., (M_PI/2.)/75.));
    else if(channel_ == muon) triangc_sel.reset(new uhh2::AndSelection(ctx));
  }
  else triangc_sel.reset(new uhh2::AndSelection(ctx));
  ////

  /* b-tagging */
  const std::string& btag_wp = ctx.get("btag_wp");

  if     (btag_wp == "CSVL") btag_ID_ = CSVBTag(CSVBTag::WP_LOOSE);
  else if(btag_wp == "CSVM") btag_ID_ = CSVBTag(CSVBTag::WP_MEDIUM);
  else if(btag_wp == "CSVT") btag_ID_ = CSVBTag(CSVBTag::WP_TIGHT);

  if     (btag_wp == "CSVL") b_working_point = CSVBTag::WP_LOOSE;
  else if(btag_wp == "CSVM") b_working_point = CSVBTag::WP_MEDIUM;
  else if(btag_wp == "CSVT") b_working_point = CSVBTag::WP_TIGHT;

  h_btagMCeffi.reset(new BTagMCEfficiencyHists(ctx,"chi2__BTAG",b_working_point));

  /*************/

  /* t-tagging */
  const std::string& ttag_wp = ctx.get("ttag_wp");

  ttag_ID_ = TopTagID_SoftDrop(ttag_wp);
  ttag_minDR_jet_ = 1.2;

  ttagevt_sel.reset(new TopTagEventSelection(ttag_ID_, ttag_minDR_jet_));
  /*************/

  //// TTBAR KINEMATICAL RECO

  const std::string ttbar_gen_label ("ttbargen");
  const std::string ttbar_hyps_label("TTbarReconstruction");
  const std::string ttbar_chi2_label("Chi2");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));
  h_ttbar_gen = ctx.get_handle<TTbarGen>   (ttbar_gen_label);

  reco_primlep.reset(new PrimaryLepton(ctx));

  ttbar_reco__ttag0.reset(new HighMassTTbarReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label));
  ttbar_reco__ttag1.reset(new        TopTagReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label, ttag_ID_, ttag_minDR_jet_));

  ttbar_chi2__ttag0.reset(new Chi2Discriminator(ctx, ttbar_hyps_label));
  ttbar_chi2__ttag0->set_Mtlep_mean (175.);
  ttbar_chi2__ttag0->set_Mtlep_sigma( 19.);
  ttbar_chi2__ttag0->set_Mthad_mean (177.);
  ttbar_chi2__ttag0->set_Mthad_sigma( 16.);

  ttbar_chi2__ttag1.reset(new Chi2DiscriminatorTTAG(ctx, ttbar_hyps_label));
  ttbar_chi2__ttag1->set_Mtlep_mean (175.);
  ttbar_chi2__ttag1->set_Mtlep_sigma( 19.);
  ttbar_chi2__ttag1->set_Mthad_mean (173.);
  ttbar_chi2__ttag1->set_Mthad_sigma( 15.);
  ttbar_chi2__ttag1->use_subjet_mass(false);

  h_ttbar_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis> >(ttbar_hyps_label);
  ////

  if(topleppt_cut){

    if     (channel_ == elec) topleppt_sel.reset(new LeptonicTopPtCut(ctx, 140., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label));
    else if(channel_ == muon) topleppt_sel.reset(new uhh2::AndSelection(ctx));
  }
  else topleppt_sel.reset(new uhh2::AndSelection(ctx));

  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., 30., ttbar_hyps_label, ttbar_chi2_label));

  //// HISTS

  std::vector<std::string> htags_1({

    "jet2",
    "jet1",
    "trigger",
    "met",
    "htlep",
    "triangc",
    "topleppt",
  });

  for(const auto& tag : htags_1){

    book_HFolder(tag, new TTbarLJHists(ctx, tag, ttag_ID_, ttag_minDR_jet_));
  }
  //

  std::vector<std::string> htags_2({

    "kine",
    "kine__t0b0",
    "kine__t0b1",
    //"kine__t0b2",
    "kine__t1b",
    //"kine__t1b1",
    //"kine__t1b2",

    "antichi2",
    "antichi2__t0b0",
    "antichi2__t0b1",
    //"antichi2__t0b2",
    "antichi2__t1b",
    //"antichi2__t1b1",
    //"antichi2__t1b2",

    "chi2",
    "chi2__t0b0",
    "chi2__t0b1",
   // "chi2__t0b2",
    "chi2__t1b",
   // "chi2__t1b1",
   // "chi2__t1b2",
      
    "chi2_bdt",
    "chi2_bdt__t0b0",
   "chi2_bdt__t0b1",
   "chi2_bdt__t1b",
  });

  for(const auto& tag : htags_2){

    book_HFolder(tag          , new TTbarLJHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  }
  //

  std::vector<std::string> htags_3({

    "chi2_L2",
    "chi2_L2__t0b0",
    "chi2_L2__t0b1",
    //"chi2_L2__t0b2",
    "chi2_L2__t1b",
   // "chi2_L2__t1b1",
    //"chi2_L2__t1b2",
  });

  for(const auto& tag : htags_3){

    book_HFolder(tag          , new TTbarLJHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
    book_HFolder(tag+"__dilep", new DileptonHists     (ctx, tag+"__dilep"));
    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  }
  //

  ////

  //// Data/MC scale factors

  //
    //
    
    // muon-ID
    const std::string& muonID_SFac    = ctx.get("muonID_SF_file");
    const std::string& muonID_directory    = ctx.get("muonID_SF_directory");
    
    
    // muon-HLT
    const std::string& muonHLT_SFac   = ctx.get("muonHLT_SF_file");
    const std::string& muonHLT_directory   = ctx.get("muonHLT_SF_directory");
    const std::string& muonHLT2_directory   = ctx.get("muonHLT2_SF_directory");
    
    //muon-Trk
    const std::string& muonTRK_SFac   = ctx.get("muonTRK_SF_file");
    
    // elec-ID
    const std::string& elecID_SFac    = ctx.get("elecID_SF_file");
    
    // elec-ID
    const std::string& elecGsf_SFac    = ctx.get("elecGsf_SF_file");
    

//!!  // elec-HLT
//!!  const std::string& elecHLT_SFac   = ctx.get("elecHLT_SF_file");
//!!  const std::string& elecHLT_hist   = ctx.get("elecHLT_SF_hist");
//!!
//!!  elecHLTSF.reset(new weightcalc_elecHLT(ctx, "electrons", elecHLT_SFac, elecHLT_hist, 0.005));
//!!  //


  // t-tagging
  const std::string& ttag_SFac_file = ctx.get("ttag_SFs");
  const std::string& ttag_effy_file = ctx.get("ttag_eff");
  const std::string& ttag_effyL     = ctx.get("ttag_eff__jetL");
  const std::string& ttag_effyT     = ctx.get("ttag_eff__jetT");

  ttagSF_ct .reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));

  ttagSF_upL.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "UP", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));
  ttagSF_dnL.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "DN", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));

  ttagSF_upT.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "UP", ttag_effy_file, ttag_effyL, ttag_effyT));
  ttagSF_dnT.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "DN", ttag_effy_file, ttag_effyL, ttag_effyT));
  //
    //reset here to avaoid dublication of output in the tree
    muonHLT2_SF.reset(new MCMuonScaleFactor(ctx, muonHLT_SFac, muonHLT2_directory, 0.0, "HLT",true));//TEST
    
    //// VARS
    ctx.undeclare_all_event_output();
    
    //pileup (define it after undeclaring all other variables to keep the weights in the output)
    pileupSF.reset(new MCPileupReweight(ctx));
    
    // //muon ID scale factors
    muonID_SF.reset(new MCMuonScaleFactor(ctx, muonID_SFac, muonID_directory, 1.12, "ID")); //hypot(1.0%,0.5%)
    // //  muonHLT_SF.reset(new MCMuonScaleFactor(ctx, muonHLT_SFac, muonHLT_directory, 0.5, "HLT",false));//TEST
    muonHLT_SF.reset(new MCMuonScaleFactor(ctx, muonHLT_SFac, muonHLT_directory, 0.0, "HLT",true));//TEST
    lumi_tot = string2double(ctx.get("target_lumi"));
    lumi1 = 622.;//0.622/fb in 2016 data
    lumi2 = lumi_tot - lumi1;
    
    muonTRK_SF.reset(new MCMuonTrkScaleFactor(ctx, muonTRK_SFac, 0.0, "TRK"));
    
    // // elec-ID
    elecID_SF.reset(new MCElecScaleFactor(ctx, elecID_SFac, 0.0, "ID"));
    // double lumi_tot = string2double(ctx.get("target_lumi"));
    // double lumi1 = 500.;//0.5/fb in 2016 data
    // double lumi2 = lumi_tot - lumi1;
    // elecID_SF.reset(new MCElecScaleFactor2(ctx, elecID_SFac_Data_part1, elecID_SFac, lumi1, lumi2, 0.0, "ID"));
    
    // // elec-ID
    elecGsf_SF.reset(new MCElecScaleFactor(ctx, elecGsf_SFac, 0.0, "Gsf"));
    
    // //b-tagging scale factors
    //  btagSF.reset(new MCBTagScaleFactor(ctx, b_working_point));
    btagSF.reset(new MCBTagScaleFactor(ctx, b_working_point,"jets","central","comb","incl","MCBtagEfficiencies"));
    //  btagSF.reset(new uhh2::AndSelection(ctx));//TEST
    


  // event
  h_run             = ctx.declare_event_output<int>("run");
  h_lumi_block      = ctx.declare_event_output<int>("lumi_block");
  h_event           = ctx.declare_event_output<int>("event");

  h_pvN             = ctx.declare_event_output<int>("pvN");

  h_muoN            = ctx.declare_event_output<int>("muoN");
  h_eleN            = ctx.declare_event_output<int>("eleN");

  h_btagN           = ctx.declare_event_output<int>("btagN");
  h_ttagN           = ctx.declare_event_output<int>("ttagN");

  h_ttagevt         = ctx.declare_event_output<bool>("ttagevt");

  h_ttgen           = ctx.declare_event_output<int>("ttgen");
  //

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
  // MET
  h_MET             = ctx.declare_event_output<TLorentzVector>("MET");

  //

  // ttbar reco hyp
  h_rec_chi2        = ctx.declare_event_output<float>         ("rec_chi2");
  h_rec_tlep        = ctx.declare_event_output<TLorentzVector>("rec_tlep");
  h_rec_thad        = ctx.declare_event_output<TLorentzVector>("rec_thad");
  // weight
  h_wgtMC__GEN            = ctx.declare_event_output<float>("wgtMC__GEN");

  h_lep_eta_err  = ctx.declare_event_output<float>("lep_eta_err");
//  h_dPhi_lep_met  = ctx.declare_event_output<float>();
//  h_fjet2_pt  = ctx.declare_event_output<float>();
  h_lep_pt  = ctx.declare_event_output<float>("lep_pt");
  h_lep_eta  = ctx.declare_event_output<float>("lep_eta");
  h_lep_pt_err = ctx.declare_event_output<float>("lep_pt_err");
  h_lep_full5x5_e5x5  = ctx.declare_event_output<float>("lep_full5x5_e5x5");
  h_lep_dB  = ctx.declare_event_output<float>("lep_dB");
  h_lep_dPhiIn  = ctx.declare_event_output<float>("lep_dPhiIn");
  h_lep_dEtaInSeed  = ctx.declare_event_output<float>("lep_dEtaInSeed");
  h_lep_hcalOverEcal  = ctx.declare_event_output<float>("lep_hcalOverEcal");
  h_lep_dr03TkSumPt  = ctx.declare_event_output<float>("lep_dr03TkSumPt");
  h_lep_effArea  = ctx.declare_event_output<float>("lep_effArea");
  h_ljet_eta = ctx.declare_event_output<float>("ljet_eta");
  h_ljet_CSV = ctx.declare_event_output<float>("ljet_CSV");
  h_fjet2_eta = ctx.declare_event_output<float>("fjet2_eta");
  h_fjet2_pt  = ctx.declare_event_output<float>("fjet2_pt");
  h_jet2_CSV  = ctx.declare_event_output<float>("jet2_CSV");
  h_met_pt  = ctx.declare_event_output<float>("met_pT");
  //h_ttagN = ctx.declare_event_output<float>("ttagN");
  //h_btagN = ctx.declare_event_output<float>("btagN");

    TMVA_response = -100;
  tt_TMVA_response = ctx.declare_event_output<float>("TMVA_response"); // this var is ploted in hist class, should always be filled
  if(channel_ == elec){
    reader_qcd.reset(new TMVA::Reader( "!Color:!Silent" ));
    reader_qcd->AddVariable("lep_pt/Mttbar", &varMVA[0]);
    reader_qcd->AddVariable("fabs(lep_eta)", &varMVA[1]);
    reader_qcd->AddVariable("lep_eta_err",&varMVA[2]);
    reader_qcd->AddVariable("lep_pt_err", &varMVA[3]);
    reader_qcd->AddVariable("lep_full5x5_e5x5", &varMVA[4]);
    reader_qcd->AddVariable("lep_dB", &varMVA[5]);
    reader_qcd->AddVariable("fabs(lep_dPhiIn)", &varMVA[6]);
    reader_qcd->AddVariable("fabs(lep_dEtaInSeed)", &varMVA[7]);
    reader_qcd->AddVariable("lep_hcalOverEcal", &varMVA[8]);
    reader_qcd->AddVariable("lep_dr03TkSumPt", &varMVA[9]);
    reader_qcd->AddVariable("lep_effArea", &varMVA[10]);
    reader_qcd->AddVariable("lep1__minDR_jet", &varMVA[11]);
    reader_qcd->AddVariable("fabs(ljet_eta)", &varMVA[12]);
    reader_qcd->AddVariable("ljet_CSV", &varMVA[13]);
    reader_qcd->AddVariable("fabs(fjet2_eta)", &varMVA[14]);
    reader_qcd->AddVariable("fjet2_pt/Mttbar", &varMVA[15]);
    reader_qcd->AddVariable("jet2_CSV", &varMVA[16]);
    reader_qcd->AddVariable("met_pt/MwT", &varMVA[17]);
    reader_qcd->AddVariable("ttagN", &varMVA[18]);
    reader_qcd->AddVariable("btagN", &varMVA[19]);
  

    //  TString dir    = "/afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_7_6_3_patch2/src/UHH2/ZprimeSemiLeptonic/TMVA_weights/76X/"; //ToDo: make it param in xml
    TString dir    = "/nfs/dust/cms/user/dansand/UHH2_2015/80X_BDT_v1/CMSSW_8_0_8/src/UHH2/ZprimeSemiLeptonic/TMVA_weights/76X/"; //ToDo: make it param in xml
    methodName = "BDT::BDTG";
    TString weightfile = dir + "Homemade_TTbarMVAClassification_BDTG_DataDriven_MET40_20vras.weights.xml";
    //            // methodName = "MLP::MLPBNN";
    //              // TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_DataDrivenMET30_24Vars_N-22_N+2.weights.xml";
    reader_qcd->BookMVA(methodName, weightfile);
    }
  

}

bool BDTQCDVariableDumpModule::process(uhh2::Event& event){

  //// COMMON MODULES
    event.set(tt_TMVA_response, 0);//set some dummy initial value
    event.set(h_lep_eta_err, 0);
    event.set(h_lep_pt, 0);
    //event.set(h_lep_eta,0);
    event.set(h_lep_pt_err ,0);
    event.set(h_lep_full5x5_e5x5,0);
    event.set(h_lep_dB,0);
    
    event.set(h_lep_dPhiIn,0);
    event.set(h_lep_dEtaInSeed,0);
    event.set(h_lep_hcalOverEcal,0);
    event.set(h_lep_dr03TkSumPt,0);
    event.set(h_lep_effArea, 0);
    event.set(h_ljet_eta,0);
    event.set(h_ljet_CSV,0);
    event.set(h_fjet2_eta,0);
    event.set(h_fjet2_pt,0);
    event.set(h_jet2_CSV,0);
    event.set(h_met_pt,0);
   
   float w_GEN(1.);
    if(!event.isRealData)
        w_GEN = event.weight;
  if(!event.isRealData){

    ttgenprod->process(event);
  }

  /* CMS-certified luminosity sections */
  if(event.isRealData){
  //low threshold run > 257933
  //only low
    //std::cout <<"run" << event.run << std::endl;
    if(!lumi_sel->passes(event)) return false;
  }

  ////

    float w_elecHLTSF_ct(1.), w_elecHLTSF_up(1.), w_elecHLTSF_dn(1.);
    float w_ttagSF_ct(1.), w_ttagSF_upL(1.), w_ttagSF_dnL(1.), w_ttagSF_upT(1.), w_ttagSF_dnT(1.);
    float w_muR_ct__muF_up(1.), w_muR_ct__muF_dn(1.), w_muR_up__muF_ct(1.), w_muR_up__muF_up(1.), w_muR_dn__muF_ct(1.), w_muR_dn__muF_dn(1.);
    float w_topptREWGT_up(1.), w_topptREWGT_dn(1.); //w_topptREWGT_ct(1.);
    float w_wjetsREWGT_ct(1.);
    std::vector<float> w_PDF;
    w_PDF.clear();
    
    //  std::cout<<event.weight<<std::endl;
    //
    //pileup
    pileupSF->process(event);
    //  std::cout<<event.weight<<std::endl;
    // // b-tagging
    btagSF->process(event);
    //  std::cout<<event.weight<<std::endl;
    //  muon-ID
    muonID_SF->process(event);
    double w_wo_HLT = event.weight;
    // std::cout<<"HLT, w_wo_HLT = "<<w_wo_HLT<<std::endl;
    // // muon-HLT eff
    muonHLT2_SF->process(event);
    double w1 = event.weight;
    event.weight = w_wo_HLT;
    muonHLT_SF->process(event);
    double w2 = event.weight;
    double w = (lumi1*w1+lumi2*w2)/(lumi_tot);
    // std::cout<<"w1 = "<<w1<<" w2 = "<<w2<<" w = "<<w<<std::endl;
    //  std::cout<<"w = "<<w<<std::endl;
    event.weight = w;
    
    //in 2016 data ICHEP JSON from [271036-274093] contains 0.622/fb
    
    
    //  std::cout<<event.weight<<std::endl;
    //  muon-Trk
    muonTRK_SF->process(event);
    //  std::cout<<event.weight<<std::endl;
    
    
    // // elec-ID
    //std::cout<<event.weight<<std::endl;
    elecID_SF->process(event);
    //std::cout<<event.weight<<std::endl;
    // elec-Gsf
    elecGsf_SF->process(event);
    if(!event.isRealData){
        //std::cout<<event.weight<<std::endl;
        //std::cout<<""<<std::endl;
        
        // w_elecIDSF_ct  = elecIDSF->weight(event, "CT");
        // w_elecIDSF_up  = elecIDSF->weight(event, "UP");
        // w_elecIDSF_dn  = elecIDSF->weight(event, "DN");
        // //
        
        // elec-HLT
        w_elecHLTSF_ct = 0.9598;//!!elecHLTSF->weight(event, "CT");
        w_elecHLTSF_up = 0.9665;//!!elecHLTSF->weight(event, "UP");
        w_elecHLTSF_dn = 0.9531;//!!elecHLTSF->weight(event, "DN");
        //
        
        
        // // elec-HLT
        // w_elecHLTSF_ct = 1.0;//!!elecHLTSF->weight(event, "CT");
        // w_elecHLTSF_up = 1.0;//!!elecHLTSF->weight(event, "UP");
        // w_elecHLTSF_dn = 1.0;//!!elecHLTSF->weight(event, "DN");
        // //
        
        // t-tagging
        w_ttagSF_ct    = ttagSF_ct ->weight(event);
        
        w_ttagSF_upL   = ttagSF_upL->weight(event);
        if(fabs(w_ttagSF_upL)>10.)
            std::cout<<"!!!!!!!!!!!!!!!! w_ttagSF_upL = "<<w_ttagSF_upL<<std::endl;
        w_ttagSF_dnL   = ttagSF_dnL->weight(event);
        w_ttagSF_upT   = ttagSF_upT->weight(event);
        if(fabs(w_ttagSF_upT)>10.)
            std::cout<<"!!!!!!!!!!!!!! w_ttagSF_upT = "<<w_ttagSF_upT<<std::endl;
        w_ttagSF_dnT   = ttagSF_dnT->weight(event);

    // Renormalization/Factorization scales
    if(event.genInfo){

      if(event.genInfo->systweights().size() >= 9){

        if(event.genInfo->originalXWGTUP()){

          w_muR_ct__muF_up = (event.genInfo->systweights().at(1) / event.genInfo->originalXWGTUP());
          w_muR_ct__muF_dn = (event.genInfo->systweights().at(2) / event.genInfo->originalXWGTUP());
          w_muR_up__muF_ct = (event.genInfo->systweights().at(3) / event.genInfo->originalXWGTUP());
          w_muR_up__muF_up = (event.genInfo->systweights().at(4) / event.genInfo->originalXWGTUP());
          w_muR_dn__muF_ct = (event.genInfo->systweights().at(6) / event.genInfo->originalXWGTUP());
          w_muR_dn__muF_dn = (event.genInfo->systweights().at(8) / event.genInfo->originalXWGTUP());

          if(store_PDF_weights_){

            for(unsigned int i=9; i<event.genInfo->systweights().size(); ++i){

              const float pdf_w(event.genInfo->systweights().at(i) / event.genInfo->originalXWGTUP());
              w_PDF.push_back(pdf_w);
            }
          }
        }
      }
    }

        // top-pt reweighting
        if(topptREWGT.get()){
            //      std::cout<<"aw!"<<std::endl;
            topptREWGT->process(event);
            
        }
        
        event.weight *= w_ttagSF_ct;
        
    }

      ////

  //// LEPTON SELECTION

  // OF lepton veto
  bool pass_lepV(0);
  if     (channel_ == muon) pass_lepV = ((event.electrons->size() == 0));
  else if(channel_ == elec) pass_lepV = ((event.muons    ->size() == 0));
  if(!pass_lepV) return false;
    //  //due to unknown efficiency in 2016 data, skip events with: muon pt>500 GeV in the endcap
    bool good_muon(0);
    if (channel_ == muon){
        const Particle* lep1 = leading_lepton(event);
        good_muon = (!(lep1->pt()>muo1_pt_max_ && lep1->eta()>muo1_eta_max_));
    }
    if(!good_muon && channel_ == muon) return false;

  // lepton multiplicity
  int lepN(-1);
  if     (channel_ == muon) lepN = int(event.muons    ->size());
  else if(channel_ == elec) lepN = int(event.electrons->size());
  if(!(lepN >= 1)) return false;
  //

  // pt-leading lepton selection
  const Particle* lep1 = leading_lepton(event);
  if(!(lep1->pt() > lep1_pt_)) return false;
  //

  ////

  //// JET selection

  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  if(lepN == 1) HFolder("jet2")->fill(event);

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  if(lepN == 1) HFolder("jet1")->fill(event);

  ////

  //// HLT selection
  const bool pass_trigger = trigger_sel->passes(event);
  if(!pass_trigger) return false;
  if(lepN == 1) HFolder("trigger")->fill(event);
  ////

  if(channel_ == elec) event.weight *= w_elecHLTSF_ct;

  //// MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  if(lepN == 1) HFolder("met")->fill(event);
  ////

  //// HT_lep selection
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  if(lepN == 1) HFolder("htlep")->fill(event);
  ////

  //// TRIANGULAR-CUTS selection
  const bool pass_triangc = triangc_sel->passes(event);
  if(!pass_triangc) return false;
  if(lepN == 1) HFolder("triangc")->fill(event);
  ////

  //// TTBAR KIN RECO

  /* TOPTAG-EVENT boolean */
  const bool pass_ttagevt = ttagevt_sel->passes(event) && use_ttagging_;

  const std::string ttag_posx = (pass_ttagevt ? "t1" : "t0");
  /************************/

  reco_primlep->process(event);

  if(!pass_ttagevt){ ttbar_reco__ttag0->process(event); ttbar_chi2__ttag0->process(event); }
  else             { ttbar_reco__ttag1->process(event); ttbar_chi2__ttag1->process(event); }

  std::vector<ReconstructionHypothesis>& ttbar_hyps = event.get(h_ttbar_hyps);

  ////

  //// LEPTONIC-TOP pt selection
  const bool pass_topleppt = topleppt_sel->passes(event);
  if(!pass_topleppt) return false;
  if(lepN == 1) HFolder("topleppt")->fill(event);
  ////

  //// FINAL selection

  /* ttagN counters */
  int ttagN(0);
  for(const auto& tj : *event.topjets) if(ttag_ID_(tj, event)) ++ttagN;

  // veto on 2-ttag events
  if(!(ttagN <= 1)) return false;

  /******************/
  //float d12 = 0.0;
  //float dR12 = 0.0;
  //float pt12min= 0.0;
  //float d13 = 0.0;
  //float dR13 = 0.0;
  //float pt13min= 0.0;
  //float d23 = 0.0;
  //float dR23 = 0.0;
  //float pt23min= 0.0;
  /* btagN counters */
  int jetbtagN(0), subjbtagN(0);

  if(!pass_ttagevt){

    for(const auto& j : *event.jets) if(btag_ID_(j, event)) ++jetbtagN;
    //event.set(h_d12, d12);
    //event.set(h_d13, d13);
   }
  else {

    const ReconstructionHypothesis* ttbar_hyp = get_best_hypothesis(ttbar_hyps, "Chi2");

    const TopJet* thad = ttbar_hyp->tophad_topjet_ptr();

    for(const auto& j : thad->subjets()) {
          if(btag_ID_(j, event)) ++subjbtagN;
    }
      
    //dR12 = uhh2::deltaR(thad->subjets()[0].v4(), thad->subjets()[1].v4());
    //if(thad->subjets()[0].v4().Pt()>thad->subjets()[1].v4().Pt()) pt12min = thad->subjets()[1].v4().Pt();
    //else pt12min = thad->subjets()[0].v4().Pt();
    //d12 =  dR12*pt12min;
    //event.set(h_d12, d12);
    /*
    dR13 = uhh2::deltaR(thad->subjets()[0].v4(), thad->subjets()[2].v4());
    if(thad->subjets()[0].v4().Pt()>thad->subjets()[2].v4().Pt()) pt13min = thad->subjets()[2].v4().Pt();
    else pt13min = thad->subjets()[0].v4().Pt();
    d13 =  dR13*pt13min;
    event.set(h_d13, d13);

    dR23 = uhh2::deltaR(thad->subjets()[1].v4(), thad->subjets()[2].v4());
    if(thad->subjets()[1].v4().Pt()>thad->subjets()[2].v4().Pt()) pt23min = thad->subjets()[2].v4().Pt();
    else pt23min = thad->subjets()[1].v4().Pt();
    d23 =  dR23*pt23min;
    event.set(h_d23, d23);
    */

    for(const auto& j : *event.jets){

      if(!(uhh2::deltaR(*thad, j) > ttag_minDR_jet_)) continue;
      if(btag_ID_(j, event)) ++jetbtagN;
    }
  }

  const int btagN = jetbtagN + subjbtagN;

  //
  //const std::string btag_posx = (btagN >= 2 ? "b2" : (btagN >= 1 ? "b1" : "b0"));
   const std::string btag_posx =  ( pass_ttagevt ? "b" :(btagN == 0 ? "b0": "b1"));
  /******************/

  /* CHI2 selection */
  const bool pass_chi2 = chi2_sel->passes(event);

  const std::string chi2_posx = pass_chi2 ? "chi2" : "antichi2";
  /******************/

  /* DATA blinding */
  if(blind_DATA_){

    if(lepN == 1 && pass_chi2){

      const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");

      const float rec_ttbar_M((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());

      if(!( rec_ttbar_M < 2000. )) return false;
    }
  }
  /*****************/

  /* KINE plots */
  if(lepN == 1){

    HFolder("kine")       ->fill(event);
    HFolder("kine__ttbar")->fill(event);

    HFolder("kine__"+ttag_posx+btag_posx)          ->fill(event);
    HFolder("kine__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
  }
  /**************/

  /* CHI2 plots */
  if(lepN == 1){

    HFolder(chi2_posx)          ->fill(event);
    HFolder(chi2_posx+"__ttbar")->fill(event);

    HFolder(chi2_posx+"__"+ttag_posx+btag_posx)          ->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
    
    if(pass_chi2 && !event.isRealData){
      h_btagMCeffi->fill(event);
    }
    
  }
  else if(lepN == 2){

    bool l2_ossf(false);
    if     (channel_ == muon) l2_ossf = ((event.muons    ->at(0).charge() * event.muons    ->at(1).charge()) == -1);
    else if(channel_ == elec) l2_ossf = ((event.electrons->at(0).charge() * event.electrons->at(1).charge()) == -1);

    if(l2_ossf && chi2_posx == "chi2"){

      HFolder(chi2_posx+"_L2")          ->fill(event);
      HFolder(chi2_posx+"_L2"+"__dilep")->fill(event);
      HFolder(chi2_posx+"_L2"+"__ttbar")->fill(event);

      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx)          ->fill(event);
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx+"__dilep")->fill(event);
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
    }
  }
  /**************/

  ////

  //// VARS

  // event
  event.set(h_run       , event.run);
  event.set(h_lumi_block, event.luminosityBlock);
  event.set(h_event     , event.event);

  event.set(h_pvN  , event.pvs->size());

  event.set(h_muoN , event.muons    ->size());
  event.set(h_eleN , event.electrons->size());

  //event.set(h_btagN, btagN);
  //event.set(h_ttagN, ttagN);

  event.set(h_ttagevt, pass_ttagevt);

  int ttgen_decay(-1);
  if(!event.isRealData){

    const auto& ttgen = event.get(h_ttbar_gen);

    if     (ttgen.DecayChannel() == TTbarGen::e_notfound) ttgen_decay = -1;
    else if(ttgen.DecayChannel() == TTbarGen::e_had     ) ttgen_decay = 00;
    else if(ttgen.DecayChannel() == TTbarGen::e_ehad    ) ttgen_decay = 01;
    else if(ttgen.DecayChannel() == TTbarGen::e_muhad   ) ttgen_decay = 02;
    else if(ttgen.DecayChannel() == TTbarGen::e_tauhad  ) ttgen_decay = 03;
    else if(ttgen.DecayChannel() == TTbarGen::e_ee      ) ttgen_decay = 11;
    else if(ttgen.DecayChannel() == TTbarGen::e_emu     ) ttgen_decay = 12;
    else if(ttgen.DecayChannel() == TTbarGen::e_etau    ) ttgen_decay = 13;
    else if(ttgen.DecayChannel() == TTbarGen::e_mumu    ) ttgen_decay = 22;
    else if(ttgen.DecayChannel() == TTbarGen::e_mutau   ) ttgen_decay = 23;
    else if(ttgen.DecayChannel() == TTbarGen::e_tautau  ) ttgen_decay = 33;
  }

  event.set(h_ttgen, ttgen_decay);
  //
    
  //adding variables for BDT QCD (1)
    
    // jet
    if(!(event.jets->size() >= 2)) throw std::runtime_error("TTbarLJAnalysisLiteModule::process -- logic error: jet multiplicity < 2 ("+std::to_string(event.jets->size())+")");
    
    TLorentzVector jet1__p4(event.jets->at(0).v4().Px(), event.jets->at(0).v4().Py(), event.jets->at(0).v4().Pz(), event.jets->at(0).v4().E());
    TLorentzVector jet2__p4(event.jets->at(1).v4().Px(), event.jets->at(1).v4().Py(), event.jets->at(1).v4().Pz(), event.jets->at(1).v4().E());
    
    event.set(h_jet1           , jet1__p4);
    event.set(h_jet2           , jet2__p4);
    
    
    const int jet_n = event.jets->size();
    //event.set(tt_nJets,jet_n);
    //leading jet
    const Jet* jet1 = &event.jets->at(0);
    //ljet_pt = jet1->pt();
    //event.set(tt_ljet_pt, ljet_pt);
    //ljet_phi = jet1->phi();
    ljet_eta = jet1->eta();
    //event.set(tt_ljet_phi, ljet_phi);     event.set(tt_ljet_eta, ljet_eta);
    ljet_CSV = jet1->btag_combinedSecondaryVertexMVA();
    //event.set(tt_ljet_CSV,ljet_CSV);
    //ljet_M = jet1->v4().M();
    //event.set(tt_ljet_M, ljet_M);
    
    if(jet_n>1){
        const Jet* jet2 =  &event.jets->at(1);
        fjet2_pt = jet2->pt(); fjet2_eta = jet2->eta(); //fjet2_phi = jet2->phi();
        //jet2_M = jet2->v4().M();
        jet2_CSV = jet2->btag_combinedSecondaryVertexMVA();
        //    std::cout<<"jet2_CSV = "<<jet2_CSV<<std::endl;
    }
    /*if(jet_n>2){
     const Jet* jet3 =  &event.jets->at(2);
     fjet3_pt = jet3->pt(); fjet3_eta = jet3->eta(); fjet3_phi = jet3->phi();
     jet3_M = jet3->v4().M();
     jet3_CSV = jet3->btag_combinedSecondaryVertexMVA();
     }*/
    //event.set(tt_jet2_pt,fjet2_pt); event.set(tt_jet2_phi,fjet2_phi); event.set(tt_jet2_eta,fjet2_eta);
    //event.set(tt_jet3_pt,fjet3_pt); event.set(tt_jet3_phi,fjet3_phi); event.set(tt_jet3_eta,fjet3_eta);
    //event.set(tt_jet2_M,jet2_M); event.set(tt_jet3_M,jet3_M);
    //event.set(tt_jet2_CSV,jet2_CSV);
    //  std::cout<<"one more time ... jet2_CSV = "<<jet2_CSV<<std::endl;
    //event.set(tt_jet3_CSV,jet3_CSV);
    //
    
    // MET
    event.set(h_MET, TLorentzVector(event.met->v4().Px(), event.met->v4().Py(), event.met->v4().Pz(), event.met->v4().P()));
    met_pt = event.met->pt();
    //event.set(tt_met_pt, met_pt);
    //met_phi = event.met->phi();
    //event.set(tt_met_phi, met_phi);
    //

    
    
    

   //END of (1)
  // lepton
  const Particle* lep2(0);
  if(lepN == 2){

    if     (channel_ == muon) lep2 = &((lep1 == &event.muons    ->at(0)) ? event.muons    ->at(1) : event.muons    ->at(0));
    else if(channel_ == elec) lep2 = &((lep1 == &event.electrons->at(0)) ? event.electrons->at(1) : event.electrons->at(0));
  }

  TLorentzVector lep1__p4(0.,0.,0.,0.), lep2__p4(0.,0.,0.,0.);
  int   lep1__pdgID(0), lep1__charge(0), lep2__pdgID(0), lep2__charge(0);
  float lep1__minDR_jet(-1.), lep1__pTrel_jet(-1.), lep2__minDR_jet(-1.), lep2__pTrel_jet(-1.);
  if(channel_ == muon){

    lep1__pdgID     = lep1->charge() * -13;
    lep1__charge    = lep1->charge();
    lep1__minDR_jet = ((Muon*) lep1)->get_tag(Muon::twodcut_dRmin);
    lep1__pTrel_jet = ((Muon*) lep1)->get_tag(Muon::twodcut_pTrel);
    lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());

    if(lep2){

      lep2__pdgID     = lep2->charge() * -13;
      lep2__charge    = lep2->charge();
      lep2__minDR_jet = ((Muon*) lep2)->get_tag(Muon::twodcut_dRmin);
      lep2__pTrel_jet = ((Muon*) lep2)->get_tag(Muon::twodcut_pTrel);
      lep2__p4        = TLorentzVector(lep2->v4().Px(), lep2->v4().Py(), lep2->v4().Pz(), lep2->v4().E());
    }
  }
  else if(channel_ == elec){

    lep1__pdgID     = lep1->charge() * -11;
    lep1__charge    = lep1->charge();
    lep1__minDR_jet = ((Electron*) lep1)->get_tag(Electron::twodcut_dRmin);
    lep1__pTrel_jet = ((Electron*) lep1)->get_tag(Electron::twodcut_pTrel);
    lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());

    if(lep2){

      lep2__pdgID     = lep2->charge() * -11;
      lep2__charge    = lep2->charge();
      lep2__minDR_jet = ((Electron*) lep2)->get_tag(Electron::twodcut_dRmin);
      lep2__pTrel_jet = ((Electron*) lep2)->get_tag(Electron::twodcut_pTrel);
      lep2__p4        = TLorentzVector(lep2->v4().Px(), lep2->v4().Py(), lep2->v4().Pz(), lep2->v4().E());
    }
      //Set variables for MVA ------------
      //lep_class = ((Electron*)lep1)->Class();
      lep_pt = lep1->pt(); lep_eta = lep1->eta();
      //fabs_lep_eta = fabs(lep_eta); lep_phi = lep1->phi();
      lep_pt_err = ((Electron*)lep1)->ptError();
      lep_eta_err = ((Electron*)lep1)->etaError();
      //lep_phi_err = ((Electron*)lep1)->phiError();
      //lep_xy = hypot(((Electron*)lep1)->gsfTrack_vx(),((Electron*)lep1)->gsfTrack_vy());
      //lep_fbriem = ((Electron*)lep1)->fbrem();//f_brem = (Pin-Pout)/Pin where Pin, Pout - electron momentum in and out of the tracker
      
      //lep_Nclusters = ((Electron*)lep1)->Nclusters();
      //lep_full5x5_e1x5 = ((Electron*)lep1)->full5x5_e1x5();
      //lep_full5x5_e2x5Max = ((Electron*)lep1)->full5x5_e2x5Max();
      lep_full5x5_e5x5 = ((Electron*)lep1)->full5x5_e5x5();
      lep_dEtaInSeed = ((Electron*)lep1)->dEtaInSeed();
      lep_dB = ((Electron*)lep1)->dB();
      //lep_sigmaIEtaIEta = ((Electron*)lep1)->sigmaIEtaIEta();
      //lep_HoverE = ((Electron*)lep1)->HoverE();
      //lep_EoverPIn = ((Electron*)lep1)->EoverPIn();
      lep_hcalOverEcal = ((Electron*)lep1)->hcalOverEcal();
      lep_dr03TkSumPt = ((Electron*)lep1)->dr03TkSumPt();
      lep_effArea = ((Electron*)lep1)->effArea();
      //lep_mvaNonTrigV0 = ((Electron*)lep1)->mvaNonTrigV0();
      //lep_dEtaIn = ((Electron*)lep1)->dEtaIn();
      //lep_dPhiIn = ((Electron*)lep1)->dPhiIn();
      
      //the closest to lepton jet
      // find jet with smallest angle to lepton (the closest jet to lepton)
      //int jet_pos = 0;
      //dR_lep_cljet = 1e7;
      //jets_pt = (&event.jets->at(0))->pt();
      /*for(int i=1; i<jet_n; i++){//skip leading jet
       const Particle* jeti =  &event.jets->at(i);
       jets_pt += jeti->pt();
       float dR_current = uhh2::deltaR(*lep1, *jeti);
       if(dR_lep_cljet>dR_current){// min distance in eta-phi
       dR_lep_cljet = dR_current;
       jet_pos = i;
       }
       }
       */
      ///const Jet*  jet0 =  &event.jets->at(jet_pos);
      //cjet_pt = jet0->pt();
      //cjet_phi = jet0->phi(); cjet_eta = jet0->eta();
      //dR_lep_ljet = uhh2::deltaR(*lep1, *jet1);
      //lep_pt_ljet = pTrel(*lep1, jet1);
      //dR_cljet_ljet = uhh2::deltaR(*jet0, *jet1);
      dPhi_lep_met = uhh2::deltaPhi(*event.met, *lep1);
      MwT = sqrt(2*fabs(lep_pt*met_pt*(1-cos(fabs(dPhi_lep_met)))));
      //dPhi_ljet_met = uhh2::deltaPhi(*event.met,*jet1);
      //dPhi_cjet_met = uhh2::deltaPhi(*event.met,*jet0);
      //lep_pt_cjet = pTrel(*lep1, jet0);
      //cjet_pt_ljet = pTrel(*jet0, jet1);// the closest not leading jet Pt to the leading jet axis
      //cjet_M = jet0->v4().M();
      //cjet_CSV = jet0->btag_combinedSecondaryVertexMVA();
  

      
  }

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
    //mva_lep1__minDR_jet = lep1__minDR_jet;

 // ttbar reco hyp
   const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");
   if(!rec_ttbar) throw std::runtime_error("TTbarLJAnalysisLiteModule::process -- logic error: ttbar reconstruction hypothesis (\"get_best_hypothesis\", discr=Chi2) not found");
 //
 //       const float MET__pz = rec_ttbar->neutrino_v4().Pz();
 //         event.set(h_MET__pz, MET__pz);
 //
 //const float rec_chi2 = rec_ttbar->discriminator("Chi2");
 


    // MET
    event.set(h_MET, TLorentzVector(event.met->v4().Px(), event.met->v4().Py(), event.met->v4().Pz(), event.met->v4().P()));
    
    const ReconstructionHypothesis* rec_ttbar_ = get_best_hypothesis(ttbar_hyps, "Chi2");
    rec_ttbar_M_ = ((rec_ttbar_->top_v4()+rec_ttbar_->antitop_v4()).M());
    // event.set(tt_mttbar,rec_ttbar_M_);
    if(channel_ == elec){
        varMVA[0] = lep_pt/rec_ttbar_M_;
        varMVA[1] = fabs(lep_eta);
        varMVA[2] = lep_eta_err;
        varMVA[3] = lep_pt_err;
        varMVA[4] = lep_full5x5_e5x5;
        varMVA[5] = lep_dB;
        varMVA[6] = fabs(lep_dPhiIn);
        varMVA[7] = fabs(lep_dEtaInSeed);
        varMVA[8] = lep_hcalOverEcal;
        varMVA[9] = lep_dr03TkSumPt;
        varMVA[10] = lep_effArea;
        varMVA[11] = lep1__minDR_jet;
        varMVA[12] = fabs(ljet_eta);
        varMVA[13] = ljet_CSV;
        varMVA[14] = fabs(fjet2_eta);
        varMVA[15] = fjet2_pt/rec_ttbar_M_;
        varMVA[16] = jet2_CSV;
        varMVA[17] = met_pt/MwT;
        varMVA[18] = ttagN;
        varMVA[19] = btagN;
        
        event.set(h_lep_pt, lep_pt/rec_ttbar_M_);
        event.set(h_lep_eta,fabs(lep_eta));
        event.set(h_lep_eta_err, lep_eta_err);
        event.set(h_lep_pt_err, lep_pt_err);
        event.set(h_lep_full5x5_e5x5, lep_full5x5_e5x5);
        event.set(h_lep_dB, lep_dB);
        event.set(h_lep_dPhiIn, fabs(lep_dPhiIn));
        event.set(h_lep_dEtaInSeed, fabs(lep_dEtaInSeed));
        event.set(h_lep_hcalOverEcal, lep_hcalOverEcal);
        event.set(h_lep_dr03TkSumPt, lep_dr03TkSumPt);
        event.set(h_lep_effArea, lep_effArea);
        event.set(h_lep1__minDR_jet, lep1__minDR_jet);
        event.set(h_ljet_eta, fabs(ljet_eta));
        event.set(h_ljet_CSV , ljet_CSV);
        event.set(h_fjet2_eta,fabs(ljet_eta));
        event.set(h_fjet2_pt, fjet2_pt/rec_ttbar_M_);
        event.set(h_jet2_CSV,jet2_CSV);
        event.set(h_met_pt, met_pt/MwT);
        event.set(h_ttagN, ttagN);
        event.set(h_btagN, btagN);
        // if(ljet_CSV<-1. || lep_pt_err>1000.)
        //    return false; // do NOT use unphysical data
        TMVA_response = reader_qcd->EvaluateMVA(methodName);
        //if(TMVA_response<-0.5) return false; //BDTG_DATADriven_MET40_20vars
        event.set(tt_TMVA_response,TMVA_response );
    }
  
  const float rec_chi2 = rec_ttbar->discriminator("Chi2");
  event.set(h_rec_chi2, rec_chi2);

  const LorentzVector tlep(rec_ttbar->toplep_v4());
  const LorentzVector thad(rec_ttbar->tophad_v4());

  event.set(h_rec_tlep, TLorentzVector(tlep.Px(), tlep.Py(), tlep.Pz(), tlep.E()));
  event.set(h_rec_thad, TLorentzVector(thad.Px(), thad.Py(), thad.Pz(), thad.E()));

    
  if (lepN==1 && pass_chi2){
        HFolder("chi2_bdt")          ->fill(event);
        HFolder("chi2_bdt__ttbar")->fill(event);
        
        HFolder("chi2_bdt__"+ttag_posx+btag_posx)          ->fill(event);
        HFolder("chi2_bdt__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
        
        
  }        
   




  // weight
  event.set(h_wgtMC__GEN         , w_GEN);
  return true;
}


UHH2_REGISTER_ANALYSIS_MODULE(BDTQCDVariableDumpModule)
