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

using namespace std;
using namespace uhh2;

/** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
 * 
 * This is the central class which calls other AnalysisModules, Hists or Selection classes.
 * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
 */
class ZprimePreSelectionModule: public AnalysisModule {
public:
    
    explicit ZprimePreSelectionModule(Context & ctx);
    virtual bool process(Event & event) override;

private: 
  //std::unique_ptr<CommonModules> common;    
  std::unique_ptr<JetCleaner> jetcleaner;
  std::unique_ptr<MuonCleaner> muoncleaner;
  std::unique_ptr<ElectronCleaner> electroncleaner;
  std::unique_ptr<JetLeptonCleaner> jetleptoncleaner;
  std::unique_ptr<JetCorrector> jetcorrector;
  std::unique_ptr<JetResolutionSmearer> jetresolutionsmearer;
  
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
  std::unique_ptr<Selection> nele_sel, nmu_sel, njet_sel;
    
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
std::unique_ptr<Hists> h_event, h_jet, h_ele, h_mu, h_tau, h_topjet;
std::unique_ptr<Hists> a_event, a_jet, a_ele, a_mu, a_tau, a_topjet;
};

ZprimePreSelectionModule::ZprimePreSelectionModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    // cout << "Hello World from ZprimePreSelectionModule!" << endl;    
    // If needed, access the configuration of the module here, e.g.:
    // string testvalue = ctx.get("TestKey", "<not set>");
    // cout << "TestKey in the configuration was: " << testvalue << endl;
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    // for(auto & kv : ctx.get_all()){
    // cout << " " << kv.first << " = " << kv.second << endl;
    //}

    // 1. setup other modules (CommonModules,JetCleaner, etc.):
  jetcorrector.reset(new JetCorrector(JERFiles::PHYS14_L123_MC));

  muoncleaner.reset(new MuonCleaner(AndId<Muon>(MuonIDTight(),PtEtaCut(45.0, 2.1))));
  electroncleaner.reset(new ElectronCleaner(AndId<Electron>(ElectronID_PHYS14_25ns_tight, PtEtaCut(35.0, 2.5))));
  jetleptoncleaner.reset(new JetLeptonCleaner(JERFiles::PHYS14_L123_MC));
  jetresolutionsmearer.reset(new JetResolutionSmearer(ctx));
  jetcleaner.reset(new JetCleaner(30.0, 2.5)); 
  
    // 2. set up selections
    // For Muons only:
    nele_sel.reset(new NElectronSelection(0,0)); //no electrons
    nmu_sel.reset(new NMuonSelection(1,-1)); // at least one muon
    njet_sel.reset(new NJetSelection(2)); // at least 2 jets

    // 3. Set up Hists classes:
    
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
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    //cout << "ZprimePreSelectionModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;
    
    // 0. Fill Presel histos.
      h_event->fill(event);
      h_jet->fill(event);
      h_ele->fill(event);
      h_mu->fill(event);
      h_tau->fill(event);
      h_topjet->fill(event);

    // 1. run all modules other modules.
      
  jetcorrector->process(event);
  muoncleaner->process(event);     
  electroncleaner->process(event);    
  jetleptoncleaner->process(event);     
  jetresolutionsmearer->process(event);      
  jetcleaner->process(event); 

  // 2. test selections and fill histograms after PreSelection 
  bool nele_selection = nele_sel->passes(event);
  bool nmu_selection = nmu_sel->passes(event);
  bool njet_selection = njet_sel->passes(event);
  
if(nele_selection && nmu_selection && njet_selection){
  a_event->fill(event);
  a_jet->fill(event);
  a_ele->fill(event);
  a_mu->fill(event);
  a_tau->fill(event);
  a_topjet->fill(event);
}

  // 3. decide whether or not to keep the current event in the output:
  return  njet_selection && nmu_selection && nele_selection; ;
  //return true;
}
  
  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ZprimePreSelectionModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(ZprimePreSelectionModule)
  

