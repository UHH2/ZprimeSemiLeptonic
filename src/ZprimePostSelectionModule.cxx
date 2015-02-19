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

class ZprimePostSelectionModule: public AnalysisModule {
public:
    
    explicit ZprimePostSelectionModule(Context & ctx);
    virtual bool process(Event & event) override;

private:    
  JetId jet_kinematic, btag_medium;
  TopJetId topjetid;
  std::vector<std::unique_ptr<AnalysisModule>> recomodules;

      
  // declare the Selections to use. 
  std::unique_ptr<Selection> njet_sel, metcut, chi2_sel, btag_sel, ntopjet_sel, cmstoptagoverlap_sel;
 
  // store the Hists collection as member variables.
  std::unique_ptr<Hists> top_hyphists, top_event, top_jet, top_ele, top_mu, top_tau, top_topjet;
  std::unique_ptr<Hists> notopb_hyphists, notopb_event, notopb_jet, notopb_ele, notopb_mu, notopb_tau, notopb_topjet;
  std::unique_ptr<Hists> notopnob_hyphists, notopnob_event, notopnob_jet, notopnob_ele, notopnob_mu, notopnob_tau, notopnob_topjet;

  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps;
};

ZprimePostSelectionModule::ZprimePostSelectionModule(Context & ctx){
  btag_medium = CSVBTag(CSVBTag::WP_MEDIUM);
  jet_kinematic = PtEtaCut(150.0, 2.5);
  topjetid = CMSTopTag();

    // 1. setup other modules (CommonModules,JetCleaner, etc.):

    // 2. set up selections
    // For Muons only:
  njet_sel.reset(new NJetSelection(1,-1,jet_kinematic)); // at least 2 jets with pt 150 and eta 2.5
  btag_sel.reset(new NJetSelection(1,-1,btag_medium));
  metcut.reset(new METCut(50,std::numeric_limits<double>::infinity()));
  ntopjet_sel.reset(new NTopJetSelection(1,1,topjetid));
  cmstoptagoverlap_sel.reset(new CMSTopTagOverlapSelection()); 
  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,0., 50.));


    //make reconstruction hypotheses
  recomodules.emplace_back(new PrimaryLepton(ctx));
  recomodules.emplace_back(new HighMassTTbarReconstruction(ctx,NeutrinoReconstruction));
  recomodules.emplace_back(new Chi2Discriminator(ctx,"HighMassReconstruction"));

    // 3. Set up Hists classes:
  h_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis>>("HighMassReconstruction");

  top_hyphists.reset(new HypothesisHists(ctx,"Chi2Hists_TopTag","HighMassReconstruction","Chi2"));
  top_event.reset(new EventHists(ctx, "Event_TopTag"));
  top_jet.reset(new JetHists(ctx, "Jets_TopTag"));
  top_ele.reset(new ElectronHists(ctx, "Electron_TopTag"));
  top_mu.reset(new MuonHists(ctx, "Muon_TopTag"));
  top_tau.reset(new TauHists(ctx, "Tau_TopTag"));
  top_topjet.reset(new TopJetHists(ctx, "TopJets_TopTag"));

  notopb_hyphists.reset(new HypothesisHists(ctx,"Chi2Hists_NoTag_BTag","HighMassReconstruction","Chi2"));
  notopb_event.reset(new EventHists(ctx, "Event_NoTag_BTag"));
  notopb_jet.reset(new JetHists(ctx, "Jets_NoTag_BTag"));
  notopb_ele.reset(new ElectronHists(ctx, "Electron_NoTag_BTag"));
  notopb_mu.reset(new MuonHists(ctx, "Muon_NoTag_BTag"));
  notopb_tau.reset(new TauHists(ctx, "Tau_NoTag_BTag"));
  notopb_topjet.reset(new TopJetHists(ctx, "TopJets_NoTag_BTag"));  

  notopnob_hyphists.reset(new HypothesisHists(ctx,"Chi2Hists_NoTopTag_NoBTag","HighMassReconstruction","Chi2"));
  notopnob_event.reset(new EventHists(ctx, "Event_NoTopTag_NoBTag"));
  notopnob_jet.reset(new JetHists(ctx, "Jets_NoTopTag_NoBTag"));
  notopnob_ele.reset(new ElectronHists(ctx, "Electron_NoTopTag_NoBTag"));
  notopnob_mu.reset(new MuonHists(ctx, "Muon_NoTopTag_NoBTag"));
  notopnob_tau.reset(new TauHists(ctx, "Tau_NoTopTag_NoBTag"));
  notopnob_topjet.reset(new TopJetHists(ctx, "TopJets_NoTopTag_NoBTag"));
}

bool ZprimePostSelectionModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    //cout << "ZprimePostSelectionModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;
    


  // 1. run all modules other modules.
  for(auto & m : recomodules){
    m->process(event);
  }

  // 2. test selections and fill histograms  
  bool chi2_selection = chi2_sel->passes(event);
  bool njet_selection = njet_sel->passes(event);
  bool metcut_selection = metcut->passes(event);
  bool ntopjet_selection = ntopjet_sel->passes(event);
  bool cmstoptagoverlap_selection = cmstoptagoverlap_sel->passes(event);
  bool btag_selection = btag_sel->passes(event);
  
  if(njet_selection && metcut_selection && chi2_selection){
    if(ntopjet_selection && cmstoptagoverlap_selection){
      top_event->fill(event);
      top_jet->fill(event);
      top_ele->fill(event);
      top_mu->fill(event);
      top_tau->fill(event);
      top_topjet->fill(event);
      top_hyphists->fill(event);
    }
    else{
      if(btag_selection){
        notopb_event->fill(event);
        notopb_jet->fill(event);
        notopb_ele->fill(event);
        notopb_mu->fill(event);
        notopb_tau->fill(event);
        notopb_topjet->fill(event);
        notopb_hyphists->fill(event);
        }  

      if(!btag_selection){
        notopnob_event->fill(event);
        notopnob_jet->fill(event);
        notopnob_ele->fill(event);
        notopnob_mu->fill(event);
        notopnob_tau->fill(event);
        notopnob_topjet->fill(event);
        notopnob_hyphists->fill(event);
        }  
    }
  }

  // 3. decide whether or not to keep the current event in the output:
  return  true;

}
  
  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ZprimePostSelectionModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(ZprimePostSelectionModule)
  

