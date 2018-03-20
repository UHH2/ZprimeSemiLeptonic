//---------------------------------------------------------------
// this macro reads hists for top-tag efficiency
// and creates file used in the analysis as "ttag_eff" (root)
// with 
// "ttag_eff__jetL" = "&channel;/wjets/tjpj_chi2tlep__TTAG/tjetA__pt__l"
// "ttag_eff__jetT" = "&channel;/ttbar/tjpj_chi2tlep__TTAG/tjetA__pt__t"
// 
// Usage:
// root -l TopTagEff.C
// 13.07.2016
// Update on 20.10.2017
// Update on 16.03.2018
//---------------------------------------------------------------

void TopTagEff_hists(){
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJAnalysis/Selas2015_4fb_TopTag/T1_v01/";
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_20171020/T1_v06/";
  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_20180317/T1_v06/";
  const int nch = 2;
  TString channels[nch] = {"muon","elec"};
  // TString channels[nch] = {"muon"};
  //  TString channels[nch] = {"elec"};
  TFile fout(path+"TTAGeff.root","RECREATE");
  for(int chI = 0; chI <nch; chI++){
    TDirectory *ch_dir = fout.mkdir(channels[chI]);
    //MC
    //WJets (light)
    TString fname_wjetsL = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.WJets__L.root";
    TFile *input_wjetsL = TFile::Open(fname_wjetsL);
    TH2F *htopjets_wjetsL_all = (TH2F*)input_wjetsL->Get("FinalV1__TTAG/TAG__vs__tjetA__pt__l");
    TH1D *htopjets_wjetsL = htopjets_wjetsL_all->ProjectionY("__wjets_topjet_l",1,2);
    TH1D *htoptags_wjetsL = htopjets_wjetsL_all->ProjectionY("__wjets_toptagjet_l",2,2);
    //clean points with low stat
    for(int i=0; i<htoptags_wjetsL->GetNbinsX();i++){
      double yval = htoptags_wjetsL->GetBinContent(i);
      if(yval<10){
	htoptags_wjetsL->SetBinContent(i,0);
	htoptags_wjetsL->SetBinError(i,0);
      }
    }
    htoptags_wjetsL->Divide(htopjets_wjetsL);

    TDirectory *wjets_dir = ch_dir->mkdir("wjets");
    TDirectory *eff_dir = wjets_dir->mkdir("tjpj_chi2tlep__TTAG");
    TGraphAsymmErrors* geff_wjets = new TGraphAsymmErrors(htoptags_wjetsL);
    geff_wjets->SetName("tjetA__pt__l");
    eff_dir->cd();
    geff_wjets->Write();
    Double_t w = 600;
    Double_t h = 600;
    TCanvas * c1 = new TCanvas("c", "c", w, h);
    geff_wjets->GetYaxis()->SetRangeUser(0., 0.1);
    geff_wjets->GetYaxis()->SetTitle("#epsilon");
    geff_wjets->GetXaxis()->SetTitle("AK8CHS p_{T}");
    geff_wjets->Draw();
    c1->SaveAs(path+channels[chI]+"/wjets_l_chi2tlep.pdf");
    delete c1;

    TH2F *htopjets_wjetsL_nochi2_all = (TH2F*)input_wjetsL->Get("FinalV0__TTAG/TAG__vs__tjetA__pt__l");
    TH1D *htopjets_wjetsL_nochi2 = htopjets_wjetsL_nochi2_all->ProjectionY("__wjets_nochi2_topjet_l",1,2);
    TH1D *htoptags_wjetsL_nochi2 = htopjets_wjetsL_nochi2_all->ProjectionY("__wjets_nochi2_toptagjet_l",2,2);
    //clean points with low stat
    for(int i=0; i<htoptags_wjetsL_nochi2->GetNbinsX();i++){
      double yval = htoptags_wjetsL_nochi2->GetBinContent(i);
      if(yval<10){
	htoptags_wjetsL_nochi2->SetBinContent(i,0);
	htoptags_wjetsL_nochi2->SetBinError(i,0);
      }
    }

    htoptags_wjetsL_nochi2->Divide(htopjets_wjetsL_nochi2);
    TDirectory *eff_dir_nochi2 = wjets_dir->mkdir("tjpj_nochi2__TTAG");
    TGraphAsymmErrors* geff_wjets_nochi2 = new TGraphAsymmErrors(htoptags_wjetsL_nochi2);
    geff_wjets_nochi2->SetName("tjetA__pt__l");
    eff_dir_nochi2->cd();
    geff_wjets_nochi2->Write();
    TCanvas * c3 = new TCanvas("c", "c", w, h);
    geff_wjets_nochi2->GetYaxis()->SetRangeUser(0., 0.1);
    geff_wjets_nochi2->GetYaxis()->SetTitle("#epsilon");
    geff_wjets_nochi2->GetXaxis()->SetTitle("AK8CHS p_{T}");
    geff_wjets_nochi2->Draw();
    c3->SaveAs(path+channels[chI]+"/wjets_l_nochi2.pdf");
    delete c3;

    TH2F *htopjets_wjetsL_all_t = (TH2F*)input_wjetsL->Get("FinalV1__TTAG/TAG__vs__tjetA__pt__t");
    TH1D *htopjets_wjetsL_t = htopjets_wjetsL_all_t->ProjectionY("__wjets_topjet_t",1,2);
    TH1D *htoptags_wjetsL_t = htopjets_wjetsL_all_t->ProjectionY("__wjets_toptagjet_t",2,2);
    //clean points with low stat
    for(int i=0; i<htoptags_wjetsL_t->GetNbinsX();i++){
      double yval = htoptags_wjetsL_t->GetBinContent(i);
      if(yval<10){
	htoptags_wjetsL_t->SetBinContent(i,0);
	htoptags_wjetsL_t->SetBinError(i,0);
      }
    }
    htoptags_wjetsL_t->Divide(htopjets_wjetsL_t);

    // TDirectory *wjets_dir = ch_dir->mkdir("wjets");
    // TDirectory *eff_dir = wjets_dir->mkdir("tjpj_chi2tlep__TTAG");
    TGraphAsymmErrors* geff_wjets_t = new TGraphAsymmErrors(htoptags_wjetsL_t);
    geff_wjets_t->SetName("tjetA__pt__t");
    // eff_dir->cd();
    // geff_wjets->Write();
    TCanvas * c1t = new TCanvas("c", "c", w, h);
    geff_wjets_t->GetYaxis()->SetRangeUser(0., 0.1);
    geff_wjets_t->GetYaxis()->SetTitle("#epsilon");
    geff_wjets_t->GetXaxis()->SetTitle("AK8CHS p_{T}");
    geff_wjets_t->Draw();
    c1t->SaveAs(path+channels[chI]+"/wjets_t_chi2tlep.pdf");
    delete c1t;

    TH2F *htopjets_wjetsL_nochi2_all_t = (TH2F*)input_wjetsL->Get("FinalV0__TTAG/TAG__vs__tjetA__pt__t");
    TH1D *htopjets_wjetsL_nochi2_t = htopjets_wjetsL_nochi2_all_t->ProjectionY("__wjets_nochi2_topjet_t",1,2);
    TH1D *htoptags_wjetsL_nochi2_t = htopjets_wjetsL_nochi2_all_t->ProjectionY("__wjets_nochi2_toptagjet_t",2,2);
    //clean points with low stat
    for(int i=0; i<htoptags_wjetsL_nochi2_t->GetNbinsX();i++){
      double yval = htoptags_wjetsL_nochi2_t->GetBinContent(i);
      if(yval<10){
    	htoptags_wjetsL_nochi2_t->SetBinContent(i,0);
    	htoptags_wjetsL_nochi2_t->SetBinError(i,0);
      }
    }

    htoptags_wjetsL_nochi2_t->Divide(htopjets_wjetsL_nochi2_t);
    // TDirectory *eff_dir_nochi2 = wjets_dir->mkdir("tjpj_nochi2__TTAG");
    TGraphAsymmErrors* geff_wjets_nochi2_t = new TGraphAsymmErrors(htoptags_wjetsL_nochi2_t);
    geff_wjets_nochi2_t->SetName("tjetA__pt__t");
    // eff_dir_nochi2->cd();
    //    geff_wjets_nochi2->Write();
    TCanvas * c3t = new TCanvas("c", "c", w, h);
    geff_wjets_nochi2_t->GetYaxis()->SetRangeUser(0., 0.1);
    geff_wjets_nochi2_t->GetYaxis()->SetTitle("#epsilon");
    geff_wjets_nochi2_t->GetXaxis()->SetTitle("AK8CHS p_{T}");
    geff_wjets_nochi2_t->Draw();
    c3t->SaveAs(path+channels[chI]+"/wjets_t_nochi2.pdf");
    delete c3t;


    //TTbar
    TString fname_ttbar = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.TTbar.root";
    TFile *input_ttbar = TFile::Open(fname_ttbar);
    //top
    TH2F *htopjets_ttbar_all = (TH2F*)input_ttbar->Get("FinalV1__TTAG/TAG__vs__tjetA__pt__t");
    TH1D *htopjets_ttbar = htopjets_ttbar_all->ProjectionY("__ttbar_topjet_t",1,2);
    TH1D *htoptags_ttbar = htopjets_ttbar_all->ProjectionY("__ttbar_toptagjet_t",2,2);
    //clean points with low stat
    for(int i=0; i<htoptags_ttbar->GetNbinsX();i++){
      double yval = htoptags_ttbar->GetBinContent(i);
      if(yval<10){
	htoptags_ttbar->SetBinContent(i,0);
	htoptags_ttbar->SetBinError(i,0);
      }
    }
    htoptags_ttbar->Divide(htopjets_ttbar);
    TDirectory *ttbar_dir = ch_dir->mkdir("ttbar");
    TDirectory *eff_t_dir = ttbar_dir->mkdir("tjpj_chi2tlep__TTAG");
    TGraphAsymmErrors* geff_ttbar = new TGraphAsymmErrors(htoptags_ttbar);
    geff_ttbar->SetName("tjetA__pt__t");
    eff_t_dir->cd();
    geff_ttbar->Write();    
    TCanvas * c2 = new TCanvas("c", "c", w, h);
    geff_ttbar->GetYaxis()->SetRangeUser(0., 1.);
    geff_ttbar->GetYaxis()->SetTitle("#epsilon");
    geff_ttbar->GetXaxis()->SetTitle("AK8CHS p_{T}");
    geff_ttbar->Draw();
    c2->SaveAs(path+channels[chI]+"/ttbar_t_chi2tlep.pdf");
    delete c2;


    TH2F *htopjets_ttbar_nochi2_all = (TH2F*)input_ttbar->Get("FinalV0__TTAG/TAG__vs__tjetA__pt__t");
    TH1D *htopjets_ttbar_nochi2 = htopjets_ttbar_nochi2_all->ProjectionY("__ttbar_nochi2_topjet_t",1,2);
    TH1D *htoptags_ttbar_nochi2 = htopjets_ttbar_nochi2_all->ProjectionY("__ttbar_nochi2_toptagjet_t",2,2);
    //clean points with low stat
    for(int i=0; i<htoptags_ttbar_nochi2->GetNbinsX();i++){
      double yval = htoptags_ttbar_nochi2->GetBinContent(i);
      if(yval<10){
	htoptags_ttbar_nochi2->SetBinContent(i,0);
	htoptags_ttbar_nochi2->SetBinError(i,0);
      }
    }

    htoptags_ttbar_nochi2->Divide(htopjets_ttbar_nochi2);

    TDirectory *eff_t_dir_nochi2 = ttbar_dir->mkdir("tjpj_nochi2__TTAG");
    TGraphAsymmErrors* geff_ttbar_nochi2 = new TGraphAsymmErrors(htoptags_ttbar_nochi2);
    geff_ttbar_nochi2->SetName("tjetA__pt__t");
    eff_t_dir_nochi2->cd();
    geff_ttbar_nochi2->Write();    
    TCanvas * c4 = new TCanvas("c", "c", w, h);
    geff_ttbar_nochi2->GetYaxis()->SetRangeUser(0., 1.);
    geff_ttbar_nochi2->GetYaxis()->SetTitle("#epsilon");
    geff_ttbar_nochi2->GetXaxis()->SetTitle("AK8CHS p_{T}");
    geff_ttbar_nochi2->Draw();
    c4->SaveAs(path+channels[chI]+"/ttbar_t_nochi2.pdf");
    delete c4;

    //not top
    TH2F *htopjets_ttbar_all_l = (TH2F*)input_ttbar->Get("FinalV1__TTAG/TAG__vs__tjetA__pt__l");
    TH1D *htopjets_ttbar_l = htopjets_ttbar_all_l->ProjectionY("__ttbar_topjet_l",1,2);
    TH1D *htoptags_ttbar_l = htopjets_ttbar_all_l->ProjectionY("__ttbar_toptagjet_l",2,2);
    //clean points with low stat
    for(int i=0; i<htoptags_ttbar_l->GetNbinsX();i++){
      double yval = htoptags_ttbar_l->GetBinContent(i);
      if(yval<10){
	htoptags_ttbar_l->SetBinContent(i,0);
	htoptags_ttbar_l->SetBinError(i,0);
      }
    }
    htoptags_ttbar_l->Divide(htopjets_ttbar_l);
    //    TDirectory *ttbar_dir = ch_dir->mkdir("ttbar");
    //    TDirectory *eff_t_dir = ttbar_dir->mkdir("tjpj_chi2tlep__TTAG");
    TGraphAsymmErrors* geff_ttbar_l = new TGraphAsymmErrors(htoptags_ttbar_l);
    geff_ttbar_l->SetName("tjetA__pt__l");
    // eff_t_dir->cd();
    // geff_ttbar->Write();    
    TCanvas * c2l = new TCanvas("c", "c", w, h);
    geff_ttbar_l->GetYaxis()->SetRangeUser(0., 0.1);
    geff_ttbar_l->GetYaxis()->SetTitle("#epsilon");
    geff_ttbar_l->GetXaxis()->SetTitle("AK8CHS p_{T}");
    geff_ttbar_l->Draw();
    c2l->SaveAs(path+channels[chI]+"/ttbar_l_chi2tlep.pdf");
    delete c2l;


    TH2F *htopjets_ttbar_nochi2_all_l = (TH2F*)input_ttbar->Get("FinalV0__TTAG/TAG__vs__tjetA__pt__l");
    TH1D *htopjets_ttbar_nochi2_l = htopjets_ttbar_nochi2_all_l->ProjectionY("__ttbar_nochi2_topjet_l",1,2);
    TH1D *htoptags_ttbar_nochi2_l = htopjets_ttbar_nochi2_all_l->ProjectionY("__ttbar_nochi2_toptagjet_l",2,2);
    //clean points with low stat
    for(int i=0; i<htoptags_ttbar_nochi2_l->GetNbinsX();i++){
      double yval = htoptags_ttbar_nochi2_l->GetBinContent(i);
      if(yval<10){
	htoptags_ttbar_nochi2_l->SetBinContent(i,0);
	htoptags_ttbar_nochi2_l->SetBinError(i,0);
      }
    }

    htoptags_ttbar_nochi2_l->Divide(htopjets_ttbar_nochi2_l);

    //    TDirectory *eff_t_dir_nochi2 = ttbar_dir->mkdir("tjpj_nochi2__TTAG");
    TGraphAsymmErrors* geff_ttbar_nochi2_l = new TGraphAsymmErrors(htoptags_ttbar_nochi2_l);
    geff_ttbar_nochi2_l->SetName("tjetA__pt__l");
    geff_ttbar_nochi2_l->Write();    
    TCanvas * c4l = new TCanvas("c", "c", w, h);
    geff_ttbar_nochi2_l->GetYaxis()->SetRangeUser(0., 0.1);
    geff_ttbar_nochi2_l->GetYaxis()->SetTitle("#epsilon");
    geff_ttbar_nochi2_l->GetXaxis()->SetTitle("AK8CHS p_{T}");
    geff_ttbar_nochi2_l->Draw();
    //    c4l->SetLogx();
    c4l->SaveAs(path+channels[chI]+"/ttbar_l_nochi2.pdf");
    delete c4l;


  }
  fout.Write();
  fout.Print();
  fout.Close();
}

