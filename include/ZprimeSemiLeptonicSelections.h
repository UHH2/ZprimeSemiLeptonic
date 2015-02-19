#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/ReconstructionHypothesisDiscriminators.h"

namespace uhh2 {
    
/* Select events with at least two jets in which the leading two jets have deltaphi > 2.7 and the third jet pt is
 * below 20% of the average of the leading two jets, where the minimum deltaphi and
 * maximum third jet pt fraction can be changed in the constructor.
 * The jets are assumed to be sorted in pt.
 */

  class DijetSelection: public uhh2::Selection {
  public:
    DijetSelection(float dphi_min = 2.7f, float third_frac_max = 0.2f);
    virtual bool passes(const uhh2::Event & event) override;
  private:
    float dphi_min, third_frac_max;
  };

class HTlepCut: public Selection {
public:
  explicit HTlepCut(Context & ctx, float min_htlep, float max_htlep = -1.);
  virtual bool passes(const Event &);

private:
  Event::Handle<double> h_htlep_;
  float min_htlep_, max_htlep_;
};



class METCut: public Selection {
public:
  explicit METCut(double min_met=0., double max_met=-1);
  virtual bool passes(const Event & event) override;

private:
  double min_met, max_met;
  };


class NJetCut: public Selection {
public:
  /// In case nmax=-1, no cut on the maximum is applied.
  explicit NJetCut(int nmin, int nmax = -1, double ptmin=0., double etamax = -1);
  virtual bool passes(const Event & event) override;
private:
  int nmin, nmax;
  double ptmin, etamax;
};
    
class TwoDCut: public Selection {
public:
  TwoDCut() {};
  ~TwoDCut() {};
  virtual bool passes(const Event & event) override;
};
  


class CMSTopTagOverlapSelection: public Selection {
 public:
  explicit CMSTopTagOverlapSelection(double delR_Lep_TopTag = 0.8 , double delR_Jet_TopTag = 1.3);
  virtual bool passes(const Event & event) override;

 private:
  double delR_Lep_TopTag;
  double delR_Jet_TopTag;
  std::unique_ptr<Selection> ntopjet_sel;
  TopJetId topjetid;
};









class HypothesisDiscriminatorCut: public Selection {
public:
    explicit HypothesisDiscriminatorCut(Context & ctx, double min_discr, double max_discr, const std::string & discriminator_name = "Chi2", const std::string & hyps_name = "HighMassReconstruction");
    virtual bool passes(const Event & event);

private:
    double m_min_discr_;
    double m_max_discr_;
    std::string m_discriminator_name;
    uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps;
    



};



































}
