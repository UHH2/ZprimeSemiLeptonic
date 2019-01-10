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


void AnalysisTool::PlotPostfitDistributions(){

  // Get the postfit file for backgrounds, input file for data (data is not modified by MLE fit)
  TString basepath = AnalysisTool::path_theta;
  TString prename = basepath + "input/theta_histograms";
  TString postname = basepath + "output/postfit_histograms_bkgonly_data";
  if(AnalysisTool::do_puppi){
    prename += "_puppi";
    postname += "_puppi";
  }
  prename += ".root";
  postname += ".root";
  TFile* f_pre = new TFile(prename, "READ");
  TFile* f_post = new TFile(postname, "READ");

  // Container to store all histograms for postfit distributions
  vector <TH1F*> histograms_to_add;

  //Go to input file, look for all nominal histograms given to theta (each variable for each process)
  // All of these histograms are needed later, store all of them
  f_pre->cd();
  unsigned int n_histos_prefit = 0;
  vector<string> nominalnames_str, nominalnames;
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;
  TH1F* h;
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    h = (TH1F*)key->ReadObj();
    TString name = h->GetName();
    string name_str = h->GetName();
    if(!name.Contains("plus") && !name.Contains("minus")){
      nominalnames.emplace_back(name);
      nominalnames_str.emplace_back(name_str);
      n_histos_prefit++;
    }
  }
  delete h;
  // delete key;
  // delete dir;

  // Look for different variable names, each one is a new plot to create
  vector<TString> varnames;
  vector<TString> procnames;
  for(unsigned int i=0; i<nominalnames_str.size(); i++){
    string s = nominalnames_str[i];
    string del = "__";
    string varname = s.substr(0, s.find(del));
    s = s.substr(s.find(del)+del.length(), s.length());
    string procname = s;
    bool already_added_var = false, already_added_proc = false;
    for(unsigned int j=0; j<varnames.size(); j++){
      if(varnames[j].Contains(varname)) already_added_var = true;
    }
    for(unsigned int j=0; j<procnames.size(); j++){
      if(procnames[j].Contains(procname)) already_added_proc = true;
    }
    if(!already_added_var){
      // cout << "Adding this variable: " << varname << endl;
      varnames.emplace_back((TString)varname);
    }
    if(!already_added_proc){
      // cout << "Adding this process: " << procname << endl;
      procnames.emplace_back((TString)procname);
    }
  }

  // Need to identify signal later on (signal and data are taken from pre- instead of postfit file)
  vector<TString> signal_identifiers = {"RSGluon"};


  // Add some histos from prefit file
  // Go through all variables
  for(unsigned int i=0; i<varnames.size(); i++){
    TString var = varnames[i];

    // We want all histos in the postfit file, just add some more from the prefit one
    for(unsigned int j=0; j<procnames.size(); j++){

      // First data and signal, that's easy
      bool is_signal = false;
      for(unsigned int k = 0; k<signal_identifiers.size(); k++) if(procnames[j].Contains(signal_identifiers[k])) is_signal = true;
      if(procnames[j].Contains("DATA") || is_signal){
        TString histname = var + "__" + procnames[j];
        histograms_to_add.emplace_back((TH1F*)f_pre->Get(histname));
        // cout << "Adding hist with name: " << histname << endl;
      }
      else{ // Take there from postfit file
        TString histname = var + "__" + procnames[j];
        TH1F* blueprint = (TH1F*)f_pre->Get(histname);
        TH1F* post = (TH1F*)f_post->Get(histname);

        vector<double> bins;
        for(int i=1; i<blueprint->GetNbinsX()+2; i++){
          // cout << "bin no. " << i << " begins at " << blueprint->GetBinLowEdge(i) << endl;
          bins.emplace_back(blueprint->GetBinLowEdge(i));
        }

        TH1F* tmp = new TH1F(blueprint->GetName(), blueprint->GetTitle(), bins.size()-1, &bins[0]);
        for(int n=1; n<tmp->GetNbinsX()+1; n++){
          tmp->SetBinContent(n,post->GetBinContent(n));
          tmp->SetBinError(n,post->GetBinError(n));
        }
        histograms_to_add.emplace_back(tmp);
      }
    }
  }

  if(n_histos_prefit != histograms_to_add.size()) throw runtime_error("Didn't find all histograms...");

  TString outfilename;
  if(AnalysisTool::do_puppi) outfilename = AnalysisTool::base_path_puppi;
  else outfilename = AnalysisTool::base_path_chs;
  outfilename += "/NOMINAL/PostfitDistributions.root";
  TFile* f_out = new TFile(outfilename, "RECREATE");
  for(unsigned int i=0; i<histograms_to_add.size(); i++){
    // cout << "Writing: " << histograms_to_add[i]->GetName() << endl;
    histograms_to_add[i]->Write();
  }
  f_out->Close();
  for(unsigned int i=0; i<histograms_to_add.size(); i++) delete histograms_to_add[i];
  delete f_out;
  delete f_pre;
  delete f_post;
}
