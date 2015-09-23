#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>
#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/HypothesisHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimePostSelectionHists.h>

/** \brief module to produce "PostSelection" output for the Z'->ttbar semileptonic analysis
 *
 * -- ITEMS TO BE IMPLEMENTED:
 *   * systematic uncertainties
 *
 */
class ZprimePostSelectionModule : public uhh2::AnalysisModule {

 public:
  explicit ZprimePostSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 private:
  enum lepton { muon, elec };
  lepton channel_;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;

  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;

  uhh2::Event::Handle<int> h_flag_toptagevent;

  // selections
  std::unique_ptr<uhh2::Selection> btagAK4_sel;
  std::unique_ptr<uhh2::Selection> topleppt_sel;
  std::unique_ptr<uhh2::Selection> chi2_sel;

  // hists
  std::unique_ptr<uhh2::Hists> hi_input;
  std::unique_ptr<uhh2::Hists> hi_input__hyp;
  std::unique_ptr<uhh2::Hists> hi_topleppt;
  std::unique_ptr<uhh2::Hists> hi_topleppt__hyp;
  std::unique_ptr<uhh2::Hists> hi_chi2;
  std::unique_ptr<uhh2::Hists> hi_chi2__hyp;
  std::unique_ptr<uhh2::Hists> hi_t0b0;
  std::unique_ptr<uhh2::Hists> hi_t0b0__hyp;
  std::unique_ptr<uhh2::Hists> hi_t0b1;
  std::unique_ptr<uhh2::Hists> hi_t0b1__hyp;
  std::unique_ptr<uhh2::Hists> hi_t1;
  std::unique_ptr<uhh2::Hists> hi_t1__hyp;

  bool fix_NLO_wgt_;
};

ZprimePostSelectionModule::ZprimePostSelectionModule(uhh2::Context& ctx){

  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else throw std::runtime_error("ZprimePostSelectionModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);

  // TTBAR RECO
  const std::string ttbar_gen_label ("ttbargen");
  const std::string ttbar_hyps_label("TTbarReconstruction");
  const std::string ttbar_chi2_label("Chi2");

  /* GEN */
  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));
  h_ttbargen = ctx.get_handle<TTbarGen>(ttbar_gen_label);

  /* RECO */
  h_ttbar_hyps = ctx.declare_event_input<std::vector<ReconstructionHypothesis>>(ttbar_hyps_label);
  //

  // b-tagging
  btagAK4_sel.reset(new NJetSelection(1, -1, JetId(CSVBTag(CSVBTag::WP_MEDIUM))));

  // top-tagging flag (from ZprimeSelection ntuple)
  h_flag_toptagevent = ctx.declare_event_input<int>("flag_toptagevent");

  // SELECTION
  if     (channel_ == elec) topleppt_sel.reset(new LeptonicTopPtCut(ctx, 140., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label));
  else if(channel_ == muon) topleppt_sel.reset(new uhh2::AndSelection(ctx));

  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx, 0., 50., ttbar_hyps_label, ttbar_chi2_label));

  // HISTS
  hi_input.reset(new ZprimePostSelectionHists(ctx, "input"));
  hi_input__hyp.reset(new HypothesisHists    (ctx, "input__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_topleppt.reset(new ZprimePostSelectionHists(ctx, "topleppt"));
  hi_topleppt__hyp.reset(new HypothesisHists    (ctx, "topleppt__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_chi2.reset(new ZprimePostSelectionHists(ctx, "chi2"));
  hi_chi2__hyp.reset(new HypothesisHists    (ctx, "chi2__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_t0b0.reset(new ZprimePostSelectionHists(ctx, "t0b0"));
  hi_t0b0__hyp.reset(new HypothesisHists    (ctx, "t0b0__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_t0b1.reset(new ZprimePostSelectionHists(ctx, "t0b1"));
  hi_t0b1__hyp.reset(new HypothesisHists    (ctx, "t0b1__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_t1.reset(new ZprimePostSelectionHists(ctx, "t1"));
  hi_t1__hyp.reset(new HypothesisHists    (ctx, "t1__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));
  ///

  // fix for NLO weight
  fix_NLO_wgt_ = false;
  fix_NLO_wgt_ |= (ctx.get("dataset_version") == "WJets");
  fix_NLO_wgt_ |= (ctx.get("dataset_version") == "ZJets");
}

bool ZprimePostSelectionModule::process(uhh2::Event& event){

  if(fix_NLO_wgt_){

    if(!event.genInfo) throw std::runtime_error("ZprimePostSelectionModule::process -- error in fixing NLO weight: failed to access Event::genInfo (null pointer)");

    if(event.genInfo->weights().size() != 1) throw std::runtime_error("ZprimePostSelectionModule::process -- error in fixing NLO weight: genInfo->weights().size() != 1");
    event.weight /= fabs(event.genInfo->weights().at(0));
  }

  hi_input->fill(event);
  hi_input__hyp->fill(event);

  //// LEPTONIC-TOP pt selection
  bool pass_topleppt = topleppt_sel->passes(event);
  if(!pass_topleppt) return false;
  hi_topleppt->fill(event);
  hi_topleppt__hyp->fill(event);
  ////

  //// CHI2 selection
  bool pass_chi2 = chi2_sel->passes(event);
  if(!pass_chi2) return false;
  hi_chi2->fill(event);
  hi_chi2__hyp->fill(event);
  ////

  const bool btag(btagAK4_sel->passes(event));
  const bool toptag(event.get(h_flag_toptagevent));

  if(!toptag){

    if(!btag){

      hi_t0b0->fill(event);
      hi_t0b0__hyp->fill(event);
    }
    else {

      hi_t0b1->fill(event);
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
