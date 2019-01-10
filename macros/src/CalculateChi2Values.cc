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

void AnalysisTool::CalculateChi2Values(){

  TString infilename = "";
  if(AnalysisTool::do_puppi) infilename = base_path_puppi;
  else infilename = base_path_chs;
  infilename += "/NOMINAL/uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root";
  TFile* infile = new TFile(infilename, "READ");

  TH1F* h_had_ak4  = (TH1F*)infile->Get("STlepPlusMet_General/M_tophad_dr_ak4");
  TH1F* h_lep_ak4  = (TH1F*)infile->Get("STlepPlusMet_General/M_toplep_dr_ak4");
  TH1F* h_had_ttag = (TH1F*)infile->Get("STlepPlusMet_General/M_tophad_dr_ttag");
  TH1F* h_lep_ttag = (TH1F*)infile->Get("STlepPlusMet_General/M_toplep_dr_ttag");

  vector<TH1F*> hists = {h_had_ak4, h_lep_ak4, h_had_ttag, h_lep_ttag};
  vector<TString> names = {"Mtop_hadronic_AK4", "Mtop_leptonic_AK4", "Mtop_hadronic_TTag", "Mtop_leptonic_TTag"};

  for(unsigned int i=0; i<hists.size(); i++){
    TCanvas* c = new TCanvas("c", "c", 600, 600);
    hists.at(i)->GetXaxis()->SetTitle(hists.at(i)->GetTitle());
    hists.at(i)->SetTitle("");

    hists.at(i)->Fit("gaus", "", "", 130, 210);
    gStyle->SetOptFit(1);

    c->SaveAs("Plots/" + AnalysisTool::tag + "/" + names.at(i) + ".eps");
    c->SaveAs("Plots/" + AnalysisTool::tag + "/" + names.at(i) + ".pdf");
    delete c;
  }

  delete infile;








}
