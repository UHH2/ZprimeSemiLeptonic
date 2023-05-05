#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicMistagHists.h"
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

ZprimeSemiLeptonicMistagHists::ZprimeSemiLeptonicMistagHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {

  is_mc = ctx.get("dataset_type") == "MC";
  ishotvr = (ctx.get("is_hotvr") == "true");
  isdeepAK8 = (ctx.get("is_deepAK8") == "true");
  if(isdeepAK8){
    h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("DeepAK8TopTags");
  }else if(ishotvr){
    h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("HOTVRTopTags");
  }
  init();
}

void ZprimeSemiLeptonicMistagHists::init(){

  // AK8 PUPPI jets pT>200
  N_AK8jets_pt200     = book<TH1F>("N_AK8jets_pt200", "N_{AK8 jets} (p_{T}>200)", 6, -0.5, 5.5);
  pt_AK8jets_pt200    = book<TH1F>("pt_AK8jets_pt200", "p_{T}^{AK8 jets} [GeV] (p_{T}>200)", 50, 0, 1000);
  pt_AK8jet1_pt200    = book<TH1F>("pt_AK8jet1_pt200", "p_{T}^{AK8 jet1} [GeV] (p_{T}>200)", 50, 0, 1000);
  eta_AK8jets_pt200   = book<TH1F>("eta_AK8jets_pt200", "#eta^{AK8 jets} (p_{T}>200)", 25, -2.5, 2.5);
  eta_AK8jet1_pt200   = book<TH1F>("eta_AK8jet1_pt200", "#eta^{AK8 jet1} (p_{T}>200)", 25, -2.5, 2.5);
  phi_AK8jets_pt200   = book<TH1F>("phi_AK8jets_pt200", "#phi^{AK8 jets} (p_{T}>200)", 35, -3.5, 3.5);
  phi_AK8jet1_pt200   = book<TH1F>("phi_AK8jet1_pt200", "#phi^{AK8 jet1} (p_{T}>200)", 35, -3.5, 3.5);
  mSD_AK8jets_pt200   = book<TH1F>("mSD_AK8jets_pt200", "m_{SD}^{AK8 jets} [GeV] (p_{T}>200)", 50, 0, 500);
  mSD_AK8jet1_pt200   = book<TH1F>("mSD_AK8jet1_pt200", "m_{SD}^{AK8 jet1} [GeV] (p_{T}>200)", 50, 0, 500);
  tau21_AK8jets_pt200 = book<TH1F>("tau21_AK8jets_pt200", "#tau_{2/1}^{AK8 jets} (p_{T}>200)", 24, 0, 1.2);
  tau21_AK8jet1_pt200 = book<TH1F>("tau21_AK8jet1_pt200", "#tau_{2/1}^{AK8 jet1} (p_{T}>200)", 24, 0, 1.2);
  tau32_AK8jets_pt200 = book<TH1F>("tau32_AK8jets_pt200", "#tau_{3/2}^{AK8 jets} (p_{T}>200)", 24, 0, 1.2);
  tau32_AK8jet1_pt200 = book<TH1F>("tau32_AK8jet1_pt200", "#tau_{3/2}^{AK8 jet1} (p_{T}>200)", 24, 0, 1.2);

  // AK8 PUPPI jets pT>200 matched to top quarks
  N_AK8Topjets_pt200     = book<TH1F>("N_AK8Topjets_pt200", "N_{AK8 Top jets} (p_{T}>200)", 6, -0.5, 5.5);
  pt_AK8Topjets_pt200    = book<TH1F>("pt_AK8Topjets_pt200", "p_{T}^{AK8 Top jets} [GeV] (p_{T}>200)", 50, 0, 1000);
  pt_AK8Topjet1_pt200    = book<TH1F>("pt_AK8Topjet1_pt200", "p_{T}^{AK8 Top jet1} [GeV] (p_{T}>200)", 50, 0, 1000);
  eta_AK8Topjets_pt200   = book<TH1F>("eta_AK8Topjets_pt200", "#eta^{AK8 Top jets} (p_{T}>200)", 25, -2.5, 2.5);
  eta_AK8Topjet1_pt200   = book<TH1F>("eta_AK8Topjet1_pt200", "#eta^{AK8 Top jet1} (p_{T}>200)", 25, -2.5, 2.5);
  phi_AK8Topjets_pt200   = book<TH1F>("phi_AK8Topjets_pt200", "#phi^{AK8 Top jets} (p_{T}>200)", 35, -3.5, 3.5);
  phi_AK8Topjet1_pt200   = book<TH1F>("phi_AK8Topjet1_pt200", "#phi^{AK8 Top jet1} (p_{T}>200)", 35, -3.5, 3.5);
  mSD_AK8Topjets_pt200   = book<TH1F>("mSD_AK8Topjets_pt200", "m_{SD}^{AK8 Top jets} [GeV] (p_{T}>200)", 50, 0, 500);
  mSD_AK8Topjet1_pt200   = book<TH1F>("mSD_AK8Topjet1_pt200", "m_{SD}^{AK8 Top jet1} [GeV] (p_{T}>200)", 50, 0, 500);
  tau21_AK8Topjets_pt200 = book<TH1F>("tau21_AK8Topjets_pt200", "#tau_{2/1}^{AK8 Top jets} (p_{T}>200)", 24, 0, 1.2);
  tau21_AK8Topjet1_pt200 = book<TH1F>("tau21_AK8Topjet1_pt200", "#tau_{2/1}^{AK8 Top jet1} (p_{T}>200)", 24, 0, 1.2);
  tau32_AK8Topjets_pt200 = book<TH1F>("tau32_AK8Topjets_pt200", "#tau_{3/2}^{AK8 Top jets} (p_{T}>200)", 24, 0, 1.2);
  tau32_AK8Topjet1_pt200 = book<TH1F>("tau32_AK8Topjet1_pt200", "#tau_{3/2}^{AK8 Top jet1} (p_{T}>200)", 24, 0, 1.2);

  // AK8 PUPPI jets pT>200 matched to light quarks (NOT spatially matched to tops)
  N_AK8Lightjets_pt200     = book<TH1F>("N_AK8Lightjets_pt200", "N_{AK8 Light jets} (p_{T}>200)", 6, -0.5, 5.5);
  pt_AK8Lightjets_pt200    = book<TH1F>("pt_AK8Lightjets_pt200", "p_{T}^{AK8 Light jets} [GeV] (p_{T}>200)", 50, 0, 1000);
  pt_AK8Lightjet1_pt200    = book<TH1F>("pt_AK8Lightjet1_pt200", "p_{T}^{AK8 Light jet1} [GeV] (p_{T}>200)", 50, 0, 1000);
  eta_AK8Lightjets_pt200   = book<TH1F>("eta_AK8Lightjets_pt200", "#eta^{AK8 Light jets} (p_{T}>200)", 25, -2.5, 2.5);
  eta_AK8Lightjet1_pt200   = book<TH1F>("eta_AK8Lightjet1_pt200", "#eta^{AK8 Light jet1} (p_{T}>200)", 25, -2.5, 2.5);
  phi_AK8Lightjets_pt200   = book<TH1F>("phi_AK8Lightjets_pt200", "#phi^{AK8 Light jets} (p_{T}>200)", 35, -3.5, 3.5);
  phi_AK8Lightjet1_pt200   = book<TH1F>("phi_AK8Lightjet1_pt200", "#phi^{AK8 Light jet1} (p_{T}>200)", 35, -3.5, 3.5);
  mSD_AK8Lightjets_pt200   = book<TH1F>("mSD_AK8Lightjets_pt200", "m_{SD}^{AK8 Light jets} [GeV] (p_{T}>200)", 50, 0, 500);
  mSD_AK8Lightjet1_pt200   = book<TH1F>("mSD_AK8Lightjet1_pt200", "m_{SD}^{AK8 Light jet1} [GeV] (p_{T}>200)", 50, 0, 500);
  tau21_AK8Lightjets_pt200 = book<TH1F>("tau21_AK8Lightjets_pt200", "#tau_{2/1}^{AK8 Light jets} (p_{T}>200)", 24, 0, 1.2);
  tau21_AK8Lightjet1_pt200 = book<TH1F>("tau21_AK8Lightjet1_pt200", "#tau_{2/1}^{AK8 Light jet1} (p_{T}>200)", 24, 0, 1.2);
  tau32_AK8Lightjets_pt200 = book<TH1F>("tau32_AK8Lightjets_pt200", "#tau_{3/2}^{AK8 Light jets} (p_{T}>200)", 24, 0, 1.2);
  tau32_AK8Lightjet1_pt200 = book<TH1F>("tau32_AK8Lightjet1_pt200", "#tau_{3/2}^{AK8 Light jet1} (p_{T}>200)", 24, 0, 1.2);

  // AK8 PUPPI jets pT>400
  N_AK8jets     = book<TH1F>("N_AK8jets", "N_{AK8 jets}", 6, -0.5, 5.5);
  pt_AK8jets    = book<TH1F>("pt_AK8jets", "p_{T}^{AK8 jets} [GeV]", 35, 300, 1000);
  pt_AK8jet1    = book<TH1F>("pt_AK8jet1", "p_{T}^{AK8 jet1} [GeV]", 35, 300, 1000);
  eta_AK8jets   = book<TH1F>("eta_AK8jets", "#eta^{AK8 jets}", 25, -2.5, 2.5);
  eta_AK8jet1   = book<TH1F>("eta_AK8jet1", "#eta^{AK8 jet1}", 25, -2.5, 2.5);
  phi_AK8jets   = book<TH1F>("phi_AK8jets", "#phi^{AK8 jets}", 35, -3.5, 3.5);
  phi_AK8jet1   = book<TH1F>("phi_AK8jet1", "#phi^{AK8 jet1}", 35, -3.5, 3.5);
  mSD_AK8jets   = book<TH1F>("mSD_AK8jets", "m_{SD}^{AK8 jets} [GeV]", 50, 0, 500);
  mSD_AK8jet1   = book<TH1F>("mSD_AK8jet1", "m_{SD}^{AK8 jet1} [GeV]", 50, 0, 500);
  tau21_AK8jets = book<TH1F>("tau21_AK8jets", "#tau_{2/1}^{AK8 jets}", 24, 0, 1.2);
  tau21_AK8jet1 = book<TH1F>("tau21_AK8jet1", "#tau_{2/1}^{AK8 jet1}", 24, 0, 1.2);
  tau32_AK8jets = book<TH1F>("tau32_AK8jets", "#tau_{3/2}^{AK8 jets}", 24, 0, 1.2);
  tau32_AK8jet1 = book<TH1F>("tau32_AK8jet1", "#tau_{3/2}^{AK8 jet1}", 24, 0, 1.2);

  // AK8 PUPPI jets pT>400 matched to top quarks
  N_AK8Topjets     = book<TH1F>("N_AK8Topjets", "N_{AK8 Top jets}", 6, -0.5, 5.5);
  pt_AK8Topjets    = book<TH1F>("pt_AK8Topjets", "p_{T}^{AK8 Top jets} [GeV]", 35, 300, 1000);
  pt_AK8Topjet1    = book<TH1F>("pt_AK8Topjet1", "p_{T}^{AK8 Top jet1} [GeV]", 35, 300, 1000);
  eta_AK8Topjets   = book<TH1F>("eta_AK8Topjets", "#eta^{AK8 Top jets}", 25, -2.5, 2.5);
  eta_AK8Topjet1   = book<TH1F>("eta_AK8Topjet1", "#eta^{AK8 Top jet1}", 25, -2.5, 2.5);
  phi_AK8Topjets   = book<TH1F>("phi_AK8Topjets", "#phi^{AK8 Top jets}", 35, -3.5, 3.5);
  phi_AK8Topjet1   = book<TH1F>("phi_AK8Topjet1", "#phi^{AK8 Top jet1}", 35, -3.5, 3.5);
  mSD_AK8Topjets   = book<TH1F>("mSD_AK8Topjets", "m_{SD}^{AK8 Top jets} [GeV]", 50, 0, 500);
  mSD_AK8Topjet1   = book<TH1F>("mSD_AK8Topjet1", "m_{SD}^{AK8 Top jet1} [GeV]", 50, 0, 500);
  tau21_AK8Topjets = book<TH1F>("tau21_AK8Topjets", "#tau_{2/1}^{AK8 Top jets}", 24, 0, 1.2);
  tau21_AK8Topjet1 = book<TH1F>("tau21_AK8Topjet1", "#tau_{2/1}^{AK8 Top jet1}", 24, 0, 1.2);
  tau32_AK8Topjets = book<TH1F>("tau32_AK8Topjets", "#tau_{3/2}^{AK8 Top jets}", 24, 0, 1.2);
  tau32_AK8Topjet1 = book<TH1F>("tau32_AK8Topjet1", "#tau_{3/2}^{AK8 Top jet1}", 24, 0, 1.2);

  // AK8 PUPPI jets pT>400 matched to light quarks (NOT spatially matched to tops)
  N_AK8Lightjets     = book<TH1F>("N_AK8Lightjets", "N_{AK8 Light jets}", 6, -0.5, 5.5);
  pt_AK8Lightjets    = book<TH1F>("pt_AK8Lightjets", "p_{T}^{AK8 Light jets} [GeV]", 35, 300, 1000);
  pt_AK8Lightjet1    = book<TH1F>("pt_AK8Lightjet1", "p_{T}^{AK8 Light jet1} [GeV]", 35, 300, 1000);
  eta_AK8Lightjets   = book<TH1F>("eta_AK8Lightjets", "#eta^{AK8 Light jets}", 25, -2.5, 2.5);
  eta_AK8Lightjet1   = book<TH1F>("eta_AK8Lightjet1", "#eta^{AK8 Light jet1}", 25, -2.5, 2.5);
  phi_AK8Lightjets   = book<TH1F>("phi_AK8Lightjets", "#phi^{AK8 Light jets}", 35, -3.5, 3.5);
  phi_AK8Lightjet1   = book<TH1F>("phi_AK8Lightjet1", "#phi^{AK8 Light jet1}", 35, -3.5, 3.5);
  mSD_AK8Lightjets   = book<TH1F>("mSD_AK8Lightjets", "m_{SD}^{AK8 Light jets} [GeV]", 50, 0, 500);
  mSD_AK8Lightjet1   = book<TH1F>("mSD_AK8Lightjet1", "m_{SD}^{AK8 Light jet1} [GeV]", 50, 0, 500);
  tau21_AK8Lightjets = book<TH1F>("tau21_AK8Lightjets", "#tau_{2/1}^{AK8 Light jets}", 24, 0, 1.2);
  tau21_AK8Lightjet1 = book<TH1F>("tau21_AK8Lightjet1", "#tau_{2/1}^{AK8 Light jet1}", 24, 0, 1.2);
  tau32_AK8Lightjets = book<TH1F>("tau32_AK8Lightjets", "#tau_{3/2}^{AK8 Light jets}", 24, 0, 1.2);
  tau32_AK8Lightjet1 = book<TH1F>("tau32_AK8Lightjet1", "#tau_{3/2}^{AK8 Light jet1}", 24, 0, 1.2);


  // Tagged AK8 PUPPI jets
  N_AK8jets_tagged     = book<TH1F>("N_AK8jets_tagged", "N_{AK8 jets tagged}", 6, -0.5, 5.5);
  pt_AK8jets_tagged    = book<TH1F>("pt_AK8jets_tagged", "p_{T}^{AK8 jets tagged} [GeV]", 35, 300, 1000);
  pt_AK8jet1_tagged    = book<TH1F>("pt_AK8jet1_tagged", "p_{T}^{AK8 jet1 tagged} [GeV]", 35, 300, 1000);
  eta_AK8jets_tagged   = book<TH1F>("eta_AK8jets_tagged", "#eta^{AK8 jets tagged}", 25, -2.5, 2.5);
  eta_AK8jet1_tagged   = book<TH1F>("eta_AK8jet1_tagged", "#eta^{AK8 jet1 tagged}", 25, -2.5, 2.5);
  phi_AK8jets_tagged   = book<TH1F>("phi_AK8jets_tagged", "#phi^{AK8 jets tagged}", 35, -3.5, 3.5);
  phi_AK8jet1_tagged   = book<TH1F>("phi_AK8jet1_tagged", "#phi^{AK8 jet1 tagged}", 35, -3.5, 3.5);
  mSD_AK8jets_tagged   = book<TH1F>("mSD_AK8jets_tagged", "m_{SD}^{AK8 jets tagged} [GeV]", 50, 0, 500);
  mSD_AK8jet1_tagged   = book<TH1F>("mSD_AK8jet1_tagged", "m_{SD}^{AK8 jet1 tagged} [GeV]", 50, 0, 500);
  tau21_AK8jets_tagged = book<TH1F>("tau21_AK8jets_tagged", "#tau_{2/1}^{AK8 jets tagged}", 24, 0, 1.2);
  tau21_AK8jet1_tagged = book<TH1F>("tau21_AK8jet1_tagged", "#tau_{2/1}^{AK8 jet1 tagged}", 24, 0, 1.2);
  tau32_AK8jets_tagged = book<TH1F>("tau32_AK8jets_tagged", "#tau_{3/2}^{AK8 jets tagged}", 24, 0, 1.2);
  tau32_AK8jet1_tagged = book<TH1F>("tau32_AK8jet1_tagged", "#tau_{3/2}^{AK8 jet1 tagged}", 24, 0, 1.2);

  // Tagged AK8 PUPPI jets matched to top quarks
  N_AK8Topjets_tagged     = book<TH1F>("N_AK8Topjets_tagged", "N_{AK8 Top jets tagged}", 6, -0.5, 5.5);
  pt_AK8Topjets_tagged    = book<TH1F>("pt_AK8Topjets_tagged", "p_{T}^{AK8 Top jets tagged} [GeV]", 35, 300, 1000);
  pt_AK8Topjet1_tagged    = book<TH1F>("pt_AK8Topjet1_tagged", "p_{T}^{AK8 Top jet1 tagged} [GeV]", 35, 300, 1000);
  eta_AK8Topjets_tagged   = book<TH1F>("eta_AK8Topjets_tagged", "#eta^{AK8 Top jets tagged}", 25, -2.5, 2.5);
  eta_AK8Topjet1_tagged   = book<TH1F>("eta_AK8Topjet1_tagged", "#eta^{AK8 Top jet1 tagged}", 25, -2.5, 2.5);
  phi_AK8Topjets_tagged   = book<TH1F>("phi_AK8Topjets_tagged", "#phi^{AK8 Top jets tagged}", 35, -3.5, 3.5);
  phi_AK8Topjet1_tagged   = book<TH1F>("phi_AK8Topjet1_tagged", "#phi^{AK8 Top jet1 tagged}", 35, -3.5, 3.5);
  mSD_AK8Topjets_tagged   = book<TH1F>("mSD_AK8Topjets_tagged", "m_{SD}^{AK8 Top jets tagged} [GeV]", 50, 0, 500);
  mSD_AK8Topjet1_tagged   = book<TH1F>("mSD_AK8Topjet1_tagged", "m_{SD}^{AK8 Top jet1 tagged} [GeV]", 50, 0, 500);
  tau21_AK8Topjets_tagged = book<TH1F>("tau21_AK8Topjets_tagged", "#tau_{2/1}^{AK8 Top jets tagged}", 24, 0, 1.2);
  tau21_AK8Topjet1_tagged = book<TH1F>("tau21_AK8Topjet1_tagged", "#tau_{2/1}^{AK8 Top jet1 tagged}", 24, 0, 1.2);
  tau32_AK8Topjets_tagged = book<TH1F>("tau32_AK8Topjets_tagged", "#tau_{3/2}^{AK8 Top jets tagged}", 24, 0, 1.2);
  tau32_AK8Topjet1_tagged = book<TH1F>("tau32_AK8Topjet1_tagged", "#tau_{3/2}^{AK8 Top jet1 tagged}", 24, 0, 1.2);

  // Tagged AK8 PUPPI jets matched to light quarks (NOT spatially matched to tops)
  N_AK8Lightjets_tagged     = book<TH1F>("N_AK8Lightjets_tagged", "N_{AK8 Light jets tagged}", 6, -0.5, 5.5);
  pt_AK8Lightjets_tagged    = book<TH1F>("pt_AK8Lightjets_tagged", "p_{T}^{AK8 Light jets tagged} [GeV]", 35, 300, 1000);
  pt_AK8Lightjet1_tagged    = book<TH1F>("pt_AK8Lightjet1_tagged", "p_{T}^{AK8 Light jet1 tagged} [GeV]", 35, 300, 1000);
  eta_AK8Lightjets_tagged   = book<TH1F>("eta_AK8Lightjets_tagged", "#eta^{AK8 Light jets tagged}", 25, -2.5, 2.5);
  eta_AK8Lightjet1_tagged   = book<TH1F>("eta_AK8Lightjet1_tagged", "#eta^{AK8 Light jet1 tagged}", 25, -2.5, 2.5);
  phi_AK8Lightjets_tagged   = book<TH1F>("phi_AK8Lightjets_tagged", "#phi^{AK8 Light jets tagged}", 35, -3.5, 3.5);
  phi_AK8Lightjet1_tagged   = book<TH1F>("phi_AK8Lightjet1_tagged", "#phi^{AK8 Light jet1 tagged}", 35, -3.5, 3.5);
  mSD_AK8Lightjets_tagged   = book<TH1F>("mSD_AK8Lightjets_tagged", "m_{SD}^{AK8 Light jets tagged} [GeV]", 50, 0, 500);
  mSD_AK8Lightjet1_tagged   = book<TH1F>("mSD_AK8Lightjet1_tagged", "m_{SD}^{AK8 Light jet1 tagged} [GeV]", 50, 0, 500);
  tau21_AK8Lightjets_tagged = book<TH1F>("tau21_AK8Lightjets_tagged", "#tau_{2/1}^{AK8 Light jets tagged}", 24, 0, 1.2);
  tau21_AK8Lightjet1_tagged = book<TH1F>("tau21_AK8Lightjet1_tagged", "#tau_{2/1}^{AK8 Light jet1 tagged}", 24, 0, 1.2);
  tau32_AK8Lightjets_tagged = book<TH1F>("tau32_AK8Lightjets_tagged", "#tau_{3/2}^{AK8 Light jets tagged}", 24, 0, 1.2);
  tau32_AK8Lightjet1_tagged = book<TH1F>("tau32_AK8Lightjet1_tagged", "#tau_{3/2}^{AK8 Light jet1 tagged}", 24, 0, 1.2);

}


void ZprimeSemiLeptonicMistagHists::fill(const Event & event){

  double weight = event.weight;

  if(isdeepAK8){

  vector<TopJet>* toppuppijets = event.toppuppijets;
  vector<GenParticle>* genparticles = event.genparticles;

  // AK8 PUPPI jets pT>200
  N_AK8jets_pt200->Fill(toppuppijets->size(), weight); 
    for(unsigned int i=0; i<toppuppijets->size(); i++){
      pt_AK8jets_pt200->Fill(toppuppijets->at(i).pt(),weight);
      eta_AK8jets_pt200->Fill(toppuppijets->at(i).eta(),weight);
      phi_AK8jets_pt200->Fill(toppuppijets->at(i).phi(),weight);
      mSD_AK8jets_pt200->Fill(toppuppijets->at(i).softdropmass(),weight);
      tau21_AK8jets_pt200->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
      tau32_AK8jets_pt200->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
      if(i==0){
          pt_AK8jet1_pt200->Fill(toppuppijets->at(i).pt(),weight);
          eta_AK8jet1_pt200->Fill(toppuppijets->at(i).eta(),weight);
          phi_AK8jet1_pt200->Fill(toppuppijets->at(i).phi(),weight);
          mSD_AK8jet1_pt200->Fill(toppuppijets->at(i).softdropmass(),weight);
          tau21_AK8jet1_pt200->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
          tau32_AK8jet1_pt200->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
      }

      // Match to gen-lvl top quark
      if(is_mc){
        double deltaR_min = 99;
        for(unsigned int j=0; j<genparticles->size(); ++j) {
            if (abs(genparticles->at(j).pdgId()) == 6){
               double deltaR_top = deltaR(toppuppijets->at(i),genparticles->at(j));
               if(deltaR_top<deltaR_min) deltaR_min = deltaR_top;
            }
        }
        if(deltaR_min<=0.4){
           N_AK8Topjets_pt200->Fill(toppuppijets->size(), weight);
           pt_AK8Topjets_pt200->Fill(toppuppijets->at(i).pt(),weight);
           eta_AK8Topjets_pt200->Fill(toppuppijets->at(i).eta(),weight);
           phi_AK8Topjets_pt200->Fill(toppuppijets->at(i).phi(),weight);
           mSD_AK8Topjets_pt200->Fill(toppuppijets->at(i).softdropmass(),weight);
           tau21_AK8Topjets_pt200->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
           tau32_AK8Topjets_pt200->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
           if(i==0){
               pt_AK8Topjet1_pt200->Fill(toppuppijets->at(i).pt(),weight);
               eta_AK8Topjet1_pt200->Fill(toppuppijets->at(i).eta(),weight);
               phi_AK8Topjet1_pt200->Fill(toppuppijets->at(i).phi(),weight);
               mSD_AK8Topjet1_pt200->Fill(toppuppijets->at(i).softdropmass(),weight);
               tau21_AK8Topjet1_pt200->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
               tau32_AK8Topjet1_pt200->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
           }
        }else{
           N_AK8Lightjets_pt200->Fill(toppuppijets->size(), weight);
           pt_AK8Lightjets_pt200->Fill(toppuppijets->at(i).pt(),weight);
           eta_AK8Lightjets_pt200->Fill(toppuppijets->at(i).eta(),weight);
           phi_AK8Lightjets_pt200->Fill(toppuppijets->at(i).phi(),weight);
           mSD_AK8Lightjets_pt200->Fill(toppuppijets->at(i).softdropmass(),weight);
           tau21_AK8Lightjets_pt200->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
           tau32_AK8Lightjets_pt200->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
           if(i==0){
               pt_AK8Lightjet1_pt200->Fill(toppuppijets->at(i).pt(),weight);
               eta_AK8Lightjet1_pt200->Fill(toppuppijets->at(i).eta(),weight);
               phi_AK8Lightjet1_pt200->Fill(toppuppijets->at(i).phi(),weight);
               mSD_AK8Lightjet1_pt200->Fill(toppuppijets->at(i).softdropmass(),weight);
               tau21_AK8Lightjet1_pt200->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
               tau32_AK8Lightjet1_pt200->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
           }
        }
      }
  } // top jets loop



  // AK8 PUPPI jets pT>400
  for(unsigned int i=0; i<toppuppijets->size(); i++){
    if(toppuppijets->at(i).pt()>400){
        N_AK8jets->Fill(toppuppijets->size(), weight);
        pt_AK8jets->Fill(toppuppijets->at(i).pt(),weight);
        eta_AK8jets->Fill(toppuppijets->at(i).eta(),weight);
        phi_AK8jets->Fill(toppuppijets->at(i).phi(),weight);
        mSD_AK8jets->Fill(toppuppijets->at(i).softdropmass(),weight);
        tau21_AK8jets->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
        tau32_AK8jets->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
        if(i==0){
            pt_AK8jet1->Fill(toppuppijets->at(i).pt(),weight);
            eta_AK8jet1->Fill(toppuppijets->at(i).eta(),weight);
            phi_AK8jet1->Fill(toppuppijets->at(i).phi(),weight);
            mSD_AK8jet1->Fill(toppuppijets->at(i).softdropmass(),weight);
            tau21_AK8jet1->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
            tau32_AK8jet1->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
        }

        // Match to gen-lvl top quark
        if(is_mc){
          double deltaR_min = 99;
          for(unsigned int j=0; j<genparticles->size(); ++j) {
              if (abs(genparticles->at(j).pdgId()) == 6){
                 double deltaR_top = deltaR(toppuppijets->at(i),genparticles->at(j));
                 if(deltaR_top<deltaR_min) deltaR_min = deltaR_top;
              }
          }
          if(deltaR_min<=0.4){
             N_AK8Topjets->Fill(toppuppijets->size(), weight);
             pt_AK8Topjets->Fill(toppuppijets->at(i).pt(),weight);
             eta_AK8Topjets->Fill(toppuppijets->at(i).eta(),weight);
             phi_AK8Topjets->Fill(toppuppijets->at(i).phi(),weight);
             mSD_AK8Topjets->Fill(toppuppijets->at(i).softdropmass(),weight);
             tau21_AK8Topjets->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
             tau32_AK8Topjets->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
             if(i==0){
                 pt_AK8Topjet1->Fill(toppuppijets->at(i).pt(),weight);
                 eta_AK8Topjet1->Fill(toppuppijets->at(i).eta(),weight);
                 phi_AK8Topjet1->Fill(toppuppijets->at(i).phi(),weight);
                 mSD_AK8Topjet1->Fill(toppuppijets->at(i).softdropmass(),weight);
                 tau21_AK8Topjet1->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
                 tau32_AK8Topjet1->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
             }
          }else{
             N_AK8Lightjets->Fill(toppuppijets->size(), weight);
             pt_AK8Lightjets->Fill(toppuppijets->at(i).pt(),weight);
             eta_AK8Lightjets->Fill(toppuppijets->at(i).eta(),weight);
             phi_AK8Lightjets->Fill(toppuppijets->at(i).phi(),weight);
             mSD_AK8Lightjets->Fill(toppuppijets->at(i).softdropmass(),weight);
             tau21_AK8Lightjets->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
             tau32_AK8Lightjets->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
             if(i==0){
                 pt_AK8Lightjet1->Fill(toppuppijets->at(i).pt(),weight);
                 eta_AK8Lightjet1->Fill(toppuppijets->at(i).eta(),weight);
                 phi_AK8Lightjet1->Fill(toppuppijets->at(i).phi(),weight);
                 mSD_AK8Lightjet1->Fill(toppuppijets->at(i).softdropmass(),weight);
                 tau21_AK8Lightjet1->Fill(toppuppijets->at(i).tau2() / toppuppijets->at(i).tau1(),weight);
                 tau32_AK8Lightjet1->Fill(toppuppijets->at(i).tau3() / toppuppijets->at(i).tau2(),weight);
             }
          }
        }
    } // pT>400
  } // top jets loop

  // Top-tagged AK8 PUPPI jets
  vector<TopJet> AK8PuppiTopTags = event.get(h_AK8TopTags);
  
  N_AK8jets_tagged->Fill(AK8PuppiTopTags.size(), weight);
  for(unsigned int l=0; l<AK8PuppiTopTags.size(); l++){
    pt_AK8jets_tagged->Fill(AK8PuppiTopTags.at(l).pt(),weight);
    eta_AK8jets_tagged->Fill(AK8PuppiTopTags.at(l).eta(),weight);
    phi_AK8jets_tagged->Fill(AK8PuppiTopTags.at(l).phi(),weight);
    mSD_AK8jets_tagged->Fill(AK8PuppiTopTags.at(l).softdropmass(),weight);
    tau21_AK8jets_tagged->Fill(AK8PuppiTopTags.at(l).tau2() / AK8PuppiTopTags.at(l).tau1(),weight);
    tau32_AK8jets_tagged->Fill(AK8PuppiTopTags.at(l).tau3() / AK8PuppiTopTags.at(l).tau2(),weight);
    if(l==0){
        pt_AK8jet1_tagged->Fill(AK8PuppiTopTags.at(l).pt(),weight);
        eta_AK8jet1_tagged->Fill(AK8PuppiTopTags.at(l).eta(),weight);
        phi_AK8jet1_tagged->Fill(AK8PuppiTopTags.at(l).phi(),weight);
        mSD_AK8jet1_tagged->Fill(AK8PuppiTopTags.at(l).softdropmass(),weight);
        tau21_AK8jet1_tagged->Fill(AK8PuppiTopTags.at(l).tau2() / AK8PuppiTopTags.at(l).tau1(),weight);
        tau32_AK8jet1_tagged->Fill(AK8PuppiTopTags.at(l).tau3() / AK8PuppiTopTags.at(l).tau2(),weight);
    }

    // Match to gen-lvl top quark
    if(is_mc){
      double deltaR_min_tagged = 99;
      for(unsigned int k=0; k<genparticles->size(); ++k) {
          if (abs(genparticles->at(k).pdgId()) == 6){
             double deltaR_top_tagged = deltaR(AK8PuppiTopTags.at(l),genparticles->at(k));
             if(deltaR_top_tagged<deltaR_min_tagged) deltaR_min_tagged = deltaR_top_tagged;
          }
      }
      if(deltaR_min_tagged<=0.4){
         N_AK8Topjets_tagged->Fill(AK8PuppiTopTags.size(), weight);
         pt_AK8Topjets_tagged->Fill(AK8PuppiTopTags.at(l).pt(),weight);
         eta_AK8Topjets_tagged->Fill(AK8PuppiTopTags.at(l).eta(),weight);
         phi_AK8Topjets_tagged->Fill(AK8PuppiTopTags.at(l).phi(),weight);
         mSD_AK8Topjets_tagged->Fill(AK8PuppiTopTags.at(l).softdropmass(),weight);
         tau21_AK8Topjets_tagged->Fill(AK8PuppiTopTags.at(l).tau2() / AK8PuppiTopTags.at(l).tau1(),weight);
         tau32_AK8Topjets_tagged->Fill(AK8PuppiTopTags.at(l).tau3() / AK8PuppiTopTags.at(l).tau2(),weight);
         if(l==0){
             pt_AK8Topjet1_tagged->Fill(AK8PuppiTopTags.at(l).pt(),weight);
             eta_AK8Topjet1_tagged->Fill(AK8PuppiTopTags.at(l).eta(),weight);
             phi_AK8Topjet1_tagged->Fill(AK8PuppiTopTags.at(l).phi(),weight);
             mSD_AK8Topjet1_tagged->Fill(AK8PuppiTopTags.at(l).softdropmass(),weight);
             tau21_AK8Topjet1_tagged->Fill(AK8PuppiTopTags.at(l).tau2() / AK8PuppiTopTags.at(l).tau1(),weight);
             tau32_AK8Topjet1_tagged->Fill(AK8PuppiTopTags.at(l).tau3() / AK8PuppiTopTags.at(l).tau2(),weight);
         }
      }else{
         N_AK8Lightjets_tagged->Fill(AK8PuppiTopTags.size(), weight);
         pt_AK8Lightjets_tagged->Fill(AK8PuppiTopTags.at(l).pt(),weight);
         eta_AK8Lightjets_tagged->Fill(AK8PuppiTopTags.at(l).eta(),weight);
         phi_AK8Lightjets_tagged->Fill(AK8PuppiTopTags.at(l).phi(),weight);
         mSD_AK8Lightjets_tagged->Fill(AK8PuppiTopTags.at(l).softdropmass(),weight);
         tau21_AK8Lightjets_tagged->Fill(AK8PuppiTopTags.at(l).tau2() / AK8PuppiTopTags.at(l).tau1(),weight);
         tau32_AK8Lightjets_tagged->Fill(AK8PuppiTopTags.at(l).tau3() / AK8PuppiTopTags.at(l).tau2(),weight);
         if(l==0){
             pt_AK8Lightjet1_tagged->Fill(AK8PuppiTopTags.at(l).pt(),weight);
             eta_AK8Lightjet1_tagged->Fill(AK8PuppiTopTags.at(l).eta(),weight);
             phi_AK8Lightjet1_tagged->Fill(AK8PuppiTopTags.at(l).phi(),weight);
             mSD_AK8Lightjet1_tagged->Fill(AK8PuppiTopTags.at(l).softdropmass(),weight);
             tau21_AK8Lightjet1_tagged->Fill(AK8PuppiTopTags.at(l).tau2() / AK8PuppiTopTags.at(l).tau1(),weight);
             tau32_AK8Lightjet1_tagged->Fill(AK8PuppiTopTags.at(l).tau3() / AK8PuppiTopTags.at(l).tau2(),weight);
         }
      }
    }
  } // tagged top jets loop

 } // isdeepAK8

} //Method



ZprimeSemiLeptonicMistagHists::~ZprimeSemiLeptonicMistagHists(){}
