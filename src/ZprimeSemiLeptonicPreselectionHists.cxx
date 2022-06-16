#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicPreselectionHists.h"
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

ZprimeSemiLeptonicPreselectionHists::ZprimeSemiLeptonicPreselectionHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {

  is_mc = ctx.get("dataset_type") == "MC";
  init();
}

void ZprimeSemiLeptonicPreselectionHists::init(){

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

  // leptons
  N_mu              = book<TH1F>("N_mu", "N^{#mu}", 11, -0.5, 10.5);
  pt_mu             = book<TH1F>("pt_mu", "p_{T}^{#mu} [GeV]", 50, 0, 1500);
  pt_mu1            = book<TH1F>("pt_mu1", "p_{T}^{#mu 1} [GeV]", 50, 0, 1500);
  pt_mu2            = book<TH1F>("pt_mu2", "p_{T}^{#mu 2} [GeV]", 50, 0, 1500);
  eta_mu            = book<TH1F>("eta_mu", "#eta^{#mu}", 50, -2.5, 2.5);
  eta_mu1           = book<TH1F>("eta_mu1", "#eta^{#mu 1}", 50, -2.5, 2.5);
  eta_mu2           = book<TH1F>("eta_mu2", "#eta^{#mu 2}", 50, -2.5, 2.5);
  phi_mu            = book<TH1F>("phi_mu", "#phi^{#mu}", 35, -3.5, 3.5);
  phi_mu1           = book<TH1F>("phi_mu1", "#phi^{#mu 1}", 35, 3.5, 3.5);
  phi_mu2           = book<TH1F>("phi_mu2", "#phi^{#mu 2}", 35, 3.5, 3.5);
  reliso_mu         = book<TH1F>("reliso_mu", "#mu rel. Iso", 40, 0, 0.5);
  reliso_mu1        = book<TH1F>("reliso_mu1", "#mu 1 rel. Iso", 40, 0, 0.5);
  reliso_mu2        = book<TH1F>("reliso_mu2", "#mu 2 rel. Iso", 40, 0, 0.5);
  reliso_mu_rebin   = book<TH1F>("reliso_mu_rebin", "#mu rel. Iso ", 400, 0, 5);
  reliso_mu1_rebin  = book<TH1F>("reliso_mu1_rebin", "#mu 1 rel. Iso ", 400, 0, 5);
  reliso_mu2_rebin  = book<TH1F>("reliso_mu2_rebin", "#mu 2 rel. Iso ", 400, 0, 5);
  N_ele             = book<TH1F>("N_ele", "N^{e}", 11, -0.5, 10.5);
  pt_ele            = book<TH1F>("pt_ele", "p_{T}^{e} [GeV]", 50, 0, 1500);
  pt_ele1           = book<TH1F>("pt_ele1", "p_{T}^{e 1} [GeV]", 50, 0, 1500);
  pt_ele2           = book<TH1F>("pt_ele2", "p_{T}^{e 2} [GeV]", 50, 0, 1500);
  eta_ele           = book<TH1F>("eta_ele", "#eta^{e}", 50, -2.5, 2.5);
  eta_ele1          = book<TH1F>("eta_ele1", "#eta^{ele 1}", 50, -2.5, 2.5);
  eta_ele2          = book<TH1F>("eta_ele2", "#eta^{ele 2}", 50, -2.5, 2.5);
  phi_ele           = book<TH1F>("phi_ele", "#phi^{e}", 35, -3.5, 3.5);
  phi_ele1          = book<TH1F>("phi_ele1", "#phi^{e 1}", 35, -3.5, 3.5);
  phi_ele2          = book<TH1F>("phi_ele2", "#phi^{e 2}", 35, -3.5, 3.5);
  reliso_ele        = book<TH1F>("reliso_ele", "e rel. Iso", 40, 0, 0.5);
  reliso_ele1       = book<TH1F>("reliso_ele1", "e 1 rel. Iso", 40, 0, 0.5);
  reliso_ele2       = book<TH1F>("reliso_ele2", "e 2 rel. Iso", 40, 0, 0.5);
  reliso_ele_rebin  = book<TH1F>("reliso_ele_rebin", "e rel. Iso", 400, 0, 5);
  reliso_ele1_rebin = book<TH1F>("reliso_ele1_rebin", "e 1 rel. Iso", 400, 0, 5);
  reliso_ele2_rebin = book<TH1F>("reliso_ele2_rebin", "e 2 rel. Iso", 400, 0, 5);
  M_mumu            = book<TH1F>("M_mumu", "M_{#mu#mu} [GeV]",75 , 0, 500);
  M_ee              = book<TH1F>("M_ee", "M_{ee} [GeV]",75 , 0, 500);

  dRmin_mu_jet          = book<TH1F>("dRmin_mu_jet", "#DeltaR_{min}(#mu, jet)", 60, 0, 3);
  dRmin_mu_jet_scaled   = book<TH1F>("dRmin_mu_jet_scaled", "#DeltaR_{min}(#mu, jet) #times p_{T}^{jet 1}", 60, 0, 1000);
  dRmin_ele_jet         = book<TH1F>("dRmin_ele_jet", "#DeltaR_{min}(e, jet)", 60, 0, 3);
  dRmin_ele_jet_scaled  = book<TH1F>("dRmin_ele_jet_scaled", "#DeltaR_{min}(e, jet) #times p_{T}^{jet 1}", 60, 0, 1000);
  ptrel_mu_jet          = book<TH1F>("ptrel_mu_jet", "p_{T}^{rel}(#mu, jet)", 50, 0, 500);
  ptrel_ele_jet         = book<TH1F>("ptrel_ele_jet", "p_{T}^{rel}(e, jet)", 50, 0, 500);
  dRmin_mu1_jet         = book<TH1F>("dRmin_mu1_jet", "#DeltaR_{min}(#mu1, jet)", 60, 0, 3);
  dRmin_mu1_jet_scaled  = book<TH1F>("dRmin_mu1_jet_scaled", "#DeltaR_{min}(#mu1, jet) #times p_{T}^{jet 1}", 60, 0, 1000);
  dRmin_ele1_jet        = book<TH1F>("dRmin_ele1_jet", "#DeltaR_{min}(e1, jet)", 60, 0, 3);
  dRmin_ele1_jet_scaled = book<TH1F>("dRmin_ele1_jet_scaled", "#DeltaR_{min}(e1, jet) #times p_{T}^{jet 1}", 60, 0, 1000);
  ptrel_mu1_jet         = book<TH1F>("ptrel_mu1_jet", "p_{T}^{rel}(#mu1, jet)", 50, 0, 500);
  ptrel_ele1_jet        = book<TH1F>("ptrel_ele1_jet", "p_{T}^{rel}(e1, jet)", 50, 0, 500);

  dRmin_ptrel_mu    = book<TH2F>("dRmin_ptrel_mu", "#DeltaR_{min}(#mu, jet);p_{T}^{rel}(#mu, jet);p_{T}^{rel}(#mu, jet) vs. #DeltaR_{min}(#mu, jet)", 60, 0, 3, 50, 0, 500);
  dRmin_ptrel_mu1   = book<TH2F>("dRmin_ptrel_mu1", "#DeltaR_{min}(#mu1, jet);p_{T}^{rel}(#mu1, jet);p_{T}^{rel}(#mu1, jet) vs. #DeltaR_{min}(#mu1, jet)", 60, 0, 3, 50, 0, 500);
  dRmin_ptrel_ele   = book<TH2F>("dRmin_ptrel_ele", "#DeltaR_{min}(e, jet);p_{T}^{rel}(e, jet);p_{T}^{rel}(e, jet) vs. #DeltaR_{min}(e, jet)", 60, 0, 3, 50, 0, 500);
  dRmin_ptrel_ele1  = book<TH2F>("dRmin_ptrel_ele1", "#DeltaR_{min}(e1, jet);p_{T}^{rel}(e1, jet);p_{T}^{rel}(e1, jet) vs. #DeltaR_{min}(e1, jet)", 60, 0, 3, 50, 0, 500);

  // HOTVR jets
  N_HOTVRjets              = book<TH1F>("N_HOTVRjets", "N_{HOTVR jets}", 6, -0.5, 5.5);
  pt_HOTVRjet              = book<TH1F>("pt_HOTVRjet", "p_{T}^{HOTVR jets} [GeV]", 50, 0, 1500);
  pt_HOTVRjet1             = book<TH1F>("pt_HOTVRjet1", "p_{T}^{HOTVR jet 1} [GeV]", 50, 0, 1500);
  pt_HOTVRjet2             = book<TH1F>("pt_HOTVRjet2", "p_{T}^{HOTVR jet 2} [GeV]", 50, 0, 1500);
  pt_HOTVRjet3             = book<TH1F>("pt_HOTVRjet3", "p_{T}^{HOTVR jet 3} [GeV]", 50, 0, 1500);
  eta_HOTVRjet             = book<TH1F>("eta_HOTVRjet", "#eta^{HOTVR jets}", 50, -2.5, 2.5);
  eta_HOTVRjet1            = book<TH1F>("eta_HOTVRjet1", "#eta^{HOTVR jet 1}", 50, -2.5, 2.5);
  eta_HOTVRjet2            = book<TH1F>("eta_HOTVRjet2", "#eta^{HOTVR jet 2}", 50, -2.5, 2.5);
  eta_HOTVRjet3            = book<TH1F>("eta_HOTVRjet3", "#eta^{HOTVR jet 3}", 50, -2.5, 2.5);
  phi_HOTVRjet             = book<TH1F>("phi_HOTVRjet", "#phi^{HOTVR jets}", 35, -3.5, 3.5);
  phi_HOTVRjet1            = book<TH1F>("phi_HOTVRjet1", "#phi^{HOTVR jet 1}", 35, -3.5, 3.5);
  phi_HOTVRjet2            = book<TH1F>("phi_HOTVRjet2", "#phi^{HOTVR jet 2}", 35, -3.5, 3.5);
  phi_HOTVRjet3            = book<TH1F>("phi_HOTVRjet3", "#phi^{HOTVR jet 3}", 35, -3.5, 3.5);
  m_HOTVRjet               = book<TH1F>("m_HOTVRjet", "m^{HOTVR jets}", 50, 0, 500);
  m_HOTVRjet1              = book<TH1F>("m_HOTVRjet1", "m^{HOTVR jet 1}", 50, 0, 500);
  m_HOTVRjet2              = book<TH1F>("m_HOTVRjet2", "m^{HOTVR jet 2}", 50, 0, 500);
  m_HOTVRjet3              = book<TH1F>("m_HOTVRjet3", "m^{HOTVR jet 3}", 50, 0, 500);
  N_subjets_HOTVRjet       = book<TH1F>("N_subjets_HOTVRjet", "N_{subjets}^{HOTVR jets}", 6, -0.5, 5.5);
  N_subjets_HOTVRjet1      = book<TH1F>("N_subjets_HOTVRjet1", "N_{subjets}^{HOTVR jet 1}", 6, -0.5, 5.5);
  N_subjets_HOTVRjet2      = book<TH1F>("N_subjets_HOTVRjet2", "N_{subjets}^{HOTVR jet 2}", 6, -0.5, 5.5);
  N_subjets_HOTVRjet3      = book<TH1F>("N_subjets_HOTVRjet3", "N_{subjets}^{HOTVR jet 3}", 6, -0.5, 5.5);
  N_daughters_HOTVRjet     = book<TH1F>("N_daughters_HOTVRjet", "N_{daughters}^{HOTVR jets}", 51, -0.5, 50.5);
  N_daughters_HOTVRjet1    = book<TH1F>("N_daughters_HOTVRjet1", "N_{daughters}^{HOTVR jet 1}", 51, -0.5, 50.5);
  N_daughters_HOTVRjet2    = book<TH1F>("N_daughters_HOTVRjet2", "N_{daughters}^{HOTVR jet 2}", 51, -0.5, 50.5);
  N_daughters_HOTVRjet3    = book<TH1F>("N_daughters_HOTVRjet3", "N_{daughters}^{HOTVR jet 3}", 51, -0.5, 50.5);
  dRmin_AK8Puppi_HOTVRjet  = book<TH1F>("dRmin_AK8Puppi_HOTVRjet", "#DeltaR_{min}(HOTVR jet, AK8Puppi jet)", 60, 0, 3);
  dRmin_AK8Puppi_HOTVRjet1 = book<TH1F>("dRmin_AK8Puppi_HOTVRjet1", "#DeltaR_{min}(HOTVR jet 1, AK8Puppi jet)", 60, 0, 3);
  dRmin_AK8Puppi_HOTVRjet2 = book<TH1F>("dRmin_AK8Puppi_HOTVRjet2", "#DeltaR_{min}(HOTVR jet 2, AK8Puppi jet)", 60, 0, 3);
  dRmin_AK8Puppi_HOTVRjet3 = book<TH1F>("dRmin_AK8Puppi_HOTVRjet3", "#DeltaR_{min}(HOTVR jet 3, AK8Puppi jet)", 60, 0, 3);
  dRmin_mu_HOTVRjet        = book<TH1F>("dRmin_mu_HOTVRjet", "#DeltaR_{min}(HOTVR jet, #mu)", 60, 0, 3);
  dRmin_mu_HOTVRjet1       = book<TH1F>("dRmin_mu_HOTVRjet1", "#DeltaR_{min}(HOTVR jet 1, #mu)", 60, 0, 3);
  dRmin_mu_HOTVRjet2       = book<TH1F>("dRmin_mu_HOTVRjet2", "#DeltaR_{min}(HOTVR jet 2, #mu)", 60, 0, 3);
  dRmin_mu_HOTVRjet3       = book<TH1F>("dRmin_mu_HOTVRjet3", "#DeltaR_{min}(HOTVR jet 3, #mu)", 60, 0, 3);
  tau1_HOTVRjet            = book<TH1F>("tau1_HOTVRjet", "#tau_{1}^{HOTVR jets}", 24, 0, 1.2);
  tau1_HOTVRjet1           = book<TH1F>("tau1_HOTVRjet1", "#tau_{1}^{HOTVR jet 1}", 24, 0, 1.2);
  tau1_HOTVRjet2           = book<TH1F>("tau1_HOTVRjet2", "#tau_{1}^{HOTVR jet 2}", 24, 0, 1.2);
  tau1_HOTVRjet3           = book<TH1F>("tau1_HOTVRjet3", "#tau_{1}^{HOTVR jet 3}", 24, 0, 1.2);
  tau2_HOTVRjet            = book<TH1F>("tau2_HOTVRjet", "#tau_{2}^{HOTVR jets}", 24, 0, 1.2);
  tau2_HOTVRjet1           = book<TH1F>("tau2_HOTVRjet1", "#tau_{2}^{HOTVR jet 1}", 24, 0, 1.2);
  tau2_HOTVRjet2           = book<TH1F>("tau2_HOTVRjet2", "#tau_{2}^{HOTVR jet 2}", 24, 0, 1.2);
  tau2_HOTVRjet3           = book<TH1F>("tau2_HOTVRjet3", "#tau_{2}^{HOTVR jet 3}", 24, 0, 1.2);
  tau3_HOTVRjet            = book<TH1F>("tau3_HOTVRjet", "#tau_{3}^{HOTVR jets}", 24, 0, 1.2);
  tau3_HOTVRjet1           = book<TH1F>("tau3_HOTVRjet1", "#tau_{3}^{HOTVR jet 1}", 24, 0, 1.2);
  tau3_HOTVRjet2           = book<TH1F>("tau3_HOTVRjet2", "#tau_{3}^{HOTVR jet 2}", 24, 0, 1.2);
  tau3_HOTVRjet3           = book<TH1F>("tau3_HOTVRjet3", "#tau_{3}^{HOTVR jet 3}", 24, 0, 1.2);
  tau21_HOTVRjet           = book<TH1F>("tau21_HOTVRjet", "#tau_{2/1}^{HOTVR jets}", 24, 0, 1.2);
  tau21_HOTVRjet1          = book<TH1F>("tau21_HOTVRjet1", "#tau_{2/1}^{HOTVR jet 1}", 24, 0, 1.2);
  tau21_HOTVRjet2          = book<TH1F>("tau21_HOTVRjet2", "#tau_{2/1}^{HOTVR jet 2}", 24, 0, 1.2);
  tau21_HOTVRjet3          = book<TH1F>("tau21_HOTVRjet3", "#tau_{2/1}^{HOTVR jet 3}", 24, 0, 1.2);
  tau32_HOTVRjet           = book<TH1F>("tau32_HOTVRjet", "#tau_{3/2}^{HOTVR jets}", 24, 0, 1.2);
  tau32_HOTVRjet1          = book<TH1F>("tau32_HOTVRjet1", "#tau_{3/2}^{HOTVR jet 1}", 24, 0, 1.2);
  tau32_HOTVRjet2          = book<TH1F>("tau32_HOTVRjet2", "#tau_{3/2}^{HOTVR jet 2}", 24, 0, 1.2);
  tau32_HOTVRjet3          = book<TH1F>("tau32_HOTVRjet3", "#tau_{3/2}^{HOTVR jet 3}", 24, 0, 1.2);

  // AK8Puppi jets
  N_AK8Puppijets            = book<TH1F>("N_AK8Puppijets", "N_{AK8Puppi jets}", 6, -0.5, 5.5);
  pt_AK8Puppijet            = book<TH1F>("pt_AK8Puppijet", "p_{T}^{AK8Puppi jets} [GeV]", 50, 0, 1500);
  pt_AK8Puppijet1           = book<TH1F>("pt_AK8Puppijet1", "p_{T}^{AK8Puppi jet 1} [GeV]", 50, 0, 1500);
  pt_AK8Puppijet2           = book<TH1F>("pt_AK8Puppijet2", "p_{T}^{AK8Puppi jet 2} [GeV]", 50, 0, 1500);
  pt_AK8Puppijet3           = book<TH1F>("pt_AK8Puppijet3", "p_{T}^{AK8Puppi jet 3} [GeV]", 50, 0, 1500);
  eta_AK8Puppijet           = book<TH1F>("eta_AK8Puppijet", "#eta^{AK8Puppi jets}", 50, -2.5, 2.5);
  eta_AK8Puppijet1          = book<TH1F>("eta_AK8Puppijet1", "#eta^{AK8Puppi jet 1}", 50, -2.5, 2.5);
  eta_AK8Puppijet2          = book<TH1F>("eta_AK8Puppijet2", "#eta^{AK8Puppi jet 2}", 50, -2.5, 2.5);
  eta_AK8Puppijet3          = book<TH1F>("eta_AK8Puppijet3", "#eta^{AK8Puppi jet 3}", 50, -2.5, 2.5);
  phi_AK8Puppijet           = book<TH1F>("phi_AK8Puppijet", "#phi^{AK8Puppi jets}", 35, -3.5, 3.5);
  phi_AK8Puppijet1          = book<TH1F>("phi_AK8Puppijet1", "#phi^{AK8Puppi jet 1}", 35, -3.5, 3.5);
  phi_AK8Puppijet2          = book<TH1F>("phi_AK8Puppijet2", "#phi^{AK8Puppi jet 2}", 35, -3.5, 3.5);
  phi_AK8Puppijet3          = book<TH1F>("phi_AK8Puppijet3", "#phi^{AK8Puppi jet 3}", 35, -3.5, 3.5);
  mSD_AK8Puppijet           = book<TH1F>("mSD_AK8Puppijet", "m_{SD}^{AK8Puppi jets}", 50, 0, 500);
  mSD_AK8Puppijet1          = book<TH1F>("mSD_AK8Puppijet1", "m_{SD}^{AK8Puppi jet 1}", 50, 0, 500);
  mSD_AK8Puppijet2          = book<TH1F>("mSD_AK8Puppijet2", "m_{SD}^{AK8Puppi jet 2}", 50, 0, 500);
  mSD_AK8Puppijet3          = book<TH1F>("mSD_AK8Puppijet3", "m_{SD}^{AK8Puppi jet 3}", 50, 0, 500);
  N_subjets_AK8Puppijet     = book<TH1F>("N_subjets_AK8Puppijet", "N_{subjets}^{AK8Puppi jets}", 6, -0.5, 5.5);
  N_subjets_AK8Puppijet1    = book<TH1F>("N_subjets_AK8Puppijet1", "N_{subjets}^{AK8Puppi jet 1}", 6, -0.5, 5.5);
  N_subjets_AK8Puppijet2    = book<TH1F>("N_subjets_AK8Puppijet2", "N_{subjets}^{AK8Puppi jet 2}", 6, -0.5, 5.5);
  N_subjets_AK8Puppijet3    = book<TH1F>("N_subjets_AK8Puppijet3", "N_{subjets}^{AK8Puppi jet 3}", 6, -0.5, 5.5);
  N_daughters_AK8Puppijet   = book<TH1F>("N_daughters_AK8Puppijet", "N_{daughters}^{AK8Puppi jets}", 51, -0.5, 50.5);
  N_daughters_AK8Puppijet1  = book<TH1F>("N_daughters_AK8Puppijet1", "N_{daughters}^{AK8Puppi jet 1}", 51, -0.5, 50.5);
  N_daughters_AK8Puppijet2  = book<TH1F>("N_daughters_AK8Puppijet2", "N_{daughters}^{AK8Puppi jet 2}", 51, -0.5, 50.5);
  N_daughters_AK8Puppijet3  = book<TH1F>("N_daughters_AK8Puppijet3", "N_{daughters}^{AK8Puppi jet 3}", 51, -0.5, 50.5);
  dRmin_AK8_AK8Puppijet     = book<TH1F>("dRmin_AK8_AK8Puppijet", "#DeltaR_{min}(AK8Puppi jet, AK8 jet)", 60, 0, 3);
  dRmin_AK8_AK8Puppijet1    = book<TH1F>("dRmin_AK8_AK8Puppijet1", "#DeltaR_{min}(AK8Puppi jet 1, AK8 jet)", 60, 0, 3);
  dRmin_AK8_AK8Puppijet2    = book<TH1F>("dRmin_AK8_AK8Puppijet2", "#DeltaR_{min}(AK8Puppi jet 2, AK8 jet)", 60, 0, 3);
  dRmin_AK8_AK8Puppijet3    = book<TH1F>("dRmin_AK8_AK8Puppijet3", "#DeltaR_{min}(AK8Puppi jet 3, AK8 jet)", 60, 0, 3);
  dRmin_mu_AK8Puppijet      = book<TH1F>("dRmin_mu_AK8Puppijet", "#DeltaR_{min}(AK8Puppi jet, #mu)", 60, 0, 3);
  dRmin_mu_AK8Puppijet1     = book<TH1F>("dRmin_mu_AK8Puppijet1", "#DeltaR_{min}(AK8Puppi jet 1, #mu)", 60, 0, 3);
  dRmin_mu_AK8Puppijet2     = book<TH1F>("dRmin_mu_AK8Puppijet2", "#DeltaR_{min}(AK8Puppi jet 2, #mu)", 60, 0, 3);
  dRmin_mu_AK8Puppijet3     = book<TH1F>("dRmin_mu_AK8Puppijet3", "#DeltaR_{min}(AK8Puppi jet 3, #mu)", 60, 0, 3);
  tau1_AK8Puppijet          = book<TH1F>("tau1_AK8Puppijet", "#tau_{1}^{AK8Puppi jets}", 24, 0, 1.2);
  tau1_AK8Puppijet1         = book<TH1F>("tau1_AK8Puppijet1", "#tau_{1}^{AK8Puppi jet 1}", 24, 0, 1.2);
  tau1_AK8Puppijet2         = book<TH1F>("tau1_AK8Puppijet2", "#tau_{1}^{AK8Puppi jet 2}", 24, 0, 1.2);
  tau1_AK8Puppijet3         = book<TH1F>("tau1_AK8Puppijet3", "#tau_{1}^{AK8Puppi jet 3}", 24, 0, 1.2);
  tau2_AK8Puppijet          = book<TH1F>("tau2_AK8Puppijet", "#tau_{2}^{AK8Puppi jets}", 24, 0, 1.2);
  tau2_AK8Puppijet1         = book<TH1F>("tau2_AK8Puppijet1", "#tau_{2}^{AK8Puppi jet 1}", 24, 0, 1.2);
  tau2_AK8Puppijet2         = book<TH1F>("tau2_AK8Puppijet2", "#tau_{2}^{AK8Puppi jet 2}", 24, 0, 1.2);
  tau2_AK8Puppijet3         = book<TH1F>("tau2_AK8Puppijet3", "#tau_{2}^{AK8Puppi jet 3}", 24, 0, 1.2);
  tau3_AK8Puppijet          = book<TH1F>("tau3_AK8Puppijet", "#tau_{3}^{AK8Puppi jets}", 24, 0, 1.2);
  tau3_AK8Puppijet1         = book<TH1F>("tau3_AK8Puppijet1", "#tau_{3}^{AK8Puppi jet 1}", 24, 0, 1.2);
  tau3_AK8Puppijet2         = book<TH1F>("tau3_AK8Puppijet2", "#tau_{3}^{AK8Puppi jet 2}", 24, 0, 1.2);
  tau3_AK8Puppijet3         = book<TH1F>("tau3_AK8Puppijet3", "#tau_{3}^{AK8Puppi jet 3}", 24, 0, 1.2);
  tau21_AK8Puppijet         = book<TH1F>("tau21_AK8Puppijet", "#tau_{2/1}^{AK8Puppi jets}", 24, 0, 1.2);
  tau21_AK8Puppijet1        = book<TH1F>("tau21_AK8Puppijet1", "#tau_{2/1}^{AK8Puppi jet 1}", 24, 0, 1.2);
  tau21_AK8Puppijet2        = book<TH1F>("tau21_AK8Puppijet2", "#tau_{2/1}^{AK8Puppi jet 2}", 24, 0, 1.2);
  tau21_AK8Puppijet3        = book<TH1F>("tau21_AK8Puppijet3", "#tau_{2/1}^{AK8Puppi jet 3}", 24, 0, 1.2);
  tau32_AK8Puppijet         = book<TH1F>("tau32_AK8Puppijet", "#tau_{3/2}^{AK8Puppi jets}", 24, 0, 1.2);
  tau32_AK8Puppijet1        = book<TH1F>("tau32_AK8Puppijet1", "#tau_{3/2}^{AK8Puppi jet 1}", 24, 0, 1.2);
  tau32_AK8Puppijet2        = book<TH1F>("tau32_AK8Puppijet2", "#tau_{3/2}^{AK8Puppi jet 2}", 24, 0, 1.2);
  tau32_AK8Puppijet3        = book<TH1F>("tau32_AK8Puppijet3", "#tau_{3/2}^{AK8Puppi jet 3}", 24, 0, 1.2);

  // general
  NPV               = book<TH1F>("NPV", "number of primary vertices", 91, -0.50, 90.5);
  MET               = book<TH1F>("MET", "missing E_{T} [GeV]", 50, 0, 7000);
  MET_rebin         = book<TH1F>("MET_rebin", "missing E_{T} [GeV]", 50, 0, 1500);
  MET_rebin2        = book<TH1F>("MET_rebin2", "missing E_{T} [GeV]", 30, 0, 1500);
  MET_rebin3        = book<TH1F>("MET_rebin3", "missing E_{T} [GeV]", 15, 0, 1500);
  ST                = book<TH1F>("ST", "S_{T} [GeV]", 50, 0, 7000);
  ST_rebin          = book<TH1F>("ST_rebin", "S_{T} [GeV]", 200, 0, 5000);
  ST_rebin2         = book<TH1F>("ST_rebin2", "S_{T} [GeV]", 100, 0, 5000);
  ST_rebin3         = book<TH1F>("ST_rebin3", "S_{T} [GeV]", 50, 0, 5000);
  STjets            = book<TH1F>("STjets", "S_{T}^{jets} [GeV]", 50, 0, 7000);
  STjets_rebin      = book<TH1F>("STjets_rebin", "S_{T}^{jets} [GeV]", 200, 0, 5000);
  STjets_rebin2     = book<TH1F>("STjets_rebin2", "S_{T}^{jets} [GeV]", 100, 0, 5000);
  STjets_rebin3     = book<TH1F>("STjets_rebin3", "S_{T}^{jets} [GeV]", 50, 0, 5000);
  STlep             = book<TH1F>("STlep", "S_{T}^{lep} [GeV]", 50, 0, 7000);
  STlep_rebin       = book<TH1F>("STlep_rebin", "S_{T}^{lep} [GeV]", 50, 0, 1500);
  STlep_rebin2      = book<TH1F>("STlep_rebin2", "S_{T}^{lep} [GeV]", 30, 0, 1500);
  STlep_rebin3      = book<TH1F>("STlep_rebin3", "S_{T}^{lep} [GeV]", 15, 0, 1500);

  // Sphericity tensor
  S11 = book<TH1F>("S11", "S_{11}", 50, 0, 1);
  S12 = book<TH1F>("S12", "S_{12}", 50, 0, 1);
  S13 = book<TH1F>("S13", "S_{13}", 50, 0, 1);
  S22 = book<TH1F>("S22", "S_{22}", 50, 0, 1);
  S23 = book<TH1F>("S23", "S_{23}", 50, 0, 1);
  S33 = book<TH1F>("S33", "S_{33}", 50, 0, 1);

  sum_event_weights = book<TH1F>("sum_event_weights", "counting experiment", 1, 0.5, 1.5);

  // calculate sum of event weights with PDF replicas
  for(int i=0; i<100; i++){
    std::stringstream ss_name;
    ss_name << "sum_event_weights_PDF_" << i+1;

    stringstream ss_title;
    ss_title << "counting experiment for PDF No. "  << i+1 << " out of 100" ;

    std::string s_name = ss_name.str();
    std::string s_title = ss_title.str();
    const char* char_name = s_name.c_str();
    const char* char_title = s_title.c_str();

    hist_names[i] = s_name;

    book<TH1F>(char_name, char_title,  1, 0.5, 1.5);

  }

}


void ZprimeSemiLeptonicPreselectionHists::fill(const Event & event){

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
    if(i==0){
      pt_jet1->Fill(jets->at(i).pt(),weight);
      eta_jet1->Fill(jets->at(i).eta(),weight);
      phi_jet1->Fill(jets->at(i).phi(),weight);
      m_jet1->Fill(jets->at(i).v4().M(),weight);
    }
    else if(i==1){
      pt_jet2->Fill(jets->at(i).pt(),weight);
      eta_jet2->Fill(jets->at(i).eta(),weight);
      phi_jet2->Fill(jets->at(i).phi(),weight);
      m_jet2->Fill(jets->at(i).v4().M(),weight);
    }
    else if(i==2){
      pt_jet3->Fill(jets->at(i).pt(),weight);
      eta_jet3->Fill(jets->at(i).eta(),weight);
      phi_jet3->Fill(jets->at(i).phi(),weight);
      m_jet3->Fill(jets->at(i).v4().M(),weight);
    }
  }


  /*
  █ ██   ██    █████  ██████ ██    ██   █████
  █ ██   ██  ██     ██  ██   ██    ██   ██  ██
  █ ███████  ██     ██  ██    ██  ██    █████
  █ ██   ██  ██     ██  ██     ████     ██  ██
  █ ██   ██    █████    ██      ██      ██   ██
  */

  vector<TopJet>* HOTVRjets = event.topjets;
  unsigned int NHOTVRjets = HOTVRjets->size();
  N_HOTVRjets->Fill(NHOTVRjets, weight);

  for(unsigned int i=0; i<NHOTVRjets; i++){
    double tau21 = HOTVRjets->at(i).tau2_groomed() / HOTVRjets->at(i).tau1_groomed();
    double tau32 = HOTVRjets->at(i).tau3_groomed() / HOTVRjets->at(i).tau2_groomed();

    // Distance to AK8 Puppi
    double dRmin_Puppi = 99999;
    for(unsigned int j=0; j<event.toppuppijets->size(); j++){
      double dR = deltaR(HOTVRjets->at(i), event.toppuppijets->at(j));
      if(dR < dRmin_Puppi) dRmin_Puppi = dR;
    }

    // Distance to muons
    double dRmin_muon = 99999;
    for(unsigned int j=0; j<event.muons->size(); j++){
      double dR = deltaR(HOTVRjets->at(i), event.muons->at(j));
      if(dR < dRmin_muon) dRmin_muon = dR;
    }

    pt_HOTVRjet->Fill(HOTVRjets->at(i).pt(), weight);
    eta_HOTVRjet->Fill(HOTVRjets->at(i).eta(), weight);
    phi_HOTVRjet->Fill(HOTVRjets->at(i).phi(), weight);
    m_HOTVRjet->Fill(HOTVRjets->at(i).v4().M(), weight);
    dRmin_AK8Puppi_HOTVRjet->Fill(dRmin_Puppi, weight);
    dRmin_mu_HOTVRjet->Fill(dRmin_muon, weight);
    N_subjets_HOTVRjet->Fill(HOTVRjets->at(i).subjets().size(), weight);
    N_daughters_HOTVRjet->Fill(HOTVRjets->at(i).numberOfDaughters(), weight);
    tau1_HOTVRjet->Fill(HOTVRjets->at(i).tau1_groomed(), weight);
    tau2_HOTVRjet->Fill(HOTVRjets->at(i).tau2_groomed(), weight);
    tau3_HOTVRjet->Fill(HOTVRjets->at(i).tau3_groomed(), weight);
    tau21_HOTVRjet->Fill(tau21, weight);
    tau32_HOTVRjet->Fill(tau32, weight);

    if(i==0){
      pt_HOTVRjet1->Fill(HOTVRjets->at(i).pt(), weight);
      eta_HOTVRjet1->Fill(HOTVRjets->at(i).eta(), weight);
      phi_HOTVRjet1->Fill(HOTVRjets->at(i).phi(), weight);
      m_HOTVRjet1->Fill(HOTVRjets->at(i).v4().M(), weight);
      dRmin_AK8Puppi_HOTVRjet1->Fill(dRmin_Puppi, weight);
      dRmin_mu_HOTVRjet1->Fill(dRmin_muon, weight);
      N_subjets_HOTVRjet1->Fill(HOTVRjets->at(i).subjets().size(), weight);
      N_daughters_HOTVRjet1->Fill(HOTVRjets->at(i).numberOfDaughters(), weight);
      tau1_HOTVRjet1->Fill(HOTVRjets->at(i).tau1_groomed(), weight);
      tau2_HOTVRjet1->Fill(HOTVRjets->at(i).tau2_groomed(), weight);
      tau3_HOTVRjet1->Fill(HOTVRjets->at(i).tau3_groomed(), weight);
      tau21_HOTVRjet1->Fill(tau21, weight);
      tau32_HOTVRjet1->Fill(tau32, weight);
    }
    else if(i==1){
      pt_HOTVRjet2->Fill(HOTVRjets->at(i).pt(), weight);
      eta_HOTVRjet2->Fill(HOTVRjets->at(i).eta(), weight);
      phi_HOTVRjet2->Fill(HOTVRjets->at(i).phi(), weight);
      m_HOTVRjet2->Fill(HOTVRjets->at(i).v4().M(), weight);
      dRmin_AK8Puppi_HOTVRjet2->Fill(dRmin_Puppi, weight);
      dRmin_mu_HOTVRjet2->Fill(dRmin_muon, weight);
      N_subjets_HOTVRjet2->Fill(HOTVRjets->at(i).subjets().size(), weight);
      N_daughters_HOTVRjet2->Fill(HOTVRjets->at(i).numberOfDaughters(), weight);
      tau1_HOTVRjet2->Fill(HOTVRjets->at(i).tau1_groomed(), weight);
      tau2_HOTVRjet2->Fill(HOTVRjets->at(i).tau2_groomed(), weight);
      tau3_HOTVRjet2->Fill(HOTVRjets->at(i).tau3_groomed(), weight);
      tau21_HOTVRjet2->Fill(tau21, weight);
      tau32_HOTVRjet2->Fill(tau32, weight);
    }
    else if(i==2){
      pt_HOTVRjet3->Fill(HOTVRjets->at(i).pt(), weight);
      eta_HOTVRjet3->Fill(HOTVRjets->at(i).eta(), weight);
      phi_HOTVRjet3->Fill(HOTVRjets->at(i).phi(), weight);
      m_HOTVRjet3->Fill(HOTVRjets->at(i).v4().M(), weight);
      dRmin_AK8Puppi_HOTVRjet3->Fill(dRmin_Puppi, weight);
      dRmin_mu_HOTVRjet3->Fill(dRmin_muon, weight);
      N_subjets_HOTVRjet3->Fill(HOTVRjets->at(i).subjets().size(), weight);
      N_daughters_HOTVRjet3->Fill(HOTVRjets->at(i).numberOfDaughters(), weight);
      tau1_HOTVRjet3->Fill(HOTVRjets->at(i).tau1_groomed(), weight);
      tau2_HOTVRjet3->Fill(HOTVRjets->at(i).tau2_groomed(), weight);
      tau3_HOTVRjet3->Fill(HOTVRjets->at(i).tau3_groomed(), weight);
      tau21_HOTVRjet3->Fill(tau21, weight);
      tau32_HOTVRjet3->Fill(tau32, weight);
    }
  }


  /*
  █  █████  ██   ██  █████  ██████  ██    ██ ██████  ██████  ██
  █ ██   ██ ██  ██  ██   ██ ██   ██ ██    ██ ██   ██ ██   ██ ██
  █ ███████ █████    █████  ██████  ██    ██ ██████  ██████  ██
  █ ██   ██ ██  ██  ██   ██ ██      ██    ██ ██      ██      ██
  █ ██   ██ ██   ██  █████  ██       ██████  ██      ██      ██
  */

  vector<TopJet>* AK8Puppijets = event.toppuppijets;
  unsigned int NAK8Puppijets = 0;
  for(unsigned int i=0; i<AK8Puppijets->size(); i++){
    if(AK8Puppijets->at(i).numberOfDaughters()<2) continue;
    NAK8Puppijets++;

    double tau21 = AK8Puppijets->at(i).tau2() / AK8Puppijets->at(i).tau1();
    double tau32 = AK8Puppijets->at(i).tau3() / AK8Puppijets->at(i).tau2();

    // Distance to AK8
    double dRmin_ak8 = 99999;
    for(unsigned int j=0; j<event.topjets->size(); j++){
      double dR = deltaR(AK8Puppijets->at(i), event.topjets->at(j));
      if(dR < dRmin_ak8) dRmin_ak8 = dR;
    }

    // Distance to muons
    double dRmin_muon = 99999;
    for(unsigned int j=0; j<event.muons->size(); j++){
      double dR = deltaR(AK8Puppijets->at(i), event.muons->at(j));
      if(dR < dRmin_muon) dRmin_muon = dR;
    }

    pt_AK8Puppijet->Fill(AK8Puppijets->at(i).pt(), weight);
    eta_AK8Puppijet->Fill(AK8Puppijets->at(i).eta(), weight);
    phi_AK8Puppijet->Fill(AK8Puppijets->at(i).phi(), weight);
    mSD_AK8Puppijet->Fill(AK8Puppijets->at(i).softdropmass(), weight);
    dRmin_AK8_AK8Puppijet->Fill(dRmin_ak8, weight);
    dRmin_mu_AK8Puppijet->Fill(dRmin_muon, weight);
    N_subjets_AK8Puppijet->Fill(AK8Puppijets->at(i).subjets().size(), weight);
    N_daughters_AK8Puppijet->Fill(AK8Puppijets->at(i).numberOfDaughters(), weight);
    tau1_AK8Puppijet->Fill(AK8Puppijets->at(i).tau1(), weight);
    tau2_AK8Puppijet->Fill(AK8Puppijets->at(i).tau2(), weight);
    tau3_AK8Puppijet->Fill(AK8Puppijets->at(i).tau3(), weight);
    tau21_AK8Puppijet->Fill(tau21, weight);
    tau32_AK8Puppijet->Fill(tau32, weight);

    if(i==0){
      pt_AK8Puppijet1->Fill(AK8Puppijets->at(i).pt(), weight);
      eta_AK8Puppijet1->Fill(AK8Puppijets->at(i).eta(), weight);
      phi_AK8Puppijet1->Fill(AK8Puppijets->at(i).phi(), weight);
      mSD_AK8Puppijet1->Fill(AK8Puppijets->at(i).softdropmass(), weight);
      dRmin_AK8_AK8Puppijet1->Fill(dRmin_ak8, weight);
      dRmin_mu_AK8Puppijet1->Fill(dRmin_muon, weight);
      N_subjets_AK8Puppijet1->Fill(AK8Puppijets->at(i).subjets().size(), weight);
      N_daughters_AK8Puppijet1->Fill(AK8Puppijets->at(i).numberOfDaughters(), weight);
      tau1_AK8Puppijet1->Fill(AK8Puppijets->at(i).tau1(), weight);
      tau2_AK8Puppijet1->Fill(AK8Puppijets->at(i).tau2(), weight);
      tau3_AK8Puppijet1->Fill(AK8Puppijets->at(i).tau3(), weight);
      tau21_AK8Puppijet1->Fill(tau21, weight);
      tau32_AK8Puppijet1->Fill(tau32, weight);
    }
    else if(i==1){
      pt_AK8Puppijet2->Fill(AK8Puppijets->at(i).pt(), weight);
      eta_AK8Puppijet2->Fill(AK8Puppijets->at(i).eta(), weight);
      phi_AK8Puppijet2->Fill(AK8Puppijets->at(i).phi(), weight);
      mSD_AK8Puppijet2->Fill(AK8Puppijets->at(i).softdropmass(), weight);
      dRmin_AK8_AK8Puppijet2->Fill(dRmin_ak8, weight);
      dRmin_mu_AK8Puppijet2->Fill(dRmin_muon, weight);
      N_subjets_AK8Puppijet2->Fill(AK8Puppijets->at(i).subjets().size(), weight);
      N_daughters_AK8Puppijet2->Fill(AK8Puppijets->at(i).numberOfDaughters(), weight);
      tau1_AK8Puppijet2->Fill(AK8Puppijets->at(i).tau1(), weight);
      tau2_AK8Puppijet2->Fill(AK8Puppijets->at(i).tau2(), weight);
      tau3_AK8Puppijet2->Fill(AK8Puppijets->at(i).tau3(), weight);
      tau21_AK8Puppijet2->Fill(tau21, weight);
      tau32_AK8Puppijet2->Fill(tau32, weight);
    }
    else if(i==2){
      pt_AK8Puppijet3->Fill(AK8Puppijets->at(i).pt(), weight);
      eta_AK8Puppijet3->Fill(AK8Puppijets->at(i).eta(), weight);
      phi_AK8Puppijet3->Fill(AK8Puppijets->at(i).phi(), weight);
      mSD_AK8Puppijet3->Fill(AK8Puppijets->at(i).softdropmass(), weight);
      dRmin_AK8_AK8Puppijet3->Fill(dRmin_ak8, weight);
      dRmin_mu_AK8Puppijet3->Fill(dRmin_muon, weight);
      N_subjets_AK8Puppijet3->Fill(AK8Puppijets->at(i).subjets().size(), weight);
      N_daughters_AK8Puppijet3->Fill(AK8Puppijets->at(i).numberOfDaughters(), weight);
      tau1_AK8Puppijet3->Fill(AK8Puppijets->at(i).tau1(), weight);
      tau2_AK8Puppijet3->Fill(AK8Puppijets->at(i).tau2(), weight);
      tau3_AK8Puppijet3->Fill(AK8Puppijets->at(i).tau3(), weight);
      tau21_AK8Puppijet3->Fill(tau21, weight);
      tau32_AK8Puppijet3->Fill(tau32, weight);
    }
  }



  /*
  ███    ███ ██    ██  ██████  ███    ██ ███████
  ████  ████ ██    ██ ██    ██ ████   ██ ██
  ██ ████ ██ ██    ██ ██    ██ ██ ██  ██ ███████
  ██  ██  ██ ██    ██ ██    ██ ██  ██ ██      ██
  ██      ██  ██████   ██████  ██   ████ ███████
  */


  vector<Muon>* muons = event.muons;
  int Nmuons = muons->size();
  N_mu->Fill(Nmuons, weight);

  for(int i=0; i<Nmuons; i++){

    pt_mu->Fill(muons->at(i).pt(),weight);
    eta_mu->Fill(muons->at(i).eta(),weight);
    phi_mu->Fill(muons->at(i).phi(),weight);
    reliso_mu->Fill(muons->at(i).relIso(),weight);
    reliso_mu_rebin->Fill(muons->at(i).relIso(),weight);
    if(muons->at(i).has_tag(Muon::twodcut_dRmin) && muons->at(i).has_tag(Muon::twodcut_pTrel)){
      dRmin_mu_jet->Fill(muons->at(i).get_tag(Muon::twodcut_dRmin), weight);
      if(event.jets->size() > 0) dRmin_mu_jet_scaled->Fill(muons->at(i).get_tag(Muon::twodcut_dRmin)*event.jets->at(0).pt(), weight);
      ptrel_mu_jet->Fill(muons->at(i).get_tag(Muon::twodcut_pTrel), weight);
      dRmin_ptrel_mu->Fill(muons->at(i).get_tag(Muon::twodcut_dRmin), muons->at(i).get_tag(Muon::twodcut_pTrel), weight);
    }
    if(i==0){
      pt_mu1->Fill(muons->at(i).pt(),weight);
      eta_mu1->Fill(muons->at(i).eta(),weight);
      phi_mu1->Fill(muons->at(i).phi(),weight);
      reliso_mu1->Fill(muons->at(i).relIso(),weight);
      reliso_mu1_rebin->Fill(muons->at(i).relIso(),weight);
      if(muons->at(i).has_tag(Muon::twodcut_dRmin) && muons->at(i).has_tag(Muon::twodcut_pTrel)){
        dRmin_mu1_jet->Fill(muons->at(i).get_tag(Muon::twodcut_dRmin), weight);
        if(event.jets->size() > 0) dRmin_mu1_jet_scaled->Fill(muons->at(i).get_tag(Muon::twodcut_dRmin)*event.jets->at(0).pt(), weight);
        ptrel_mu1_jet->Fill(muons->at(i).get_tag(Muon::twodcut_pTrel), weight);
        dRmin_ptrel_mu1->Fill(muons->at(i).get_tag(Muon::twodcut_dRmin), muons->at(i).get_tag(Muon::twodcut_pTrel), weight);
      }
    }
    else if(i==1){
      pt_mu2->Fill(muons->at(i).pt(),weight);
      eta_mu2->Fill(muons->at(i).eta(),weight);
      phi_mu2->Fill(muons->at(i).phi(),weight);
      reliso_mu2->Fill(muons->at(i).relIso(),weight);
      reliso_mu2_rebin->Fill(muons->at(i).relIso(),weight);
    }
  }

  for(int i=0; i<Nmuons; i++){
    for(int j=0; j<Nmuons; j++){
      if(j <= i) continue;
      M_mumu->Fill((muons->at(i).v4() + muons->at(j).v4()).M() ,weight);
    }
  }

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
    reliso_ele->Fill(electrons->at(i).relIso(),weight);
    reliso_ele_rebin->Fill(electrons->at(i).relIso(),weight);
    if(electrons->at(i).has_tag(Electron::twodcut_dRmin) && electrons->at(i).has_tag(Electron::twodcut_pTrel)){
      dRmin_ele_jet->Fill(electrons->at(i).get_tag(Electron::twodcut_dRmin), weight);
      if(event.jets->size() > 0) dRmin_ele_jet_scaled->Fill(electrons->at(i).get_tag(Electron::twodcut_dRmin)*event.jets->at(0).pt(), weight);
      ptrel_ele_jet->Fill(electrons->at(i).get_tag(Electron::twodcut_pTrel), weight);
      dRmin_ptrel_ele->Fill(electrons->at(i).get_tag(Electron::twodcut_dRmin), electrons->at(i).get_tag(Electron::twodcut_pTrel), weight);
    }
    if(i==0){
      pt_ele1->Fill(electrons->at(i).pt(),weight);
      eta_ele1->Fill(electrons->at(i).eta(),weight);
      phi_ele1->Fill(electrons->at(i).phi(),weight);
      reliso_ele1->Fill(electrons->at(i).relIso(),weight);
      reliso_ele1_rebin->Fill(electrons->at(i).relIso(),weight);
      if(electrons->at(i).has_tag(Electron::twodcut_dRmin) && electrons->at(i).has_tag(Electron::twodcut_pTrel)){
        dRmin_ele1_jet->Fill(electrons->at(i).get_tag(Electron::twodcut_dRmin), weight);
        if(event.jets->size() > 0) dRmin_ele1_jet_scaled->Fill(electrons->at(i).get_tag(Electron::twodcut_dRmin)*event.jets->at(0).pt(), weight);
        ptrel_ele1_jet->Fill(electrons->at(i).get_tag(Electron::twodcut_pTrel), weight);
        dRmin_ptrel_ele1->Fill(electrons->at(i).get_tag(Electron::twodcut_dRmin), electrons->at(i).get_tag(Electron::twodcut_pTrel), weight);
      }
    }
    else if(i==1){
      pt_ele2->Fill(electrons->at(i).pt(),weight);
      eta_ele2->Fill(electrons->at(i).eta(),weight);
      phi_ele2->Fill(electrons->at(i).phi(),weight);
      reliso_ele2->Fill(electrons->at(i).relIso(),weight);
      reliso_ele2_rebin->Fill(electrons->at(i).relIso(),weight);
    }
  }

  for(int i=0; i<Nelectrons; i++){
    for(int j=0; j<Nelectrons; j++){
      if(j <= i) continue;
      M_ee->Fill((electrons->at(i).v4() + electrons->at(j).v4()).M() ,weight);
    }
  }


  /*
  ██████  ███████ ███    ██ ███████ ██████   █████  ██
  ██      ██      ████   ██ ██      ██   ██ ██   ██ ██
  ██  ███ █████   ██ ██  ██ █████   ██████  ███████ ██
  ██   ██ ██      ██  ██ ██ ██      ██   ██ ██   ██ ██
  ██████  ███████ ██   ████ ███████ ██   ██ ██   ██ ███████
  */



  int Npvs = event.pvs->size();
  NPV->Fill(Npvs, weight);

  double met = event.met->pt();
  double st = 0., st_jets = 0., st_lep = 0.;
  for(const auto & jet : *jets)           st_jets += jet.pt();
  for(const auto & electron : *electrons) st_lep += electron.pt();
  for(const auto & muon : *muons)         st_lep += muon.pt();
  st = st_jets + st_lep + met;

  MET->Fill(met, weight);
  MET_rebin->Fill(met, weight);
  MET_rebin2->Fill(met, weight);
  MET_rebin3->Fill(met, weight);
  ST->Fill(st, weight);
  ST_rebin->Fill(st, weight);
  ST_rebin2->Fill(st, weight);
  ST_rebin3->Fill(st, weight);
  STjets->Fill(st_jets, weight);
  STjets_rebin->Fill(st_jets, weight);
  STjets_rebin2->Fill(st_jets, weight);
  STjets_rebin3->Fill(st_jets, weight);
  STlep->Fill(st_lep, weight);
  STlep_rebin->Fill(st_lep, weight);
  STlep_rebin2->Fill(st_lep, weight);
  STlep_rebin3->Fill(st_lep, weight);

  // Sphericity tensor
  double s11 = -1., s12 = -1., s13 = -1., s22 = -1., s23 = -1., s33 = -1., mag = -1.;
  for(const Jet jet : *event.jets){
    mag += (jet.v4().Px()*jet.v4().Px()+jet.v4().Py()*jet.v4().Py()+jet.v4().Pz()*jet.v4().Pz());
    s11 += jet.v4().Px()*jet.v4().Px();
    s12 += jet.v4().Px()*jet.v4().Py();
    s13 += jet.v4().Px()*jet.v4().Pz();
    s22 += jet.v4().Py()*jet.v4().Py();
    s23 += jet.v4().Py()*jet.v4().Pz();
    s33 += jet.v4().Pz()*jet.v4().Pz();
  }

  s11 = s11 / mag;
  s12 = s12 / mag;
  s13 = s13 / mag;
  s22 = s22 / mag;
  s23 = s23 / mag;
  s33 = s33 / mag;

  S11->Fill(s11, weight);
  S12->Fill(s12, weight);
  S13->Fill(s13, weight);
  S22->Fill(s22, weight);
  S23->Fill(s23, weight);
  S33->Fill(s33, weight);


  sum_event_weights->Fill(1., weight);

  if(event.genInfo->systweights().size()){
    float orig_weight = event.genInfo->originalXWGTUP();
    int MY_FIRST_INDEX = 9;
      for(int i=0; i<100; i++){
        double pdf_weight = event.genInfo->systweights().at(i+MY_FIRST_INDEX);
        const char* name = hist_names[i].c_str();
        hist(name)->Fill(1.,weight * pdf_weight / orig_weight);
     }
  }


} //Method



ZprimeSemiLeptonicPreselectionHists::~ZprimeSemiLeptonicPreselectionHists(){}
