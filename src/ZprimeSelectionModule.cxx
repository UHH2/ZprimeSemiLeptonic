#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Selection.h"

#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/common/include/TTbarReconstruction.h"
#include "UHH2/common/include/ReconstructionHypothesisDiscriminators.h"
#include "UHH2/common/include/HypothesisHists.h"
#include "UHH2/common/include/TriggerSelection.h"

#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSelectionHists.h"

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
 *   * primary vertex selection
 *   * JER smearing for TopJet collection
 *   * update 2D cut values (after validation)
 *
 */
using namespace uhh2;

class ZprimeSelectionModule: public AnalysisModule {
 public:
  explicit ZprimeSelectionModule(Context & ctx);
  virtual bool process(Event & event) override;

 private:    
  Event::Handle<int> h_flag_toptagevent;

  // cleaners
  std::unique_ptr<MuonCleaner> muo_cleaner;
  std::unique_ptr<ElectronCleaner> ele_cleaner;
  std::unique_ptr<JetCorrector> jet_corrector;
  std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
  std::unique_ptr<JetResolutionSmearer> jetER_smearer;
  std::unique_ptr<JetCleaner> jet_cleaner1;
  std::unique_ptr<JetCleaner> jet_cleaner2;
  std::unique_ptr<TopJetCorrector> topjet_corrector;
  std::unique_ptr<TopJetLeptonDeltaRCleaner> topjetlepton_cleaner;
//  std::unique_ptr<TopJetResolutionSmearer> topjetER_smearer;
  std::unique_ptr<TopJetCleaner> topjet_cleaner;

  // selections
  std::unique_ptr<Selection> trigger_sel;
  std::unique_ptr<AndSelection> lep1_sel;
  std::unique_ptr<Selection> jet2_sel;
  std::unique_ptr<Selection> jet1_sel;
  std::unique_ptr<Selection> met_sel;
  std::unique_ptr<Selection> htlep_sel;
  std::unique_ptr<Selection> twodcut_sel;
  std::unique_ptr<Selection> triangc_sel;
  std::unique_ptr<Selection> toptagevent_sel;

  // ttbar reconstruction
  std::unique_ptr<AnalysisModule> ttgenprod;
  std::unique_ptr<AnalysisModule> reco_primlep;
  std::unique_ptr<AnalysisModule> ttbar_reco_toptag0, ttbar_reco_toptag1;
  std::unique_ptr<AnalysisModule> ttbar_chi2min;
  Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;

  // hists
  std::unique_ptr<Hists> input_h;
  std::unique_ptr<Hists> trigger_h;
  std::unique_ptr<Hists> lep1_h;
  std::unique_ptr<Hists> jet2_h;
  std::unique_ptr<Hists> jet1_h;
  std::unique_ptr<Hists> met_h;
  std::unique_ptr<Hists> htlep_h;
  std::unique_ptr<Hists> twodcut_h;
  std::unique_ptr<Hists> triangc_h;
  std::unique_ptr<Hists> toptagevent_h;
  std::unique_ptr<Hists> chi2min_toptag0_h;
  std::unique_ptr<Hists> chi2min_toptag1_h;
};

ZprimeSelectionModule::ZprimeSelectionModule(Context & ctx){

  //// OBJ CLEANING
  muo_cleaner.reset(new MuonCleaner(AndId<Muon>(MuonIDTight(), PtEtaCut(45., 2.1))));
  ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(ElectronID_PHYS14_25ns_tight_noIso, PtEtaCut(50., 2.5))));
  jet_corrector.reset(new JetCorrector(JERFiles::PHYS14_L123_MC));
  jetlepton_cleaner.reset(new JetLeptonCleaner(JERFiles::PHYS14_L123_MC));
  jetlepton_cleaner->set_drmax(.4);
  jetER_smearer.reset(new JetResolutionSmearer(ctx));
  jet_cleaner1.reset(new JetCleaner(25., std::numeric_limits<double>::infinity())); 
  jet_cleaner2.reset(new JetCleaner(50., 2.4));
  topjet_corrector.reset(new TopJetCorrector(JERFiles::PHYS14_L123_MC));
  topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(.8));
//  topjetER_smearer.reset(new TopJetResolutionSmearer(ctx));
  topjet_cleaner.reset(new TopJetCleaner(TopJetId(PtEtaCut(400., 2.4))));
  ////

  //// EVENT SELECTION
  bool muon(false), elec(false);
  const std::string channel(ctx.get("channel", ""));
  const std::string triggername(ctx.get("triggername", "NotSet"));
  if(channel == "muon") muon = true;
  else if(channel == "electron") elec = true;
  else throw std::runtime_error("undefined argument for 'channel' key in xml file (must be 'muon' or 'electron'): "+channel);

  lep1_sel.reset(new AndSelection(ctx));
  if(muon){
    lep1_sel->add<NMuonSelection>("muoN == 1", 1, 1);
    lep1_sel->add<NElectronSelection>("eleN == 0", 0, 0);

    if(triggername != "NotSet") trigger_sel = make_unique<TriggerSelection>(triggername);
    else trigger_sel = make_unique<TriggerSelection>("HLT_Mu40_eta2p1_PFJet200_PFJet50_v*");
  }
  else if(elec){
    lep1_sel->add<NMuonSelection>("muoN == 0", 0, 0);
    lep1_sel->add<NElectronSelection>("eleN == 1", 1, 1);

    if(triggername != "NotSet") trigger_sel = make_unique<TriggerSelection>(triggername);
    else trigger_sel = make_unique<TriggerSelection>("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v*");
  }

  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut( 50., 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(200., 2.4))));
  met_sel.reset(new METCut(50., std::numeric_limits<double>::infinity()));
  htlep_sel.reset(new HTlepCut(150., std::numeric_limits<double>::infinity()));
  twodcut_sel.reset(new TwoDCut(.4, 25.));

  if(elec) triangc_sel.reset(new TriangularCuts(1.5, 75.));
  else if(muon) triangc_sel.reset(new AndSelection(ctx)); // always true (no triangular cuts for muon channel)

  const TopJetId topjetID = CMSTopTag();
  const float minDR_topjet_jet(1.2);

  toptagevent_sel.reset(new TopTagEventSelection(topjetID, minDR_topjet_jet));
  h_flag_toptagevent = ctx.declare_event_output<int>("flag_toptagevent");
  ////

  //// TTBAR KINEMATICAL RECO
  ttgenprod.reset(new TTbarGenProducer(ctx, "ttbargen", false));

  reco_primlep.reset(new PrimaryLepton(ctx));

  std::string ttbar_hyps_label("TTbarReconstruction");
  ttbar_reco_toptag0.reset(new HighMassTTbarReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label));
  ttbar_reco_toptag1.reset(new TopTagReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label, topjetID, minDR_topjet_jet));
  ttbar_chi2min.reset(new Chi2Discriminator(ctx, ttbar_hyps_label));
  h_ttbar_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis>>(ttbar_hyps_label);
  ////

  //// HISTS
  input_h.reset(new ZprimeSelectionHists(ctx, "input"));
  trigger_h.reset(new ZprimeSelectionHists(ctx, "trigger"));
  lep1_h.reset(new ZprimeSelectionHists(ctx, "lep1"));
  jet2_h.reset(new ZprimeSelectionHists(ctx, "jet2"));
  jet1_h.reset(new ZprimeSelectionHists(ctx, "jet1"));
  met_h.reset(new ZprimeSelectionHists(ctx, "met"));
  htlep_h.reset(new ZprimeSelectionHists(ctx, "htlep"));
  twodcut_h.reset(new ZprimeSelectionHists(ctx, "twodcut"));
  triangc_h.reset(new ZprimeSelectionHists(ctx, "triangc"));
  toptagevent_h.reset(new ZprimeSelectionHists(ctx, "toptagevent"));
  chi2min_toptag0_h.reset(new HypothesisHists(ctx, "chi2min_toptag0__HypHists", ttbar_hyps_label, "Chi2"));
  chi2min_toptag1_h.reset(new HypothesisHists(ctx, "chi2min_toptag1__HypHists", ttbar_hyps_label, "Chi2"));
  ////
}

bool ZprimeSelectionModule::process(Event & event){

  input_h->fill(event);

  //// HLT selection
  bool pass_trigger = trigger_sel->passes(event);
  if(!pass_trigger) return false;
  trigger_h->fill(event);
  ////

  //// LEPTON selection
  muo_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  ele_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  bool pass_lep1 = lep1_sel->passes(event);
  if(!pass_lep1) return false;
  lep1_h->fill(event);
  ////

  //// JET selection
  jet_corrector->process(event);
  jetlepton_cleaner->process(event);
  jetER_smearer->process(event);

  /* lepton-2Dcut boolean */
  jet_cleaner1->process(event); // jets w/ pt>25 GeV for lepton-2Dcut
  bool pass_twodcut = twodcut_sel->passes(event);

  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);

  topjet_corrector->process(event);
  topjetlepton_cleaner->process(event);
//  topjetER_smearer->process(event);
  topjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

  /* 2nd AK4 jet selection */
  bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  jet2_h->fill(event);

  /* 1st AK4 jet selection */
  bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  jet1_h->fill(event);
  ////

  //// MET selection
  bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  met_h->fill(event);

  /* HT_lep selection */
  bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  htlep_h->fill(event);
  ////

  //// LEPTON-2Dcut selection
  if(!pass_twodcut) return false;
  twodcut_h->fill(event);
  ////

  //// TRIANGULAR-CUTS selection (electron-only)
  bool pass_triangc = triangc_sel->passes(event);
  if(!pass_triangc) return false;
  triangc_h->fill(event);
  ////

  //// TOPTAG-EVENT selection
  bool pass_toptagevent = toptagevent_sel->passes(event);
  if(pass_toptagevent) toptagevent_h->fill(event);

  /* add flag_toptagevent to output ntuple */
  event.set(h_flag_toptagevent, int(pass_toptagevent));
  ////

  //// TTBAR KIN RECO
  ttgenprod->process(event);

  reco_primlep->process(event);

  if(pass_toptagevent){
    ttbar_reco_toptag1->process(event);
    ttbar_chi2min->process(event);
    chi2min_toptag1_h->fill(event);
  }
  else{
    ttbar_reco_toptag0->process(event);
    ttbar_chi2min->process(event);
    chi2min_toptag0_h->fill(event);
  }
  ////

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeSelectionModule)
