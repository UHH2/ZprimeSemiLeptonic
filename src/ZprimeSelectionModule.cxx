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
#include <UHH2/common/include/ReconstructionHypothesis.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/HypothesisHists.h>
#include <UHH2/common/include/Utils.h>

#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSelectionHists.h>

/** \brief module to produce "Selection" ntuples for the Z'->ttbar semileptonic analysis
 *
 *  -- GOALS:
 *   * complete object reconstruction (pt/eta cuts, IDs, jet-lepton cleaning, JER smearing)
 *   * apply (most of) the kinematic cuts for the lepton+jets SR. current cutflow:
 *     * HLT
 *     * ==1 lepton (w/ pt+eta+ID cuts)
 *     * >=2 AK4 jets w/ pt> 50 |eta|<2.4
 *     * >=1 AK4 jets w/ pt>200 |eta|<2.4
 *     * MET > 50 GeV
 *     * MET+lepton.pt > 150 GeV
 *     * lepton-2D-cut [DR>0.4 || pTrel>25 GeV] (wrt AK4 jets w/ pt>25 GeV)
 *     * (electron-only) triangular cuts
 *   * perform ttbar kinematical reconstruction (hyps stored in output ntuple)
 *
 * -- ITEMS TO BE IMPLEMENTED:
 *   * JER smearing for TopJet collection
 *   * update 2D cut values (validation ongoing)
 *
 */

class ZprimeSelectionModule : public uhh2::AnalysisModule {

 public:
  explicit ZprimeSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 private:
  enum lepton { muon, elec };
  lepton channel_;

  uhh2::Event::Handle<int> h_flag_toptagevent;

  // cleaners
  std::unique_ptr<MuonCleaner>     muo_cleaner;
  std::unique_ptr<ElectronCleaner> ele_cleaner;
  std::unique_ptr<JetCleaner>           jet_IDcleaner;
  std::unique_ptr<JetCorrector>         jet_corrector;
//!!  std::unique_ptr<JetResolutionSmearer> jetER_smearer;
  std::unique_ptr<JetLeptonCleaner>     jetlepton_cleaner;
  std::unique_ptr<JetCleaner>           jet_cleaner1;
  std::unique_ptr<JetCleaner>           jet_cleaner2;
  std::unique_ptr<JetCleaner>                topjet_IDcleaner;
  std::unique_ptr<TopJetCorrector>           topjet_corrector;
//!!  std::unique_ptr<TopJetResolutionSmearer>   topjetER_smearer;
  std::unique_ptr<TopJetLeptonDeltaRCleaner> topjetlepton_cleaner;
  std::unique_ptr<TopJetCleaner>             topjet_cleaner;

  // Data/MC scale factors
  std::unique_ptr<uhh2::AnalysisModule> pileup_SF;

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel;

  std::unique_ptr<uhh2::Selection> trigger_sel;
  std::unique_ptr<uhh2::AndSelection> lep1_sel;
  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> twodcut_sel;
  std::unique_ptr<uhh2::Selection> triangc_sel;
  std::unique_ptr<uhh2::Selection> toptagevt_sel;

  // ttbar reconstruction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  std::unique_ptr<uhh2::Selection> genmttbar_sel;
  std::unique_ptr<uhh2::AnalysisModule> reco_primlep;
  std::unique_ptr<uhh2::AnalysisModule> ttbar_reco__ttag0, ttbar_reco__ttag1;
  std::unique_ptr<uhh2::AnalysisModule> ttbar_chi2__ttag0, ttbar_chi2__ttag1;

  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;

  // hists
  std::unique_ptr<uhh2::Hists> input_h;
  std::unique_ptr<uhh2::Hists> trigger_h;
  std::unique_ptr<uhh2::Hists> lep1_h;
  std::unique_ptr<uhh2::Hists> jet2_h;
  std::unique_ptr<uhh2::Hists> jet1_h;
  std::unique_ptr<uhh2::Hists> met_h;
  std::unique_ptr<uhh2::Hists> htlep_h;
  std::unique_ptr<uhh2::Hists> twodcut_h;
  std::unique_ptr<uhh2::Hists> triangc_h;
  std::unique_ptr<uhh2::Hists> toptagevt_h;
  std::unique_ptr<uhh2::Hists> chi2min_toptag0_h;
  std::unique_ptr<uhh2::Hists> chi2min_toptag1_h;
};

ZprimeSelectionModule::ZprimeSelectionModule(uhh2::Context& ctx){

  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else throw std::runtime_error("ZprimeSelectionModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);

  const bool isMC = (ctx.get("dataset_type") == "MC");

  //// COMMON MODULES
  if(isMC) pileup_SF.reset(new MCPileupReweight(ctx));
  else     lumi_sel.reset(new LumiSelection(ctx));

  /* MET filters */
  metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
  metfilters_sel->add<TriggerSelection>("CSCTightHalo", "Flag_CSCTightHaloFilter");
  metfilters_sel->add<TriggerSelection>("eeBadSc"     , "Flag_eeBadScFilter");
  metfilters_sel->add<NPVSelection>    ("1-good-vtx"  , 1, -1, PrimaryVertexId(StandardPrimaryVertexId()));

  //// OBJ CLEANING
  muo_cleaner.reset(new MuonCleaner    (AndId<Muon>    (PtEtaCut  (50., 2.1), MuonIDMedium())));
  ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(PtEtaSCCut(50., 2.5), ElectronID_MVAnotrig_Spring15_25ns_loose)));

  const JetId jetID(JetPFID(JetPFID::WP_LOOSE));

  std::vector<std::string> JEC_AK4, JEC_AK8;
  if(isMC){

    JEC_AK4 = JERFiles::Summer15_50ns_L123_AK4PFchs_MC;
    JEC_AK8 = JERFiles::Summer15_50ns_L123_AK8PFchs_MC;
  }
  else {

    JEC_AK4 = JERFiles::Summer15_50ns_L123_AK4PFchs_DATA;
    JEC_AK8 = JERFiles::Summer15_50ns_L123_AK8PFchs_DATA;
  }

  jet_IDcleaner.reset(new JetCleaner(jetID));
  jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
//!!  jetER_smearer.reset(new JetResolutionSmearer(ctx));
  jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JEC_AK4));
  jetlepton_cleaner->set_drmax(.4);
  jet_cleaner1.reset(new JetCleaner(25., uhh2::infinity));
  jet_cleaner2.reset(new JetCleaner(30., 2.4));

  topjet_IDcleaner.reset(new JetCleaner(jetID));
  topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
//!!  topjetER_smearer.reset(new TopJetResolutionSmearer(ctx));
  topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(.8));
  topjet_cleaner.reset(new TopJetCleaner(TopJetId(PtEtaCut(400., 2.4))));
  ////

  //// EVENT SELECTION
  const std::string& trigger = ctx.get("trigger", "NULL");

  lep1_sel.reset(new uhh2::AndSelection(ctx));
  if(channel_ == muon){

    lep1_sel->add<NMuonSelection>    ("muoN == 1", 1, 1);
    lep1_sel->add<NElectronSelection>("eleN == 0", 0, 0);

    if(trigger != "NULL") trigger_sel = make_unique<TriggerSelection>(trigger);
    else                  trigger_sel = make_unique<TriggerSelection>("HLT_Mu45_eta2p1_v*");
  }
  else if(channel_ == elec){

    lep1_sel->add<NMuonSelection>    ("muoN == 0", 0, 0);
    lep1_sel->add<NElectronSelection>("eleN == 1", 1, 1);

    if(trigger != "NULL") trigger_sel = make_unique<TriggerSelection>(trigger);
    else                  trigger_sel = make_unique<TriggerSelection>("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v*");
  }

  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut( 50., 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(200., 2.4))));

  met_sel  .reset(new METCut  ( 50., uhh2::infinity));
  htlep_sel.reset(new HTlepCut(150., uhh2::infinity));

  twodcut_sel.reset(new TwoDCut(.4, 25.));

  if     (channel_ == elec) triangc_sel.reset(new TriangularCuts(1.5, 75.));
  else if(channel_ == muon) triangc_sel.reset(new uhh2::AndSelection(ctx)); // always true (no triangular cuts for muon channel)

  /* t-tagging */
  const TopJetId topjetID = AndId<TopJet>(CMSTopTag(CMSTopTag::MassType::groomed), Tau32());
  const float minDR_topjet_jet(1.2);

  toptagevt_sel.reset(new TopTagEventSelection(topjetID, minDR_topjet_jet));
  h_flag_toptagevent = ctx.declare_event_output<int>("flag_toptagevent");
  /**/

  /* TTBAR KINEMATICAL RECO */
  const std::string ttbar_gen_label ("ttbargen");
  const std::string ttbar_hyps_label("TTbarReconstruction");
  const std::string ttbar_chi2_label("Chi2");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  if(ctx.get("dataset_version") == "TTbar_Mtt0000to0700") genmttbar_sel.reset(new GenMttbarCut(ctx, 0., 700., ttbar_gen_label));
  else                                                    genmttbar_sel.reset(new uhh2::AndSelection(ctx));

  reco_primlep.reset(new PrimaryLepton(ctx));

  ttbar_reco__ttag0.reset(new HighMassTTbarReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label));
  ttbar_reco__ttag1.reset(new        TopTagReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label, topjetID, minDR_topjet_jet));

  ttbar_chi2__ttag0.reset(new Chi2Discriminator    (ctx, ttbar_hyps_label));
  ttbar_chi2__ttag1.reset(new Chi2DiscriminatorTTAG(ctx, ttbar_hyps_label));

  h_ttbar_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis>>(ttbar_hyps_label);
  /**/

  //// HISTS
  input_h    .reset(new ZprimeSelectionHists(ctx, "input"));
  trigger_h  .reset(new ZprimeSelectionHists(ctx, "trigger"));
  lep1_h     .reset(new ZprimeSelectionHists(ctx, "lep1"));
  jet2_h     .reset(new ZprimeSelectionHists(ctx, "jet2"));
  jet1_h     .reset(new ZprimeSelectionHists(ctx, "jet1"));
  met_h      .reset(new ZprimeSelectionHists(ctx, "met"));
  htlep_h    .reset(new ZprimeSelectionHists(ctx, "htlep"));
  twodcut_h  .reset(new ZprimeSelectionHists(ctx, "twodcut"));
  triangc_h  .reset(new ZprimeSelectionHists(ctx, "triangc"));
  toptagevt_h.reset(new ZprimeSelectionHists(ctx, "toptagevent"));
  chi2min_toptag0_h.reset(new HypothesisHists(ctx, "chi2min_toptag0__HypHists", ttbar_hyps_label, ttbar_chi2_label));
  chi2min_toptag1_h.reset(new HypothesisHists(ctx, "chi2min_toptag1__HypHists", ttbar_hyps_label, ttbar_chi2_label));
  ////
}

bool ZprimeSelectionModule::process(uhh2::Event& event){

  if(!event.isRealData){

    ttgenprod->process(event);
    if(!genmttbar_sel->passes(event)) return false;
  }

  input_h->fill(event);

  // COMMON MODULES

  /* luminosity sections from CMS golden-JSON file */
  if(event.isRealData && !lumi_sel->passes(event)) return false;

  /* MET filters */
  if(!metfilters_sel->passes(event)) return false;

  /* pileup SF */
  if(!event.isRealData) pileup_SF->process(event);
  ////

  // OBJ CLEANING
  muo_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  ele_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  jet_IDcleaner->process(event);
  jet_corrector->process(event);
//!!  jetER_smearer->process(event);
  jetlepton_cleaner->process(event);
  jet_cleaner1->process(event); // jet collection for lepton-2Dcut
  sort_by_pt<Jet>(*event.jets);

  topjet_IDcleaner->process(event);
  topjet_corrector->process(event);
//!!  topjetER_smearer->process(event);
  topjetlepton_cleaner->process(event);
  topjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

  //// HLT selection
  const bool pass_trigger = trigger_sel->passes(event);
  if(!pass_trigger) return false;
  trigger_h->fill(event);
  ////

  //// LEPTON selection
  const bool pass_lep1 = lep1_sel->passes(event);
  if(!pass_lep1) return false;
  lep1_h->fill(event);
  ////

  //// JET selection

  /* lepton-2Dcut boolean */
  const bool pass_twodcut = twodcut_sel->passes(event);

  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);

  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  jet2_h->fill(event);

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  jet1_h->fill(event);
  ////

  //// MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  met_h->fill(event);

  /* HT_lep selection */
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  htlep_h->fill(event);
  ////

  //// LEPTON-2Dcut selection
  if(!pass_twodcut) return false;
  twodcut_h->fill(event);
  ////

  //// TRIANGULAR-CUTS selection [e+jets only]
  const bool pass_triangc = triangc_sel->passes(event);
  if(!pass_triangc) return false;
  triangc_h->fill(event);
  ////

  /* TOPTAG-EVENT boolean */
  const bool pass_ttagevt = toptagevt_sel->passes(event);
  if(pass_ttagevt) toptagevt_h->fill(event);

  /* add flag_toptagevent to output ntuple */
  event.set(h_flag_toptagevent, int(pass_ttagevt));
  ////

  //// TTBAR KIN RECO
  reco_primlep->process(event);
  if(!pass_ttagevt){ ttbar_reco__ttag0->process(event); ttbar_chi2__ttag0->process(event); }
  else             { ttbar_reco__ttag1->process(event); ttbar_chi2__ttag1->process(event); }
  ////

  if(!pass_ttagevt) chi2min_toptag0_h->fill(event);
  else              chi2min_toptag1_h->fill(event);

  // save only the chi2-best ttbar hypothesis in output sub-ntuple
  std::vector<ReconstructionHypothesis>& hyps = event.get(h_ttbar_hyps);
  const ReconstructionHypothesis* hyp = get_best_hypothesis(hyps, "Chi2");
  if(!hyp) std::runtime_error("ZprimeSelectionModule::process -- best hypothesis for ttbar-reconstruction not found");

  const ReconstructionHypothesis hyp_obj(*hyp);

  hyps.clear();
  hyps.push_back(hyp_obj);

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeSelectionModule)
