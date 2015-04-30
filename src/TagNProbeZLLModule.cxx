#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Selection.h"

#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/EventHists.h"

#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h"

/** \brief module to produce "Tag-N-Probe" ntuples for Z->ll control region
 *         used in Z'->ttbar semileptonic analysis to measure lepton efficiencies (e.g. lepton 2D-cut)
 *
 *  -- GOALS:
 *   * complete object reconstruction (pt/eta cuts, IDs, jet-lepton cleaning, JER smearing)
 *   * apply baseline kinematic cuts similar to lepton+jets SR. current cutflow:
 *     * HLT (if specified)
 *     * ==2 leptons (w/ pt+eta+ID cuts)
 *     * >=2 AK4 jets w/ pt> 50 |eta|<2.4
 *     * >=1 AK4 jets w/ pt>200 |eta|<2.4
 *     * TAG lepton : tighter selection
 *           -- ID and/or isolation cut and/or lepton 2D-cut
 *           -- NB: avoid triangular cuts b/c correlated to MET cut (and Z->ll sample has no real MET)
 *     * PROBE lepton : same lepton selection (pt+eta+ID) as for lepton in l+jets SR
 *
 */
using namespace uhh2;

class TagNProbeZLLModule: public AnalysisModule {
 public:
  explicit TagNProbeZLLModule(Context&);
  virtual bool process(Event&) override;

  enum lepton { muon, elec };
  lepton channel;

 private:    
  // cleaners
  std::unique_ptr<MuonCleaner> muo_cleaner;
  std::unique_ptr<ElectronCleaner> ele_cleaner;
  std::unique_ptr<JetCorrector> jet_corrector;
  std::unique_ptr<JetResolutionSmearer> jetER_smearer;
  std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
  std::unique_ptr<JetCleaner> jet_cleaner1;
  std::unique_ptr<JetCleaner> jet_cleaner2;
  std::unique_ptr<JetCleaner> jet_cleaner3;
  std::unique_ptr<JetCleaner> jet_cleaner4;
  std::unique_ptr<JetCleaner> jet_cleaner5;

  // selections
  std::unique_ptr<Selection> trigger_sel;
  std::unique_ptr<AndSelection> lep2_sel;
  std::unique_ptr<Selection> jet2_sel;
  std::unique_ptr<Selection> jet1_sel;

  // hists
  std::unique_ptr<Hists> hi_input__event;
  std::unique_ptr<Hists> hi_output__event;

  // TnP vars
  Event::Handle<float> h_MCweight;
  Event::Handle<int>   h_pvN;
  Event::Handle<float> h_MET__pt;
  Event::Handle<float> h_MET__phi;
  Event::Handle<int>   h_jetN__pt030_eta2p4;
  Event::Handle<int>   h_jetN__pt050_eta2p4;
  Event::Handle<int>   h_jetN__pt100_eta2p4;
  Event::Handle<int>   h_jetN__pt200_eta2p4;

  Event::Handle<float> h_ZLL__M;
  Event::Handle<float> h_ZLL__pt;
  Event::Handle<float> h_ZLL__eta;
  Event::Handle<float> h_ZLL__phi;

  Event::Handle<float> h_TAG__E;
  Event::Handle<float> h_TAG__pt;
  Event::Handle<float> h_TAG__eta;
  Event::Handle<float> h_TAG__etaSC;
  Event::Handle<float> h_TAG__phi;
  Event::Handle<int>   h_TAG__charge;
  Event::Handle<float> h_TAG__pfiso_dbeta;
  Event::Handle<float> h_TAG__dRjet_pt025;
  Event::Handle<float> h_TAG__dRjet_pt030_eta2p4;
  Event::Handle<float> h_TAG__dRjet_pt050_eta2p4;
  Event::Handle<float> h_TAG__pTrel_pt025;
  Event::Handle<float> h_TAG__pTrel_pt030_eta2p4;
  Event::Handle<float> h_TAG__pTrel_pt050_eta2p4;

  Event::Handle<float> h_PRO__E;
  Event::Handle<float> h_PRO__pt;
  Event::Handle<float> h_PRO__eta;
  Event::Handle<float> h_PRO__etaSC;
  Event::Handle<float> h_PRO__phi;
  Event::Handle<int>   h_PRO__charge;
  Event::Handle<float> h_PRO__pfiso_dbeta;
  Event::Handle<float> h_PRO__dRjet_pt025;
  Event::Handle<float> h_PRO__dRjet_pt030_eta2p4;
  Event::Handle<float> h_PRO__dRjet_pt050_eta2p4;
  Event::Handle<float> h_PRO__pTrel_pt025;
  Event::Handle<float> h_PRO__pTrel_pt030_eta2p4;
  Event::Handle<float> h_PRO__pTrel_pt050_eta2p4;
};

TagNProbeZLLModule::TagNProbeZLLModule(Context & ctx){

  //// OBJ CLEANING
  muo_cleaner.reset(new MuonCleaner(AndId<Muon>(MuonIDTight(), PtEtaCut(45., 2.1))));
  ele_cleaner.reset(new ElectronCleaner(AndId<Electron>(ElectronID_PHYS14_25ns_tight_noIso, PtEtaCut(50., 2.5))));
  jet_corrector.reset(new JetCorrector(JERFiles::PHYS14_L123_MC));
  jetER_smearer.reset(new JetResolutionSmearer(ctx));
  jetlepton_cleaner.reset(new JetLeptonCleaner(JERFiles::PHYS14_L123_MC));
  jetlepton_cleaner->set_drmax(.4);
  jet_cleaner1.reset(new JetCleaner( 25., std::numeric_limits<double>::infinity()));
  jet_cleaner2.reset(new JetCleaner( 30., 2.4));
  jet_cleaner3.reset(new JetCleaner( 50., 2.4));
  jet_cleaner4.reset(new JetCleaner(100., 2.4));
  jet_cleaner5.reset(new JetCleaner(200., 2.4));
  ////

  //// EVENT SELECTION
  const std::string trigger(ctx.get("trigger", "NULL"));
  if(trigger != "NULL") trigger_sel.reset(new TriggerSelection(trigger));
  else trigger_sel.reset(new AndSelection(ctx));

  const std::string channel_str(ctx.get("channel", ""));
  if(channel_str == "muon") channel = muon;
  else if(channel_str == "elec") channel = elec;
  else throw std::runtime_error("undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel_str);

  lep2_sel.reset(new AndSelection(ctx));
  if(channel == muon){
    lep2_sel->add<NMuonSelection>("muoN == 2", 2, 2);
    lep2_sel->add<NElectronSelection>("eleN == 0", 0, 0);
  }
  else if(channel == elec){
    lep2_sel->add<NMuonSelection>("muoN == 0", 0, 0);
    lep2_sel->add<NElectronSelection>("eleN == 2", 2, 2);
  }

  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut( 50., 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(200., 2.4))));
  ////

  //// HISTS
  hi_input__event.reset(new EventHists(ctx, "input__event"));
  hi_output__event.reset(new EventHists(ctx, "output__event"));
  ////

  //// TNP VARS
  h_MCweight           = ctx.declare_event_output<float> ("TnP_MCweight");
  h_pvN                = ctx.declare_event_output<int>   ("TnP_pvN");
  h_MET__pt            = ctx.declare_event_output<float> ("TnP_MET__pt");
  h_MET__phi           = ctx.declare_event_output<float> ("TnP_MET__phi");
  h_jetN__pt030_eta2p4 = ctx.declare_event_output<int>   ("TnP_jetN__pt030_eta2p4");
  h_jetN__pt050_eta2p4 = ctx.declare_event_output<int>   ("TnP_jetN__pt050_eta2p4");
  h_jetN__pt100_eta2p4 = ctx.declare_event_output<int>   ("TnP_jetN__pt100_eta2p4");
  h_jetN__pt200_eta2p4 = ctx.declare_event_output<int>   ("TnP_jetN__pt200_eta2p4");
  				
  h_ZLL__M   = ctx.declare_event_output<float> ("TnP_ZLL__M");
  h_ZLL__pt  = ctx.declare_event_output<float> ("TnP_ZLL__pt");
  h_ZLL__eta = ctx.declare_event_output<float> ("TnP_ZLL__eta");
  h_ZLL__phi = ctx.declare_event_output<float> ("TnP_ZLL__phi");
  				
  h_TAG__E                 = ctx.declare_event_output<float> ("TnP_TAG__E");
  h_TAG__pt                = ctx.declare_event_output<float> ("TnP_TAG__pt");
  h_TAG__eta               = ctx.declare_event_output<float> ("TnP_TAG__eta");
  h_TAG__etaSC             = ctx.declare_event_output<float> ("TnP_TAG__etaSC");
  h_TAG__phi               = ctx.declare_event_output<float> ("TnP_TAG__phi");
  h_TAG__charge            = ctx.declare_event_output<int>   ("TnP_TAG__charge");
  h_TAG__pfiso_dbeta       = ctx.declare_event_output<float> ("TnP_TAG__pfiso_dbeta");
  h_TAG__dRjet_pt025        = ctx.declare_event_output<float> ("TnP_TAG__dRjet_pt025");
  h_TAG__dRjet_pt030_eta2p4 = ctx.declare_event_output<float> ("TnP_TAG__dRjet_pt030_eta2p4");
  h_TAG__dRjet_pt050_eta2p4 = ctx.declare_event_output<float> ("TnP_TAG__dRjet_pt050_eta2p4");
  h_TAG__pTrel_pt025        = ctx.declare_event_output<float> ("TnP_TAG__pTrel_pt025");
  h_TAG__pTrel_pt030_eta2p4 = ctx.declare_event_output<float> ("TnP_TAG__pTrel_pt030_eta2p4");
  h_TAG__pTrel_pt050_eta2p4 = ctx.declare_event_output<float> ("TnP_TAG__pTrel_pt050_eta2p4");
  				
  h_PRO__E                 = ctx.declare_event_output<float> ("TnP_PRO__E");
  h_PRO__pt                = ctx.declare_event_output<float> ("TnP_PRO__pt");
  h_PRO__eta               = ctx.declare_event_output<float> ("TnP_PRO__eta");
  h_PRO__etaSC             = ctx.declare_event_output<float> ("TnP_PRO__etaSC");
  h_PRO__phi               = ctx.declare_event_output<float> ("TnP_PRO__phi");
  h_PRO__charge            = ctx.declare_event_output<int>   ("TnP_PRO__charge");
  h_PRO__pfiso_dbeta       = ctx.declare_event_output<float> ("TnP_PRO__pfiso_dbeta");
  h_PRO__dRjet_pt025        = ctx.declare_event_output<float> ("TnP_PRO__dRjet_pt025");
  h_PRO__dRjet_pt030_eta2p4 = ctx.declare_event_output<float> ("TnP_PRO__dRjet_pt030_eta2p4");
  h_PRO__dRjet_pt050_eta2p4 = ctx.declare_event_output<float> ("TnP_PRO__dRjet_pt050_eta2p4");
  h_PRO__pTrel_pt025        = ctx.declare_event_output<float> ("TnP_PRO__pTrel_pt025");
  h_PRO__pTrel_pt030_eta2p4 = ctx.declare_event_output<float> ("TnP_PRO__pTrel_pt030_eta2p4");
  h_PRO__pTrel_pt050_eta2p4 = ctx.declare_event_output<float> ("TnP_PRO__pTrel_pt050_eta2p4");
  ////
}

bool TagNProbeZLLModule::process(Event & event){

  hi_input__event->fill(event);

  //// HLT selection
  bool pass_trigger = trigger_sel->passes(event);
  if(!pass_trigger) return false;
  ////

  //// LEPTON selection
  muo_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  ele_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  bool pass_lep2 = lep2_sel->passes(event);
  if(!pass_lep2) return false;
  ////

  //// JET selection
  jet_corrector->process(event);
  jetER_smearer->process(event);
  jetlepton_cleaner->process(event);

  /* 2nd AK4 jet selection */
  bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;

  /* 1st AK4 jet selection */
  bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  ////

  hi_output__event->fill(event);

  /* TAG and PROBE assignment */
  const Particle *tag(0), *pro(0);

  jet_cleaner1->process(event);
  sort_by_pt<Jet>(*event.jets);

  if(channel == muon){

    if(event.muons->size() != 2) 
      std::runtime_error("logical error: incorrect number of muons (!=2)");

    for(const auto& muo : *event.muons){

      float dRjet_pt025(0.), pTrel_pt025(0.);
      std::tie(dRjet_pt025, pTrel_pt025) = drmin_pTrel(muo, *event.jets);

      if(dRjet_pt025 > .4 && muo.relIso() < .1){ tag = &muo; break; }
    }

    if(!tag) return false;

    pro = (tag == &event.muons->at(0)) ? &event.muons->at(1) : &event.muons->at(0);
  }
  else if(channel == elec){

    if(event.electrons->size() != 2) 
      std::runtime_error("logical error: incorrect number of electrons (!=2)");

    for(const auto& ele : *event.electrons){

      float dRjet_pt025(0.), pTrel_pt025(0.);
      std::tie(dRjet_pt025, pTrel_pt025) = drmin_pTrel(ele, *event.jets);

      if(dRjet_pt025 > .4 && ele.relIsodb() < .1){ tag = &ele; break; }
    }

    if(!tag) return false;

    pro = (tag == &event.electrons->at(0)) ? &event.electrons->at(1) : &event.electrons->at(0);
  }

  /* add TnP vars to output ntuple */

  // global vars
  event.set(h_MCweight, event.weight);
  event.set(h_pvN     , event.pvs->size());
  event.set(h_MET__pt , event.met->pt());
  event.set(h_MET__phi, event.met->phi());
  //

  float tag__dRjet_pt025(0.), tag__dRjet_pt030_eta2p4(0.), tag__dRjet_pt050_eta2p4(0.);
  float tag__pTrel_pt025(0.), tag__pTrel_pt030_eta2p4(0.), tag__pTrel_pt050_eta2p4(0.);

  float pro__dRjet_pt025(0.), pro__dRjet_pt030_eta2p4(0.), pro__dRjet_pt050_eta2p4(0.);
  float pro__pTrel_pt025(0.), pro__pTrel_pt030_eta2p4(0.), pro__pTrel_pt050_eta2p4(0.);

  std::tie(tag__dRjet_pt025, tag__pTrel_pt025) = drmin_pTrel(*tag, *event.jets);
  std::tie(pro__dRjet_pt025, pro__pTrel_pt025) = drmin_pTrel(*pro, *event.jets);
  //

  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt030_eta2p4, event.jets->size());

  std::tie(tag__dRjet_pt030_eta2p4, tag__pTrel_pt030_eta2p4) = drmin_pTrel(*tag, *event.jets);
  std::tie(pro__dRjet_pt030_eta2p4, pro__pTrel_pt030_eta2p4) = drmin_pTrel(*pro, *event.jets);
  //

  jet_cleaner3->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt050_eta2p4, event.jets->size());

  std::tie(tag__dRjet_pt050_eta2p4, tag__pTrel_pt050_eta2p4) = drmin_pTrel(*tag, *event.jets);
  std::tie(pro__dRjet_pt050_eta2p4, pro__pTrel_pt050_eta2p4) = drmin_pTrel(*pro, *event.jets);
  //

  jet_cleaner4->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt100_eta2p4, event.jets->size());
  //

  jet_cleaner5->process(event);
  sort_by_pt<Jet>(*event.jets);
  event.set(h_jetN__pt200_eta2p4, event.jets->size());
  //

  float tag__etaSC(0.), tag__pfiso_dbeta(0.);
  float pro__etaSC(0.), pro__pfiso_dbeta(0.);

  if(channel == muon){
    tag__pfiso_dbeta = ((Muon*) tag)->relIso();
    pro__pfiso_dbeta = ((Muon*) pro)->relIso();
  }
  else if(channel == elec){
    tag__pfiso_dbeta = ((Electron*) tag)->relIsodb();
    pro__pfiso_dbeta = ((Electron*) pro)->relIsodb();

    tag__etaSC = ((Electron*) tag)->supercluster_eta();
    pro__etaSC = ((Electron*) pro)->supercluster_eta();
  }

  /* ZLL */
  event.set(h_ZLL__M  , (tag->v4()+pro->v4()).M());
  event.set(h_ZLL__pt , (tag->v4()+pro->v4()).Pt());
  event.set(h_ZLL__eta, (tag->v4()+pro->v4()).Eta());
  event.set(h_ZLL__phi, (tag->v4()+pro->v4()).Phi());

  /* TAG */
  event.set(h_TAG__E                , tag->v4().E());
  event.set(h_TAG__pt               , tag->v4().Pt());
  event.set(h_TAG__eta              , tag->v4().Eta());
  event.set(h_TAG__etaSC            , tag__etaSC);
  event.set(h_TAG__phi              , tag->v4().Phi());
  event.set(h_TAG__charge           , int(tag->charge()));
  event.set(h_TAG__pfiso_dbeta      , tag__pfiso_dbeta);
  event.set(h_TAG__dRjet_pt025       , tag__dRjet_pt025);
  event.set(h_TAG__dRjet_pt030_eta2p4, tag__dRjet_pt030_eta2p4);
  event.set(h_TAG__dRjet_pt050_eta2p4, tag__dRjet_pt050_eta2p4);
  event.set(h_TAG__pTrel_pt025       , tag__pTrel_pt025);
  event.set(h_TAG__pTrel_pt030_eta2p4, tag__pTrel_pt030_eta2p4);
  event.set(h_TAG__pTrel_pt050_eta2p4, tag__pTrel_pt050_eta2p4);

  /* PROBE */
  event.set(h_PRO__E                , pro->v4().E());
  event.set(h_PRO__pt               , pro->v4().Pt());
  event.set(h_PRO__eta              , pro->v4().Eta());
  event.set(h_PRO__etaSC            , pro__etaSC);
  event.set(h_PRO__phi              , pro->v4().Phi());
  event.set(h_PRO__charge           , int(pro->charge()));
  event.set(h_PRO__pfiso_dbeta      , pro__pfiso_dbeta);
  event.set(h_PRO__dRjet_pt025       , pro__dRjet_pt025);
  event.set(h_PRO__dRjet_pt030_eta2p4, pro__dRjet_pt030_eta2p4);
  event.set(h_PRO__dRjet_pt050_eta2p4, pro__dRjet_pt050_eta2p4);
  event.set(h_PRO__pTrel_pt025       , pro__pTrel_pt025);
  event.set(h_PRO__pTrel_pt030_eta2p4, pro__pTrel_pt030_eta2p4);
  event.set(h_PRO__pTrel_pt050_eta2p4, pro__pTrel_pt050_eta2p4);
  ///

  // clear default output collections (reduce output size)
  if(event.pvs) event.pvs->clear();	      
  if(event.electrons) event.electrons->clear();   
  if(event.muons) event.muons->clear();	      
  if(event.taus) event.taus->clear();	      
  if(event.photons) event.photons->clear();     
  if(event.jets) event.jets->clear();	      
  if(event.topjets) event.topjets->clear();     
  if(event.gentopjets) event.gentopjets->clear();  
  if(event.genparticles) event.genparticles->clear();
  if(event.genjets) event.genjets->clear();

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TagNProbeZLLModule)
