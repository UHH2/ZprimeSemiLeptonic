#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"
#include "UHH2/core/include/Event.h"
#include <UHH2/core/include/Utils.h>
#include <UHH2/common/include/Utils.h>
#include "UHH2/common/include/JetIds.h"
#include <math.h>

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include "TH1F.h"
#include "TH2D.h"
#include <iostream>

using namespace std;
using namespace uhh2;

ZprimeSemiLeptonicGeneratorHists::ZprimeSemiLeptonicGeneratorHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {


  is_mc = ctx.get("dataset_type") == "MC";
  init();
}

void ZprimeSemiLeptonicGeneratorHists::init(){


  M_Zprime                 = book<TH1F>("M_Zprime", "M_{Z'}}^{gen} [GeV]", 280, 0, 7000);
  M_Zprime_rebin           = book<TH1F>("M_Zprime_rebin", "M_{Z'}^{gen} [GeV]", 140, 0, 7000);
  M_Zprime_rebin2          = book<TH1F>("M_Zprime_rebin2", "M_{Z'}^{gen} [GeV]", 70, 0, 7000);
  M_Zprime_rebin3          = book<TH1F>("M_Zprime_rebin3", "M_{Z'}^{gen} [GeV]", 35, 0, 7000);
  M_ttbar                  = book<TH1F>("M_ttbar", "M_{t#bar{t}}^{gen} [GeV]", 280, 0, 7000);
  M_ttbar_rebin            = book<TH1F>("M_ttbar_rebin", "M_{t#bar{t}}^{gen} [GeV]", 140, 0, 7000);
  M_ttbar_rebin2           = book<TH1F>("M_ttbar_rebin2", "M_{t#bar{t}}^{gen} [GeV]", 70, 0, 7000);
  M_ttbar_rebin3           = book<TH1F>("M_ttbar_rebin3", "M_{t#bar{t}}^{gen} [GeV]", 35, 0, 7000);
  M_top                    = book<TH1F>("M_top", "M_{t}^{gen} [GeV]", 30, 0, 300);
  M_antitop                = book<TH1F>("M_antitop", "M_{#bar{t}}^{gen} [GeV]", 30, 0, 300);
  Pt_ttbar                 = book<TH1F>("Pt_ttbar", "p_{T}^{t#bar{t}, gen} [GeV]", 100, 0, 1000);
  Pt_Zprime                = book<TH1F>("Pt_Zprime", "p_{T}^{Z', gen} [GeV]", 100, 0, 1000);
  Pt_top                   = book<TH1F>("Pt_top", "p_{T}^{t, gen} [GeV]", 300, 0, 3000);
  Pt_antitop               = book<TH1F>("Pt_antitop", "p_{T}^{#bar{t}, gen} [GeV]", 300, 0, 3000);

}


void ZprimeSemiLeptonicGeneratorHists::fill(const Event & event){

  if(!is_mc) return;
  assert(event.genparticles);

  double weight = event.weight;

  // Find signal, top, and antitop
  GenParticle zprime, top, antitop;
  bool found_zprime = false, found_top = false, found_antitop = false;
  for(const GenParticle & gp : *event.genparticles){
    if(gp.pdgId() == 6){
      top = gp;
      found_top = true;
    }
    else if(gp.pdgId() == -6){
      antitop = gp;
      found_antitop = true;
    }
    else if(gp.pdgId() == 5100021){
      zprime = gp;
      found_zprime = true;
    }
  }

  if(!found_top || !found_antitop) return;
  if(found_zprime){
    float m_zprime = inv_mass(zprime.v4());
    M_Zprime->Fill(m_zprime, weight);
    M_Zprime_rebin->Fill(m_zprime, weight);
    M_Zprime_rebin2->Fill(m_zprime, weight);
    M_Zprime_rebin3->Fill(m_zprime, weight);
    Pt_Zprime->Fill(zprime.pt());
  }
  float m_ttbar = inv_mass(top.v4() + antitop.v4());
  M_ttbar->Fill(m_ttbar, weight);
  M_ttbar_rebin->Fill(m_ttbar, weight);
  M_ttbar_rebin2->Fill(m_ttbar, weight);
  M_ttbar_rebin3->Fill(m_ttbar, weight);
  M_top->Fill(inv_mass(top.v4()), weight);
  M_antitop->Fill(inv_mass(antitop.v4()), weight);
  Pt_ttbar->Fill((top.v4() + antitop.v4()).Pt());
  Pt_top->Fill(top.pt(), weight);
  Pt_antitop->Fill(antitop.pt(), weight);


}


ZprimeSemiLeptonicGeneratorHists::~ZprimeSemiLeptonicGeneratorHists(){}
