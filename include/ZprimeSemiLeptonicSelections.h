#pragma once

#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/ReconstructionHypothesis.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/TopJetIds.h"

#include <string>
#include <vector>

namespace uhh2 {
    
  class HTlepCut : public Selection {
   public:
    explicit HTlepCut(float, float max_htlep=infinity);
    virtual bool passes(const Event&) override;

   private:
    float min_htlep_, max_htlep_;
  };
  /////

  class METCut : public Selection {
   public:
    explicit METCut(float, float max_met=infinity);
    virtual bool passes(const Event&) override;

   private:
    float min_met_, max_met_;
  };
  /////

  class NJetCut : public Selection {
   public:
    explicit NJetCut(int, int nmax=999, float ptmin=0., float etamax=infinity);
    virtual bool passes(const Event&) override;

   private:
    int nmin, nmax;
    float ptmin, etamax;
  };
  /////

  class TwoDCut : public Selection {
   public:
    explicit TwoDCut(float min_deltaR, float min_pTrel): min_deltaR_(min_deltaR), min_pTrel_(min_pTrel) {}
    virtual bool passes(const Event&) override;

   private:
    float min_deltaR_, min_pTrel_;
  };
  /////

  class TwoDCut1 : public Selection {
   public:
    explicit TwoDCut1(float min_deltaR, float min_pTrel): min_deltaR_(min_deltaR), min_pTrel_(min_pTrel) {}
    virtual bool passes(const Event&) override;

   private:
    float min_deltaR_, min_pTrel_;
  };
  /////

  class TwoDCutALL : public Selection {
   public:
    explicit TwoDCutALL(float min_deltaR, float min_pTrel): min_deltaR_(min_deltaR), min_pTrel_(min_pTrel) {}
    virtual bool passes(const Event&) override;

   private:
    float min_deltaR_, min_pTrel_;
  };
  /////

  class TriangularCuts : public Selection {
   public:
    explicit TriangularCuts(float, float);
    virtual bool passes(const Event&) override;

   private:
    float a_, b_;
  };
  /////

  class TriangularCutsELE : public Selection {
   public:
    explicit TriangularCutsELE(float, float);
    virtual bool passes(const Event&) override;

   private:
    float a_, b_;
  };
  /////

  class DiLeptonSelection: public Selection {
   public:
    explicit DiLeptonSelection(const std::string&, const bool, const bool);
    virtual bool passes(const Event&) override;

   private:
    std::string channel_;
    bool opposite_charge_;
    bool veto_other_flavor_;
  };
  /////

  class TopTagEventSelection: public Selection {
   public:
    explicit TopTagEventSelection(const TopJetId& tjet_id=CMSTopTag(), float minDR_jet_ttag=1.2);
    virtual bool passes(const Event&) override;

   private:
    TopJetId topjetID_;
    std::unique_ptr<Selection> topjet1_sel_;
    float minDR_jet_toptag_;
  };
  /////

  class LeptonicTopPtCut: public Selection {
   public:
    explicit LeptonicTopPtCut(Context&, float, float, const std::string& hyps="TTbarReconstruction", const std::string& disc="Chi2");
    virtual bool passes(const Event&) override;

   private:
    float tlep_pt_min_, tlep_pt_max_;
    Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps_;
    std::string disc_name_;
  };
  /////

  class HypothesisDiscriminatorCut: public Selection {
   public:
    explicit HypothesisDiscriminatorCut(Context&, float, float, const std::string& hyps="TTbarReconstruction", const std::string& disc_bhyp="Chi2", const std::string& disc_cut="Chi2");
    virtual bool passes(const Event&) override;

   private:
    float disc_min_, disc_max_;
    Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps_;
    std::string disc_bhyp_;
    std::string disc_cut_;
  };
  /////

}
