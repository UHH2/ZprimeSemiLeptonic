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

void cosmetics();



void AnalysisTool::PlotLimits(bool draw_data){
  /*
  ==========================================
  |                                          |
  |  handy script to make a nice limit plot  |
  |                                          |
  ==========================================   */

  //0) general cosmetics
  cosmetics();


  TString filename = AnalysisTool::path_theta + "output/";
  TString txtname;
  if(AnalysisTool::do_puppi) txtname = "expected_limits_puppi.txt";
  else txtname = "expected_limits.txt";
  filename += txtname;
  ifstream myfile(filename);

  vector<double> mass, expected, expected_low_68, expected_high_68, expected_low_95, expected_high_95, observed;
  float val;
  while(!myfile.eof()){
    myfile >> val;
    mass.emplace_back(val);
    myfile >> val;
    expected.emplace_back(val);
    myfile >> val;
    expected_low_95.emplace_back(val);
    myfile >> val;
    expected_high_95.emplace_back(val);
    myfile >> val;
    expected_low_68.emplace_back(val);
    myfile >> val;
    expected_high_68.emplace_back(val);
  }
  myfile.clear();

  for(unsigned int i=0; i<expected.size(); i++){
    cout << "Mass: " << mass[i] << ", expected: " << expected[i] << endl;
  }

  filename.ReplaceAll("expected_limits", "observed_limits");
  myfile = ifstream(filename);
  while(!myfile.eof()){
    myfile >> val; // Skip the mass-line, jump to the observed limit directly
    myfile >> val;
    observed.emplace_back(val);
    myfile >> val; // Skip the uncertainty on obs
  }


  myfile.clear();




  //5) convert to upper and lower errors to be used in TGraphAsymmErrors
  vector<double> expected_up_68, expected_down_68, expected_up_95, expected_down_95;
  for(unsigned int i=0; i<expected.size(); i++){
    expected_up_68.push_back(expected_high_68[i] - expected[i]);
    expected_up_95.push_back(expected_high_95[i] - expected[i]);
    expected_down_68.push_back(expected[i] - expected_low_68[i]);
    expected_down_95.push_back(expected[i] - expected_low_95[i]);
  }

  //6) build graph objects
  TGraphAsymmErrors* g_expected_68 = new TGraphAsymmErrors(expected.size(),&mass[0],&expected[0],0,0,&expected_down_68[0], &expected_up_68[0]);
  TGraphAsymmErrors* g_expected_95 = new TGraphAsymmErrors(expected.size(),&mass[0],&expected[0],0,0,&expected_down_95[0], &expected_up_95[0]);

  TGraph* g_expected = new TGraph(expected.size(),&mass[0],&expected[0]);
  TGraph* g_observed = new TGraph(expected.size(),&mass[0],&observed[0]);

  //7) cosmetics
  g_expected->SetLineWidth(3);
  g_expected->SetLineStyle(2);
  g_observed->SetLineWidth(3);
  g_observed->SetLineStyle(1);
  g_expected_68->SetFillStyle(1001);
  g_expected_95->SetFillStyle(1001);
  g_expected_68->SetFillColor(kGreen+1);
  g_expected_95->SetFillColor(kOrange);
  g_expected_68->SetLineWidth(0);
  g_expected_95->SetLineWidth(0);

  g_expected_95->SetMaximum(10000);
  g_expected_95->SetMinimum(5E-5);
  g_expected_95->SetTitle("");

  //8) Draw Graphs
  TCanvas* c = new TCanvas("c", "Nice limit plot", 800,600);
  gPad->SetLogy();
  g_expected_95->Draw("A3");
  g_expected_68->Draw("3 SAME");
  g_expected->Draw("SAME");
  if(draw_data) g_observed->Draw("SAME");

  //9) Legend
  TLegend *leg;
  leg = new TLegend(0.60,0.67,0.95,0.92,"");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.030);
  leg->SetFillStyle(0);
  leg->SetLineColor(1);
  leg->SetTextFont(42);
  leg->SetTextSize(0.041);
  leg->SetHeader("95% CL upper limit");
  ((TLegendEntry*)leg->GetListOfPrimitives()->First())->SetTextSize(0.045);
  if(draw_data) leg->AddEntry(g_observed, "Observed","L");
  leg->AddEntry(g_expected, "Expected","L");
  leg->AddEntry(g_expected_68, "68% expected","F");
  leg->AddEntry(g_expected_95, "95% expected","F");
  leg->Draw();

  //10) CMS tags
  TString infotext = "41.5 fb^{-1} (13 TeV)";
  TLatex *text1 = new TLatex(3.5, 24, infotext);
  text1->SetNDC();
  text1->SetTextAlign(33);
  text1->SetX(0.94);
  text1->SetTextFont(42);
  text1->SetTextSize(0.045);
  text1->SetY(1.);
  text1->Draw();

  TString cmstext = "CMS";
  TLatex *text2 = new TLatex(3.5, 24, cmstext);
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.15);
  text2->SetTextFont(62);
  text2->SetTextSize(0.072);
  text2->SetY(0.905);
  text2->Draw();

  TString preltext = "Supplementary";
  TLatex *text3 = new TLatex(3.5, 24, preltext);
  text3->SetNDC();
  text3->SetTextAlign(13);
  text3->SetX(0.263);
  text3->SetTextFont(52);
  text3->SetTextSize(0.05);
  text3->SetY(0.893);
  // text3->Draw();


  //12) care about axes
  TH1D* h = (TH1D*)g_expected_95->GetHistogram();
  h->GetXaxis()->SetRangeUser(mass[0], mass[expected.size()-1]);
  h->SetXTitle("M_{RSG} [GeV]");
  h->SetYTitle("#sigma_{RSG} #times #bf{#it{#Beta}} [pb]");
  h->GetYaxis()->SetTitleSize(0.048);
  h->GetYaxis()->SetTitleOffset(1.05);
  h->Draw("AXIS SAME");
  gPad->SetLeftMargin(0.11);
  gPad->SetRightMargin(0.035);
  gPad->SetBottomMargin(0.11);

  TString outfilename = "limitplot";
  if(!draw_data) outfilename+="_blinded";
  TString outpath;
  if(AnalysisTool::do_puppi) outpath = AnalysisTool::base_path_puppi + "/NOMINAL/Plots/";
  else outpath = AnalysisTool::base_path_chs + "/NOMINAL/Plots/";
  outpath += outfilename;
  c->SaveAs(outpath + ".eps");
  c->SaveAs(outpath + ".pdf");
  c->SaveAs("Plots/" + AnalysisTool::tag + "/" + outfilename + ".eps");
  c->SaveAs("Plots/" + AnalysisTool::tag + "/" + outfilename + ".pdf");


}




void cosmetics(){
  TStyle *thesisStyle = new TStyle("thesisStyle","Style for Thesis"); //hard


  // For the canvas:
  thesisStyle->SetCanvasBorderMode(0);
  thesisStyle->SetCanvasColor(kWhite);
  thesisStyle->SetCanvasDefH(600); //Height of canvas
  thesisStyle->SetCanvasDefW(600); //Width of canvas
  thesisStyle->SetCanvasDefX(0);   //POsition on screen
  thesisStyle->SetCanvasDefY(0);

  // For the Pad:
  thesisStyle->SetPadBorderMode(0);
  // thesisStyle->SetPadBorderSize(Width_t size = 1);
  thesisStyle->SetPadColor(kWhite);
  thesisStyle->SetPadGridX(false);
  thesisStyle->SetPadGridY(false);
  thesisStyle->SetGridColor(0);
  thesisStyle-> SetPadTickX(1);
  thesisStyle->   SetPadTickY(1);
  //thesisStyle->SetGridStyle(3);
  //thesisStyle->SetGridWidth(1);

  // For the frame:
  thesisStyle->SetFrameBorderMode(0);
  thesisStyle->SetFrameBorderSize(3);
  thesisStyle->SetFrameFillColor(0);
  thesisStyle->SetFrameFillStyle(0);
  thesisStyle->SetFrameLineColor(1);
  thesisStyle->SetFrameLineStyle(1);
  thesisStyle->SetFrameLineWidth(3);

  // For the histo:
  // thesisStyle->SetHistFillColor(1);
  // thesisStyle->SetHistFillStyle(0);
  thesisStyle->SetHistLineColor(1);
  thesisStyle->SetHistLineStyle(0);
  thesisStyle->SetHistLineWidth(3);
  // thesisStyle->SetLegoInnerR(Float_t rad = 0.5);
  // thesisStyle->SetNumberContours(Int_t number = 20);

  thesisStyle->SetEndErrorSize(2);
  //  thesisStyle->SetErrorMarker(20);
  thesisStyle->SetErrorX(0.);

  thesisStyle->SetMarkerStyle(20);

  //For the fit/function:
  thesisStyle->SetOptFit(0);
  thesisStyle->SetFitFormat("5.4g");
  thesisStyle->SetFuncColor(2);
  thesisStyle->SetFuncStyle(1);
  thesisStyle->SetFuncWidth(3);

  //For the date:
  thesisStyle->SetOptDate(0);
  // thesisStyle->SetDateX(Float_t x = 0.01);
  // thesisStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  thesisStyle->SetOptFile(0);
  thesisStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  thesisStyle->SetStatColor(kWhite);
  thesisStyle->SetStatFont(42);
  thesisStyle->SetStatFontSize(0.025);
  thesisStyle->SetStatTextColor(1);
  thesisStyle->SetStatFormat("6.4g");
  thesisStyle->SetStatBorderSize(1);
  thesisStyle->SetStatH(0.1);
  thesisStyle->SetStatW(0.15);
  // thesisStyle->SetStatStyle(Style_t style = 1001);
  // thesisStyle->SetStatX(Float_t x = 0);
  // thesisStyle->SetStatY(Float_t y = 0);

  // Margins:
  thesisStyle->SetPadTopMargin(0.05);
  thesisStyle->SetPadBottomMargin(0.13);
  thesisStyle->SetPadLeftMargin(0.16);
  thesisStyle->SetPadRightMargin(0.06);

  // For the Global title:

  thesisStyle->SetOptTitle(0);
  thesisStyle->SetTitleFont(42);
  thesisStyle->SetTitleColor(1);
  thesisStyle->SetTitleTextColor(1);
  thesisStyle->SetTitleFillColor(10);
  thesisStyle->SetTitleFontSize(0.05);
  // thesisStyle->SetTitleH(0); // Set the height of the title box
  // thesisStyle->SetTitleW(0); // Set the width of the title box
  // thesisStyle->SetTitleX(0); // Set the position of the title box
  // thesisStyle->SetTitleY(0.985); // Set the position of the title box
  // thesisStyle->SetTitleStyle(Style_t style = 1001);
  // thesisStyle->SetTitleBorderSize(2);

  // For the axis titles:

  thesisStyle->SetTitleColor(1, "XYZ");
  thesisStyle->SetTitleFont(42, "XYZ");
  thesisStyle->SetTitleSize(0.055, "XYZ");
  // thesisStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // thesisStyle->SetTitleYSize(Float_t size = 0.02);
  thesisStyle->SetTitleXOffset(0.9);//0.9
  thesisStyle->SetTitleYOffset(1.25);//1.35
  // thesisStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  thesisStyle->SetLabelColor(1, "XYZ");
  thesisStyle->SetLabelFont(42, "XYZ");
  thesisStyle->SetLabelOffset(0.007, "XYZ");
  thesisStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:

  thesisStyle->SetAxisColor(1, "XYZ");
  thesisStyle->SetStripDecimals(kTRUE);
  thesisStyle->SetTickLength(0.03, "XYZ");
  thesisStyle->SetNdivisions(505, "XYZ");//510
  //thesisStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  //thesisStyle->SetPadTickY(1);
  thesisStyle->SetPadTickX(1);
  thesisStyle->SetPadTickY(1);
  thesisStyle->SetNdivisions(510, "Z");//510

  // Change for log plots:
  thesisStyle->SetOptLogx(0);
  thesisStyle->SetOptLogy(0);
  thesisStyle->SetOptLogz(0);

  // Postscript options:
  thesisStyle->SetPaperSize(20.,20.);
  // thesisStyle->SetLineScalePS(Float_t scale = 3);
  // thesisStyle->SetLineStyleString(Int_t i, const char* text);
  // thesisStyle->SetHeaderPS(const char* header);
  // thesisStyle->SetTitlePS(const char* pstitle);

  // thesisStyle->SetBarOffset(Float_t baroff = 0.5);
  // thesisStyle->SetBarWidth(Float_t barwidth = 0.5);
  // thesisStyle->SetPaintTextFormat(const char* format = "g");
  // thesisStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // thesisStyle->SetTimeOffset(Double_t toffset);
  // thesisStyle->SetHistMinimumZero(kTRUE);

  thesisStyle->cd();
}
