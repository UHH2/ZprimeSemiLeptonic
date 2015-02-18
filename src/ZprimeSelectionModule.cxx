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
#include "UHH2/common/include/TauHists.h"
#include "UHH2/common/include/TauIds.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSelectionHists.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/TTbarReconstruction.h"
#include "UHH2/common/include/ReconstructionHypothesisDiscriminators.h"
#include "UHH2/common/include/HypothesisHists.h"


using namespace std;
using namespace uhh2;

class ZprimeSelectionModule: public AnalysisModule {
public:
    
    explicit ZprimeSelectionModule(Context & ctx);
    virtual bool process(Event & event) override;

private:    
  std::unique_ptr<JetCleaner> jetcleaner;
  std::unique_ptr<MuonCleaner> muoncleaner;
  std::unique_ptr<ElectronCleaner> electroncleaner;
  std::unique_ptr<JetLeptonCleaner> jetleptoncleaner;
  std::unique_ptr<JetCorrector> jetcorrector;
  JetId jet_kinematic;
  TopJetId topjetid;

  std::vector<std::unique_ptr<AnalysisModule>> recomodules;
  std::vector<std::unique_ptr<AnalysisModule>> pre_modules;
    
    // declare the Selections to use. 
  std::unique_ptr<Selection> nele_sel, nmu_sel, njet_sel, twodcut, htlepcut, metcut, ntopjet_sel, cmstoptagoverlap_sel;
  // add later: npv_sel, etc.
 
    // store the Hists collection as member variables.
  std::unique_ptr<Hists> h_hyphists, h_event, h_jet, h_ele, h_mu, h_tau, h_topjet;
  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps;
};

ZprimeSelectionModule::ZprimeSelectionModule(Context & ctx){
   
  jet_kinematic = PtEtaCut(150.0, 2.5);
  topjetid = CMSTopTag();

    // 1. setup other modules (CommonModules,JetCleaner, etc.):
  jetcleaner.reset(new JetCleaner(25.0,std::numeric_limits<double>::infinity())); 
  muoncleaner.reset(new MuonCleaner(AndId<Muon>(MuonIDTight(),PtEtaCut(45.0, 2.1))));
  electroncleaner.reset(new ElectronCleaner(AndId<Electron>(ElectronID_PHYS14_25ns_medium, PtEtaCut(35.0, 2.5))));
  jetcorrector.reset(new JetCorrector(JERFiles::PHYS14_L123_MC));
  jetleptoncleaner.reset(new JetLeptonCleaner(JERFiles::PHYS14_L123_MC));
  pre_modules.push_back(std::unique_ptr<AnalysisModule>(new HTlepCalculator(ctx)));
   
    // 2. set up selections
    // For Muons only:
  nele_sel.reset(new NElectronSelection(0,0)); //no electrons
  nmu_sel.reset(new NMuonSelection(1,1)); // exactly one muon
  twodcut.reset(new TwoDCut()); 
  njet_sel.reset(new NJetSelection(1, -1,jet_kinematic)); // at least 2 jets with pt 150 and eta 2.5
  htlepcut.reset(new HTlepCut(ctx,150,std::numeric_limits<double>::infinity()));
  metcut.reset(new METCut(20,std::numeric_limits<double>::infinity()));
  ntopjet_sel.reset(new NTopJetSelection(1,-1,topjetid));
  cmstoptagoverlap_sel.reset(new CMSTopTagOverlapSelection()); 

 //make reconstruction hypotheses
  recomodules.emplace_back(new PrimaryLepton(ctx));
  recomodules.emplace_back(new HighMassTTbarReconstruction(ctx,NeutrinoReconstruction));
  recomodules.emplace_back(new Chi2Discriminator(ctx,"HighMassReconstruction"));

    // 3. Set up Hists classes:
  h_hyphists.reset(new HypothesisHists(ctx,"Chi2Hists","HighMassReconstruction","Chi2"));
  h_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis>>("HighMassReconstruction");
  h_event.reset(new EventHists(ctx, "Event_Sel"));
  h_jet.reset(new JetHists(ctx, "Jets_Sel"));
  h_ele.reset(new ElectronHists(ctx, "Electron_Sel"));
  h_mu.reset(new MuonHists(ctx, "Muon_Sel"));
  h_tau.reset(new TauHists(ctx, "Tau_Sel"));
  h_topjet.reset(new TopJetHists(ctx, "TopJets_Sel"));
}

bool ZprimeSelectionModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    //cout << "ZprimeSelectionModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;
    


    // 1. run all modules other modules.
  jetcleaner->process(event);
  muoncleaner->process(event);
  electroncleaner->process(event);
  jetcorrector->process(event);
  jetleptoncleaner->process(event);

  for (auto & mod : pre_modules) {
  mod->process(event);
  }

  // 2. test selections and fill histograms  
  bool nele_selection = nele_sel->passes(event);
  bool nmu_selection = nmu_sel->passes(event);
  bool njet_selection = njet_sel->passes(event);
  bool twodcut_selection = twodcut->passes(event);
  bool htlepcut_selection = htlepcut->passes(event);
  bool metcut_selection = metcut->passes(event);
  bool ntopjet_selection = ntopjet_sel->passes(event);
  bool cmstoptagoverlap_selection = cmstoptagoverlap_sel->passes(event);
  

  //if(nele_selection && nmu_selection && njet_selection && twodcut_selection && htlepcut_selection && metcut_selection && ntopjet_selection && cmstoptagoverlap_selection){
if(nele_selection && nmu_selection && njet_selection && twodcut_selection && htlepcut_selection && metcut_selection && ntopjet_selection && cmstoptagoverlap_selection){
    for(auto & m : recomodules){
        m->process(event);
      }

    h_event->fill(event);
    h_jet->fill(event);
    h_ele->fill(event);
    h_mu->fill(event);
    h_tau->fill(event);
    h_topjet->fill(event);
    h_hyphists->fill(event);
  }

  // 3. decide whether or not to keep the current event in the output:
  return  nele_selection && nmu_selection && njet_selection && twodcut_selection && htlepcut_selection && metcut_selection && ntopjet_selection && cmstoptagoverlap_selection;

}
  
  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ZprimeSelectionModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(ZprimeSelectionModule)
  

