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
#include "UHH2/ZprimeSemiLeptonic/include/ZprimePreSelectionHists.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/core/include/Selection.h"

using namespace uhh2;

/** \brief module to produce "PreSelection" ntuples for the Z'->ttbar semileptonic analysis
 *  SELECTION: ">=1 lepton (muon or electron) & >=2 small-radius jets"
 *  NOTE: output ntuple contains uncleaned jets (no jet-lepton cleaning, no JER smearing)
 */
class ZprimePreSelectionModule: public AnalysisModule {

 public:
  explicit ZprimePreSelectionModule(Context & ctx);
  virtual bool process(Event & event) override;

 private:
  std::unique_ptr<JetCleaner> jetcleaner;
  std::unique_ptr<MuonCleaner> muoncleaner;
  std::unique_ptr<ElectronCleaner> electroncleaner;
  std::unique_ptr<JetLeptonCleaner> jetleptoncleaner;
  std::unique_ptr<JetCorrector> jetcorrector;
  std::unique_ptr<JetResolutionSmearer> jetresolutionsmearer;

  // declare the Selections to use
  std::unique_ptr<Selection> muoN_sel, eleN_sel, jetN_sel;

  // store the Hists collection as member variables
  std::unique_ptr<Hists> h_event, h_jet, h_ele, h_mu, h_tau, h_topjet;
  std::unique_ptr<Hists> a_event, a_jet, a_ele, a_mu, a_tau, a_topjet;

  void debug(const Event&, const std::string&);
};

ZprimePreSelectionModule::ZprimePreSelectionModule(Context & ctx){

  // setup object cleaners
  jetcorrector.reset(new JetCorrector(JERFiles::PHYS14_L123_MC));

  muoncleaner.reset(new MuonCleaner(AndId<Muon>(MuonIDTight(), PtEtaCut(45., 2.1))));
  electroncleaner.reset(new ElectronCleaner(AndId<Electron>(ElectronID_PHYS14_25ns_tight, PtEtaCut(35., 2.5))));
  jetleptoncleaner.reset(new JetLeptonCleaner(JERFiles::PHYS14_L123_MC));
  jetresolutionsmearer.reset(new JetResolutionSmearer(ctx));
  jetcleaner.reset(new JetCleaner(30., 2.4));

  // set up selections
  muoN_sel.reset(new NMuonSelection(1));    // at least 1 muon
  eleN_sel.reset(new NElectronSelection(1));// at least 1 electron
  jetN_sel.reset(new NJetSelection(2));     // at least 2 jets

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

  // apply JECs
  jetcorrector->process(event);

  // clean muons/electrons/jets to preselect events
  muoncleaner->process(event);
  electroncleaner->process(event);
  jetleptoncleaner->process(event);
  jetresolutionsmearer->process(event);
  jetcleaner->process(event);

  // compute preselection-filter boolean
  bool pass_presel = (muoN_sel->passes(event) || eleN_sel->passes(event)) && jetN_sel->passes(event);

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
  }

  return pass_presel;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimePreSelectionModule)
