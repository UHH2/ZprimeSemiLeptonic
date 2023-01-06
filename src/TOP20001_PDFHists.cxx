#include <iostream>
#include <math.h>
#include <sstream>

#include "TH1F.h"
#include "TLorentzVector.h"

#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/LorentzVector.h"

#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_PDFHists.h"

using namespace std;
using namespace uhh2;

TOP20001_PDFHists::TOP20001_PDFHists(uhh2::Context & ctx, const std::string& dirname): Hists(ctx, dirname){
  is_mc = ctx.get("dataset_type") == "MC";
  is_alps = ctx.get("dataset_version").find("ALP") == 0;
  h_ttbargen = ctx.get_handle<TOP20001_TTbarGen>("ttbargen");

  for(int i=0; i<100; i++){
    std::stringstream ss_mtt_name, ss_cts_bin1_name, ss_cts_bin2_name, ss_cts_bin3_name, ss_cts_bin4_name, ss_cts_bin5_name, ss_cts_bin6_name;
    ss_mtt_name << "mtt_PDF_" << i+1;
    ss_cts_bin1_name << "cts_mtt250To420_PDF_" << i+1;
    ss_cts_bin2_name << "cts_mtt420To520_PDF_" << i+1;
    ss_cts_bin3_name << "cts_mtt520To620_PDF_" << i+1;
    ss_cts_bin4_name << "cts_mtt620To800_PDF_" << i+1;
    ss_cts_bin5_name << "cts_mtt800To1000_PDF_" << i+1;
    ss_cts_bin6_name << "cts_mtt1000To3500_PDF_" << i+1;

    stringstream ss_mtt_title, ss_cts_bin1_title, ss_cts_bin2_title, ss_cts_bin3_title, ss_cts_bin4_title, ss_cts_bin5_title, ss_cts_bin6_title;
    ss_mtt_title << "m(t#bar{t}) [GeV] for PDF #"  << i+1 << "/100";
    ss_cts_bin1_title << "cos(#theta*) (250 GeV < m(t#bar{t}) < 420 GeV) for PDF #" << i+1 << "/100";
    ss_cts_bin2_title << "cos(#theta*) (420 GeV < m(t#bar{t}) < 520 GeV) for PDF #" << i+1 << "/100";
    ss_cts_bin3_title << "cos(#theta*) (520 GeV < m(t#bar{t}) < 620 GeV) for PDF #" << i+1 << "/100";
    ss_cts_bin4_title << "cos(#theta*) (620 GeV < m(t#bar{t}) < 800 GeV) for PDF #" << i+1 << "/100";
    ss_cts_bin5_title << "cos(#theta*) (800 GeV < m(t#bar{t}) < 1000 GeV) for PDF #" << i+1 << "/100";
    ss_cts_bin6_title << "cos(#theta*) (1000 GeV < m(t#bar{t}) < 3500 GeV) for PDF #" << i+1 << "/100";

    std::string s_mtt_name = ss_mtt_name.str();
    std::string s_cts_bin1_name = ss_cts_bin1_name.str();
    std::string s_cts_bin2_name = ss_cts_bin2_name.str();
    std::string s_cts_bin3_name = ss_cts_bin3_name.str();
    std::string s_cts_bin4_name = ss_cts_bin4_name.str();
    std::string s_cts_bin5_name = ss_cts_bin5_name.str();
    std::string s_cts_bin6_name = ss_cts_bin6_name.str();

    std::string s_mtt_title = ss_mtt_title.str();
    std::string s_cts_bin1_title = ss_cts_bin1_title.str();
    std::string s_cts_bin2_title = ss_cts_bin2_title.str();
    std::string s_cts_bin3_title = ss_cts_bin3_title.str();
    std::string s_cts_bin4_title = ss_cts_bin4_title.str();
    std::string s_cts_bin5_title = ss_cts_bin5_title.str();
    std::string s_cts_bin6_title = ss_cts_bin6_title.str();

    const char* char_mtt_name = s_mtt_name.c_str();
    const char* char_cts_bin1_name = s_cts_bin1_name.c_str();
    const char* char_cts_bin2_name = s_cts_bin2_name.c_str();
    const char* char_cts_bin3_name = s_cts_bin3_name.c_str();
    const char* char_cts_bin4_name = s_cts_bin4_name.c_str();
    const char* char_cts_bin5_name = s_cts_bin5_name.c_str();
    const char* char_cts_bin6_name = s_cts_bin6_name.c_str();

    const char* char_mtt_title = s_mtt_title.c_str();
    const char* char_cts_bin1_title = s_cts_bin1_title.c_str();
    const char* char_cts_bin2_title = s_cts_bin2_title.c_str();
    const char* char_cts_bin3_title = s_cts_bin3_title.c_str();
    const char* char_cts_bin4_title = s_cts_bin4_title.c_str();
    const char* char_cts_bin5_title = s_cts_bin5_title.c_str();
    const char* char_cts_bin6_title = s_cts_bin6_title.c_str();

    mtt_hist_names[i] = s_mtt_name;
    cts_bin1_hist_names[i] = s_cts_bin1_name;
    cts_bin2_hist_names[i] = s_cts_bin2_name;
    cts_bin3_hist_names[i] = s_cts_bin3_name;
    cts_bin4_hist_names[i] = s_cts_bin4_name;
    cts_bin5_hist_names[i] = s_cts_bin5_name;
    cts_bin6_hist_names[i] = s_cts_bin6_name;

    vector<double> bins_mtt = {250,400,480,560,640,720,800,900,1000,1150,1300,1500,1700,2000,2300,3500};
    vector<double> bins_cts = {-1,-0.65,-0.3,0.0,0.3,0.65,1.0};

    book<TH1F>(char_mtt_name, char_mtt_title, bins_mtt.size()-1, &bins_mtt[0]);
    book<TH1F>(char_cts_bin1_name, char_cts_bin1_title, bins_cts.size()-1, &bins_cts[0]);
    book<TH1F>(char_cts_bin2_name, char_cts_bin2_title, bins_cts.size()-1, &bins_cts[0]);
    book<TH1F>(char_cts_bin3_name, char_cts_bin3_title, bins_cts.size()-1, &bins_cts[0]);
    book<TH1F>(char_cts_bin4_name, char_cts_bin4_title, bins_cts.size()-1, &bins_cts[0]);
    book<TH1F>(char_cts_bin5_name, char_cts_bin5_title, bins_cts.size()-1, &bins_cts[0]);
    book<TH1F>(char_cts_bin6_name, char_cts_bin6_title, bins_cts.size()-1, &bins_cts[0]);
  }
}

void TOP20001_PDFHists::fill(const Event & event){
  double weight = event.weight;
  TOP20001_TTbarGen TOP20001_TTbarGen = event.get(h_ttbargen);

  if(is_mc && TOP20001_TTbarGen.IsSemiLeptonicDecay()){
    LorentzVector top = TOP20001_TTbarGen.Top().v4();
    LorentzVector antitop = TOP20001_TTbarGen.Antitop().v4();

    double mttbar = (top + antitop).M();

    const TLorentzVector Top(top.px(), top.py(), top.pz(), top.E());
    const TLorentzVector Antitop(antitop.px(), antitop.py(), antitop.pz(), antitop.E());
    const TLorentzVector TTbar = Top + Antitop;
    TLorentzVector topcms = Top;
    topcms.Boost(-1.*TTbar.BoostVector());
    double cts = TTbar.Vect().Dot(topcms.Vect())/TTbar.P()/topcms.P();

    int MY_FIRST_INDEX = 9;
    if(is_alps) MY_FIRST_INDEX = 47;

    if(event.genInfo->systweights().size() > (unsigned int) 100 + MY_FIRST_INDEX){
      double orig_weight = event.genInfo->originalXWGTUP();

      for(int i=0; i<100; i++){
        double pdf_weight = event.genInfo->systweights().at(i+MY_FIRST_INDEX);
        const char* name_mtt = mtt_hist_names[i].c_str();
        const char* name_cts_bin1 = cts_bin1_hist_names[i].c_str();
        const char* name_cts_bin2 = cts_bin2_hist_names[i].c_str();
        const char* name_cts_bin3 = cts_bin3_hist_names[i].c_str();
        const char* name_cts_bin4 = cts_bin4_hist_names[i].c_str();
        const char* name_cts_bin5 = cts_bin5_hist_names[i].c_str();
        const char* name_cts_bin6 = cts_bin6_hist_names[i].c_str();

        hist(name_mtt)->Fill(mttbar, weight * pdf_weight / orig_weight);

        if(mttbar < 250.){} // do nothing: underflow bin
        else if(mttbar < 420.) hist(name_cts_bin1)->Fill(cts, weight * pdf_weight / orig_weight);
        else if(mttbar < 520.) hist(name_cts_bin2)->Fill(cts, weight * pdf_weight / orig_weight);
        else if(mttbar < 620.) hist(name_cts_bin3)->Fill(cts, weight * pdf_weight / orig_weight);
        else if(mttbar < 800.) hist(name_cts_bin4)->Fill(cts, weight * pdf_weight / orig_weight);
        else if(mttbar < 1000.) hist(name_cts_bin5)->Fill(cts, weight * pdf_weight / orig_weight);
        else if(mttbar < 3500.) hist(name_cts_bin6)->Fill(cts, weight * pdf_weight / orig_weight);
        else{} // do nothing: overflow bin
      }
    }
  }
}

TOP20001_PDFHists::~TOP20001_PDFHists(){}
