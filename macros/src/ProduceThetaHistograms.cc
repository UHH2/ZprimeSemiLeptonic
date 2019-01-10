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


void AnalysisTool::ProduceThetaHistograms(){

  vector<TString> samples = {"DYJets", "QCD_Mu", "ST", "TTbar", "WJets", "RSGluon_M500", "RSGluon_M750", "RSGluon_M1000", "RSGluon_M1250", "RSGluon_M1500", "RSGluon_M2000", "RSGluon_M2500", "RSGluon_M3000", "RSGluon_M3500", "RSGluon_M4000", "RSGluon_M4500", "RSGluon_M5000", "RSGluon_M5500", "RSGluon_M6000", "RSGluon_M6500", "RSGluon_M7000", "RSGluon_M7500", "RSGluon_M8000", "DATA"};

  vector<TString> histnames = {"TopTagReconstruction_General/M_Zprime_rebin5", "NotTopTagReconstruction_General/M_Zprime_rebin4"};
  vector<TString> histoutnames_base = {"MZprime_toptag__", "MZprime_nottoptag__"};

  TString dir = "";
  if(AnalysisTool::do_puppi) dir = AnalysisTool::base_path_puppi;
  else dir = AnalysisTool::base_path_chs;
  dir += "/NOMINAL/";
  TString filename_base = "uhh2.AnalysisModuleRunner.";


  vector<TH1F*> outputs;
  for(unsigned int i=0; i<samples.size(); i++){
    TString sample = samples[i];

    TString type = "MC.";
    if(sample == "DATA") type = "DATA.";

    TString filename = dir + filename_base + type + sample + ".root";
    // cout << "Trying to open file: " << filename << endl;
    TFile* f_in = new TFile(filename, "READ");

    for(unsigned int j=0; j<histnames.size(); j++){
      TH1F* h_in = (TH1F*)f_in->Get(histnames[j]);

      TString hist_outname = histoutnames_base[j] + sample;
      h_in->SetName(hist_outname);
      outputs.emplace_back(h_in);
    }
  }

  TString outfilename = AnalysisTool::path_theta + "input/";
  if(AnalysisTool::do_puppi) outfilename += "theta_histograms_puppi.root";
  else outfilename += "theta_histograms.root";

  TFile* f_out = new TFile(outfilename, "RECREATE");
  for(unsigned int i=0; i<outputs.size(); i++){
    outputs.at(i)->Write();
  }
  f_out->Close();


}
