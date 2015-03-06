#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/ReconstructionHypothesisDiscriminators.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/TopJetIds.h"

namespace uhh2 {
    
  class HTlepCut : public Selection {
   public:
    explicit HTlepCut(float min_htlep, float max_htlep=infinity);
    virtual bool passes(const Event &) override;

   private:
    float min_htlep_, max_htlep_;
  };
  /////

  class METCut : public Selection {
   public:
    explicit METCut(float min_met, float max_met=infinity);
    virtual bool passes(const Event & event) override;

   private:
    float min_met_, max_met_;
  };
  /////

  class NJetCut : public Selection {
   public:
    explicit NJetCut(int nmin, int nmax=999, float ptmin=0., float etamax=infinity);
    virtual bool passes(const Event & event) override;

   private:
    int nmin, nmax;
    float ptmin, etamax;
  };
  /////

  class TwoDCut : public Selection {
   public:
    explicit TwoDCut(float min_deltaR, float min_pTrel): min_deltaR_(min_deltaR), min_pTrel_(min_pTrel) {}
    virtual bool passes(const Event & event) override;

   private:
    float min_deltaR_, min_pTrel_;
  };
  /////

  class TriangularCuts : public Selection {
   public:
    explicit TriangularCuts(float a, float b);
    virtual bool passes(const Event & event) override;

   private:
    float a_, b_;
  };
  /////

  class TopTagEventSelection: public Selection {
   public:
    explicit TopTagEventSelection(const TopJetId& tjet_id=CMSTopTag(), float minDR_jet_ttag=1.2);
    virtual bool passes(const Event & event) override;

   private:
    TopJetId topjetID_;
    std::unique_ptr<Selection> topjet1_sel_;
    float minDR_jet_toptag_;
  };
  /////

  class HypothesisDiscriminatorCut: public Selection {
   public:
    explicit HypothesisDiscriminatorCut(Context& ctx, float min_discr, float max_discr, const std::string& discr_name="Chi2", const std::string& hyps_name="HighMassReconstruction");
    virtual bool passes(const Event & event) override;

   private:
    float m_min_discr_, m_max_discr_;
    std::string m_discriminator_name;
    uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps;
  };
  /////

}
