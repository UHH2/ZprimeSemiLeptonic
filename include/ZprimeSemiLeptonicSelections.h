#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/ReconstructionHypothesisDiscriminators.h"

namespace uhh2 {
    
  class HTlepCut : public Selection {
   public:
    explicit HTlepCut(float min_htlep, float max_htlep=infinity);
    virtual bool passes(const Event &);

   private:
    Event::Handle<double> h_htlep_;
    float min_htlep_, max_htlep_;
  };

  class METCut : public Selection {
   public:
    explicit METCut(float min_met, float max_met=infinity);
    virtual bool passes(const Event & event) override;

   private:
    float min_met_, max_met_;
  };

  class NJetCut : public Selection {
   public:
    explicit NJetCut(int nmin, int nmax=-1, float ptmin=0., float etamax=infinity);
    virtual bool passes(const Event & event) override;

   private:
    int nmin, nmax;
    float ptmin, etamax;
  };

  class TwoDCut : public Selection {
   public:
    TwoDCut() {}
    virtual bool passes(const Event & event) override;
  };

  class TopJetOverlapSelection: public Selection {
   public:
    explicit TopJetOverlapSelection(float delR_Lep_TopJet=0.8 , float delR_Jet_TopJet=1.2);
    virtual bool passes(const Event & event) override;

   private:
    float delR_Lep_TopJet, delR_Jet_TopJet;
    std::unique_ptr<Selection> ntopjet_sel;
    TopJetId topjetid;
  };

  class HypothesisDiscriminatorCut: public Selection {
   public:
    explicit HypothesisDiscriminatorCut(Context& ctx, float min_discr, float max_discr, const std::string& discr_name="Chi2", const std::string& hyps_name="HighMassReconstruction");
    virtual bool passes(const Event & event);

   private:
    float m_min_discr_, m_max_discr_;
    std::string m_discriminator_name;
    uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps;
  };

}
