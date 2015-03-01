#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/EventHists.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/TauHists.h"
#include "UHH2/common/include/TauIds.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimePreSelectionHists.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/core/include/Selection.h"

using namespace uhh2;

/** \brief module to produce "PreSelection" ntuples for the Z'->ttbar semileptonic analysis
 *  NOTE: output ntuple contains uncleaned jets (no jet-lepton cleaning, no JER smearing)
 */
class ZprimePreSelectionModule: public AnalysisModule {

 public:
  explicit ZprimePreSelectionModule(Context & ctx);
  virtual bool process(Event & event) override;

 private:
  std::unique_ptr<MuonCleaner> muo_cleaner;
  std::unique_ptr<ElectronCleaner> ele_cleaner;

  std::unique_ptr<JetCorrector> jet_corrector;
  std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
  std::unique_ptr<JetResolutionSmearer> jetER_smearer;
  std::unique_ptr<JetCleaner> jet_cleaner;

  std::unique_ptr<TopJetCorrector> topjet_corrector;
  std::unique_ptr<TopJetLeptonDeltaRCleaner> topjetlepton_cleaner;
  std::unique_ptr<TopJetCleaner> topjet_cleaner;

  // declare the Selections to use
  std::unique_ptr<Selection> muoN_sel, eleN_sel, jet1_sel, jet2_sel, topjet1_sel;

  // store the Hists collection as member variables
  std::unique_ptr<Hists> h_event, h_jet, h_ele, h_mu, h_tau, h_topjet;
  std::unique_ptr<Hists> a_event, a_jet, a_ele, a_mu, a_tau, a_topjet;
};

ZprimePreSelectionModule::ZprimePreSelectionModule(Context & ctx){

  // setup object cleaners
  muo_cleaner.reset(new MuonCleaner(AndId<Muon>(MuonIDTight(), PtEtaCut(45., 2.1))));
  ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(ElectronID_PHYS14_25ns_tight, PtEtaCut(35., 2.5))));

  jet_corrector.reset(new JetCorrector(JERFiles::PHYS14_L123_MC));
  jetlepton_cleaner.reset(new JetLeptonCleaner(JERFiles::PHYS14_L123_MC));
  jetlepton_cleaner->set_drmax(.4);
  jetER_smearer.reset(new JetResolutionSmearer(ctx));
  jet_cleaner.reset(new JetCleaner(30., 2.4));

  topjet_corrector.reset(new TopJetCorrector(JERFiles::PHYS14_L123_MC));
  topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(.8));
  topjet_cleaner.reset(new TopJetCleaner(TopJetId(PtEtaCut(200., 2.4))));

  // set up selections
  muoN_sel.reset(new NMuonSelection(1));      // at least 1 muon
  eleN_sel.reset(new NElectronSelection(1));  // at least 1 electron
  jet1_sel.reset(new NJetSelection(1));       // at least 1 jet
  jet2_sel.reset(new NJetSelection(2));       // at least 2 jets
  topjet1_sel.reset(new NTopJetSelection(1)); // at least 1 topjet

  // set up Hists classes
  h_event.reset(new EventHists(ctx, "Event_before_Presel"));
  h_jet.reset(new JetHists(ctx, "Jets_before_Presel"));
  h_ele.reset(new ElectronHists(ctx, "Electron_before_Presel"));
  h_mu.reset(new MuonHists(ctx, "Muon_before_Presel"));
  h_tau.reset(new TauHists(ctx, "Tau_before_Presel"));
  h_topjet.reset(new TopJetHists(ctx, "TopJets_before_Presel"));

  a_event.reset(new EventHists(ctx, "Event_after_Presel"));
  a_jet.reset(new JetHists(ctx, "Jets_after_Presel"));
  a_ele.reset(new ElectronHists(ctx, "Electron_after_Presel"));
  a_mu.reset(new MuonHists(ctx, "Muon_after_Presel"));
  a_tau.reset(new TauHists(ctx, "Tau_after_Presel"));
  a_topjet.reset(new TopJetHists(ctx, "TopJets_after_Presel"));
}

bool ZprimePreSelectionModule::process(Event & event) {

  h_event->fill(event);
  h_jet->fill(event);
  h_ele->fill(event);
  h_mu->fill(event);
  h_tau->fill(event);
  h_topjet->fill(event);

  // keep Jets *before cleaning* to store them in the ntuple if event is accepted
  std::unique_ptr< std::vector<Jet> > uncleaned_jets(new std::vector<Jet>(*event.jets));
  std::unique_ptr< std::vector<TopJet> > uncleaned_topjets(new std::vector<TopJet>(*event.topjets));

  // clean muons/electrons/jets to preselect events
  muo_cleaner->process(event);
  ele_cleaner->process(event);

  jet_corrector->process(event);
  jetlepton_cleaner->process(event);
  jetER_smearer->process(event);
  jet_cleaner->process(event);

  topjet_corrector->process(event);
  topjetlepton_cleaner->process(event);
  topjet_cleaner->process(event);

  // compute preselection-filter boolean
  bool pass_lep = (muoN_sel->passes(event) || eleN_sel->passes(event));
  bool pass_jet = jet2_sel->passes(event) || (jet1_sel->passes(event) && topjet1_sel->passes(event));
  bool pass_presel = pass_lep && pass_jet;

  if(pass_presel){

    a_event->fill(event);
    a_jet->fill(event);
    a_ele->fill(event);
    a_mu->fill(event);
    a_tau->fill(event);
    a_topjet->fill(event);

    // store Jets *before cleaning* in the ntuple
    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(auto & j : *uncleaned_jets) event.jets->push_back(j); 

    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(auto & j : *uncleaned_topjets) event.topjets->push_back(j); 
  }

  return pass_presel;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimePreSelectionModule)
