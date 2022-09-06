#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicEleHists.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"
#include "UHH2/core/include/Event.h"
#include <UHH2/core/include/Utils.h>
#include <UHH2/common/include/Utils.h>
#include "UHH2/common/include/JetIds.h"
#include <math.h>

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <UHH2/core/include/LorentzVector.h>

#include "TH1F.h"
#include "TH2D.h"
#include <iostream>

using namespace std;
using namespace uhh2;

ZprimeSemiLeptonicEleHists::ZprimeSemiLeptonicEleHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {
  init();
}

void ZprimeSemiLeptonicEleHists::init(){

  // leptons
  N_ele             = book<TH1F>("N_ele", "N^{e}", 11, -0.5, 10.5);
  pt_ele            = book<TH1F>("pt_ele", "p_{T}^{e} [GeV]", 90, 0, 900);
  eta_ele           = book<TH1F>("eta_ele", "#eta^{e}", 50, -2.5, 2.5);
  phi_ele           = book<TH1F>("phi_ele", "#phi^{e}", 35, -3.5, 3.5);
  pt_ele_lowpt      = book<TH1F>("pt_ele_lowpt", "p_{T}^{e} [GeV] p_{T}<120 GeV", 180, 0, 900);
  pt_ele_midpt      = book<TH1F>("pt_ele_midpt", "p_{T}^{e} [GeV] 120<p_{T}<200 GeV", 180, 0, 900);
  pt_ele_highpt     = book<TH1F>("pt_ele_highpt", "p_{T}^{e} [GeV] p_{T}>200 GeV", 180, 0, 900);
  eta_ele_lowpt     = book<TH1F>("eta_ele_lowpt", "#eta^{e} p_{T}<120 GeV", 50, -2.5, 2.5);
  eta_ele_midpt     = book<TH1F>("eta_ele_midpt", "#eta^{e} 120<p_{T}<200 GeV", 50, -2.5, 2.5);
  eta_ele_highpt    = book<TH1F>("eta_ele_highpt", "#eta^{e} p_{T}>200 GeV", 50, -2.5, 2.5);
  phi_ele_lowpt     = book<TH1F>("phi_ele_lowpt", "#phi^{e} p_{T}<120 GeV", 35, -3.5, 3.5);
  phi_ele_midpt     = book<TH1F>("phi_ele_midpt", "#phi^{e} 120<p_{T}<200 GeV", 35, -3.5, 3.5);
  phi_ele_highpt    = book<TH1F>("phi_ele_highpt", "#phi^{e} p_{T}>200 GeV", 35, -3.5, 3.5);

}


void ZprimeSemiLeptonicEleHists::fill(const Event & event){

  double weight = event.weight;


  /*
  ███████ ██      ███████  ██████ ████████ ██████   ██████  ███    ██ ███████
  ██      ██      ██      ██         ██    ██   ██ ██    ██ ████   ██ ██
  █████   ██      █████   ██         ██    ██████  ██    ██ ██ ██  ██ ███████
  ██      ██      ██      ██         ██    ██   ██ ██    ██ ██  ██ ██      ██
  ███████ ███████ ███████  ██████    ██    ██   ██  ██████  ██   ████ ███████
  */


  vector<Electron>* electrons = event.electrons;
  int Nelectrons = electrons->size();
  N_ele->Fill(Nelectrons, weight);

  for(int i=0; i<Nelectrons; i++){
    pt_ele->Fill(electrons->at(i).pt(),weight);
    eta_ele->Fill(electrons->at(i).eta(),weight);
    phi_ele->Fill(electrons->at(i).phi(),weight);
    if(electrons->at(i).pt()<120){
      pt_ele_lowpt->Fill(electrons->at(i).pt(),weight);
      eta_ele_lowpt->Fill(electrons->at(i).eta(),weight);
      phi_ele_lowpt->Fill(electrons->at(i).phi(),weight);
    }
    if(electrons->at(i).pt()>=120 && electrons->at(i).pt()<200){
      pt_ele_midpt->Fill(electrons->at(i).pt(),weight);
      eta_ele_midpt->Fill(electrons->at(i).eta(),weight);
      phi_ele_midpt->Fill(electrons->at(i).phi(),weight);
    }
    if(electrons->at(i).pt()>=200){
      pt_ele_highpt->Fill(electrons->at(i).pt(),weight);
      eta_ele_highpt->Fill(electrons->at(i).eta(),weight);
      phi_ele_highpt->Fill(electrons->at(i).phi(),weight);      
    }

  }


} //Method


ZprimeSemiLeptonicEleHists::~ZprimeSemiLeptonicEleHists(){}
