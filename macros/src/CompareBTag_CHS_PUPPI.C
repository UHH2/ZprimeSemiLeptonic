#include "../include/cosmetics.h"
#include "../include/Tools.h"
#include <TString.h>
#include <iostream>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TText.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>

using namespace std;

void CompareBTag_CHS_PUPPI(){

  TString filename_PUPPI = "";
  TString filename_CHS = "";
  filename_PUPPI += "/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_lowmass_HOTVR/ZPrime_2018/Analysis_2018_AK4CHS/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.TTbar_PUPPI.root";
  filename_CHS += "/nfs/dust/cms/user/deleokse/RunII_102X_v2/ZPrime_lowmass_HOTVR/ZPrime_2018/Analysis_2018_AK4CHS/muon/NOMINAL/uhh2.AnalysisModuleRunner.MC.TTbar_CHS.root";

  TFile* f_in_PUPPI = new TFile(filename_PUPPI, "READ");
  TFile* f_in_CHS = new TFile(filename_CHS, "READ");

  TH1F* h_NJets_PUPPI                 = (TH1F*)f_in_PUPPI->Get("HTlep_General/N_jets");
  TH1F* h_pt_jet1_PUPPI               = (TH1F*)f_in_PUPPI->Get("HTlep_General/pt_jet1");
  TH1F* h_eta_jet1_PUPPI              = (TH1F*)f_in_PUPPI->Get("HTlep_General/eta_jet1");
  TH1F* h_phi_jet1_PUPPI              = (TH1F*)f_in_PUPPI->Get("HTlep_General/phi_jet1");
  TH1F* h_N_bJetsDeepJet_loose_PUPPI  = (TH1F*)f_in_PUPPI->Get("HTlep_General/N_bJetsDeepJet_loose");
  TH1F* h_N_bJetsDeepJet_med_PUPPI    = (TH1F*)f_in_PUPPI->Get("HTlep_General/N_bJetsDeepJet_med");
  TH1F* h_N_bJetsDeepJet_tight_PUPPI  = (TH1F*)f_in_PUPPI->Get("HTlep_General/N_bJetsDeepJet_tight");
  TH1F* h_deepjetbscore_jet_PUPPI     = (TH1F*)f_in_PUPPI->Get("HTlep_General/deepjetbscore_jet");
  TH1F* h_deepjetbscore_jet1_PUPPI    = (TH1F*)f_in_PUPPI->Get("HTlep_General/deepjetbscore_jet1");
  TH1F* h_deepjetbscore_jet2_PUPPI    = (TH1F*)f_in_PUPPI->Get("HTlep_General/deepjetbscore_jet2");
  TH1F* h_deepjetbscore_jet3_PUPPI    = (TH1F*)f_in_PUPPI->Get("HTlep_General/deepjetbscore_jet3");


  TH1F* h_NJets_CHS                   = (TH1F*)f_in_CHS->  Get("HTlep_General/N_jets");
  TH1F* h_pt_jet1_CHS                 = (TH1F*)f_in_CHS->  Get("HTlep_General/pt_jet1");
  TH1F* h_eta_jet1_CHS                = (TH1F*)f_in_CHS->  Get("HTlep_General/eta_jet1");
  TH1F* h_phi_jet1_CHS                = (TH1F*)f_in_CHS->  Get("HTlep_General/phi_jet1");
  TH1F* h_N_bJetsDeepJet_loose_CHS    = (TH1F*)f_in_CHS->  Get("HTlep_General/N_bJetsDeepJet_loose");
  TH1F* h_N_bJetsDeepJet_med_CHS      = (TH1F*)f_in_CHS->  Get("HTlep_General/N_bJetsDeepJet_med");
  TH1F* h_N_bJetsDeepJet_tight_CHS    = (TH1F*)f_in_CHS->  Get("HTlep_General/N_bJetsDeepJet_tight");
  TH1F* h_deepjetbscore_jet_CHS       = (TH1F*)f_in_CHS->  Get("HTlep_General/deepjetbscore_jet");
  TH1F* h_deepjetbscore_jet1_CHS      = (TH1F*)f_in_CHS->  Get("HTlep_General/deepjetbscore_jet1");
  TH1F* h_deepjetbscore_jet2_CHS      = (TH1F*)f_in_CHS->  Get("HTlep_General/deepjetbscore_jet2");
  TH1F* h_deepjetbscore_jet3_CHS      = (TH1F*)f_in_CHS->  Get("HTlep_General/deepjetbscore_jet3");

  vector<TH1F*> hists_PUPPI = {h_NJets_PUPPI,h_pt_jet1_PUPPI,h_eta_jet1_PUPPI,h_phi_jet1_PUPPI,h_N_bJetsDeepJet_loose_PUPPI,h_N_bJetsDeepJet_med_PUPPI,h_N_bJetsDeepJet_tight_PUPPI,h_deepjetbscore_jet_PUPPI,h_deepjetbscore_jet1_PUPPI,h_deepjetbscore_jet2_PUPPI,h_deepjetbscore_jet3_PUPPI};
  vector<TH1F*> hists_CHS = {h_NJets_CHS,h_pt_jet1_CHS,h_eta_jet1_CHS,h_phi_jet1_CHS,h_N_bJetsDeepJet_loose_CHS,h_N_bJetsDeepJet_med_CHS,h_N_bJetsDeepJet_tight_CHS,h_deepjetbscore_jet_CHS,h_deepjetbscore_jet1_CHS,h_deepjetbscore_jet2_CHS,h_deepjetbscore_jet3_CHS};

  vector<TString> names = {"N_jets", "pt_jet1", "eta_jet1", "phi_jet1", "N_bJetsDeepJet_loose", "N_bJetsDeepJet_med", "N_bJetsDeepJet_tight", "deepjetbscore_jets", "deepjetbscore_jet1", "deepjetbscore_jet2", "deepjetbscore_jet3"};


  for(unsigned int i=0; i<hists_PUPPI.size(); i++){
     TCanvas* c = new TCanvas("c", "c", 1200, 800);
     c->Divide(1,1);
     c->cd(1);
     gPad->SetTopMargin(0.07);
     gPad->SetBottomMargin(0.17);
     gPad->SetLeftMargin(0.2);
     gPad->SetRightMargin(0.1);
     gPad->SetLogy();
     gStyle->SetOptStat(0);

     //hists_PUPPI.at(i)->Scale(1/hists_PUPPI.at(i)->Integral());
     //hists_CHS.at(i)->Scale(1/hists_CHS.at(i)->Integral());

     hists_PUPPI.at(i)->Draw("hist");
     hists_CHS.at(i)->Draw("hist same");

     hists_PUPPI.at(i)->SetTitle("");
     hists_PUPPI.at(i)->GetXaxis()->SetTitle(names.at(i));
     hists_PUPPI.at(i)->SetLineColor(kBlue);
     hists_PUPPI.at(i)->SetLineWidth(2);
     hists_PUPPI.at(i)->SetLineStyle(2);
     hists_PUPPI.at(i)->GetXaxis()->SetTitleSize(0.055);
     hists_PUPPI.at(i)->GetXaxis()->SetLabelSize(0.05);
     hists_PUPPI.at(i)->GetYaxis()->SetTitle("Events");
     hists_PUPPI.at(i)->GetYaxis()->SetTitleSize(0.055);
     hists_PUPPI.at(i)->GetYaxis()->SetLabelSize(0.05);
     hists_PUPPI.at(i)->Draw("hist");

     hists_CHS.at(i)->SetLineColor(kRed);
     hists_CHS.at(i)->SetLineWidth(2);
     hists_CHS.at(i)->SetLineStyle(2);
     hists_CHS.at(i)->Draw("hist same");

     if(i!=2 && i!=3){
     auto legend = new TLegend(0.58,0.74,0.86,0.92);
     legend->SetBorderSize(0);
     legend->AddEntry(hists_PUPPI.at(i),"TTbar PUPPI","l");
     legend->AddEntry(hists_CHS.at(i),"TTbar CHS","l");
     legend->Draw("same");
     }

     if(i==2 || i==3){
     auto legend = new TLegend(0.58,0.24,0.86,0.42);
     legend->SetBorderSize(0);
     legend->AddEntry(hists_PUPPI.at(i),"TTbar PUPPI","l");
     legend->AddEntry(hists_CHS.at(i),"TTbar CHS","l");
     legend->Draw("same");
     }


     TString infotext = "59.7 fb^{-1}(13 TeV)";
     TLatex *text1 = new TLatex(3.5, 24, infotext);
     text1->SetNDC();
     text1->SetTextAlign(31);
     text1->SetX(1.-0.1);
     text1->SetTextFont(42);
     text1->SetTextSize(0.07*0.7);
     text1->SetY(1.-0.07+0.2*0.07);
     text1->Draw();

     c->SaveAs("Plots_CHS_PUPPI/HTlep_" +names.at(i) + ".pdf");

     delete c;
  }

  delete f_in_PUPPI;
  delete f_in_CHS;



}
