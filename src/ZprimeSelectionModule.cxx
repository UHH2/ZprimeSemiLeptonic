#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/EventHists.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSelectionHists.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/TTbarReconstruction.h"
#include "UHH2/common/include/ReconstructionHypothesisDiscriminators.h"
#include "UHH2/common/include/HypothesisHists.h"
#include "UHH2/common/include/TriggerSelection.h"
//
// -- ITEMS TO BE IMPLEMENTED
//   * trigger selection
//   * update 2D cut values and thresholds for leptons and jets according to the HLT paths
//   * primary vertex selection
//   * triangular cuts (electron only)
//   * JER smearing for TopJet collection
//
using namespace uhh2;

class ZprimeSelectionModule: public AnalysisModule {
 public:
  explicit ZprimeSelectionModule(Context & ctx);
  virtual bool process(Event & event) override;

 private:    
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

  std::vector<std::unique_ptr<AnalysisModule>> recomodules;

  // Selection
  std::unique_ptr<AndSelection> lepN_sel;
  std::unique_ptr<Selection> jet1_sel, jet2_sel, htlep_sel, met_sel, twodcut_sel, toptagevent_sel;
  std::unique_ptr<Selection> ele_Trigger, mu_Trigger;
  // Hists
  std::unique_ptr<Hists> input_h_event, lep1_h_event, jet1_h_event, jet2_h_event, trigger_h_event;
  std::unique_ptr<Hists> htlep_h_event, met_h_event, twodcut_h_event, toptagevent_h_event;
  std::unique_ptr<Hists> h_hyphists, h_event, h_jet, h_ele, h_mu, h_topjet;
  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps;
};

ZprimeSelectionModule::ZprimeSelectionModule(Context & ctx){

  muo_cleaner.reset(new MuonCleaner(AndId<Muon>(MuonIDTight(), PtEtaCut(45., 2.1))));
  ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(ElectronID_PHYS14_25ns_tight_noIso, PtEtaCut(35., 2.5))));
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

  bool muon(false), elec(false);
  const std::string channel(ctx.get("channel", ""));
  if(channel == "muon") muon = true;
  else if(channel == "electron") elec = true;
  else throw std::runtime_error("undefined argument for 'channel' key in xml file (must be 'muon' or 'electron'): "+channel);

  lepN_sel.reset(new AndSelection(ctx));
  if(muon){
    lepN_sel->add<NMuonSelection>("muoN == 1", 1, 1);
    lepN_sel->add<NElectronSelection>("eleN == 0", 0, 0);
    mu_Trigger.reset(new TriggerSelection("HLT_Mu40_eta2p1_PFJet200_PFJet50_v*"));
  }
  else if(elec){
    lepN_sel->add<NMuonSelection>("muoN == 0", 0, 0);
    lepN_sel->add<NElectronSelection>("eleN == 1", 1, 1);
    ele_Trigger.reset(new TriggerSelection("HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v*")); 
  }

  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(150., 2.4)))); // at least 1 jet with pt>150 and |eta|<2.4
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(50., 2.4))));  // at least 2 jets with pt>50 and |eta|<2.4
  met_sel.reset(new METCut(50., std::numeric_limits<double>::infinity()));
  htlep_sel.reset(new HTlepCut(150., std::numeric_limits<double>::infinity()));
  twodcut_sel.reset(new TwoDCut(.4, 25.));
  toptagevent_sel.reset(new TopTagEventSelection(CMSTopTag(), 1.2));

  // reconstruction hypotheses
  recomodules.emplace_back(new PrimaryLepton(ctx));
  recomodules.emplace_back(new HighMassTTbarReconstruction(ctx,NeutrinoReconstruction));
  recomodules.emplace_back(new Chi2Discriminator(ctx,"HighMassReconstruction"));

  // Hists setup
  input_h_event.reset(new EventHists(ctx, "input_Event"));
  lep1_h_event.reset(new EventHists(ctx, "lep1_Event"));
  jet1_h_event.reset(new EventHists(ctx, "jet1_Event"));
  jet2_h_event.reset(new EventHists(ctx, "jet2_Event"));
  met_h_event.reset(new EventHists(ctx, "met_Event"));
  htlep_h_event.reset(new EventHists(ctx, "htlep_Event"));
  twodcut_h_event.reset(new EventHists(ctx, "twodcut_Event"));
  toptagevent_h_event.reset(new EventHists(ctx, "toptagevent_Event"));
  trigger_h_event.reset(new EventHists(ctx,"trigger_Event"));
  h_hyphists.reset(new HypothesisHists(ctx, "Chi2Hists", "HighMassReconstruction", "Chi2"));
  h_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis>>("HighMassReconstruction");
  h_event.reset(new EventHists(ctx, "Event_Sel"));
  h_jet.reset(new JetHists(ctx, "Jets_Sel"));
  h_ele.reset(new ElectronHists(ctx, "Electron_Sel"));
  h_mu.reset(new MuonHists(ctx, "Muon_Sel"));
  h_topjet.reset(new TopJetHists(ctx, "TopJets_Sel"));
}

bool ZprimeSelectionModule::process(Event & event){

  input_h_event->fill(event);

  muo_cleaner->process(event);
  ele_cleaner->process(event);
  bool pass_lepN = lepN_sel->passes(event);
  if(!pass_lepN) return false;
  lep1_h_event->fill(event);

  jet_corrector->process(event);
  jetlepton_cleaner->process(event);
  jetER_smearer->process(event);
  jet_cleaner1->process(event); // jets w/ pt>25 GeV for lepton-2Dcut
  //Trigger selection
  bool ele_Trigger_selection = ele_Trigger->passes(event);
  bool mu_Trigger_selection = mu_Trigger->passes(event);
  if (!ele_Trigger_selection || !mu_Trigger_selection || (mu_Trigger_selection && ele_Trigger_selection)) return false;
  trigger_h_event->fill(event);
  // 2D cut
  bool pass_twodcut = twodcut_sel->passes(event);

  jet_cleaner2->process(event); // cleaned jets with pt>50 GeV & |eta|<2.4
  sort_by_pt<Jet>(*event.jets);

  topjet_corrector->process(event);
  topjetlepton_cleaner->process(event);
//  topjetER_smearer->process(event);
  topjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

  // selection on 1st AK4 jet
  bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  jet1_h_event->fill(event);

  // selection on 2nd AK4 jet
  bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  jet2_h_event->fill(event);

  // selection on MET
  bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  met_h_event->fill(event);

  // selection on HT_lep
  bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  htlep_h_event->fill(event);

  // selection on lepton-2Dcut
  if(!pass_twodcut) return false;
  twodcut_h_event->fill(event);

  // selection for 'top-tagged jet event'
  bool pass_toptagevent = toptagevent_sel->passes(event);
  if(pass_toptagevent) toptagevent_h_event->fill(event);

  for(auto & m : recomodules) m->process(event);
  h_event->fill(event);
  h_jet->fill(event);
  h_ele->fill(event);
  h_mu->fill(event);
  h_topjet->fill(event);
  h_hyphists->fill(event);

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeSelectionModule)
