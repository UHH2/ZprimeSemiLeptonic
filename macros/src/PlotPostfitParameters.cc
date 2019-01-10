
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

// Declare functions used later on
struct parameter{
  TString name;
  float value;
  float error;
};

vector<parameter> get_parameters_from_file(TString infilename);
void do_nuisance_plot(TString infilename, TString orientation, TString tag, TString outname, TString outpath, TString outname_local);



// Main function
void AnalysisTool::PlotPostfitParameters(){

  TString infilename_toys = AnalysisTool::path_theta + "output/";
  if(AnalysisTool::do_puppi) infilename_toys += "postfitparameters_toys_puppi.txt";
  else infilename_toys += "postfitparameters_toys.txt";
  TString infilename_data = infilename_toys;
  infilename_data.ReplaceAll("_toys", "_data");

  TString outpath;
  if(AnalysisTool::do_puppi) outpath = AnalysisTool::base_path_puppi + "/NOMINAL/Plots/";
  else outpath = AnalysisTool::base_path_chs + "/NOMINAL/Plots/";

  TString outname_local = "Plots/" + AnalysisTool::tag + "/Parameters_postfit";
  do_nuisance_plot(infilename_toys, "vertical", "background-only", "Parameters_postfit_toys", outpath, outname_local+"_toys");
  do_nuisance_plot(infilename_data, "vertical", "background-only", "Parameters_postfit_data", outpath, outname_local+"_data");
}





// Function definitions
vector<parameter> get_parameters_from_file(TString infilename){

  vector<parameter> par_list;

  ifstream myfile(infilename);

  while(!myfile.eof()){
    parameter par;
    myfile >> par.value;
    myfile >> par.error;
    myfile >> par.name;

    // Check if end of file is reached (might end with empty line)
    if(par.name == "") break;

    par_list.emplace_back(par);
  }

  return par_list;
}


void do_nuisance_plot(TString infilename, TString orientation, TString tag, TString outname, TString outpath, TString outname_local){

  // def nuisance_plot(input_file_, orien_, sticker_, oname_):
  vector<parameter> pars = get_parameters_from_file(infilename);
  const unsigned int N = pars.size();

  for(unsigned int i=0; i<pars.size(); i++){
    cout << "Parameter " << pars[i].name << ": " << pars[i].value << " +- " << pars[i].error << endl;
  }


  TGraph* g68 = new TGraph(2*N+7);
  TGraph* g95 = new TGraph(2*N+7);
  TGraphAsymmErrors* gPR = new TGraphAsymmErrors(N);

  for(unsigned int i=0; i<N; i++){
    float x = pars[i].value;
    float y = i + 1.5;
    float xerr = pars[i].error;
    float yerr = 0.;

    if(orientation == "horizontal"){
      float tmp = x;
      x = y;
      y = tmp;
      tmp = xerr;
      xerr = yerr;
      yerr = tmp;
    }

    gPR->SetPoint(i, x, y);
    gPR->SetPointEXlow(i, xerr);
    gPR->SetPointEYlow(i, yerr);
    gPR->SetPointEXhigh(i, xerr);
    gPR->SetPointEYhigh(i, yerr);
  }

  for(unsigned int a=0; a<N+3; a++){

    if(orientation == "horizontal"){
      g68->SetPoint(a, a, -1);
      g95->SetPoint(a, a, -2);
      g68->SetPoint(a+1+N+2, N+2-a, 1);
      g95->SetPoint(a+1+N+2, N+2-a, 2);
    }
    else{
      g68->SetPoint(a, -1, a);
      g95->SetPoint(a, -2, a);
      g68->SetPoint(a+1+N+2, 1, N+2-a);
      g95->SetPoint(a+1+N+2, 2, N+2-a);
    }
  }

  gPR->SetLineStyle(1);
  gPR->SetLineWidth(1);
  gPR->SetLineColor(1);
  gPR->SetMarkerStyle(21);
  gPR->SetMarkerSize(1.25);

  g68->SetFillColor(417);
  g95->SetFillColor(800);

  TPaveText* text_TR;
  if(orientation == "horizontal") text_TR = new TPaveText(0.587, 0.925, 0.999, 0.993, "NDC");
  else text_TR = new TPaveText(0.600, 0.945, 0.995, 0.993, "NDC");

  text_TR->AddText(tag);
  text_TR->SetFillColor(0);
  text_TR->SetTextAlign(32);
  text_TR->SetTextSize(0.05);
  text_TR->SetTextFont(42);

  TCanvas* c;
  if(orientation == "h"){
    c = new TCanvas("c","c",1000,700);
    c->SetTopMargin(0.08);
    c->SetRightMargin(0.02);
    c->SetBottomMargin(0.16);
    c->SetLeftMargin(0.11);
  }
  else{
    c = new TCanvas("c","c",700,1000);
    c->SetTopMargin(0.06);
    c->SetRightMargin(0.02);
    c->SetBottomMargin(0.12);
    c->SetLeftMargin(0.35*700/650);
  }

  c->SetTickx();
  c->SetTicky();

  c->Update();
  g95->Draw("AF");
  g68->Draw("F");
  gPR->Draw("P");
  text_TR->Draw("same");

  TAxis* ax_1 = (TAxis*)g95->GetHistogram()->GetYaxis();
  TAxis* ax_2 = (TAxis*)g95->GetHistogram()->GetXaxis();
  if(orientation == "horizontal"){
    TAxis* tmp = (TAxis*)ax_1->Clone();
    ax_1 = ax_2;
    ax_2 = tmp;
  }

  ax_1->Set(N+2,0,N+2);
  ax_1->SetNdivisions(-414);
  for(unsigned int i=0; i<N; i++) ax_1->SetBinLabel(i+2, pars[i].name);

  g95->SetTitle("");
  ax_2->SetTitle("post-fit nuisance parameters values");
  ax_1->SetTitleSize(0.050);
  ax_2->SetTitleSize(0.050);
  ax_1->SetTitleOffset(1.4);
  ax_2->SetTitleOffset(1.0);
  ax_1->SetLabelSize(0.05);
  ax_1->SetRangeUser(0, N+2);
  ax_2->SetRangeUser(-2.4, 2.4);

  g95->GetHistogram()->Draw("axis,same");

  c->SaveAs(outname_local+".eps");
  c->SaveAs(outname_local+".pdf");
  c->SaveAs(outpath+outname+".eps");
  c->SaveAs(outpath+outname+".pdf");

  c->Close();
  delete c;
}
