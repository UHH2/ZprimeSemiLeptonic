{
  //
  TString input_dir = "/nfs/dust/cms/user/deleokse/RunII_106_v2/DNN_";
  TString save_dir = "/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/";

  vector<TString> year = {"UL16preVFP", "UL16postVFP", "UL17", "UL18"};
  vector<TString> channel = {"muon","electron"};
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
    "DNN_output0_TopTag_thetastar_bin1",
    "DNN_output0_TopTag_thetastar_bin2",
    "DNN_output0_TopTag_thetastar_bin3",
    "DNN_output0_TopTag_thetastar_bin4",
    "DNN_output0_NoTopTag_thetastar_bin1",
    "DNN_output0_NoTopTag_thetastar_bin2",
    "DNN_output0_NoTopTag_thetastar_bin3",
    "DNN_output0_NoTopTag_thetastar_bin4"
  };

  vector<TString> v_samples = {"Diboson", "RSGluonToTT_M-500", "RSGluonToTT_M-1000", "RSGluonToTT_M-1500", "RSGluonToTT_M-2000", "RSGluonToTT_M-2500", "RSGluonToTT_M-3000", "RSGluonToTT_M-3500", "RSGluonToTT_M-4000", "RSGluonToTT_M-4500", "RSGluonToTT_M-5000", "RSGluonToTT_M-5500", "RSGluonToTT_M-6000"};

  for(unsigned int j=0; j<year.size(); j++){
    for(unsigned int k=0; k<channel.size(); k++){
      for(unsigned int i=0; i<v_samples.size(); i++){


      TFile *file_in = TFile::Open(input_dir +  year.at(j) +"_"+channel.at(k)  + "/uhh2.AnalysisModuleRunner.MC."+ v_samples.at(i) +".root");
      TFile* file_out = new TFile(save_dir + year.at(j) + "/" + channel.at(k) +"/uhh2.AnalysisModuleRunner.MC." + v_samples.at(i) +".root", "RECREATE");

      for(int l=0; l<v_root_directories.size(); l++){
         TH1F *hist = (TH1F*)file_in->Get(v_root_directories.at(l)+"_General/M_Zprime_rebin4");
         TString output_root_directory = "Zprime_SystVariations_" + v_root_directories.at(l);

        // generic shape systematics in mttbar: multiply with linear function "Events = 1.6 * mttbar"
        TH1F *hist_genericShapeSyst_up = (TH1F*) hist->Clone();
        TH1F *hist_genericShapeSyst_down = (TH1F*) hist->Clone();
        double syst_weight = 0.0; // Diboson
        if(i==0) syst_weight = 0.01; // Diboson
        if(i>=1) syst_weight = 0.1; // RSGluon

        for(int i=0; i<hist->GetNbinsX()+2; i++){
          double bin_content = hist->GetBinContent(i);
          double bin_center = hist->GetBinCenter(i);

          double bin_content_syst_up = bin_content * (1. + bin_center / 6100. * syst_weight);
          double bin_content_syst_down = bin_content * (1. - bin_center / 6100. * syst_weight);
          hist_genericShapeSyst_up->SetBinContent(i, bin_content_syst_up);
          hist_genericShapeSyst_down->SetBinContent(i, bin_content_syst_down);

           //cout << "     bin_content: " << bin_content << endl;
           //cout << "      bin_center: " << bin_center << endl;
           //cout << "bin_content_syst up : " << bin_content_syst_up << endl;
           //cout << "bin_content_syst down : " << bin_content_syst_down << endl;
           //cout << endl;
        }

        // Save the histo with the up/down variations in root file
        file_out->mkdir(output_root_directory);
        file_out->cd(output_root_directory);
        hist_genericShapeSyst_up->SetName("M_Zprime_pdf_up");
        hist_genericShapeSyst_down->SetName("M_Zprime_pdf_down");
        hist_genericShapeSyst_up->Write();
        hist_genericShapeSyst_down->Write();

        hist->SetLineColor(kBlack);
        hist->SetLineWidth(2);

        hist_genericShapeSyst_up->SetLineColor(kBlue);
        hist_genericShapeSyst_up->SetLineWidth(2);
        hist_genericShapeSyst_up->SetLineStyle(2);

        hist_genericShapeSyst_down->SetLineColor(kRed+1);
        hist_genericShapeSyst_down->SetLineWidth(2);
        hist_genericShapeSyst_down->SetLineStyle(2);

        TH1F *hist_ratio_up = (TH1F*) hist_genericShapeSyst_up->Clone();
        hist_ratio_up->Divide(hist);

        TH1F *hist_ratio_down = (TH1F*) hist_genericShapeSyst_down->Clone();
        hist_ratio_down->Divide(hist);


        //// plotting
        //if( l== 0 && year.at(j)=="UL18" && v_samples.at(i)=="Diboson"){
        //   TCanvas *c1 = new TCanvas("c1","c1",0,0,800,800);

        //   // upper pad
        //   double upperpad_titlesize    = 0.04;
        //   double upperpad_topmargin    = 0.05;
        //   double upperpad_leftmargin   = 0.10;
        //   double upperpad_rightmargin  = 0.05;
        //   double upperpad_bottommargin = 0.25;
        //   double upperpad_width  = 1 - upperpad_leftmargin - upperpad_rightmargin;
        //   double upperpad_height = 1 - upperpad_topmargin - upperpad_bottommargin;

        //   TPad *upperPad = new TPad("upperPad","upperPad",0,0,1,1);
        //   gStyle->SetOptStat(0);
        //   gStyle->SetOptTitle(kFALSE);
        //   upperPad->Draw();
        //   upperPad->SetTitle("upperPad");
        //   upperPad->SetTopMargin(upperpad_topmargin);
        //   upperPad->SetLeftMargin(upperpad_leftmargin);
        //   upperPad->SetRightMargin(upperpad_rightmargin);
        //   upperPad->SetBottomMargin(upperpad_bottommargin);
        //   upperPad->SetTicks();
        //   upperPad->SetLogy();
        //   upperPad->cd();

        //   // lumi tag
        //   double x_pos = 0.95;
        //   double y_pos = 0.957;
        //   auto *lumitag = new TLatex(3.5, 24, "59.8 fb^{-1} (13 TeV)");
        //   lumitag->SetNDC();
        //   lumitag->SetTextAlign(31);
        //   lumitag->SetX(x_pos);
        //   lumitag->SetY(y_pos);
        //   lumitag->SetTextFont(42);
        //   lumitag->SetTextSize(0.032);

        //   // tag
        //   x_pos = 0.11;
        //   y_pos = 0.957;
        //   auto *channel_tag = new TLatex(3.5,24,"UL18 "+channel.at(k)+" channel: "+ v_samples.at(i));
        //   channel_tag->SetNDC();
        //   channel_tag->SetTextAlign(11);
        //   channel_tag->SetX(x_pos);
        //   channel_tag->SetY(y_pos);
        //   channel_tag->SetTextFont(62);
        //   channel_tag->SetTextSize(0.028);

        //   // legend
        //   x_pos  = 0.7;
        //   y_pos  = 0.8;
        //   double x_width =  0.2;
        //   double y_width =  0.1;
        //   TLegend *legend;
        //   legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
        //   legend->SetBorderSize(1);
        //   legend->SetTextSize(0.025);
        //   legend->SetLineColor(0);
        //   legend->SetFillColor(0);
        //   legend->SetFillStyle(1001);
        //   legend->SetNColumns(1);
        //   legend->AddEntry(hist_genericShapeSyst_up, "syst up", "l");
        //   legend->AddEntry(hist, "nominal", "l");
        //   legend->AddEntry(hist_genericShapeSyst_down, "syst down", "l");

        //   // draw
        //   hist->Draw("hist");
        //   hist_genericShapeSyst_up->Draw("hist same");
        //   hist_genericShapeSyst_down->Draw("hist same");
        //   lumitag->Draw("same");
        //   channel_tag->Draw("same");
        //   legend->Draw("same");


        //   // x-axis
        //   hist->GetXaxis()->SetRangeUser(0, 5000);
        //   // hist->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
        //   // hist->GetXaxis()->SetTitleOffset(1.2);
        //   // y-axis
        //   // hist->GetYaxis()->SetRangeUser();
        //   hist->GetYaxis()->SetTitle("Events");

        //   // lower pad
        //   TPad *lowerPad = new TPad ("lowerPad","lowerPad",0.,0.,1,0.24);
        //   gStyle->SetOptStat(0);
        //   gStyle->SetOptTitle(kFALSE);
        //   lowerPad->Draw();
        //   lowerPad->SetTitle("lowerPad");
        //   lowerPad->SetTopMargin(0.0);
        //   lowerPad->SetLeftMargin(upperpad_leftmargin);
        //   lowerPad->SetRightMargin(upperpad_rightmargin);
        //   lowerPad->SetBottomMargin(0.35);
        //   lowerPad->SetTicks();
        //   lowerPad->cd();

        //   // line at ratio = 1
        //   TLine *line1;
        //   line1 = new TLine (0,1,5000,1);
        //   line1->SetLineColor(kBlack);
        //   line1->SetLineWidth(2);
        //   // line1->SetLineStyle(2);
        //   // draw
        //   hist_ratio_up->Draw("hist");
        //   hist_ratio_down->Draw("hist same");
        //   line1->Draw();

        //   // x-axis
        //   hist_ratio_up->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
        //   hist_ratio_up->GetXaxis()->SetTitleSize(upperpad_titlesize * 10/3);
        //   hist_ratio_up->GetXaxis()->SetTitleOffset(1.2);
        //   hist_ratio_up->GetXaxis()->SetLabelSize(upperpad_titlesize * 10/3);
        //   hist_ratio_up->GetXaxis()->SetRangeUser(0,5000);
        //   // hist_ratio_up->GetXaxis()->SetNdivisions(50205);
        //   hist_ratio_up->GetXaxis()->SetTickLength(0.1);
        //   // y-axis
        //   hist_ratio_up->GetYaxis()->SetTitle("ratio");
        //   hist_ratio_up->GetYaxis()->CenterTitle(true);
        //   hist_ratio_up->GetYaxis()->SetTitleSize(upperpad_titlesize * 10/3);
        //   hist_ratio_up->GetYaxis()->SetTitleOffset(0.4);
        //   hist_ratio_up->GetYaxis()->SetLabelSize(upperpad_titlesize * 10/3);
        //   hist_ratio_up->GetYaxis()->SetNdivisions(-502);
        //   hist_ratio_up->SetMinimum(0.5);
        //   hist_ratio_up->SetMaximum(1.5);

        //   c1->Modified();

        //   // save
        //   c1->SaveAs(save_dir + year.at(j) + "/" + channel.at(k) + "/pdf_"+ v_samples.at(i)+".pdf");

        //   c1->Close();
        // }
        }
      delete file_in;
      delete file_out;
      }
    }
  }

}
