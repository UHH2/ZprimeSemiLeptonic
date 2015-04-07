#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimePostSelectionHists.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/TTbarReconstruction.h"
#include "UHH2/common/include/ReconstructionHypothesisDiscriminators.h"
#include "UHH2/common/include/HypothesisHists.h"
#include <UHH2/core/include/Utils.h>

using namespace uhh2;

class ZprimePostSelectionModule: public AnalysisModule {
 public:
  explicit ZprimePostSelectionModule(Context&);
  virtual bool process(Event&) override;

 private:
  std::unique_ptr<AnalysisModule> ttgenprod;
  Event::Handle<TTbarGen> h_ttbargen;

  Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;

  JetId btagAK4_wp;
  Event::Handle<int> h_flag_toptagevent;

  // selections
  std::unique_ptr<Selection> btagAK4_sel;
  std::unique_ptr<Selection> leptoppt_sel;
  std::unique_ptr<Selection> chi2_sel;

  // hists
  std::unique_ptr<Hists> hi_input;
  std::unique_ptr<Hists> hi_input__hyp;
  std::unique_ptr<Hists> hi_leptoppt;
  std::unique_ptr<Hists> hi_leptoppt__hyp;
  std::unique_ptr<Hists> hi_chi2;
  std::unique_ptr<Hists> hi_chi2__hyp;
  std::unique_ptr<Hists> hi_t0b0;
  std::unique_ptr<Hists> hi_t0b0__hyp;
  std::unique_ptr<Hists> hi_t0b1;
  std::unique_ptr<Hists> hi_t0b1__hyp;
  std::unique_ptr<Hists> hi_t1;
  std::unique_ptr<Hists> hi_t1__hyp;
};

ZprimePostSelectionModule::ZprimePostSelectionModule(Context& ctx){

  bool muon(false), elec(false);
  const std::string channel(ctx.get("channel", ""));
  if(channel == "muon") muon = true;
  else if(channel == "electron") elec = true;
  else throw std::runtime_error("undefined argument for 'channel' key in xml file (must be 'muon' or 'electron'): "+channel);

  // ttbar GEN
  ttgenprod.reset(new TTbarGenProducer(ctx, "ttbargen", false));
  h_ttbargen = ctx.get_handle<TTbarGen>("ttbargen");

  // ttbar RECO hypotheses
  h_ttbar_hyps = ctx.declare_event_input<std::vector<ReconstructionHypothesis>>("TTbarReconstruction");

  // b-tagging
  btagAK4_wp = CSVBTag(CSVBTag::WP_MEDIUM);
  btagAK4_sel.reset(new NJetSelection(1, -1, btagAK4_wp));

  // top-tagging flag (from ZprimeSelection ntuple)
  h_flag_toptagevent = ctx.declare_event_input<int>("flag_toptagevent");

  // SELECTION
  if(elec) leptoppt_sel.reset(new LeptonicTopPtCut(ctx, 140., infinity, "TTbarReconstruction", "Chi2"));
  else if(muon) leptoppt_sel.reset(new AndSelection(ctx));

  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx, 0., 50., "TTbarReconstruction", "Chi2"));

  // HISTS
  hi_input.reset(new ZprimePostSelectionHists(ctx, "input"));
  hi_input__hyp.reset(new HypothesisHists(ctx, "input__hyp_chi2min", "TTbarReconstruction", "Chi2"));

  hi_leptoppt.reset(new ZprimePostSelectionHists(ctx, "leptoppt"));
  hi_leptoppt__hyp.reset(new HypothesisHists(ctx, "leptoppt__hyp_chi2min", "TTbarReconstruction", "Chi2"));

  hi_chi2.reset(new ZprimePostSelectionHists(ctx, "chi2"));
  hi_chi2__hyp.reset(new HypothesisHists(ctx, "chi2__hyp_chi2min", "TTbarReconstruction", "Chi2"));

  hi_t0b0.reset(new ZprimePostSelectionHists(ctx, "t0b0"));
  hi_t0b0__hyp.reset(new HypothesisHists(ctx, "t0b0__hyp_chi2min", "TTbarReconstruction", "Chi2"));

  hi_t0b1.reset(new ZprimePostSelectionHists(ctx, "t0b1"));
  hi_t0b1__hyp.reset(new HypothesisHists(ctx, "t0b1__hyp_chi2min", "TTbarReconstruction", "Chi2"));

  hi_t1.reset(new ZprimePostSelectionHists(ctx, "t1"));
  hi_t1__hyp.reset(new HypothesisHists(ctx, "t1__hyp_chi2min", "TTbarReconstruction", "Chi2"));
}

bool ZprimePostSelectionModule::process(Event& event) {

  hi_input->fill(event);
  hi_input__hyp->fill(event);

  //// LEPTONIC-TOP pt selection
  bool pass_leptoppt = leptoppt_sel->passes(event);
  if(!pass_leptoppt) return false;
  hi_leptoppt->fill(event);
  hi_leptoppt__hyp->fill(event);
  ////

  //// CHI2 selection
  bool pass_chi2 = chi2_sel->passes(event);
  if(!pass_chi2) return false;
  hi_chi2->fill(event);
  hi_chi2__hyp->fill(event);
  ////

  bool btag(btagAK4_sel->passes(event));
  bool toptag(event.get(h_flag_toptagevent));

  if(!toptag){

    if(!btag){

      hi_t0b0->fill(event);
      hi_t0b0__hyp->fill(event);
    }
    else {

      hi_t0b0->fill(event);
      hi_t0b1__hyp->fill(event);
    }
  }
  else {

    hi_t1->fill(event);
    hi_t1__hyp->fill(event);
  }

  return false;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimePostSelectionModule)
