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
  std::unique_ptr<JetCleaner> jet_cleaner;

  std::vector<std::unique_ptr<AnalysisModule>> recomodules;

  // Selection
  std::unique_ptr<AndSelection> lepN_sel;
  std::unique_ptr<Selection> pvN_sel, jet1_sel, jet2_sel, htlep_sel, met_sel, twodcut_sel, topjetN_sel, topjetoverlap_sel;
 
  // Hists
  std::unique_ptr<Hists> h_hyphists, h_event, h_jet, h_ele, h_mu, h_tau, h_topjet;
  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps;
};

ZprimeSelectionModule::ZprimeSelectionModule(Context & ctx){

  muo_cleaner.reset(new MuonCleaner(AndId<Muon>(MuonIDTight(), PtEtaCut(45., 2.1))));
  ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(ElectronID_PHYS14_25ns_medium, PtEtaCut(35., 2.5))));
  jet_corrector.reset(new JetCorrector(JERFiles::PHYS14_L123_MC));
  jetlepton_cleaner.reset(new JetLeptonCleaner(JERFiles::PHYS14_L123_MC));
  jet_cleaner.reset(new JetCleaner(25., std::numeric_limits<double>::infinity())); 

  bool muon(false), elec(false);
  const std::string channel(ctx.get("channel", ""));
  if(channel == "muon") muon = true;
  else if(channel == "electron") elec = true;
  else throw std::runtime_error("undefined argument for analysis channel (must be 'muon' or 'electron'): "+channel);

  lepN_sel.reset(new AndSelection(ctx));
  if(muon){
    lepN_sel->add<NMuonSelection>("muoN == 1", 1, 1);
    lepN_sel->add<NElectronSelection>("eleN == 0", 0, 0);
  }
  else if(elec){
    lepN_sel->add<NMuonSelection>("muoN == 0", 0, 0);
    lepN_sel->add<NElectronSelection>("eleN == 1", 1, 1);
  }

  jet1_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(150., 2.4)))); // at least 2 jets with pt>50 and |eta|<2.4
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(50., 2.4)))); // at least 2 jets with pt>50 and |eta|<2.4
  htlep_sel.reset(new HTlepCut(150., std::numeric_limits<double>::infinity()));
  met_sel.reset(new METCut(50., std::numeric_limits<double>::infinity()));
  twodcut_sel.reset(new TwoDCut());
  topjetN_sel.reset(new NTopJetSelection(1, -1, TopJetId(CMSTopTag())));
  topjetoverlap_sel.reset(new TopJetOverlapSelection());

  // reconstruction hypotheses
  recomodules.emplace_back(new PrimaryLepton(ctx));
  recomodules.emplace_back(new HighMassTTbarReconstruction(ctx,NeutrinoReconstruction));
  recomodules.emplace_back(new Chi2Discriminator(ctx,"HighMassReconstruction"));

  // Hists setup
  h_hyphists.reset(new HypothesisHists(ctx, "Chi2Hists", "HighMassReconstruction", "Chi2"));
  h_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis>>("HighMassReconstruction");
  h_event.reset(new EventHists(ctx, "Event_Sel"));
  h_jet.reset(new JetHists(ctx, "Jets_Sel"));
  h_ele.reset(new ElectronHists(ctx, "Electron_Sel"));
  h_mu.reset(new MuonHists(ctx, "Muon_Sel"));
  h_tau.reset(new TauHists(ctx, "Tau_Sel"));
  h_topjet.reset(new TopJetHists(ctx, "TopJets_Sel"));
}

bool ZprimeSelectionModule::process(Event & event){

  muo_cleaner->process(event);
  ele_cleaner->process(event);
  jet_corrector->process(event);
  jetlepton_cleaner->process(event);
  jet_cleaner->process(event);

  bool pass_lepN = lepN_sel->passes(event);
  bool pass_jet1 = jet1_sel->passes(event);
  bool pass_jet2 = jet2_sel->passes(event);
  bool pass_twodcut = twodcut_sel->passes(event);
  bool pass_htlep = htlep_sel->passes(event);
  bool pass_met = met_sel->passes(event);
  bool pass_topjetN = topjetN_sel->passes(event);
  bool pass_topjetoverlap = topjetoverlap_sel->passes(event);

///  if(nele_selection && nmu_selection && njet_selection && twodcut_selection && htlepcut_selection && metcut_selection && ntopjet_selection && topjetoverlap_selection){
///
///    for(auto & m : recomodules) m->process(event);
///
///    h_event->fill(event);
///    h_jet->fill(event);
///    h_ele->fill(event);
///    h_mu->fill(event);
///    h_tau->fill(event);
///    h_topjet->fill(event);
///    h_hyphists->fill(event);
///  }

  return pass_lepN && pass_jet1 && pass_jet2 && pass_twodcut && pass_htlep && pass_met && pass_topjetN && pass_topjetoverlap;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeSelectionModule)
