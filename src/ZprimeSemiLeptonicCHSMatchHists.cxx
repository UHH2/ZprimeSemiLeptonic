#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicCHSMatchHists.h"
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

ZprimeSemiLeptonicCHSMatchHists::ZprimeSemiLeptonicCHSMatchHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {

  is_mc = ctx.get("dataset_type") == "MC";
  h_CHSjets_matched = ctx.get_handle<std::vector<Jet>>("CHS_matched");
  init();
}

void ZprimeSemiLeptonicCHSMatchHists::init(){

  // jets
  N_jets            = book<TH1F>("N_jets", "N_{jets}", 21, -0.5, 20.5);
  pt_jet            = book<TH1F>("pt_jet", "p_{T}^{jets} [GeV]", 50, 0, 1500);
  pt_jet1           = book<TH1F>("pt_jet1", "p_{T}^{jet 1} [GeV]", 50, 0, 1500);
  pt_jet2           = book<TH1F>("pt_jet2", "p_{T}^{jet 2} [GeV]", 50, 0, 1500);
  pt_jet3           = book<TH1F>("pt_jet3", "p_{T}^{jet 3} [GeV]", 50, 0, 1500);
  eta_jet           = book<TH1F>("eta_jet", "#eta^{jets}", 50, -2.5, 2.5);
  eta_jet1          = book<TH1F>("eta_jet1", "#eta^{jet 1}", 50, -2.5, 2.5);
  eta_jet2          = book<TH1F>("eta_jet2", "#eta^{jet 2}", 50, -2.5, 2.5);
  eta_jet3          = book<TH1F>("eta_jet3", "#eta^{jet 3}", 50, -2.5, 2.5);
  phi_jet           = book<TH1F>("phi_jet", "#phi^{jets}", 35, -3.5, 3.5);
  phi_jet1          = book<TH1F>("phi_jet1", "#phi^{jet 1}", 35, -3.5, 3.5);
  phi_jet2          = book<TH1F>("phi_jet2", "#phi^{jet 2}", 35, -3.5, 3.5);
  phi_jet3          = book<TH1F>("phi_jet3", "#phi^{jet 3}", 35, -3.5, 3.5);
  m_jet             = book<TH1F>("m_jet", "m^{jets}", 50, 0, 500);
  m_jet1            = book<TH1F>("m_jet1", "m^{jet 1}", 50, 0, 500);
  m_jet2            = book<TH1F>("m_jet2", "m^{jet 2}", 50, 0, 500);
  m_jet3            = book<TH1F>("m_jet3", "m^{jet 3}", 50, 0, 500);
  bscore_jet        = book<TH1F>("bscore_jet",  "bscore^{jets}", 20, 0, 1);
  bscore_jet1       = book<TH1F>("bscore_jet1", "bscore^{jet 1}", 20, 0, 1);
  bscore_jet2       = book<TH1F>("bscore_jet2", "bscore^{jet 2}", 20, 0, 1);
  bscore_jet3       = book<TH1F>("bscore_jet3", "bscore^{jet 3}", 20, 0, 1);
  N_bJets_loose     = book<TH1F>("N_bJets_loose", "N_{jets}^{bscore loose}", 11, -0.5, 10.5);
  N_bJets_med       = book<TH1F>("N_bJets_med",   "N_{jets}^{bscore medium}", 11, -0.5, 10.5);
  N_bJets_tight     = book<TH1F>("N_bJets_tight", "N_{jets}^{bscore tight}", 11, -0.5, 10.5);

  // CHS matched jets
  CHS_matched_N_jets            = book<TH1F>("CHS_matched_N_jets", "CHS matched N_{jets}", 21, -0.5, 20.5);
  CHS_matched_pt_jet            = book<TH1F>("CHS_matched_pt_jet", "CHS matched p_{T}^{jets} [GeV]", 50, 0, 1500);
  CHS_matched_pt_jet1           = book<TH1F>("CHS_matched_pt_jet1", "CHS matched p_{T}^{jet 1} [GeV]", 50, 0, 1500);
  CHS_matched_pt_jet2           = book<TH1F>("CHS_matched_pt_jet2", "CHS matched p_{T}^{jet 2} [GeV]", 50, 0, 1500);
  CHS_matched_pt_jet3           = book<TH1F>("CHS_matched_pt_jet3", "CHS matched p_{T}^{jet 3} [GeV]", 50, 0, 1500);
  CHS_matched_eta_jet           = book<TH1F>("CHS_matched_eta_jet", "CHS matched #eta^{jets}", 50, -2.5, 2.5);
  CHS_matched_eta_jet1          = book<TH1F>("CHS_matched_eta_jet1", "CHS matched #eta^{jet 1}", 50, -2.5, 2.5);
  CHS_matched_eta_jet2          = book<TH1F>("CHS_matched_eta_jet2", "CHS matched #eta^{jet 2}", 50, -2.5, 2.5);
  CHS_matched_eta_jet3          = book<TH1F>("CHS_matched_eta_jet3", "CHS matched #eta^{jet 3}", 50, -2.5, 2.5);
  CHS_matched_phi_jet           = book<TH1F>("CHS_matched_phi_jet", "CHS matched #phi^{jets}", 35, -3.5, 3.5);
  CHS_matched_phi_jet1          = book<TH1F>("CHS_matched_phi_jet1", "CHS matched #phi^{jet 1}", 35, -3.5, 3.5);
  CHS_matched_phi_jet2          = book<TH1F>("CHS_matched_phi_jet2", "CHS matched #phi^{jet 2}", 35, -3.5, 3.5);
  CHS_matched_phi_jet3          = book<TH1F>("CHS_matched_phi_jet3", "CHS matched #phi^{jet 3}", 35, -3.5, 3.5);
  CHS_matched_m_jet             = book<TH1F>("CHS_matched_m_jet", "CHS matched m^{jets}", 50, 0, 500);
  CHS_matched_m_jet1            = book<TH1F>("CHS_matched_m_jet1", "CHS matched m^{jet 1}", 50, 0, 500);
  CHS_matched_m_jet2            = book<TH1F>("CHS_matched_m_jet2", "CHS matched m^{jet 2}", 50, 0, 500);
  CHS_matched_m_jet3            = book<TH1F>("CHS_matched_m_jet3", "CHS matched m^{jet 3}", 50, 0, 500);
  CHS_matched_bscore_jet        = book<TH1F>("CHS_matched_bscore_jet",  "CHS matched bscore^{jets}", 20, 0, 1);
  CHS_matched_bscore_jet1       = book<TH1F>("CHS_matched_bscore_jet1", "CHS matched bscore^{jet 1}", 20, 0, 1);
  CHS_matched_bscore_jet2       = book<TH1F>("CHS_matched_bscore_jet2", "CHS matched bscore^{jet 2}", 20, 0, 1);
  CHS_matched_bscore_jet3       = book<TH1F>("CHS_matched_bscore_jet3", "CHS matched bscore^{jet 3}", 20, 0, 1);
  CHS_matched_N_bJets_loose     = book<TH1F>("CHS_matched_N_bJets_loose", "CHS matched N_{jets}^{bscore loose}", 11, -0.5, 10.5);
  CHS_matched_N_bJets_med       = book<TH1F>("CHS_matched_N_bJets_med",   "CHS matched N_{jets}^{bscore medium}", 11, -0.5, 10.5);
  CHS_matched_N_bJets_tight     = book<TH1F>("CHS_matched_N_bJets_tight", "CHS matched N_{jets}^{bscore tight}", 11, -0.5, 10.5);

}


void ZprimeSemiLeptonicCHSMatchHists::fill(const Event & event){

  double weight = event.weight;

  /*
  █      ██ ███████ ████████ ███████
  █      ██ ██         ██    ██
  █      ██ █████      ██    ███████
  █ ██   ██ ██         ██         ██
  █  █████  ███████    ██    ███████
  */

  vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  N_jets->Fill(Njets, weight);

  for(unsigned int i=0; i<jets->size(); i++){
    pt_jet->Fill(jets->at(i).pt(),weight);
    eta_jet->Fill(jets->at(i).eta(),weight);
    phi_jet->Fill(jets->at(i).phi(),weight);
    m_jet->Fill(jets->at(i).v4().M(),weight);
    bscore_jet->Fill(jets->at(i).btag_DeepJet(), weight);
    if(i==0){
      pt_jet1->Fill(jets->at(i).pt(),weight);
      eta_jet1->Fill(jets->at(i).eta(),weight);
      phi_jet1->Fill(jets->at(i).phi(),weight);
      m_jet1->Fill(jets->at(i).v4().M(),weight);
      bscore_jet1->Fill(jets->at(i).btag_DeepJet(), weight);
    }
    else if(i==1){
      pt_jet2->Fill(jets->at(i).pt(),weight);
      eta_jet2->Fill(jets->at(i).eta(),weight);
      phi_jet2->Fill(jets->at(i).phi(),weight);
      m_jet2->Fill(jets->at(i).v4().M(),weight);
      bscore_jet2->Fill(jets->at(i).btag_DeepJet(), weight);
    }
    else if(i==2){
      pt_jet3->Fill(jets->at(i).pt(),weight);
      eta_jet3->Fill(jets->at(i).eta(),weight);
      phi_jet3->Fill(jets->at(i).phi(),weight);
      m_jet3->Fill(jets->at(i).v4().M(),weight);
      bscore_jet3->Fill(jets->at(i).btag_DeepJet(), weight);
    }
  }

  int Nbjets_loose = 0, Nbjets_medium = 0, Nbjets_tight = 0;
  DeepJetBTag Btag_loose  = DeepJetBTag(DeepJetBTag::WP_LOOSE);
  DeepJetBTag Btag_medium = DeepJetBTag(DeepJetBTag::WP_MEDIUM);
  DeepJetBTag Btag_tight  = DeepJetBTag(DeepJetBTag::WP_TIGHT);

  for (unsigned int i =0; i<jets->size(); i++) {
    if(Btag_loose(jets->at(i),event))  Nbjets_loose++;
    if(Btag_medium(jets->at(i),event)) Nbjets_medium++;
    if(Btag_tight(jets->at(i),event))  Nbjets_tight++;
  }

  N_bJets_loose->Fill(Nbjets_loose,weight);
  N_bJets_med->Fill(Nbjets_medium,weight);
  N_bJets_tight->Fill(Nbjets_tight,weight);


  /*
  █  ██████ ██   ██ ███████      ██ ███████ ████████ ███████
  █ ██      ██   ██ ██           ██ ██         ██    ██
  █ ██      ███████ ███████      ██ █████      ██    ███████
  █ ██      ██   ██      ██ ██   ██ ██         ██         ██
  █  ██████ ██   ██ ███████  █████  ███████    ██    ███████
  */

  //// Matched to Puppi jets

  vector<Jet> AK4CHSjets_matched = event.get(h_CHSjets_matched);
  int CHS_matched_Njets = AK4CHSjets_matched.size();
  CHS_matched_N_jets->Fill(CHS_matched_Njets, weight);

  for(unsigned int i=0; i<AK4CHSjets_matched.size(); i++){
    CHS_matched_pt_jet->Fill(AK4CHSjets_matched.at(i).pt(),weight);
    CHS_matched_eta_jet->Fill(AK4CHSjets_matched.at(i).eta(),weight);
    CHS_matched_phi_jet->Fill(AK4CHSjets_matched.at(i).phi(),weight);
    CHS_matched_m_jet->Fill(AK4CHSjets_matched.at(i).v4().M(),weight);
    CHS_matched_bscore_jet->Fill(AK4CHSjets_matched.at(i).btag_DeepJet(), weight);
    if(i==0){
      CHS_matched_pt_jet1->Fill(AK4CHSjets_matched.at(i).pt(),weight);
      CHS_matched_eta_jet1->Fill(AK4CHSjets_matched.at(i).eta(),weight);
      CHS_matched_phi_jet1->Fill(AK4CHSjets_matched.at(i).phi(),weight);
      CHS_matched_m_jet1->Fill(AK4CHSjets_matched.at(i).v4().M(),weight);
      CHS_matched_bscore_jet1->Fill(AK4CHSjets_matched.at(i).btag_DeepJet(), weight);
    }
    else if(i==1){
      CHS_matched_pt_jet2->Fill(AK4CHSjets_matched.at(i).pt(),weight);
      CHS_matched_eta_jet2->Fill(AK4CHSjets_matched.at(i).eta(),weight);
      CHS_matched_phi_jet2->Fill(AK4CHSjets_matched.at(i).phi(),weight);
      CHS_matched_m_jet2->Fill(AK4CHSjets_matched.at(i).v4().M(),weight);
      CHS_matched_bscore_jet2->Fill(AK4CHSjets_matched.at(i).btag_DeepJet(), weight);
    }
    else if(i==2){
      CHS_matched_pt_jet3->Fill(AK4CHSjets_matched.at(i).pt(),weight);
      CHS_matched_eta_jet3->Fill(AK4CHSjets_matched.at(i).eta(),weight);
      CHS_matched_phi_jet3->Fill(AK4CHSjets_matched.at(i).phi(),weight);
      CHS_matched_m_jet3->Fill(AK4CHSjets_matched.at(i).v4().M(),weight);
      CHS_matched_bscore_jet3->Fill(AK4CHSjets_matched.at(i).btag_DeepJet(), weight);
    }
  }

  int CHS_matched_Nbjets_loose = 0, CHS_matched_Nbjets_medium = 0, CHS_matched_Nbjets_tight = 0;
  DeepJetBTag CHS_matched_Btag_loose  = DeepJetBTag(DeepJetBTag::WP_LOOSE);
  DeepJetBTag CHS_matched_Btag_medium = DeepJetBTag(DeepJetBTag::WP_MEDIUM);
  DeepJetBTag CHS_matched_Btag_tight  = DeepJetBTag(DeepJetBTag::WP_TIGHT);

  for (unsigned int i =0; i<AK4CHSjets_matched.size(); i++) {
    if(CHS_matched_Btag_loose(AK4CHSjets_matched.at(i),event))  CHS_matched_Nbjets_loose++;
    if(CHS_matched_Btag_medium(AK4CHSjets_matched.at(i),event)) CHS_matched_Nbjets_medium++;
    if(CHS_matched_Btag_tight(AK4CHSjets_matched.at(i),event))  CHS_matched_Nbjets_tight++;
  }

  CHS_matched_N_bJets_loose->Fill(CHS_matched_Nbjets_loose,weight);
  CHS_matched_N_bJets_med->Fill(CHS_matched_Nbjets_medium,weight);
  CHS_matched_N_bJets_tight->Fill(CHS_matched_Nbjets_tight,weight);



} //Method



ZprimeSemiLeptonicCHSMatchHists::~ZprimeSemiLeptonicCHSMatchHists(){}
