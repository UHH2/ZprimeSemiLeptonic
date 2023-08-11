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
#include <string>

using namespace std;

void getRMS(){

  TString uhh2_basedir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/";
  TString file_dir = "/nfs/dust/cms/group/zprime-uhh/";
  TString file_name = "";

  vector<TString> v_years = {
    "UL16preVFP",
    "UL16postVFP",
    "UL17",
    "UL18",
  };
  vector<TString> v_channels = {
    "electron",
    "muon"
  };
  vector<TString> v_root_directories = {
    "DNN_output0",
    "DNN_output1",
    "DNN_output2",
    "DNN_output0_TopTag",
    "DNN_output1_TopTag",
    "DNN_output2_TopTag",
    "DNN_output0_NoTopTag",
    "DNN_output1_NoTopTag",
    "DNN_output2_NoTopTag",
    "DNN_output0_thetastar_bin1",
    "DNN_output0_thetastar_bin2",
    "DNN_output0_thetastar_bin3",
    "DNN_output0_thetastar_bin4",
    "DNN_output0_thetastar_bin5",
    "DNN_output0_thetastar_bin6",
    "DNN_output0_TopTag_thetastar_bin1",
    "DNN_output0_TopTag_thetastar_bin2",
    "DNN_output0_TopTag_thetastar_bin3",
    "DNN_output0_TopTag_thetastar_bin4",
    "DNN_output0_TopTag_thetastar_bin5",
    "DNN_output0_TopTag_thetastar_bin6",
    "DNN_output0_NoTopTag_thetastar_bin1",
    "DNN_output0_NoTopTag_thetastar_bin2",
    "DNN_output0_NoTopTag_thetastar_bin3",
    "DNN_output0_NoTopTag_thetastar_bin4",
    "DNN_output0_NoTopTag_thetastar_bin5",
    "DNN_output0_NoTopTag_thetastar_bin6",
  };

  vector<TString> v_samples = {
    "TTbar",
    "WJets",
    "ST",
    "QCD",
    "DY",
    // "Diboson", // has no PDF weights stored
    "others",
    "ALP_ttbar_signal",
    "ALP_ttbar_interference",
    "HscalarToTTTo1L1Nu2J_m365_w36p5_res",
    "HscalarToTTTo1L1Nu2J_m400_w40p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w50p0_res",
    "HscalarToTTTo1L1Nu2J_m600_w60p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w80p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w100p0_res",
    "HscalarToTTTo1L1Nu2J_m365_w36p5_int_pos",
    "HscalarToTTTo1L1Nu2J_m400_w40p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m500_w50p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m600_w60p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m800_w80p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m1000_w100p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m365_w36p5_int_neg",
    "HscalarToTTTo1L1Nu2J_m400_w40p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m500_w50p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m600_w60p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m800_w80p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m1000_w100p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m365_w36p5_res",
    "HpseudoToTTTo1L1Nu2J_m400_w40p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w50p0_res",
    "HpseudoToTTTo1L1Nu2J_m600_w60p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w80p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_w36p5_int_pos",
    "HpseudoToTTTo1L1Nu2J_m400_w40p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m500_w50p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m600_w60p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m800_w80p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m365_w36p5_int_neg",
    "HpseudoToTTTo1L1Nu2J_m400_w40p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m500_w50p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m600_w60p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m800_w80p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m365_w91p25_res",
    "HscalarToTTTo1L1Nu2J_m400_w100p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w125p0_res",
    "HscalarToTTTo1L1Nu2J_m600_w150p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w200p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w250p0_res",
    "HscalarToTTTo1L1Nu2J_m365_w91p25_int_pos",
    "HscalarToTTTo1L1Nu2J_m400_w100p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m500_w125p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m600_w150p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m800_w200p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m1000_w250p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m365_w91p25_int_neg",
    "HscalarToTTTo1L1Nu2J_m400_w100p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m500_w125p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m600_w150p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m800_w200p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m1000_w250p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m365_w91p25_res",
    "HpseudoToTTTo1L1Nu2J_m400_w100p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w125p0_res",
    "HpseudoToTTTo1L1Nu2J_m600_w150p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w200p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_w91p25_int_pos",
    "HpseudoToTTTo1L1Nu2J_m400_w100p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m500_w125p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m600_w150p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m800_w200p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m365_w91p25_int_neg",
    "HpseudoToTTTo1L1Nu2J_m400_w100p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m500_w125p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m600_w150p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m800_w200p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m365_w9p125_res",
    "HscalarToTTTo1L1Nu2J_m400_w10p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w12p5_res",
    "HscalarToTTTo1L1Nu2J_m600_w15p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w20p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w25p0_res",
    "HscalarToTTTo1L1Nu2J_m365_w9p125_int_pos",
    "HscalarToTTTo1L1Nu2J_m400_w10p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m500_w12p5_int_pos",
    "HscalarToTTTo1L1Nu2J_m600_w15p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m800_w20p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m1000_w25p0_int_pos",
    "HscalarToTTTo1L1Nu2J_m365_w9p125_int_neg",
    "HscalarToTTTo1L1Nu2J_m400_w10p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m500_w12p5_int_neg",
    "HscalarToTTTo1L1Nu2J_m600_w15p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m800_w20p0_int_neg",
    "HscalarToTTTo1L1Nu2J_m1000_w25p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m365_w9p125_res",
    "HpseudoToTTTo1L1Nu2J_m400_w10p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w12p5_res",
    "HpseudoToTTTo1L1Nu2J_m600_w15p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w20p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_w9p125_int_pos",
    "HpseudoToTTTo1L1Nu2J_m400_w10p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m500_w12p5_int_pos",
    "HpseudoToTTTo1L1Nu2J_m600_w15p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m800_w20p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_pos",
    "HpseudoToTTTo1L1Nu2J_m365_w9p125_int_neg",
    "HpseudoToTTTo1L1Nu2J_m400_w10p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m500_w12p5_int_neg",
    "HpseudoToTTTo1L1Nu2J_m600_w15p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m800_w20p0_int_neg",
    "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_neg",
    // "RSGluonToTT_M-500", // has no PDF weights stored
    // "RSGluonToTT_M-1000", // has no PDF weights stored
    // "RSGluonToTT_M-1500", // has no PDF weights stored
    // "RSGluonToTT_M-2000", // has no PDF weights stored
    // "RSGluonToTT_M-2500", // has no PDF weights stored
    // "RSGluonToTT_M-3000", // has no PDF weights stored
    // "RSGluonToTT_M-3500", // has no PDF weights stored
    // "RSGluonToTT_M-4000", // has no PDF weights stored
    // "RSGluonToTT_M-4500", // has no PDF weights stored
    // "RSGluonToTT_M-5000", // has no PDF weights stored
    // "RSGluonToTT_M-5500", // has no PDF weights stored
    // "RSGluonToTT_M-6000", // has no PDF weights stored
    "ZPrimeToTT_M400_W40",
    "ZPrimeToTT_M500_W50",
    "ZPrimeToTT_M600_W60",
    "ZPrimeToTT_M700_W70",
    "ZPrimeToTT_M800_W80",
    "ZPrimeToTT_M900_W90",
    "ZPrimeToTT_M1000_W100",
    "ZPrimeToTT_M1200_W120",
    "ZPrimeToTT_M1400_W140",
    "ZPrimeToTT_M1600_W160",
    "ZPrimeToTT_M1800_W180",
    "ZPrimeToTT_M2000_W200",
    "ZPrimeToTT_M2500_W250",
    "ZPrimeToTT_M3000_W300",
    "ZPrimeToTT_M3500_W350",
    "ZPrimeToTT_M4000_W400",
    "ZPrimeToTT_M4500_W450",
    "ZPrimeToTT_M5000_W500",
    "ZPrimeToTT_M6000_W600",
    "ZPrimeToTT_M7000_W700",
    "ZPrimeToTT_M8000_W800",
    "ZPrimeToTT_M9000_W900",
    "ZPrimeToTT_M400_W120",
    "ZPrimeToTT_M500_W150",
    "ZPrimeToTT_M600_W180",
    "ZPrimeToTT_M700_W210",
    "ZPrimeToTT_M800_W240",
    "ZPrimeToTT_M900_W270",
    "ZPrimeToTT_M1000_W300",
    "ZPrimeToTT_M1200_W360",
    "ZPrimeToTT_M1400_W420",
    "ZPrimeToTT_M1600_W480",
    "ZPrimeToTT_M1800_W540",
    "ZPrimeToTT_M2000_W600",
    "ZPrimeToTT_M2500_W750",
    "ZPrimeToTT_M3000_W900",
    "ZPrimeToTT_M3500_W1050",
    "ZPrimeToTT_M4000_W1200",
    "ZPrimeToTT_M4500_W1350",
    "ZPrimeToTT_M5000_W1500",
    "ZPrimeToTT_M6000_W1800",
    "ZPrimeToTT_M7000_W2100",
    "ZPrimeToTT_M8000_W2400",
    "ZPrimeToTT_M9000_W2700",
    "ZPrimeToTT_M400_W4",
    "ZPrimeToTT_M500_W5",
    "ZPrimeToTT_M600_W6",
    "ZPrimeToTT_M700_W7",
    "ZPrimeToTT_M800_W8",
    "ZPrimeToTT_M900_W9",
    "ZPrimeToTT_M1000_W10",
    "ZPrimeToTT_M1200_W12",
    "ZPrimeToTT_M1400_W14",
    "ZPrimeToTT_M1600_W16",
    "ZPrimeToTT_M1800_W18",
    "ZPrimeToTT_M2000_W20",
    "ZPrimeToTT_M2500_W25",
    "ZPrimeToTT_M3000_W30",
    "ZPrimeToTT_M3500_W35",
    "ZPrimeToTT_M4000_W40",
    "ZPrimeToTT_M4500_W45",
    "ZPrimeToTT_M5000_W50",
    "ZPrimeToTT_M6000_W60",
    "ZPrimeToTT_M7000_W70",
    "ZPrimeToTT_M8000_W80",
    "ZPrimeToTT_M9000_W90",
    "ZprimeDMToTTbarResoIncl_MZp1000_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp1500_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp2000_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp2500_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp3000_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp3500_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp4000_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp4500_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp5000_Mchi10_V1",
    "ZprimeDMToTTbarResoIncl_MZp2500_Mchi1000_A1",
    "ZprimeDMToTTbarResoIncl_MZp2500_Mchi1000_V1",
    "ZprimeDMToTTbarResoIncl_MZp2500_Mchi10_A1",
  };

  vector<bool> isSignalInt (v_samples.size(), false);

  for(unsigned int j=0; j<v_years.size(); j++){
    TString year = v_years.at(j);
    cout << "year: " << year << endl;

    for(unsigned int k=0; k<v_channels.size(); k++){
      TString channel = v_channels.at(k);
      cout << "channel: " << channel << endl;

      for(unsigned int i=0; i<v_samples.size(); i++){
        TString sample = v_samples.at(i);
        cout << sample << endl;

        // check if the sample is an interference sample with negative weights
        isSignalInt.at(i) = (((sample.Index("Hscalar") == 0 || sample.Index("Hpseudo") == 0) && (sample.Index("_int_neg") != -1)) || sample == "ALP_ttbar_interference");

        file_name = file_dir + "AnalysisDNN_" + year +"/" + channel +"/uhh2.AnalysisModuleRunner.MC."+ sample + ".root";
        TFile* f_in = new TFile(file_name, "READ");

        vector<double> v_variation_norms;
        TString presel_file_name = file_dir + "Presel_" + year + "/uhh2.AnalysisModuleRunner.MC.";
        if(sample.EndsWith("_int_pos") || sample.EndsWith("_int_neg")){
          TString sample_fix = sample;
          sample_fix.Resize(sample_fix.Length() - 4); // remove last 4 characters from string
          presel_file_name += sample_fix + ".root";
        }
        else{
          presel_file_name += sample + ".root";
        }

        TFile *presel_file = TFile::Open(presel_file_name);
        TH1F *nominal_hist = (TH1F*) presel_file->Get("Input_General/sum_event_weights");
        for(int c=1; c<101; ++c){
          TString pdfnumber = (TString) to_string(c);
          TH1F *variation_hist = (TH1F*) presel_file->Get("Input_General/sum_event_weights_PDF_" + pdfnumber);
          double norm = variation_hist->GetBinContent(1) / nominal_hist->GetBinContent(1);
          v_variation_norms.push_back(norm);
        }
        presel_file->Close();

        TFile* f_out = new TFile(uhh2_basedir + "CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/" + year + "/" + channel +"/uhh2.AnalysisModuleRunner.MC." + sample +".root", "RECREATE");
        for(int l=0; l<v_root_directories.size(); l++){
          TString output_root_directory = "Zprime_SystVariations_" + v_root_directories.at(l);

          TH1F *h_nominal = (TH1F*)f_in->Get("Zprime_SystVariations_" + v_root_directories.at(l)+"/M_Zprime");
          TH1F *h_PDF_up = (TH1F*)h_nominal->Clone();
          TH1F *h_PDF_down = (TH1F*)h_nominal->Clone();

          float sum_bins = 0;
          // Loop over each bin of the Mtt histograms
          for(int a=1; a<h_nominal->GetNbinsX()+1; a++){
            float nominal = h_nominal->GetBinContent(a);
            float sum_bins = 0;

            for(int b=0; b<100; b++){
              TString vars = "Zprime_PDFVariations_" + v_root_directories.at(l) + "/M_Zprime_PDF_" + to_string(b+1);
              float bin_content = ((TH1F*) f_in->Get(vars))->GetBinContent(a) / v_variation_norms.at(b);
              sum_bins += pow(bin_content - nominal, 2);
            }
            float rms = sqrt(sum_bins / 100);
            if(isSignalInt.at(i)){
              h_PDF_up->SetBinContent(a, nominal-rms);
              h_PDF_down->SetBinContent(a, nominal+rms);
            }
            else{
              h_PDF_up->SetBinContent(a, nominal+rms);
              h_PDF_down->SetBinContent(a, nominal-rms);
            }
          }

          // Save the histo with the up/down variations in root file
          f_out->mkdir(output_root_directory);
          f_out->cd(output_root_directory);
          h_PDF_up->SetName("M_Zprime_pdf_up");
          h_PDF_down->SetName("M_Zprime_pdf_down");
          h_PDF_up->Write();
          h_PDF_down->Write();



          // // Plots nominal hist + up/down variations
          // if( l== 0 && year.at(j)=="UL18" && channel == "muon" && sample=="ZPrimeToTT_M8000_W80"){
          //   TCanvas* c = new TCanvas("c", "c", 1200, 800);
          //   c->Divide(1,1);
          //   c->cd(1);
          //   gPad->SetTopMargin(0.07);
          //   gPad->SetBottomMargin(0.17);
          //   gPad->SetLeftMargin(0.2);
          //   gPad->SetRightMargin(0.1);
          //   //gPad->SetLogy();
          //   gStyle->SetOptStat(0);
          //
          //   h_nominal->SetLineWidth(1);
          //   h_nominal->SetLineColor(kBlack);
          //   h_PDF_up->SetLineWidth(1);
          //   h_PDF_up->SetLineColor(kRed);
          //   h_PDF_down->SetLineWidth(1);
          //   h_PDF_down->SetLineColor(kBlue);
          //
          //   h_nominal->Draw("HIST");
          //   h_nominal->SetTitle("");
          //   h_nominal->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
          //   h_nominal->GetXaxis()->SetRangeUser(0.,3000.);
          //   h_nominal->GetXaxis()->SetTitleSize(0.055);
          //   h_nominal->GetXaxis()->SetLabelSize(0.05);
          //   h_nominal->GetYaxis()->SetTitle("Events");
          //   h_nominal->GetYaxis()->SetRangeUser(0.,200.);
          //   h_nominal->GetYaxis()->SetTitleSize(0.055);
          //   h_nominal->GetYaxis()->SetLabelSize(0.05);
          //   h_nominal->Draw("HIST");
          //   h_PDF_up->Draw("HIST same");
          //   h_PDF_down->Draw("HIST same");
          //
          //   auto legend = new TLegend(0.7,0.67,0.85,0.9);
          //   legend->SetBorderSize(0);
          //   legend->SetFillStyle(0);
          //   legend->SetTextSize(0.035);
          //   legend->SetTextFont(42);
          //   legend->AddEntry(h_nominal,"nominal","le");
          //   legend->AddEntry(h_PDF_up,"PDF up","le");
          //   legend->AddEntry(h_PDF_down,"PDF down","le");
          //   legend->Draw();
          //
          //   TString cmstext = "CMS";
          //   TLatex *text2 = new TLatex(3.5, 24, cmstext);
          //   text2->SetNDC();
          //   text2->SetTextAlign(13);
          //   text2->SetX(0.24);
          //   text2->SetTextFont(62);
          //   text2->SetTextSize(0.06825);
          //   text2->SetY(0.895);
          //   text2->Draw();
          //
          //
          //   TString supptext = "Simulation";
          //   TLatex *text4 = new TLatex(3.5, 24, supptext);
          //   text4->SetNDC();
          //   text4->SetTextAlign(13);
          //   text4->SetX(0.24);
          //   text4->SetTextFont(52);
          //   text4->SetTextSize(0.55*0.06825);
          //   text4->SetY(0.8312);
          //   text4->Draw();
          //
          //   TString supptext2 = "Work in progress";
          //   TLatex *text5 = new TLatex(3.5, 24, supptext2);
          //   text5->SetNDC();
          //   text5->SetTextAlign(13);
          //   text5->SetX(0.24);
          //   text5->SetTextFont(52);
          //   text5->SetTextSize(0.55*0.06825);
          //   text5->SetY(0.79);
          //   text5->Draw();
          //
          //   TString infotext = "59.8 fb^{-1}(13 TeV)";
          //   TLatex *text1 = new TLatex(3.5, 24, infotext);
          //   text1->SetNDC();
          //   text1->SetTextAlign(31);
          //   text1->SetX(1.-0.1);
          //   text1->SetTextFont(42);
          //   text1->SetTextSize(0.07*0.7);
          //   text1->SetY(1.-0.07+0.2*0.07);
          //   text1->Draw();
          //
          //
          //   c->SaveAs(uhh2_basedir + "CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/" + year.at(j) + "/" + channel + "/PDF_"+ sample + "_" + v_root_directories.at(l) +".pdf");
          //   c->Close();
        }
        f_in->Close();
        f_out->Close();
        v_variation_norms.clear();
      }
    }
  }
}
