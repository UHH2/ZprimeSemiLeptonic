#pragma once
#include "TASImage.h"
#include "TBox.h"
#include <TCanvas.h>
#include <TColor.h>
#include <TDecompSVD.h>
#include <TDecompLU.h>
#include <TEllipse.h>
#include <TF1.h>
#include <TF2.h>
#include <TF3.h>
#include <TFile.h>
#include <TFitResult.h>
#include "TFrame.h"
#include <TGaxis.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TGraph2DErrors.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include "TH1D.h"
#include <TH2.h>
#include <THStack.h>
#include <TLine.h>
#include <TLatex.h>
#include <TLegend.h>
#include "TLegendEntry.h"
#include <TMath.h>
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>
#include <TMultiGraph.h>
#include "TPad.h"
#include "TPaveLabel.h"
#include <TPolyLine3D.h>
#include <TPolyMarker3D.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TTree.h>
#include <TVirtualFitter.h>
#include <TVectorD.h>

#include <cmath>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>

using namespace std;
using namespace std::chrono;

typedef vector<TString> VecTS;
typedef vector<VecTS> VecTSS;
typedef vector<int> VecI;
typedef vector<VecI> VecII;
typedef vector<double> VecD;
typedef vector<vector<double>> VecDD;
typedef vector<TH1F*> VecH;
typedef vector<vector<TH1F*>> VecHH;

typedef map<TString, int> MapI;
typedef map<TString, VecI> MapVI;
typedef map<TString, MapVI> MapVII;
typedef map<TString, MapVII> MapVIII;

typedef map<TString, TString> MapTS;
typedef map<TString, MapTS> Map2TS;
typedef map<TString, Map2TS> Map3TS;
typedef map<TString, Map3TS> Map4TS;
typedef map<TString, VecTS> MapVecTS;

typedef map<TString, double> MapD;
typedef map<TString, VecD> MapVD;
typedef map<TString, MapVD> MapVDD;
typedef map<TString, MapVDD> MapVDDD;

typedef map<TString, TH1F*> MapH;
typedef map<TString, MapH> MapHH;
typedef map<TString, MapHH> MapHHH;
typedef map<TString, MapHHH> MapHHHH;

// typedef map<TString, TMatrixD> MapM;
// typedef map<TString, MapM> MapMM;
// typedef map<TString, MapMM> MapMMM;
// typedef map<TString, MapMMM> MapMMMM;

typedef map<TString, THStack*> MapStack;
typedef map<TString, MapStack> Map2Stack;
typedef map<TString, Map2Stack> Map3Stack;
typedef map<TString, Map3Stack> Map4Stack;

typedef map<TString, TFile*> MapF;
typedef map<TString, MapF> MapFF;


// -------------------------------------------------------------------------------------------
void SetupGlobalStyle()
{
  // general appearance and style

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle -> SetPadTickX(1);
  gStyle -> SetPadTickY(1);

  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);

  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(2);

  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");

  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(kTRUE);
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");

  gStyle->SetLegendBorderSize(0);

  gStyle->UseCurrentStyle();

}

// -------------------------------------------------------------------------------------------
void CMSLabel(double x=0.25, double y=0.83, TString extra = ""){
  TString cmstext = "CMS";
  TLatex *text = new TLatex(3.5, 24, cmstext);
  text->SetNDC();
  text->SetTextAlign(13);
  text->SetX(x);
  text->SetTextFont(62);
  text->SetTextSize(0.07);
  text->SetY(y);
  text->Draw();

  TLatex *text3 = new TLatex(3.5, 24, extra);
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(x);
  text3->SetTextFont(52);
  text3->SetTextSize(0.05);
  text3->SetY(y-0.06);
  text3->Draw();
}

// -------------------------------------------------------------------------------------------
void CMSLabelOffset(double x=0.25, double y=0.83, double x1 = 0.0, double y1 = 0.0){
  TString cmstext = "CMS";
  TLatex *text = new TLatex(3.5, 24, cmstext);
  text->SetNDC();
  text->SetTextAlign(13);
  text->SetX(x);
  text->SetTextFont(62);
  text->SetTextSize(0.05);
  text->SetY(y);
  text->Draw();

  TString simtext = "Work in Progress";
  TLatex *text3 = new TLatex(3.5, 24, simtext);
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(x+x1);
  text3->SetTextFont(52);
  text3->SetTextSize(0.035);
  text3->SetY(y+y1);
  text3->Draw();
}

// -------------------------------------------------------------------------------------------
void CMSSimLabel(bool prelim, double x=0.24, double y=0.9){
  TString cmstext = "CMS";
  TLatex *text2 = new TLatex(3.5, 24, cmstext);
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(x);
  text2->SetTextFont(62);
  text2->SetTextSize(0.06);
  text2->SetY(y);
  text2->Draw();

  TString simtext = "Simulation";
  TLatex *text3 = new TLatex(3.5, 24, simtext);
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(x);
  text3->SetTextFont(52);
  text3->SetTextSize(0.05);
  text3->SetY(y-0.06);
  text3->Draw();

  if(prelim){
    TString simtext = "Preliminary";
    TLatex *text4 = new TLatex(3.5, 24, simtext);
    text4->SetNDC();
    text4->SetTextAlign(13);
    text4->SetX(x);
    text4->SetTextFont(52);
    text4->SetTextSize(0.05);
    text4->SetY(y-0.12);
    text4->Draw();
  }
}

// -------------------------------------------------------------------------------------------
void LumiInfo(double lumi = 35.9, bool bratio = false, double x=0.9, double y=0.945){
  TString infotext = TString::Format("%3.1f fb^{-1} (13 TeV)", lumi);
  TLatex *text1 = new TLatex(3.5, 24, infotext);
  text1->SetNDC();
  text1->SetTextAlign(33);
  text1->SetTextFont(42);
  text1->SetX(x);
  text1->SetY(y);
  text1->Draw();
}

// -------------------------------------------------------------------------------------------
