#include "../include/CentralInclude.h"
#include "../include/tdrstyle_all.h"
#include "../include/HistogramUtils.h"

using namespace std;

// variables from root tree
Double_t pt;
Double_t eta;
Double_t weight;
Double_t lumi_plot;
Double_t weight_sfpt;
Double_t weight_sfeta;
Double_t weight_sfetapt;
Double_t weight_sfetaptUP;
Double_t weight_sfetaptDOWN;
Int_t run;
Int_t lumin;
Int_t eventnr;
bool passed, passed_elec, passed_photon;
bool debug = false;
TString weighttag;
TString year, year_v;

//vector<double> pt_bins = {55, 75, 95, 115, 135, 155, 175, 200, 300, 1500};
vector<double> pt_bins = {25, 45, 65, 85, 105, 125, 145, 165, 185, 200, 250, 300, 400, 500, 1500};
vector<double> pt_bins_control;
vector<double> eta_bins = {-2.5, -2.0, -1.566, -1.444, -0.8, 0.0, 0.8, 1.444, 1.566, 2.0, 2.5};

// filling hists
void fill_pteta(TTree* tree, vector<TH1F*> h_pt, vector<TH1F*> h_eta);
void FillEGap(TH1F* h);
TH1F* GetRatioGraph(TGraphAsymmErrors* h1, TGraphAsymmErrors* h2, bool isData);
// Calculate SF
vector<TH1F*> GetSF(TGraphAsymmErrors* h_data, TGraphAsymmErrors* h_mc, TH1F* hist);
// Plotter
void DrawText(TString name);
void PlotEfficiency(TGraphAsymmErrors* h_data, TGraphAsymmErrors* h_mc, TString xaxis, TString histname);
void PlotHist(TH1F* h_data, TString xaxis, TString histname);
void PlotHist(TH2F* h_data, TString xaxis, TString yaxis, TString histname);
void PlotSF(vector<TH1F*> h_SF, TString xaxis, TString histname);
void CompareHists(TH1F* h_all, TH1F* h_pass, TString xaxis, TString histname);
void DrawControl(TString path, VecH hists, TH1F* rData, TH1F* rMC, VecI colors, VecTS names, TString xaxis);
void fill_control(TTree* tree, vector<TH1F*> h_pt, vector<TH1F*> h_eta);
void AdjustBinContent(TH1F* h_pass, TH1F* h_all, TString text);

void ElecTriggerSFs(){
//int main(int argc, char* argv[]){
int argc = 2;

  cout << endl << "===================================================" << endl;

  double start = 25;
  while(start < 1005){
    pt_bins_control.push_back(start);
    start +=25;
  }
  gErrorIgnoreLevel = kWarning;

  year = "UL17";
  //year = "UL18";
  TString fdir;
  fdir = "/nfs/dust/cms/user/deleokse/RunII_106_v2/Analysis_" + year +"_dilepton_Trigger/";
  lumi_plot = 41.5;
  //year = argv[1];
  //TString fdir;
  //if(year.EqualTo("2016")){year_v = "_2016v3"; lumi_plot = 35.9; fdir = "no";}
  //else if(year.EqualTo("2017")){year_v = "_2017v2"; lumi_plot = 41.5; fdir = "no";}
  //else if(year.EqualTo("2018")){year_v = "_2018"; lumi_plot = 59.74; fdir = "no";}
  //else if(year.EqualTo("UL16")){year_v = "_UL16"; lumi_plot = 0.0; fdir = "no";}
  //else if(year.EqualTo("UL17")){year_v = "_UL17"; lumi_plot = 0.0; fdir = "no";}
  //else if(year.EqualTo("UL18")){year_v = "_UL18"; lumi_plot = 59.8; fdir = "/nfs/dust/cms/user/deleokse/RunII_106_v2/Analysis_UL18_EleTriggerModule/muon/";}
  //else throw runtime_error("I need the correct year; 2016, 2017, 2018, UL16, UL17 or UL18");

  if(argc == 2){
    cout << "Calculate ElecTrigger SF for "+year+" dependent on pt and eta..." << endl << endl;
    weighttag = "weight";
  }

  // ===========================================================================
  //                        Define Hists
  // ===========================================================================
  vector<TH1F*> h_pt_data, h_pt_mc;
  h_pt_data.push_back(new TH1F("h_pt_all_data","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_data.push_back(new TH1F("h_pt_pass_data","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_data.push_back(new TH1F("h_pt_all_data_weirdbin","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_data.push_back(new TH1F("h_pt_pass_data_weirdbin","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_data.push_back(new TH1F("h_pt_elec_data","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_data.push_back(new TH1F("h_pt_photon_data","pt", pt_bins.size()-1, &pt_bins[0]));
  // h_pt_data.push_back(new TH1F("h_pt_all_data_barrel","pt", pt_bins.size()-1, &pt_bins[0]));
  // h_pt_data.push_back(new TH1F("h_pt_pass_data_barrel","pt", pt_bins.size()-1, &pt_bins[0]));
  // h_pt_data.push_back(new TH1F("h_pt_all_data_endcap","pt", pt_bins.size()-1, &pt_bins[0]));
  // h_pt_data.push_back(new TH1F("h_pt_pass_data_endcap","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_mc.push_back(new TH1F("h_pt_all_mc","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_mc.push_back(new TH1F("h_pt_pass_mc","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_mc.push_back(new TH1F("h_pt_all_mc_weirdbin","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_mc.push_back(new TH1F("h_pt_pass_mc_weirdbin","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_mc.push_back(new TH1F("h_pt_elec_mc","pt", pt_bins.size()-1, &pt_bins[0]));
  h_pt_mc.push_back(new TH1F("h_pt_photon_mc","pt", pt_bins.size()-1, &pt_bins[0]));
  // h_pt_mc.push_back(new TH1F("h_pt_all_mc_barrel","pt", pt_bins.size()-1, &pt_bins[0]));
  // h_pt_mc.push_back(new TH1F("h_pt_pass_mc_barrel","pt", pt_bins.size()-1, &pt_bins[0]));
  // h_pt_mc.push_back(new TH1F("h_pt_all_mc_endcap","pt", pt_bins.size()-1, &pt_bins[0]));
  // h_pt_mc.push_back(new TH1F("h_pt_pass_mc_endcap","pt", pt_bins.size()-1, &pt_bins[0]));

  vector<TH1F*> h_eta_data, h_eta_mc;
  h_eta_data.push_back(new TH1F("h_eta_all_data","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data.push_back(new TH1F("h_eta_pass_data","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data.push_back(new TH1F("h_eta_all_data_lowpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data.push_back(new TH1F("h_eta_pass_data_lowpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data.push_back(new TH1F("h_eta_all_data_midpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data.push_back(new TH1F("h_eta_pass_data_midpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data.push_back(new TH1F("h_eta_all_data_highpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data.push_back(new TH1F("h_eta_pass_data_highpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data.push_back(new TH1F("h_eta_fail_data_highpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_all_mc","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_pass_mc","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_all_mc_lowpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_pass_mc_lowpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_all_mc_midpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_pass_mc_midpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_all_mc_highpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_pass_mc_highpt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc.push_back(new TH1F("h_eta_fail_mc_highpt","eta", eta_bins.size()-1, &eta_bins[0]));

  // ===========================================================================
  // Control Hists
  vector<TH1F*> h_pt_tt, h_pt_st, h_eta_tt, h_eta_st;
  vector<TH1F*> h_pt_wj, h_pt_di, h_pt_dy, h_eta_wj, h_eta_di, h_eta_dy;
  vector<TH1F*> h_pt_data_control, h_eta_data_control;
  vector<TH1F*> h_pt_mc_control, h_eta_mc_control;
  h_eta_data_control.push_back(new TH1F("h_eta_all_data_control","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_data_control.push_back(new TH1F("h_eta_pass_data_control","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc_control.push_back(new TH1F("h_eta_all_mc_control","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_mc_control.push_back(new TH1F("h_eta_pass_mc_control","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_tt.push_back(new TH1F("h_eta_all_tt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_tt.push_back(new TH1F("h_eta_pass_tt","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_st.push_back(new TH1F("h_eta_all_st","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_st.push_back(new TH1F("h_eta_pass_st","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_wj.push_back(new TH1F("h_eta_all_wj","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_wj.push_back(new TH1F("h_eta_pass_wj","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_di.push_back(new TH1F("h_eta_all_di","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_di.push_back(new TH1F("h_eta_pass_di","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_dy.push_back(new TH1F("h_eta_all_dy","eta", eta_bins.size()-1, &eta_bins[0]));
  h_eta_dy.push_back(new TH1F("h_eta_pass_dy","eta", eta_bins.size()-1, &eta_bins[0]));

  h_pt_data_control.push_back(new TH1F("h_pt_all_data_control","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_data_control.push_back(new TH1F("h_pt_pass_data_control","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_mc_control.push_back(new TH1F("h_pt_all_mc_control","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_mc_control.push_back(new TH1F("h_pt_pass_mc_control","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_tt.push_back(new TH1F("h_pt_all_tt","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_tt.push_back(new TH1F("h_pt_pass_tt","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_st.push_back(new TH1F("h_pt_all_st","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_st.push_back(new TH1F("h_pt_pass_st","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_wj.push_back(new TH1F("h_pt_all_wj","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_wj.push_back(new TH1F("h_pt_pass_wj","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_di.push_back(new TH1F("h_pt_all_di","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_di.push_back(new TH1F("h_pt_pass_di","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_dy.push_back(new TH1F("h_pt_all_dy","eta", pt_bins_control.size()-1, &pt_bins_control[0]));
  h_pt_dy.push_back(new TH1F("h_pt_pass_dy","eta", pt_bins_control.size()-1, &pt_bins_control[0]));

  // ===========================================================================
  //                        Hists
  // ===========================================================================

  vector<vector<TH1F*>> h_pt_time, h_eta_time;
  vector<TFile*> f_time;

  TFile *f_data=new TFile(fdir+"uhh2.AnalysisModuleRunner.DATA.DATA.root");
  fill_pteta((TTree *) f_data->Get("AnalysisTree"), h_pt_data, h_eta_data);
  fill_control((TTree *) f_data->Get("AnalysisTree"), h_pt_data_control, h_eta_data_control);

  // claculating MC trigger efficiency in ttbar MC
  TFile *f_tt=new TFile(fdir+"uhh2.AnalysisModuleRunner.MC.TTbar.root");
  fill_pteta((TTree *) f_tt->Get("AnalysisTree"), h_pt_mc, h_eta_mc);
  fill_control((TTree *) f_tt->Get("AnalysisTree"), h_pt_tt, h_eta_tt);
  fill_control((TTree *) f_tt->Get("AnalysisTree"), h_pt_mc_control, h_eta_mc_control);

  AdjustBinContent(h_pt_mc[1], h_pt_mc[0], "pt - ");

  if(debug) cout << "Plots Hists ... " << endl;
  if(debug) cout << "\n\t ... data" << endl;
  PlotHist(h_pt_data[0], "p_{T}", "data_pt_all");
  PlotHist(h_pt_data[1], "p_{T}", "data_pt_pass");
  PlotHist(h_pt_data[2], "p_{T}", "data_pt_fail_highpt");
  PlotHist(h_pt_data[3], "p_{T}", "data_pt_pass_highpt");
  PlotHist(h_eta_data[0], "#eta", "data_eta_all");
  PlotHist(h_eta_data[1], "#eta", "data_eta_pass");
  PlotHist(h_eta_data[2], "#eta", "data_eta_lowpt_all");
  PlotHist(h_eta_data[3], "#eta", "data_eta_lowpt_pass");
  PlotHist(h_eta_data[4], "#eta", "data_eta_midpt_all");
  PlotHist(h_eta_data[5], "#eta", "data_eta_midpt_pass");
  PlotHist(h_eta_data[6], "#eta", "data_eta_highpt_all");
  PlotHist(h_eta_data[7], "#eta", "data_eta_highpt_pass");
  PlotHist(h_eta_data[8], "#eta", "data_eta_highpt_fail");

  if(debug) cout << "\n\t ... MC" << endl;
  PlotHist(h_pt_mc[0], "p_{T}", "mc_pt_all");
  PlotHist(h_pt_mc[1], "p_{T}", "mc_pt_pass");
  PlotHist(h_pt_mc[2], "p_{T}", "mc_pt_fail_highpt");
  PlotHist(h_pt_mc[3], "p_{T}", "mc_pt_pass_highpt");
  // PlotHist(h_pt_mc[4], "p_{T}", "mc_pt_elec");
  // PlotHist(h_pt_mc[5], "p_{T}", "mc_pt_photon");
  PlotHist(h_eta_mc[0], "#eta", "mc_eta_all");
  PlotHist(h_eta_mc[1], "#eta", "mc_eta_pass");
  PlotHist(h_eta_mc[2], "#eta", "mc_eta_lowpt_all");
  PlotHist(h_eta_mc[3], "#eta", "mc_eta_lowpt_pass");
  PlotHist(h_eta_mc[4], "#eta", "mc_eta_midpt_all");
  PlotHist(h_eta_mc[5], "#eta", "mc_eta_midpt_pass");
  PlotHist(h_eta_mc[6], "#eta", "mc_eta_highpt_all");
  PlotHist(h_eta_mc[7], "#eta", "mc_eta_highpt_pass");
  PlotHist(h_eta_mc[8], "#eta", "mc_eta_highpt_fail");

  // ===========================================================================
  // Control Plots
  TH1F* ratio_eta_all_data = GetRatio(h_eta_data_control[0], h_eta_mc_control[0], false);
  TH1F* ratio_eta_all_mc = GetRatio(h_eta_mc_control[0], h_eta_mc_control[0], true);
  TH1F* ratio_eta_pass_data = GetRatio(h_eta_data_control[1], h_eta_mc_control[1], false);
  TH1F* ratio_eta_pass_mc = GetRatio(h_eta_mc_control[1], h_eta_mc_control[1], true);

  TH1F* ratio_pt_all_data = GetRatio(h_pt_data_control[0], h_pt_mc_control[0], false);
  TH1F* ratio_pt_all_mc = GetRatio(h_pt_mc_control[0], h_pt_mc_control[0], true);
  TH1F* ratio_pt_pass_data = GetRatio(h_pt_data_control[1], h_pt_mc_control[1], false);
  TH1F* ratio_pt_pass_mc = GetRatio(h_pt_mc_control[1], h_pt_mc_control[1], true);

  // void DrawControl(TString path, VecH hists, TH1F* rData, TH1F* rMC, VecI colors, VecTS names)
  DrawControl("eta_all_"+year, {h_eta_data_control[0], h_eta_dy[0], h_eta_di[0], h_eta_wj[0], h_eta_st[0], h_eta_tt[0]}, ratio_eta_all_data, ratio_eta_all_mc, {kBlack, kYellow+1, kMagenta+2, kGreen+2, kBlue+1, kRed+1}, {"Data", "DY", "Diboson", "WJets", "Single Top", "t#bar{t}"}, "#eta_{e}");
  DrawControl("eta_pass_"+year, {h_eta_data_control[1], h_eta_dy[1], h_eta_di[1], h_eta_wj[1], h_eta_st[1], h_eta_tt[1]}, ratio_eta_pass_data, ratio_eta_pass_mc, {kBlack, kYellow+1, kMagenta+2, kGreen+2, kBlue+1, kRed+1}, {"Data", "DY", "Diboson", "WJets", "Single Top", "t#bar{t}"}, "#eta_{e}");
  DrawControl("pt_all_"+year, {h_pt_data_control[0], h_pt_dy[0], h_pt_di[0], h_pt_wj[0], h_pt_st[0], h_pt_tt[0]}, ratio_pt_all_data, ratio_pt_all_mc, {kBlack, kYellow+1, kMagenta+2, kGreen+2, kBlue+1, kRed}, {"Data", "DY", "Diboson", "WJets", "Single Top", "t#bar{t}"}, "p_{T}");
  DrawControl("pt_pass_"+year, {h_pt_data_control[1], h_pt_dy[1], h_pt_di[1], h_pt_wj[1], h_pt_st[1], h_pt_tt[1]}, ratio_pt_pass_data, ratio_pt_pass_mc, {kBlack, kYellow+1, kMagenta+2, kGreen+2, kBlue+1, kRed}, {"Data", "DY", "Diboson", "WJets", "Single Top", "t#bar{t}"}, "p_{T}");

  // ===========================================================================
  //                        Efficiency
  // ===========================================================================
  // TGraphAsymmErrors divides bin content of the two input histograms

  /*
  Necessary for binning which consideres gap in ECAL.
  The bins in data and mc are abs(eta) in [1444, 1.566] are zero.
  This leads to problems in the construction of the TGraphs
  With FillGap avoid division by zero.
  */

  FillEGap(h_eta_data[0]); FillEGap(h_eta_mc[0]);
  FillEGap(h_eta_data[2]); FillEGap(h_eta_mc[2]);
  FillEGap(h_eta_data[4]); FillEGap(h_eta_mc[4]);
  FillEGap(h_eta_data[6]); FillEGap(h_eta_mc[6]);

  if(debug) cout << "Create efficiency graphs ... " << endl;
  TGraphAsymmErrors* h_effi_pt_data = new TGraphAsymmErrors(h_pt_data[1], h_pt_data[0],"cl=0.683 b(1,1) mode");
  //TGraphAsymmErrors* h_effi_pt_data_elec = new TGraphAsymmErrors(h_pt_data[4], h_pt_data[0],"cl=0.683 b(1,1) mode");
  //TGraphAsymmErrors* h_effi_pt_data_photon = new TGraphAsymmErrors(h_pt_data[5], h_pt_data[0],"cl=0.683 b(1,1) mode");
  TGraphAsymmErrors* h_effi_eta_data = new TGraphAsymmErrors(h_eta_data[1], h_eta_data[0],"cl=0.683 b(1,1) mode");
  TGraphAsymmErrors* h_effi_eta_lowpt_data = new TGraphAsymmErrors(h_eta_data[3], h_eta_data[2],"cl=0.683 b(1,1) mode");
  TGraphAsymmErrors* h_effi_eta_midpt_data = new TGraphAsymmErrors(h_eta_data[5], h_eta_data[4],"cl=0.683 b(1,1) mode");
  TGraphAsymmErrors* h_effi_eta_highpt_data = new TGraphAsymmErrors(h_eta_data[7], h_eta_data[6],"cl=0.683 b(1,1) mode");

   cout << h_pt_mc[1]->GetEntries() << "\t" << h_pt_mc[0]->GetEntries() << endl;
   cout << h_pt_mc[1]->GetDimension() << "\t" << h_pt_mc[0]->GetDimension() << endl;
   cout << h_pt_data[1]->GetEntries() << "\t" << h_pt_data[0]->GetEntries() << endl;
   cout << "mc"<< endl;
   for(int i=1; i<=h_pt_mc[0]->GetNbinsX();i++) cout << "\t" << h_pt_mc[0]->GetBinContent(i);
   cout << endl;
   for(int i=1; i<=h_pt_mc[1]->GetNbinsX();i++) cout << "\t" << h_pt_mc[1]->GetBinContent(i);
   cout << endl;
   cout << "data"<< endl;
   for(int i=1; i<=h_pt_data[0]->GetNbinsX();i++) cout << "\t" << h_pt_data[0]->GetBinContent(i);
   cout << endl;
   for(int i=1; i<=h_pt_data[1]->GetNbinsX();i++) cout << "\t" << h_pt_data[1]->GetBinContent(i);
   cout << endl;

  if(debug) std::cout << "got effi data" << std::endl;

  TGraphAsymmErrors* h_effi_pt_mc = new TGraphAsymmErrors(h_pt_mc[1], h_pt_mc[0],"cl=0.683 b(1,1) mode");
  // TGraphAsymmErrors* h_effi_pt_mc_elec = new TGraphAsymmErrors(h_pt_mc[4], h_pt_mc[0],"cl=0.683 b(1,1) mode");
  // TGraphAsymmErrors* h_effi_pt_mc_photon = new TGraphAsymmErrors(h_pt_mc[5], h_pt_mc[0],"cl=0.683 b(1,1) mode");
  TGraphAsymmErrors* h_effi_eta_mc = new TGraphAsymmErrors(h_eta_mc[1], h_eta_mc[0],"cl=0.683 b(1,1) mode");
  TGraphAsymmErrors* h_effi_eta_lowpt_mc = new TGraphAsymmErrors(h_eta_mc[3], h_eta_mc[2],"cl=0.683 b(1,1) mode");
  TGraphAsymmErrors* h_effi_eta_midpt_mc = new TGraphAsymmErrors(h_eta_mc[5], h_eta_mc[4],"cl=0.683 b(1,1) mode");
  TGraphAsymmErrors* h_effi_eta_highpt_mc = new TGraphAsymmErrors(h_eta_mc[7], h_eta_mc[6],"cl=0.683 b(1,1) mode");

  if(debug) cout << "Plot efficiency graphs ... " << endl;
  PlotEfficiency(h_effi_pt_data, h_effi_pt_mc, "p_{T}", "effi_pt");
  // PlotEfficiency(h_effi_pt_data_elec, h_effi_pt_mc_elec, "p_{T}", "effi_pt_elec");
  // PlotEfficiency(h_effi_pt_data_photon, h_effi_pt_mc_photon, "p_{T}", "effi_pt_photon");
  PlotEfficiency(h_effi_eta_data, h_effi_eta_mc, "#eta", "effi_eta");
  PlotEfficiency(h_effi_eta_lowpt_data, h_effi_eta_lowpt_mc, "#eta", "effi_eta_lowpt");
  PlotEfficiency(h_effi_eta_midpt_data, h_effi_eta_midpt_mc, "#eta", "effi_eta_midpt");
  PlotEfficiency(h_effi_eta_highpt_data, h_effi_eta_highpt_mc, "#eta", "effi_eta_highpt");

  // ===========================================================================
  //                        SF
  // ===========================================================================
  if(debug) cout << "Scale Factors ... " << endl;
  vector<TH1F*> h_SF_pt = GetSF(h_effi_pt_data, h_effi_pt_mc, h_pt_data[0]);
  vector<TH1F*> h_SF_eta = GetSF(h_effi_eta_data, h_effi_eta_mc, h_eta_data[0]);
  vector<TH1F*> h_SF_eta_lowpt = GetSF(h_effi_eta_lowpt_data, h_effi_eta_lowpt_mc, h_eta_data[2]);
  vector<TH1F*> h_SF_eta_midpt = GetSF(h_effi_eta_midpt_data, h_effi_eta_midpt_mc, h_eta_data[4]);
  vector<TH1F*> h_SF_eta_highpt = GetSF(h_effi_eta_highpt_data, h_effi_eta_highpt_mc, h_eta_data[6]);

  if(debug) cout << "\t ... Plot SF" << endl;
  PlotSF(h_SF_pt, "p_{T}", "SF_pt");
  PlotSF(h_SF_eta, "#eta", "SF_eta");
  PlotSF(h_SF_eta_lowpt, "#eta", "SF_eta_lowpt");
  PlotSF(h_SF_eta_midpt, "#eta", "SF_eta_midpt");
  PlotSF(h_SF_eta_highpt, "#eta", "SF_eta_highpt");

  // ===========================================================================
  //                        Ntuples
  // ===========================================================================
  if(argc == 2){
    cout << "Creating file..." << endl;
    TFile * f_out = new TFile("files_EleTrigger/ElecTriggerSF"+year+".root","RECREATE");;
    h_SF_pt[0]->Write("Central_pt");
    h_SF_pt[1]->Write("Up_pt");
    h_SF_pt[2]->Write("Down_pt");
    h_SF_eta[0]->Write("Central_eta");
    h_SF_eta[1]->Write("Up_eta");
    h_SF_eta[2]->Write("Down_eta");
    h_SF_eta_lowpt[0]->Write("Central_eta_lowpt");
    h_SF_eta_lowpt[1]->Write("Up_eta_lowpt");
    h_SF_eta_lowpt[2]->Write("Down_eta_lowpt");
    h_SF_eta_midpt[0]->Write("Central_eta_midpt");
    h_SF_eta_midpt[1]->Write("Up_eta_midpt");
    h_SF_eta_midpt[2]->Write("Down_eta_midpt");
    h_SF_eta_highpt[0]->Write("Central_eta_highpt");
    h_SF_eta_highpt[1]->Write("Up_eta_highpt");
    h_SF_eta_highpt[2]->Write("Down_eta_highpt");
    f_out->Close();
  }

  // ===========================================================================
  //                        Additional Hists
  // ===========================================================================
  // cout << "Additional hists for debugging..." << endl;
  // CompareHists(h_pt_mc[0], h_pt_mc[1], "p_{T}", "Compare_MC")

  return 0;
}

// ==================================================================================================
void AdjustBinContent(TH1F* h_pass, TH1F* h_all, TString text){
  for(unsigned int i=0; i<=h_all->GetNbinsX()+1; i++){
    if(h_pass->GetBinContent(i) >= h_all->GetBinContent(i)){
      cout << text << "\t pass: " << h_pass->GetBinContent(i) << "\t all: " << h_all->GetBinContent(i) << endl;
      h_pass->SetBinContent(i, h_all->GetBinContent(i));
    }
  }
}

// ==================================================================================================

void fill_control(TTree* tree, vector<TH1F*> h_pt, vector<TH1F*> h_eta){
  if(!tree) cout << "could not read tree\n";

  // outputFile->cd();
  tree->ResetBranchAddresses();
  tree->SetBranchAddress("pt",&pt);
  tree->SetBranchAddress("eta",&eta);
  tree->SetBranchAddress("passed",&passed);
  tree->SetBranchAddress("weight",&weight);

  for(Int_t ievent=0; ievent < tree->GetEntriesFast(); ievent++) {
    if(tree->GetEntry(ievent)<=0) break;
    h_pt[0]->Fill(pt, weight);
    h_eta[0]->Fill(eta, weight);

    if(passed){
      h_pt[1]->Fill(pt, weight);
      h_eta[1]->Fill(eta, weight);
    }
  }
  return;
}

// ==================================================================================================

void fill_pteta(TTree* tree, vector<TH1F*> h_pt, vector<TH1F*> h_eta){
  if(!tree) cout << "could not read tree\n";

  // For debugging pt efficiency in 2017
  TH2F* h_eta_pt_all = new TH2F("h_eta_pt_all", "eta vs pt", eta_bins.size()-1, &eta_bins[0], pt_bins.size()-1, &pt_bins[0]);
  TH2F* h_eta_pt_pass = new TH2F("h_eta_pt_pass", "eta vs pt", eta_bins.size()-1, &eta_bins[0], pt_bins.size()-1, &pt_bins[0]);
  TH2F* h_eta_pt_all_lowpt = new TH2F("h_eta_pt_all_lowpt", "eta vs pt", eta_bins.size()-1, &eta_bins[0], pt_bins.size()-1, &pt_bins[0]);
  TH2F* h_eta_pt_pass_lowpt = new TH2F("h_eta_pt_pass_lowpt", "eta vs pt", eta_bins.size()-1, &eta_bins[0], pt_bins.size()-1, &pt_bins[0]);

  // outputFile->cd();
  tree->ResetBranchAddresses();
  tree->SetBranchAddress("pt",&pt);
  tree->SetBranchAddress("eta",&eta);
  tree->SetBranchAddress("passed",&passed);
  // tree->SetBranchAddress("passed_elec",&passed_elec);
  // tree->SetBranchAddress("passed_photon",&passed_photon);
  //tree->SetBranchAddress("weight_SFpt",&weight_sfpt);
  //tree->SetBranchAddress("weight_SFeta",&weight_sfeta);
  //tree->SetBranchAddress("weight_SFetapt",&weight_sfetapt);
  //tree->SetBranchAddress("weight_SFetaptUP",&weight_sfetaptUP);
  //tree->SetBranchAddress("weight_SFetaptDOWN",&weight_sfetaptDOWN);
  tree->SetBranchAddress("weight",&weight);
  //tree->SetBranchAddress("run",&run);
  //tree->SetBranchAddress("lumi",&lumin);
  //tree->SetBranchAddress("eventnr",&eventnr);

  tree->SetBranchStatus("*",1);

  int ipass = 0; int ifull = 0; int ineg = 0; int ineg_pass = 0;
  for(Int_t ievent=0; ievent < tree->GetEntriesFast(); ievent++) {
    if(tree->GetEntry(ievent)<=0) break;

    ifull++; // debugging
    h_eta_pt_all->Fill(eta, pt, weight); // debugging
    if(pt<300) h_eta_pt_all_lowpt->Fill(eta, pt, weight); // debugging
    // if(eta<1.566 && 1.444<eta) cout << "INNNN " << eta << "\t" << pt << endl;
    h_pt[0]->Fill(pt, weight);
    h_eta[0]->Fill(eta, weight);
    if(pt < 120)             h_eta[2]->Fill(eta, weight);
    else if(pt>120 && pt<200)h_eta[4]->Fill(eta, weight);
    else if(pt>200)          h_eta[6]->Fill(eta, weight);

    //if(!passed&&debug){
    //  if(pt>200){
    //    h_pt[2]->Fill(pt, weight);
    //    h_eta[8]->Fill(eta, weight);
    //    //cout << "--------------------" << endl;
    //    //cout << "run:        " << run << endl;
    //    //cout << "lumi block: " << lumin << endl;
    //    //cout << "event nr:   " << eventnr << endl;
    //  }
    //}

    if(weight<0&&pt>300) ineg++;

    if(passed){
      ipass++; // debugging
      h_eta_pt_pass->Fill(eta, pt, weight); // debugging
      if(pt<300) h_eta_pt_pass_lowpt->Fill(eta, pt, weight); // debugging

      // cout << pt << ", " << eta << endl;
      // cout  << weight << ", "<< weight_sfpt << ", " << weight_sfeta << ", " << weight_sfetapt << endl;
      //double weight_pass = 0;
      //if(weighttag == "weight_sfpt") weight_pass = weight_sfpt;
      //else if(weighttag == "weight_sfeta") weight_pass = weight_sfeta;
      //else if(weighttag == "weight_sfetapt") weight_pass = weight_sfetapt;
      //else if(weighttag == "weight_sfetaptUP") weight_pass = weight_sfetaptUP;
      //else if(weighttag == "weight_sfetaptDOWN") weight_pass = weight_sfetaptDOWN;
      //else weight_pass = weight;
      // if(year=="2017"&&ievent==10) cout << "weight: " << weight << "\t" << "weight_pass: " << weight_pass << endl;
      h_pt[1]->Fill(pt, weight);
      h_eta[1]->Fill(eta, weight);
      if(pt < 120)             h_eta[3]->Fill(eta, weight);
      else if(pt>120 && pt<200)h_eta[5]->Fill(eta, weight);
      else if(pt>200)          h_eta[7]->Fill(eta, weight);

      if(weight<0&&pt>300) ineg_pass++;
      if(pt>200) h_pt[3]->Fill(pt, weight);

    }

    /* Only checked one trigger for pT>120 GeV */
    // if( (pt<120 && passed) || passed_elec) h_pt[4]->Fill(pt, weight);
    // if( (pt<120 && passed) || passed_photon) h_pt[5]->Fill(pt, weight);

  }

  // For debugging pt efficiency in 2017
  PlotHist(h_eta_pt_all, "#eta", "p_{T}", "etaVSpt_all");
  PlotHist(h_eta_pt_pass, "#eta", "p_{T}", "etaVSpt_pass");
  PlotHist(h_eta_pt_all_lowpt, "#eta", "p_{T}", "etaVSpt_all_lowpt");
  PlotHist(h_eta_pt_pass_lowpt, "#eta", "p_{T}", "etaVSpt_pass_lowpt");
  // tdrDiCanvas2("etaVSpt_all", -2.5, 2.5, 55, 1500, 0.6, 1.6, "#eta", "p_{T}", "ratio");
  // TCanvas* tdrDiCanvas2(const char* canvName, double x_min, double x_max, double y_min, double y_max, double y_min2, double y_max2,  const char* nameXaxis, const char* nameYaxis, const char* nameYaxis2, bool square = kRectangular, int iPeriod = 4, int iPos = 11) {
  // GetRatio();

  return;
}

// ==================================================================================================
// calculate central value and up/down variation of SF and return in vector
// [0] - central
// [1] - up
// [2] - down
vector<TH1F*> GetSF(TGraphAsymmErrors* h_data, TGraphAsymmErrors* h_mc, TH1F* hist){
  TH1F* h_central = (TH1F*) hist->Clone();
  TH1F* h_up = (TH1F*) hist->Clone();
  TH1F* h_down = (TH1F*) hist->Clone();
  int nbins = hist->GetSize() -2;
  cout << "Nbins " << nbins << endl;

  for(unsigned int i=0; i<nbins; i++){
    double xvalue = hist->GetBinCenter(i+1);
    double value_data = h_data->Eval(xvalue);
    double e_data_hi = h_data->GetErrorYhigh(i);
    double e_data_lo = h_data->GetErrorYlow(i);

    double value_mc = h_mc->Eval(xvalue);
    double e_mc_hi = h_mc->GetErrorYhigh(i);
    double e_mc_lo = h_mc->GetErrorYlow(i);

    double central = 1;
    if(value_data != 0 && value_mc != 0) central = value_data/value_mc;

    double up = 0;
    if(value_mc != 0) up = -value_data/(value_mc*value_mc) * e_mc_hi + e_data_hi/value_mc;

    double down = 0;
    if(value_mc != 0) down = -value_data/(value_mc*value_mc) * e_mc_lo + e_data_lo/value_mc;

    // add 2% uncertainty to cover non-closure
    up += 0.02;
    down += 0.02;

    // cout << i<< ", " << xvalue << ", " << value_mc << ", " << value_data << ", "<< central << endl;
    h_central->SetBinContent(i+1, central);
    h_up->SetBinContent(i+1, central+up);
    h_down->SetBinContent(i+1, central-down);
    // bin errors are just set very small to not annoy in plotting
    h_central->SetBinError(i+1, 0.000000000000001);
    h_up->SetBinError(i+1, 0.000000000000001);
    h_down->SetBinError(i+1, 0.000000000000001);
  }
  vector<TH1F*> h_sf;
  h_sf.push_back(h_central);
  h_sf.push_back(h_up);
  h_sf.push_back(h_down);
  return h_sf;
}


// ==================================================================================================

void PlotEfficiency(TGraphAsymmErrors* h_data, TGraphAsymmErrors* h_mc, TString xaxis, TString histname){
  // if(histname == "effi_pt") cout << h_data->Eval(25) << endl;
  // if(histname == "effi_pt") cout << h_mc->Eval(25) << endl;

  h_data->SetTitle(" ");
  h_data->GetXaxis()->SetTitle(xaxis);
  h_data->GetYaxis()->SetTitle("efficiency");
  h_data->GetYaxis()->SetTitleOffset(1.6);
  h_data->GetXaxis()->SetTitleOffset(1.3);
  h_data->GetXaxis()->SetNdivisions(505);
  h_data->GetYaxis()->SetNdivisions(505);
  if(xaxis.Contains("p_{T}")) h_data->GetXaxis()->SetRangeUser(0.0, 1500);
  h_data->GetYaxis()->SetRangeUser(0.0, 1.1);

  h_data->SetLineColor(kBlack);
  h_data->SetMarkerColor(kBlack);
  h_data->SetMarkerStyle(2);
  h_data->SetMarkerSize(0.2);

  h_mc->SetLineColor(kRed);
  h_mc->SetMarkerColor(kRed);
  h_mc->SetMarkerStyle(2);
  h_mc->SetMarkerSize(0.2);

  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetLegendBorderSize(0);

  TLine* line = new TLine(120, 0, 120, 1.1);
  line->SetLineWidth(1);
  // GetRatio(h_data, h_mc, false);

  TCanvas *A = new TCanvas("A", "A", 600, 600);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.1);
  h_data->Draw("AP");
  h_mc->Draw("P SAME");

  TLegend *leg = new TLegend(0.33,0.20,0.66,0.33);
  // leg->SetHeader(textBin);
  leg->AddEntry(h_data,"data","pl");
  leg->AddEntry(h_mc,"simulation","pl");
  leg->Draw("");

  DrawText(histname);
  gPad->RedrawAxis();
  if(weighttag == "weight_sfpt") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfeta") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetapt") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetaptUP") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetaptDOWN") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  delete A;
  return;
}

// ==================================================================================================

void PlotHist(TH1F* hist, TString xaxis, TString histname){
  hist->SetTitle(" ");
  hist->GetXaxis()->SetTitle(xaxis);
  hist->GetYaxis()->SetTitle("events");
  hist->GetYaxis()->SetTitleOffset(1.6);
  hist->GetXaxis()->SetTitleOffset(1.3);
  hist->GetXaxis()->SetNdivisions(505);
  hist->GetYaxis()->SetNdivisions(505);
  hist->GetYaxis()->SetRangeUser(0, hist->GetMaximum()*1.2);
  hist->SetLineColor(kBlack);
  hist->SetFillColor(13);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetLegendBorderSize(0);

  TCanvas *A = new TCanvas("A", "A", 600, 600);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.1);
  hist->Draw("HIST");
  DrawText(histname);
  gPad->RedrawAxis();
  if(weighttag == "weight_sfpt") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfeta") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetapt") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetaptUP") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetaptDOWN") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  delete A;
  return;
}

// ==================================================================================================

void PlotHist(TH2F* hist, TString xaxis, TString yaxis, TString histname){
  hist->SetTitle(" ");
  hist->GetXaxis()->SetTitle(xaxis);
  hist->GetYaxis()->SetTitle(yaxis);
  hist->GetZaxis()->SetTitle("Events");
  hist->GetYaxis()->SetTitleOffset(1.7);
  hist->GetXaxis()->SetTitleOffset(1.3);
  hist->GetZaxis()->SetTitleOffset(1.2);
  hist->GetXaxis()->SetNdivisions(505);
  hist->GetYaxis()->SetNdivisions(505);
  hist->GetZaxis()->SetRangeUser(0, 80);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetLegendBorderSize(0);

  TCanvas *A = new TCanvas("A", "A", 600, 600);
  gPad->SetLeftMargin(0.12);
  gPad->SetRightMargin(0.15);
  gPad->SetBottomMargin(0.1);
  hist->Draw("COLZ");
  DrawText(histname);
  gPad->RedrawAxis();
  A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  delete A;
  return;
}

// ==================================================================================================

void PlotSF(vector<TH1F*> h_SF, TString xaxis, TString histname){
  if(h_SF.size() != 3) cout << "THERE ARE NOT EXACTLY 3 SF hists" << endl;
  h_SF[0]->SetTitle(" ");
  h_SF[0]->GetXaxis()->SetTitle(xaxis);
  h_SF[0]->GetYaxis()->SetTitle("scale factor");
  h_SF[0]->GetYaxis()->SetTitleOffset(1.6);
  h_SF[0]->GetXaxis()->SetTitleOffset(1.3);
  h_SF[0]->GetXaxis()->SetNdivisions(505);
  h_SF[0]->GetYaxis()->SetNdivisions(505);
  h_SF[0]->GetYaxis()->SetRangeUser(0.7, 1.05);
  //if(histname.Contains("mid")) h_SF[0]->GetYaxis()->SetRangeUser(0.7, 1.5);
  h_SF[0]->SetLineColor(kBlack);
  h_SF[0]->SetLineWidth(3);
  h_SF[0]->SetFillColor(13);
  h_SF[0]->SetMarkerStyle(0);

  if(weighttag == "weight_sfpt") h_SF[0]->GetYaxis()->SetRangeUser(0.89, 1.11);
  else if(weighttag == "weight_sfeta") h_SF[0]->GetYaxis()->SetRangeUser(0.89, 1.11);
  else if(weighttag == "weight_sfetapt") h_SF[0]->GetYaxis()->SetRangeUser(0.89, 1.11);
  // else if(weighttag == "weight_sfetaptUP") h_SF[0]->GetYaxis()->SetRangeUser(0.85, 1.15);
  // else if(weighttag == "weight_sfetaptDOWN") h_SF[0]->GetYaxis()->SetRangeUser(0.85, 1.15);

  // For root file
  h_SF[1]->GetYaxis()->SetTitle("scale factor");
  h_SF[1]->GetYaxis()->SetRangeUser(0.7, 1.5);
  if(histname.Contains("mid")) h_SF[1]->GetYaxis()->SetRangeUser(0.7, 1.5);
  h_SF[2]->GetYaxis()->SetTitle("scale factor");
  h_SF[2]->GetYaxis()->SetRangeUser(0.7, 1.5);
  if(histname.Contains("mid")) h_SF[2]->GetYaxis()->SetRangeUser(0.7, 1.5);

  Color_t uncert_col = kOrange+9;

  h_SF[1]->SetLineColor(uncert_col);
  h_SF[1]->SetFillStyle(3144);
  h_SF[1]->SetFillColor(uncert_col);
  h_SF[2]->SetLineColor(uncert_col);
  h_SF[2]->SetFillColor(10);

  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetLegendBorderSize(0);

  TCanvas *A = new TCanvas("A", "A", 600, 600);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.1);
  h_SF[0]->Draw("E1");
  h_SF[1]->Draw("HIST SAME");
  h_SF[2]->Draw("HIST SAME");
  h_SF[0]->Draw("E1 SAME");

  TLegend *leg = new TLegend(0.33,0.20,0.66,0.33);
  leg->AddEntry(h_SF[0],"scale factor","l");
  leg->AddEntry(h_SF[1],"uncertainty","f");
  leg->Draw();

  DrawText(histname);
  gPad->RedrawAxis();
  if(weighttag == "weight_sfpt") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfeta") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetapt") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetaptUP") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else if(weighttag == "weight_sfetaptDOWN") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  else A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  delete A;
  return;
}

// ==================================================================================================

void CompareHists(TH1F* h_all, TH1F* h_pass, TString xaxis, TString histname){
  h_all->SetTitle(" ");
  h_all->GetXaxis()->SetTitle(xaxis);
  h_all->GetYaxis()->SetTitle("events");
  h_all->GetYaxis()->SetTitleOffset(1.6);
  h_all->GetXaxis()->SetTitleOffset(1.3);
  h_all->GetXaxis()->SetNdivisions(505);
  h_all->GetYaxis()->SetNdivisions(505);
  h_all->GetYaxis()->SetRangeUser(0, h_all->GetMaximum()*1.1);
  h_all->SetLineColor(kBlack);
  h_all->SetFillColor(13);

  h_pass->SetLineColor(kRed+1);
  h_pass->SetLineWidth(1);

  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  gStyle->SetLegendBorderSize(0);

  TCanvas *A = new TCanvas("A", "A", 600, 600);
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.1);
  h_all->Draw("HIST");
  h_pass->Draw("HIST SAME");
  gPad->RedrawAxis();
  if(weighttag == "weight") A->SaveAs("plots_EleTrigger/"+histname+"_"+year+".pdf");
  delete A;
  return;
}

// ==================================================================================================

TH1F* GetRatioGraph(TGraphAsymmErrors* h1, TGraphAsymmErrors* h2, bool isData){
  TH1F* g1 = h1->GetHistogram();
  TH1F* g2 = h2->GetHistogram();
  TH1F* ratio = (TH1F*) g1->Clone();
  int Nbins = g1->GetNbinsX();
  cout << Nbins << endl;
  for(int i=1; i<=Nbins;i++){
    double N1 = g1->GetBinContent(i);
    double N2 = g2->GetBinContent(i);
    double E1 = g1->GetBinError(i);
    double E2 = g2->GetBinError(i);
    cout << "1: " << N1 << "\t 2: " << N2 << endl;
    if(N1==0 || N2==0){
      if(isData) ratio->SetBinContent(i, 0);
      else       ratio->SetBinContent(i, 1);

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

// ==================================================================================================
void FillEGap(TH1F* h){
  for(unsigned int i=1; i<=h->GetNbinsX(); i++){
    // high bin content to make error bars very small
    if(abs(h->GetBinCenter(i))==1.505) h->SetBinContent(i, 1000000);
  }
  return;
}

// ==================================================================================================
void DrawControl(TString path, VecH hists, TH1F* rData, TH1F* rMC, VecI colors, VecTS names, TString xaxis)
{
  TString unique_path = "plots_EleTrigger/Control_"+path+".pdf";
  double nHists = hists.size();
  double bins = hists[0]->GetNbinsX();

  if(debug) cout << "Draw Control Hists ..." << endl;
  hists[0]->SetTitle("");
  hists[0]->GetXaxis()->SetTitle("");
  hists[0]->GetYaxis()->SetTitle("Events");
  hists[0]->SetMarkerStyle(8);
  hists[0]->SetMarkerColor(colors[0]);
  hists[0]->SetLineColor(colors[0]);

  THStack* stack = new THStack(unique_path, "");
  for(unsigned int c=1; c<colors.size(); c++){
    hists[c]->SetFillColor(colors[c]);
    hists[c]->SetLineColor(colors[c]);
    stack->Add(hists[c]);
  }
  double maximum = stack->GetMaximum();

  TLegend *leg = new TLegend(0.7,0.6,0.85,0.85);
  TCanvas *A = new TCanvas(unique_path, unique_path, 600, 600);

  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.12);

  TH1F* errorUp = (TH1F*) rMC->Clone(); TH1F* errorDown = (TH1F*) rMC->Clone();
  for(unsigned int i=1; i<=rMC->GetNbinsX(); i++){
    errorUp->SetBinContent(i, rMC->GetBinContent(i)+rMC->GetBinError(i));
    errorDown->SetBinContent(i, rMC->GetBinContent(i)-rMC->GetBinError(i));
  }
  errorUp->SetFillColorAlpha(kGray+2, 0.5);
  errorUp->SetLineWidth(0);
  errorDown->SetFillColorAlpha(kWhite, 1);
  errorDown->SetLineWidth(0);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.31, 1, 1.0);
  pad1->SetBottomMargin(0.02); // 0.015
  pad1->SetLeftMargin(0.19);
  pad1->Draw();
  pad1->cd();

  hists[0]->Draw("P");
  hists[0]->GetXaxis()->SetLabelSize(0);
  hists[0]->GetYaxis()->SetRangeUser(0, maximum*1.5);
  hists[0]->GetYaxis()->SetTitle("Events");
  hists[0]->GetYaxis()->SetLabelSize(0.05);
  hists[0]->GetYaxis()->SetTitleSize(0.06);
  hists[0]->GetYaxis()->SetTitleOffset(1.15);
  stack->Draw("same hist");
  hists[0]->Draw("same PE"); // redraw
  gPad->RedrawAxis();

  leg->AddEntry(hists[0], "Data", "pl");
  for(int i=nHists-1; 1<=i; i--) leg->AddEntry(hists[i], names[i], "f");
  leg->SetTextSize(0.04);
  leg->Draw();

  CMSLabel(0.25, 0.83, "Work in Progress");
  LumiInfo(lumi_plot, false, 0.9, 0.96);

  // Ratio Plot kommt in unteres pad
  A->cd();
  if(debug) cout << "\t ... Pad2" << endl;
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.19);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.4);
  pad2->Draw();
  pad2->cd();

  A->SetTickx(0);
  A->SetTicky(0);

  TLine* lMC = new TLine(-2.5, 1, 2.5, 1);
  lMC->SetLineWidth(1);
  lMC->SetLineColor(kBlack);

  rData->SetMarkerStyle(8);
  rData->SetLineColor(colors[0]);
  rMC->SetFillStyle(0);
  rMC->SetLineStyle(kSolid);
  rMC->SetLineWidth(0);
  rMC->GetXaxis()->SetLabelSize(0.15);
  rMC->GetYaxis()->SetLabelSize(0.13);
  rMC->GetXaxis()->SetTitleSize(0.1);
  rMC->GetYaxis()->SetRangeUser(0.4, 1.6);
  rMC->GetXaxis()->SetTitle(xaxis);
  rMC->GetYaxis()->SetTitle("#frac{DATA}{MC}");
  rMC->GetXaxis()->SetTitleOffset(0.8);
  rMC->GetXaxis()->SetTitleSize(0.2);
  rMC->GetYaxis()->SetTitleSize(0.15);
  rMC->GetYaxis()->SetNdivisions(505);
  rMC->GetYaxis()->SetTitleOffset(0.4);
  rMC->GetYaxis()->CenterTitle();
  rMC->Draw("Axis");
  errorUp->Draw("Hist same");
  errorDown->Draw("Hist same");
  lMC->Draw("same");
  rData->Draw("SAME PE");

  gPad->RedrawAxis();
  A->SaveAs(unique_path);

  delete A;
  leg->Clear();
}

// ==================================================================================================
void DrawText(TString name){
  TString textBin = "";
  if(name.Contains("lowpt")) textBin = "p_{T} < 120 GeV";
  if(name.Contains("midpt")) textBin = "120 < p_{T} < 200 GeV";
  if(name.Contains("highpt")) textBin = "200 < p_{T} GeV";
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);
  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(0.04);
  latex.DrawLatex(0.89, 0.925,textBin);
}
