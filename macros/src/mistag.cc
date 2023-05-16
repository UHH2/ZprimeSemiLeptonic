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

void mistag(){

TString file_dir = "/nfs/dust/cms/group/zprime-uhh/AnalysisDNN_UL17/Mistag_rate/muon";

TString  filename_DATA  = file_dir + "/uhh2.AnalysisModuleRunner.DATA.DATA.root";
TString  filename_TTbar = file_dir + "/uhh2.AnalysisModuleRunner.MC.TTbar.root";
TString  filename_WJets = file_dir + "/uhh2.AnalysisModuleRunner.MC.WJets.root";
TString  filename_ST    = file_dir + "/uhh2.AnalysisModuleRunner.MC.ST.root";
TString  filename_DY    = file_dir + "/uhh2.AnalysisModuleRunner.MC.DY.root";
TString  filename_QCD   = file_dir + "/uhh2.AnalysisModuleRunner.MC.QCD.root";

TFile* f_in_DATA  = new TFile(filename_DATA, "READ");
TFile* f_in_TTbar = new TFile(filename_TTbar, "READ");
TFile* f_in_WJets = new TFile(filename_WJets, "READ");
TFile* f_in_ST    = new TFile(filename_ST, "READ");
TFile* f_in_DY    = new TFile(filename_DY, "READ");
TFile* f_in_QCD   = new TFile(filename_QCD, "READ");
 
float n_jets_DATA        = ((TH1F*)(f_in_DATA->Get("Mistag/pt_AK8jet1")))->Integral();
float n_jets_DATA_tagged = ((TH1F*)(f_in_DATA->Get("Mistag/pt_AK8jet1_tagged")))->Integral();

float n_jets_TTbar_t        = ((TH1F*)(f_in_TTbar->Get("Mistag/pt_AK8Topjet1")))->Integral();
float n_jets_TTbar_l        = ((TH1F*)(f_in_TTbar->Get("Mistag/pt_AK8Lightjet1")))->Integral();
float n_jets_TTbar_t_tagged = ((TH1F*)(f_in_TTbar->Get("Mistag/pt_AK8Topjet1_tagged")))->Integral();
float n_jets_TTbar_l_tagged = ((TH1F*)(f_in_TTbar->Get("Mistag/pt_AK8Lightjet1_tagged")))->Integral();

float n_jets_ST_t        = ((TH1F*)(f_in_ST->Get("Mistag/pt_AK8Topjet1")))->Integral();
float n_jets_ST_l        = ((TH1F*)(f_in_ST->Get("Mistag/pt_AK8Lightjet1")))->Integral();
float n_jets_ST_t_tagged = ((TH1F*)(f_in_ST->Get("Mistag/pt_AK8Topjet1_tagged")))->Integral();
float n_jets_ST_l_tagged = ((TH1F*)(f_in_ST->Get("Mistag/pt_AK8Lightjet1_tagged")))->Integral();

float n_jets_WJets        = ((TH1F*)(f_in_WJets->Get("Mistag/pt_AK8jet1")))->Integral();
float n_jets_WJets_tagged = ((TH1F*)(f_in_WJets->Get("Mistag/pt_AK8jet1_tagged")))->Integral();

float n_jets_DY        = ((TH1F*)(f_in_DY->Get("Mistag/pt_AK8jet1")))->Integral();
float n_jets_DY_tagged = ((TH1F*)(f_in_DY->Get("Mistag/pt_AK8jet1_tagged")))->Integral();

float n_jets_QCD        = ((TH1F*)(f_in_QCD->Get("Mistag/pt_AK8jet1")))->Integral();
float n_jets_QCD_tagged = ((TH1F*)(f_in_QCD->Get("Mistag/pt_AK8jet1_tagged")))->Integral();
  
//cout << "Number of leading AK8jets DATA = " << n_jets_DATA << endl;
//cout << "Number of leading AK8jets DATA tagged = " << n_jets_DATA_tagged << endl;
//
//cout << "Number of leading AK8jets TTbar tagged t = " << n_jets_TTbar_t_tagged << endl;
//cout << "Number of leading AK8jets ST tagged t = " << n_jets_ST_t_tagged << endl;
//cout << "Number of leading AK8jets TTbar t = " << n_jets_TTbar_t << endl;
//cout << "Number of leading AK8jets ST t = " << n_jets_ST_t << endl;
//
//cout << "Number of leading AK8jets QCD = " << n_jets_QCD << endl;
//cout << "Number of leading AK8jets QCD tagged = " << n_jets_QCD_tagged << endl;
//
//cout << "Number of leading AK8jets TTbar tagged l = " << n_jets_TTbar_l_tagged << endl;
//cout << "Number of leading AK8jets ST tagged l = " << n_jets_ST_l_tagged << endl;
//cout << "Number of leading AK8jets WJets tagged = " << n_jets_WJets_tagged << endl;
//cout << "Number of leading AK8jets DY tagged = " << n_jets_DY_tagged << endl;
//cout << "Number of leading AK8jets TTbar l = " << n_jets_TTbar_l << endl;
//cout << "Number of leading AK8jets ST l = " << n_jets_ST_l << endl;
//cout << "Number of leading AK8jets WJets = " << n_jets_WJets << endl;
//cout << "Number of leading AK8jets DY = " << n_jets_DY << endl;

cout << "Efficieny DATA      = " << (n_jets_DATA_tagged - n_jets_TTbar_t_tagged - n_jets_ST_t_tagged)/(n_jets_DATA - n_jets_TTbar_t - n_jets_ST_t) << endl;
cout << "Efficieny MC        = " << (n_jets_WJets_tagged + n_jets_TTbar_l_tagged + n_jets_ST_l_tagged + n_jets_DY_tagged)/(n_jets_WJets + n_jets_TTbar_l + n_jets_ST_l + n_jets_DY) << endl;
cout << "Efficieny MC wQCD   = " << (n_jets_WJets_tagged + n_jets_TTbar_l_tagged + n_jets_ST_l_tagged + n_jets_DY_tagged + n_jets_QCD_tagged)/(n_jets_WJets + n_jets_TTbar_l + n_jets_ST_l + n_jets_DY + n_jets_QCD) << endl;

cout << "SF = " << ((n_jets_DATA_tagged - n_jets_TTbar_t_tagged - n_jets_ST_t_tagged)/(n_jets_DATA - n_jets_TTbar_t - n_jets_ST_t)) / ((n_jets_WJets_tagged + n_jets_TTbar_l_tagged + n_jets_ST_l_tagged + n_jets_DY_tagged)/(n_jets_WJets + n_jets_TTbar_l + n_jets_ST_l + n_jets_DY)) << endl; 

cout << "SF wQCD = " << ((n_jets_DATA_tagged - n_jets_TTbar_t_tagged - n_jets_ST_t_tagged)/(n_jets_DATA - n_jets_TTbar_t - n_jets_ST_t))/((n_jets_WJets_tagged + n_jets_TTbar_l_tagged + n_jets_ST_l_tagged + n_jets_DY_tagged + n_jets_QCD_tagged)/(n_jets_WJets + n_jets_TTbar_l + n_jets_ST_l + n_jets_DY + n_jets_QCD)) << endl;

delete f_in_DATA;
delete f_in_TTbar;
delete f_in_WJets;
delete f_in_ST;
delete f_in_DY;
delete f_in_QCD;
}
