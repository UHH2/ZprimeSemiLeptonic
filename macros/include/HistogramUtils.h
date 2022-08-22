#pragma once
#include <TCanvas.h>
#include <TColor.h>
#include <TDecompSVD.h>
#include <TDecompLU.h>
#include <TEllipse.h>
#include <TF1.h>
#include <TF2.h>
#include <TFile.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TGraphErrors.h>
#include <TGraph2DErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TMultiGraph.h>
#include <TGraphAsymmErrors.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TMatrix.h>
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>
#include <TFitResult.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TTree.h>
#include <TVirtualFitter.h>
#include <TVectorD.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
// #include <tuple>
#include <vector>

using namespace std;

/*
This header contains many outdated functions and should be reorganized.
*/

// =====================================================================================
// ===                                                                               ===
// =====================================================================================

// -------------------------------------------------------------------------------------------
vector<int> bins_upper_limit(TH1F* hist, double limit){
  vector<int> bin_pass_v;
  for(int bin=1; bin <= hist->GetNbinsX(); bin++){
    if((hist->GetBinContent(bin)>limit)) bin_pass_v.push_back(bin);
  }
  return bin_pass_v;
}

// -------------------------------------------------------------------------------------------
vector<double> bin_center_upper_limit(TH1F* hist, vector<int> bins_above_limit, int bin_width){
  int lower_bin = bins_above_limit[0];
  int upper_bin = bins_above_limit[bins_above_limit.size()-1];

  // bin_width/2 just a saftey. Boundaries must be greater than actual bin content for </> operator
  double down_center = hist->GetBinCenter(lower_bin)-bin_width/2;
  double up_center   = hist->GetBinCenter(upper_bin)+bin_width/2;

  return {down_center, up_center};
}

// -------------------------------------------------------------------------------------------
vector<int> bins_empty(TH1F* hist){
  vector<int> bin_empty_v;
  for(int bin=0; bin < hist->GetNbinsX(); bin++){
    if(!(abs(hist->GetBinContent(bin+1))>0)) bin_empty_v.push_back(bin+1);
  }
  return bin_empty_v;
}

// -------------------------------------------------------------------------------------------------------
TH1F* copy_bin_content(TH1F* h1, int MinBin, int MaxBin, TString name)
{
  TH1F* new_hist = new TH1F(name, name, h1->GetNbinsX(), MinBin, MaxBin);

  for(int i=1; i<=h1->GetNbinsX(); i++)
  {
    new_hist->SetBinContent(i, h1->GetBinContent(i));
  }

  return new_hist;
}

// -------------------------------------------------------------------------------------------------------
void set_new_bin_error(TH1F* h1, vector<double> err)
{
  if(h1->GetNbinsX() != err.size()) throw runtime_error("Vector with errors has not the same size as the histogram");
  for(int bin=1; bin<=h1->GetNbinsX(); bin++) h1->SetBinError(bin, err[bin-1]);
}

// =====================================================================================
// ===                                                                               ===
// =====================================================================================

// -------------------------------------------------------------------------------------------
TH1F* RebinHist(TH1F* hist, int rebin){
  TH1F* clone = (TH1F*) hist->Clone();
  clone->Rebin(rebin);
  return clone;
}

vector<TH1F*> RebinVector(vector<TH1F*> hists, int rebin){
  vector<TH1F*> new_hist;
  for(auto hist: hists) new_hist.push_back(RebinHist(hist, rebin));
  return new_hist;
}

// =====================================================================================
// ===                                                                               ===
// =====================================================================================

// ------------------------------------------------------------------------------------------- uncorrelated
TH1F* Normalize(TH1F* hist){
  TH1F* norm = (TH1F*) hist->Clone();
  int nbins = hist->GetXaxis()->GetNbins();
  double integral = hist->Integral();
  norm->Scale(1/integral);
  // Now do error propagation:
  // Bin content of norm hist: b_i = N_i / (N_1 + N_2 + N_3 + ...)
  // Two derivations:
  // 1. db_i / dN_i = (N_2 + N_3 + ...) / (N_1 + N_2 + N_3 + ...)^2 = (Integral - N_i) / Integral^2
  // 2. db_i / dN_j = - N_1 / (N_1 + N_2 + N_3 + ...)^2

  for(int i=1; i<=nbins; i++){
    double error2 = 0;
    for(int j=1; j<=nbins; j++){
      double additionalterm;
      if(i==j) additionalterm = (integral - hist->GetBinContent(i)) / (integral * integral);
      else     additionalterm = - hist->GetBinContent(i) / (integral * integral);
      error2 += additionalterm*additionalterm * hist->GetBinError(j)*hist->GetBinError(j);
    }
    double error = sqrt(error2);
    norm->SetBinError(i, error);
  }
  return norm;
}

// -------------------------------------------------------------------------------------------
vector<TH1F*> VectorNormalize(vector<TH1F*> hists){
  vector<TH1F*> hists_norm;
  for(auto hist: hists) hists_norm.push_back((TH1F*) Normalize(hist));
  return hists_norm;
}


// -------------------------------------------------------------------------------------------
TH1F *normalize(TH1F *hist){
  TH1F *hist_norm = (TH1F*) hist->Clone();
  hist_norm->Scale(1/hist->Integral());
  return hist_norm;
}

// -------------------------------------------------------------------------------------------
vector<TH1F*> normalize(vector<TH1F*> hist){
  vector<TH1F*> hist_norm_v;
  for(unsigned int i=0; i<hist.size(); i++) hist_norm_v.push_back(normalize(hist[i]));
  return hist_norm_v;
}

// -------------------------------------------------------------------------------------------
vector<vector<TH1F*>> normalize(vector<vector<TH1F*>> hist){
  vector<vector<TH1F*>> hist_norm_vv;
  for(unsigned int i=0; i<hist.size(); i++) hist_norm_vv.push_back(normalize(hist[i]));
  return hist_norm_vv;
}


// =====================================================================================
// ===                                                                               ===
// =====================================================================================

/*
**********************************************************************************************
********************* Propagation of Uncertainties *******************************************
**********************************************************************************************
*/

// -------------------------------------------------------------------------------------------
/* Propagation of Uncertainties: many variables --------------------------------------------
dy = dely/delx_1 * dx_1 + dely/delx_2 * dx_2 + ... + dely/delx_n * dx_n
Gauss: dy^2 = (dely/delx_1 * dx_1)^2 + (dely/delx_2 * dx_2)^2 + ... + (dely/delx_n * dx_n)^2
...... variables are independent  of each other

PoU for normalized hists: ------------------------------------------------------------------
I = Integral of Histogram
bin x_1 and x_1,n(orm)
x_1,n = x_1/(Sum(all bins))
two different terms for PoU of dx_1,n:
delx_1,n/delx_1 * dx_1 = (I-x_1)/(I)^2 * dx_1
delx_1,n/delx_y * dx_y = -(x_1)/(I)^2 * dx_y (y = every bin except 1 in this example) */

vector<double> normalize_error(TH1F* hist){
  // error of each bin normalized and into vector
  TH1F* hist_ = (TH1F*) hist->Clone();
  double integral = hist_->Integral();
  double integral2 = integral*integral;
  int number_bins = hist_->GetNbinsX();

  vector<double> bin_error_norm, bin_content, bin_error;
  for(unsigned int bin=1; bin<number_bins+1; bin++){
    bin_content.push_back(hist_->GetBinContent(bin));
    bin_error.push_back(hist_->GetBinError(bin));
  }

  double error_term = 0;
  for(unsigned int bin=0; bin<number_bins; bin++){ // Calculate the error for each bin
    for(unsigned int i=0; i<number_bins; i++){ // Include contribution of each bin for PoU
      if(bin == i) error_term += pow(((integral-bin_content[bin])/integral2)*bin_error[i], 2.0);
      else         error_term += pow(((-1)*(bin_content[bin])/integral2)*bin_error[i], 2.0);
    }
    bin_error_norm.push_back(sqrt(error_term));
    error_term=0;
  }

  return bin_error_norm;
}

vector<vector<double>> normalize_error(vector<TH1F*> hist_v){
  // error of each bin normalized and into vector
  vector<vector<double>> all_errors;
  for(unsigned int i=0; i<hist_v.size(); i++){
    TH1F* hist_ = (TH1F*) hist_v[i]->Clone();
    double integral = hist_->Integral();
    double integral2 = integral*integral;
    int number_bins = hist_->GetNbinsX();

    vector<double> bin_error_norm, bin_content, bin_error;
    for(unsigned int bin=1; bin<number_bins+1; bin++){
      bin_content.push_back(hist_->GetBinContent(bin));
      bin_error.push_back(hist_->GetBinError(bin));
    }

    double error_term = 0;
    for(unsigned int bin=0; bin<number_bins; bin++){ // Calculate the error for each bin
      for(unsigned int i=0; i<number_bins; i++){ // Include contribution of each bin for PoU
        if(bin == i) error_term += pow(((integral-bin_content[bin])/integral2)*bin_error[i], 2.0);
        else         error_term += pow(((-1)*(bin_content[bin])/integral2)*bin_error[i], 2.0);
      }
      bin_error_norm.push_back(sqrt(error_term));
      error_term=0;
    }
    all_errors.push_back(bin_error_norm);
  }
  return all_errors;
}

// ============================================================================================
// ===                                                                                      ===
// ============================================================================================

// -------------------------------------------------------------------------------------------
double get_highest_peak(vector<TH1F*> hists){
  vector<double> max;
  double max_value;
  for(unsigned int i = 0; i<hists.size(); i++) max.push_back(hists[i]->GetMaximum());
  sort(max.begin(), max.end());
  double top_index = max.size()-1;
  return max[top_index];
}

// ============================================================================================
// ===                                                                                      ===
// ============================================================================================


TH1F* AddHists(vector<TH1F*> hists_, int factor){
  TH1F* hist_added = (TH1F*) hists_[0]->Clone();
  for(unsigned int i=1; i<hists_.size();i++){
    hist_added->Add(hists_[i], factor);
  }
  return hist_added;
}

// -------------------------------------------------------------------------------------------------------
TH2F* AddHists(vector<TH2F*> hists_, int factor){
  TH2F* hist_added = (TH2F*) hists_[0]->Clone();
  for(unsigned int i=1; i<hists_.size();i++) hist_added->Add(hists_[i], factor);
  return hist_added;
}

// -------------------------------------------------------------------------------------------------------
TH1F* AddHists(TH1F* h1, TH1F* h2, int factor){
  TH1F* hist_added = (TH1F*) h1->Clone();
  hist_added->Add(h2, factor);
  return hist_added;
}

// -------------------------------------------------------------------------------------------------------
vector<TH1F*> AddHists(vector<TH1F*> h1, vector<TH1F*> h2, int factor){
  vector<TH1F*> hists;
  if(h1.size()!=h2.size()) throw runtime_error("Hists have not the same size!");
  for(unsigned int i=0; i<h1.size(); i++) hists.push_back(AddHists(h1[i], h2[i], factor));
  return hists;
}

// -------------------------------------------------------------------------------------------------------
vector<TH1F*> AddHists(vector<TH1F*> h1, vector<TH1F*> h2, vector<TH1F*> h3, int factor){
  vector<TH1F*> dummy = AddHists(h1, h2, factor);
  if(h1.size()!=h3.size()) throw runtime_error("Hists have not the same size! (h1 and h3)");
  vector<TH1F*> hists = AddHists(dummy, h3, factor);
  return hists;
}

// ============================================================================================
// ===                                                                                      ===
// ============================================================================================

// -------------------------------------------------------------------------------------------------------
void add_plot_settings(TH1F* hist, int color=1, int style=kSolid, int width=2)
{
  hist->SetLineWidth(width);
  hist->SetLineStyle(style);
  hist->SetLineColor(color);
}

// -------------------------------------------------------------------------------------------------------
void data_plot_settings(TH1F* hist)
{
  hist->SetMarkerStyle(8);  // data hist style
  hist->SetMarkerColor(kBlack);
  hist->SetLineColor(kBlack);
}

// ============================================================================================
// ===                                                                                      ===
// ============================================================================================

// -------------------------------------------------------------------------------------------------------
double trunc_mean(TH1F* hist, int cut_down, int cut_up)
{
  TH1F* hist_trunc = (TH1F*) hist->Clone();

  for(int bin=1; bin<hist->GetNbinsX()+1; bin++)
  {
    bool bin_ = (hist->GetBinCenter(bin)<cut_down||hist->GetBinCenter(bin)>cut_up);
    if(bin_) hist_trunc->SetBinContent(bin, 0);
    else     hist_trunc->SetBinContent(bin, hist->GetBinContent(bin));
  }

  double mean_trunc = hist_trunc->GetMean();
  double mean_old   = hist->GetMean();
  return mean_trunc;
}

// -------------------------------------------------------------------------------------------------------
double trunc_mean_bin(TH1F* hist, int bin_down, int bin_up)
{
  TH1F* hist_trunc = (TH1F*) hist->Clone();

  for(int bin=1; bin<hist->GetNbinsX()+1; bin++)
  {
    bool bin_ = (bin<bin_down||bin>bin_up);
    if(bin_) hist_trunc->SetBinContent(bin, 0);
    else     hist_trunc->SetBinContent(bin, hist->GetBinContent(bin));
  }

  double mean_trunc = hist_trunc->GetMean();
  double mean_old   = hist->GetMean();
  return mean_trunc;
}

// =====================================================================================
// ===                                                                               ===
// =====================================================================================

// -------------------------------------------------------------------------------------------------------
void CompareHistStructure(TH1F* h1, TH1F* h2){
  // Check if histograms have the same structure
  bool sameBins = h1->GetNbinsX() == h2->GetNbinsX();
  bool sameCenter = true;
  for(unsigned int i=1; i<h1->GetNbinsX(); i++){
    sameCenter = h1->GetBinCenter(i) == h2->GetBinCenter(i);
    if(!sameCenter) break;
  }
  if(!sameBins||!sameCenter) throw runtime_error("GetRatio: Histograms do not have the same structure!");
}

// -------------------------------------------------------------------------------------------------------
TH1F* GetRatio(TH1F* h1, TH1F* h2, bool equal){
  CompareHistStructure(h1, h2);
  TH1F* ratio = (TH1F*) h1->Clone();
  int Nbins = h1->GetNbinsX();
  for(int i=1; i<=Nbins;i++){
    double N1 = h1->GetBinContent(i);
    double N2 = h2->GetBinContent(i);
    double E1 = h1->GetBinError(i);
    double E2 = h2->GetBinError(i);
    if(N1==0 || N2==0){
      if(equal) ratio->SetBinContent(i, 1);
      else      ratio->SetBinContent(i, 1);

      ratio->SetBinError(i, 0);
    }
    else{
      double r = N1/N2;
      double error = sqrt(E1/N2 * E1/N2 + N1*E2/(N2*N2) * N1*E2/(N2*N2));
      ratio->SetBinContent(i, r);
      ratio->SetBinError(i, error);
    }
  }
  return ratio;
}
