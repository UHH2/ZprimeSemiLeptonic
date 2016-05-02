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

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/EffyJetTTAGHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/EffyTTbarRECOHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/SF_elec.h>

class EffyJetXTAGLiteModule : public ModuleBASE {

 public:
  explicit EffyJetXTAGLiteModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:
  enum lepton { muon, elec };
  lepton channel_;

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::vector<std::unique_ptr<uhh2::RunLumiEventSelection> > met_filters2;

  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> trigger_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> triangc_sel;
  std::unique_ptr<uhh2::Selection> ttagevt_sel;
  std::unique_ptr<uhh2::Selection> topleppt_sel;
  std::unique_ptr<uhh2::Selection> tjpjevt_sel;
  std::unique_ptr<uhh2::Selection> chi2tlep_sel;
  std::unique_ptr<uhh2::Selection> chi2_sel;

  // ttbar reconstruction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  std::unique_ptr<uhh2::AnalysisModule> reco_primlep;

  std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag0;
  std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag1;
  std::unique_ptr<Chi2Discriminator>     ttbar_chi2__ttag0;
  std::unique_ptr<Chi2DiscriminatorTTAG> ttbar_chi2__ttag1;

  uhh2::Event::Handle<std::vector<ReconstructionHypothesis> > h_ttbar_hyps;

  bool use_ttagging_;
  TopJetId ttag_ID_;
  float    ttag_minDR_jet_;

  bool blind_DATA_;

  //// Data/MC scale factors
  std::unique_ptr<uhh2::AnalysisModule> pileupSF;
  std::unique_ptr<uhh2::AnalysisModule> muonID_SF;
  std::unique_ptr<uhh2::AnalysisModule> muonHLT_SF;

  std::unique_ptr<weightcalc_elecID>  elecIDSF;
//!!  std::unique_ptr<weightcalc_elecHLT> elecHLTSF;
  ////
};

EffyJetXTAGLiteModule::EffyJetXTAGLiteModule(uhh2::Context& ctx){

  //// CONFIGURATION

  const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else throw std::runtime_error("EffyJetXTAGLiteModule::EffyJetXTAGLiteModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);

  use_ttagging_ = true;

  blind_DATA_ = ((ctx.get("dataset_version").find("BLINDED") != std::string::npos) && (ctx.get("dataset_type") == "DATA") && !isMC);

  const std::string& ttag_wp = ctx.get("ttag_wp");
  //

  const std::string& keyword = ctx.get("keyword");

  float jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);
  bool triangul_cut(false);
  bool topleppt_cut(false);

  if(keyword == "T0_v01" || keyword == "T1_v01"){

    if     (keyword == "T0_v01") use_ttagging_ = false;
    else if(keyword == "T1_v01") use_ttagging_ = true;

    if(channel_ == muon){

      jet1_pt = 150.;
      jet2_pt =  50.;

      MET    =  50.;
      HT_lep = 100.;

      triangul_cut = false;
      topleppt_cut = false;
    }
    else if(channel_ == elec){

      jet1_pt = 250.;
      jet2_pt =  70.;

      MET    =  50.;
      HT_lep = 100.;

      triangul_cut = false;
      topleppt_cut = false;
    }
  }
  else throw std::runtime_error("EffyJetXTAGLiteModule::EffyJetXTAGLiteModule -- undefined \"keyword\" argument in .xml configuration file: "+keyword);
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

  met_sel  .reset(new METCut  (MET   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));

  if(triangul_cut){

    if     (channel_ == elec) triangc_sel.reset(new TriangularCuts(M_PI/2., (M_PI/2.)/75.));
    else if(channel_ == muon) triangc_sel.reset(new uhh2::AndSelection(ctx));
  }
  else triangc_sel.reset(new uhh2::AndSelection(ctx));
  ////

  //// TTBAR KINEMATICAL RECO

  /* t-tagging */
  ttag_ID_ = TopTagID_SoftDrop(ttag_wp);
  ttag_minDR_jet_ = 1.2;

  ttagevt_sel.reset(new TopTagEventSelection(ttag_ID_, ttag_minDR_jet_));
  tjpjevt_sel.reset(new TopJetPlusJetEventSelection(ttag_minDR_jet_, jet2_pt));
  /*************/

  const std::string ttbar_gen_label ("ttbargen");
  const std::string ttbar_hyps_label("TTbarReconstruction");
  const std::string ttbar_chi2_label("Chi2");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

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

  chi2tlep_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., 30., ttbar_hyps_label, ttbar_chi2_label, "Chi2_tlep"));
  chi2_sel    .reset(new HypothesisDiscriminatorCut(ctx,  0., 30., ttbar_hyps_label, ttbar_chi2_label, "Chi2"));

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

  TopTagID_SoftDrop ttagIDsd_noMsd(ttag_wp);
  ttagIDsd_noMsd.cut_mass(false);
  TopJetId ttag_ID_noMsd(ttagIDsd_noMsd);

  TopTagID_SoftDrop ttagIDsd_noTau(ttag_wp);
  ttagIDsd_noTau.cut_tau32(false);
  TopJetId ttag_ID_noTau(ttagIDsd_noTau);

  std::vector<std::string> htags_2({
    "kine",
    "chi2",
    "antichi2",
  });

  for(const auto& sel : htags_2){

    book_HFolder(sel               , new TTbarLJHists      (ctx, sel               , ttag_ID_     , ttag_minDR_jet_));
    book_HFolder(sel+"__ttbar"     , new EffyTTbarRECOHists(ctx, sel+"__ttbar"     , ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));

    book_HFolder(sel+"__TTAG"      , new EffyJetTTAGHists  (ctx, sel+"__TTAG"      , ttag_ID_     , ttag_minDR_jet_));
    book_HFolder(sel+"__TTAG_noMsd", new EffyJetTTAGHists  (ctx, sel+"__TTAG_noMsd", ttag_ID_noMsd, ttag_minDR_jet_));
    book_HFolder(sel+"__TTAG_noTau", new EffyJetTTAGHists  (ctx, sel+"__TTAG_noTau", ttag_ID_noTau, ttag_minDR_jet_));
  }
  //

  std::vector<std::string> htags_3({

    "tjpj_kine",
    "tjpj_chi2",
    "tjpj_chi2tlep",
    "tjpj_antichi2tlep",
    "tjpj_antichi2tlep__CSVL0",
    "tjpj_antichi2tlep__CSVL1",
    "tjpj_antichi2tlep__CSVM0",
    "tjpj_antichi2tlep__CSVM1",
    "tjpj_antichi2tlep__CSVT0",
    "tjpj_antichi2tlep__CSVT1",
  });

  const std::vector<std::string> htags_ETA({
    "",
    "_etaLO",
    "_etaHI",
  });

  for(const auto& sel : htags_3){

    book_HFolder(sel          , new TTbarLJHists      (ctx, sel          , ttag_ID_, ttag_minDR_jet_));
    book_HFolder(sel+"__ttbar", new EffyTTbarRECOHists(ctx, sel+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));

    for(const auto& eta : htags_ETA){

      book_HFolder(sel+"__TTAG"      +eta, new EffyJetTTAGHists(ctx, sel+"__TTAG"      +eta, ttag_ID_     , ttag_minDR_jet_));
      book_HFolder(sel+"__TTAG_noMsd"+eta, new EffyJetTTAGHists(ctx, sel+"__TTAG_noMsd"+eta, ttag_ID_noMsd, ttag_minDR_jet_));
      book_HFolder(sel+"__TTAG_noTau"+eta, new EffyJetTTAGHists(ctx, sel+"__TTAG_noTau"+eta, ttag_ID_noTau, ttag_minDR_jet_));
    }
  }
  //

  ////

  //// Data/MC scale factors

  // pileup
  pileupSF.reset(new MCPileupReweight(ctx));
  //

  // muon-ID
  const std::string& muonID_SFac    = ctx.get("muonID_SF_file");
  const std::string& muonID_directory    = ctx.get("muonID_SF_directory");

  muonID_SF.reset(new MCMuonScaleFactor(ctx, muonID_SFac, muonID_directory, 1.0, "ID"));
  //

  // muon-HLT
  const std::string& muonHLT_SFac   = ctx.get("muonHLT_SF_file");
  const std::string& muonHLT_directory   = ctx.get("muonHLT_SF_directory");

  muonHLT_SF.reset(new MCMuonScaleFactor(ctx, muonHLT_SFac, muonHLT_directory, 0.5, "HLT"));
  //

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

  ////
}

bool EffyJetXTAGLiteModule::process(uhh2::Event& event){

  //// COMMON MODULES

  if(!event.isRealData){

    ttgenprod->process(event);
  }

  /* CMS-certified luminosity sections */
  if(event.isRealData){

    if(!lumi_sel->passes(event)) return false;
  }

  /* MET filters #2 */
  if(event.isRealData){

    for(const auto& metf2 : met_filters2){

      if(metf2->found(event)) return false;
    }
  }

  ////

  //// LEPTON SELECTION

  // OF lepton veto
  bool pass_lepV(0);
  if     (channel_ == muon) pass_lepV = ((event.electrons->size() == 0));
  else if(channel_ == elec) pass_lepV = ((event.muons    ->size() == 0));
  if(!pass_lepV) return false;
  //

  int lepN(-1);
  if     (channel_ == muon) lepN = int(event.muons    ->size());
  else if(channel_ == elec) lepN = int(event.electrons->size());
  if(!(lepN == 1)) return false;

  ////

  //// Data/MC scale factors

  float w_GEN(1.);
  float w_elecIDSF_ct(1.);
  float w_elecHLTSF_ct(1.);

  //pileup
  pileupSF->process(event);

  // muon-ID
  muonID_SF->process(event);

  if(!event.isRealData){

    w_GEN = event.weight;

    // elec-ID
    w_elecIDSF_ct  = elecIDSF->weight(event, "CT");
    //

    // elec-HLT
    w_elecHLTSF_ct = 0.99;//!!elecHLTSF->weight(event, "CT");
    //

    // central weight (histograms)
    event.weight   = w_GEN;
  
    if(channel_ == elec) event.weight *= w_elecIDSF_ct;
    //
  }
  //

  ////

  //// JET selection

  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  HFolder("jet2")->fill(event);

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  HFolder("jet1")->fill(event);

  ////

  //// HLT selection
  const bool pass_trigger = trigger_sel->passes(event);
  if(!pass_trigger) return false;
  HFolder("trigger")->fill(event);
  ////

  // HLT
  muonHLT_SF->process(event);

  if(channel_ == elec) event.weight *= w_elecHLTSF_ct;

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

  //// TRIANGULAR-CUTS selection
  const bool pass_triangc = triangc_sel->passes(event);
  if(!pass_triangc) return false;
  HFolder("triangc")->fill(event);
  ////

  //// TTBAR KIN RECO

  /* TOPTAG-EVENT boolean */
  const bool pass_ttagevt = ttagevt_sel->passes(event) && use_ttagging_;
  /************************/

  reco_primlep->process(event);

  if(!pass_ttagevt){ ttbar_reco__ttag0->process(event); ttbar_chi2__ttag0->process(event); }
  else             { ttbar_reco__ttag1->process(event); ttbar_chi2__ttag1->process(event); }

  const std::vector<ReconstructionHypothesis>& ttbar_hyps = event.get(h_ttbar_hyps);

  ////

  //// LEPTONIC-TOP pt selection
  const bool pass_topleppt = topleppt_sel->passes(event);
  if(!pass_topleppt) return false;
  HFolder("topleppt")->fill(event);
  ////

  //// FINAL selection

  /* ttagN counters */
  int ttagN(0);
  for(const auto& tj : *event.topjets) if(ttag_ID_(tj, event)) ++ttagN;

  // veto on 2-ttag events
  if(!(ttagN <= 1)) return false;

  /******************/

  /* DATA blinding */
  if(blind_DATA_){

    const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");

    const float rec_ttbar_M((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());

    if(!( rec_ttbar_M < 2000. )) return false;
  }
  /*****************/

  HFolder("kine")            ->fill(event);
  HFolder("kine__ttbar")     ->fill(event);
  HFolder("kine__TTAG")      ->fill(event);
  HFolder("kine__TTAG_noMsd")->fill(event);
  HFolder("kine__TTAG_noTau")->fill(event);
  ////

  //// CHI2 selection
  const bool pass_chi2 = chi2_sel->passes(event);

  const std::string chi2_posx = pass_chi2 ? "chi2" : "antichi2";

  HFolder(chi2_posx)               ->fill(event);
  HFolder(chi2_posx+"__ttbar")     ->fill(event);
  HFolder(chi2_posx+"__TTAG")      ->fill(event);
  HFolder(chi2_posx+"__TTAG_noMsd")->fill(event);
  HFolder(chi2_posx+"__TTAG_noTau")->fill(event);
  ////

  //// TTAG SF CR
  const bool pass_tjpjevt = tjpjevt_sel->passes(event);
  if(pass_tjpjevt){

    std::vector<std::string> htags_ETA({""});
    if(fabs(event.topjets->at(0).eta()) < 1.0) htags_ETA.push_back("_etaLO");
    else                                       htags_ETA.push_back("_etaHI");

    HFolder("tjpj_kine")       ->fill(event);
    HFolder("tjpj_kine__ttbar")->fill(event);

    for(const auto& eta : htags_ETA){

      HFolder("tjpj_kine__TTAG"      +eta)->fill(event);
      HFolder("tjpj_kine__TTAG_noMsd"+eta)->fill(event);
      HFolder("tjpj_kine__TTAG_noTau"+eta)->fill(event);
    }
    ////

    //// inverted CHI2(top-lep) selection
    const bool pass_chi2tlep = chi2tlep_sel->passes(event);

    /* maximum CSV score of AK4 jets not overlapping with AK8 jet */
    float outjet_maxCSV(-1.);
    for(const auto& topjet : *event.topjets){

      for(const auto& jet : *event.jets){

        if(uhh2::deltaR(topjet, jet) > ttag_minDR_jet_){

          if(outjet_maxCSV < jet.btag_combinedSecondaryVertex()){
             outjet_maxCSV = jet.btag_combinedSecondaryVertex();
          }
        }
      }
    }

    const std::string btag_csvL = (outjet_maxCSV > 0.605) ? "CSVL1" : "CSVL0";
    const std::string btag_csvM = (outjet_maxCSV > 0.890) ? "CSVM1" : "CSVM0";
    const std::string btag_csvT = (outjet_maxCSV > 0.970) ? "CSVT1" : "CSVT0";
    /*------------------------------------------------------------*/

    if(pass_chi2){

      HFolder("tjpj_chi2")       ->fill(event);
      HFolder("tjpj_chi2__ttbar")->fill(event);

      for(const auto& eta : htags_ETA){

        HFolder("tjpj_chi2__TTAG"      +eta)->fill(event);
        HFolder("tjpj_chi2__TTAG_noMsd"+eta)->fill(event);
        HFolder("tjpj_chi2__TTAG_noTau"+eta)->fill(event);
      }
    }

    if(pass_chi2tlep){

      HFolder("tjpj_chi2tlep")       ->fill(event);
      HFolder("tjpj_chi2tlep__ttbar")->fill(event);

      for(const auto& eta : htags_ETA){

        HFolder("tjpj_chi2tlep__TTAG"      +eta)->fill(event);
        HFolder("tjpj_chi2tlep__TTAG_noMsd"+eta)->fill(event);
        HFolder("tjpj_chi2tlep__TTAG_noTau"+eta)->fill(event);
      }
    }
    else {

      HFolder("tjpj_antichi2tlep")       ->fill(event);
      HFolder("tjpj_antichi2tlep__ttbar")->fill(event);

      for(const auto& eta : htags_ETA){

        HFolder("tjpj_antichi2tlep__TTAG"      +eta)->fill(event);
        HFolder("tjpj_antichi2tlep__TTAG_noMsd"+eta)->fill(event);
        HFolder("tjpj_antichi2tlep__TTAG_noTau"+eta)->fill(event);
      }

      HFolder("tjpj_antichi2tlep__"+btag_csvL)          ->fill(event);
      HFolder("tjpj_antichi2tlep__"+btag_csvL+"__ttbar")->fill(event);

      for(const auto& eta : htags_ETA){

        HFolder("tjpj_antichi2tlep__"+btag_csvL+"__TTAG"      +eta)->fill(event);
        HFolder("tjpj_antichi2tlep__"+btag_csvL+"__TTAG_noMsd"+eta)->fill(event);
        HFolder("tjpj_antichi2tlep__"+btag_csvL+"__TTAG_noTau"+eta)->fill(event);
      }

      HFolder("tjpj_antichi2tlep__"+btag_csvM)          ->fill(event);
      HFolder("tjpj_antichi2tlep__"+btag_csvM+"__ttbar")->fill(event);

      for(const auto& eta : htags_ETA){

        HFolder("tjpj_antichi2tlep__"+btag_csvM+"__TTAG"      +eta)->fill(event);
        HFolder("tjpj_antichi2tlep__"+btag_csvM+"__TTAG_noMsd"+eta)->fill(event);
        HFolder("tjpj_antichi2tlep__"+btag_csvM+"__TTAG_noTau"+eta)->fill(event);
      }

      HFolder("tjpj_antichi2tlep__"+btag_csvT)          ->fill(event);
      HFolder("tjpj_antichi2tlep__"+btag_csvT+"__ttbar")->fill(event);

      for(const auto& eta : htags_ETA){

        HFolder("tjpj_antichi2tlep__"+btag_csvT+"__TTAG"      +eta)->fill(event);
        HFolder("tjpj_antichi2tlep__"+btag_csvT+"__TTAG_noMsd"+eta)->fill(event);
        HFolder("tjpj_antichi2tlep__"+btag_csvT+"__TTAG_noTau"+eta)->fill(event);
      }
    }
    ////
  }

  return false;
}

UHH2_REGISTER_ANALYSIS_MODULE(EffyJetXTAGLiteModule)
