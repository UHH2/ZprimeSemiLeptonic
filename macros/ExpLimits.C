//---------------------------------------------------------------
// this macro make a plot of expected limits
// 28.11.2016
//---------------------------------------------------------------

//#include "tdrstyle_mod15.C"

void ExpLimits(){

  double Zprime_mass[]={0.5,0.75,1.0,1.25,1.5,2.0,2.5,3.0,3.5,4.0};
  double exp_2015[]={86.2,6.2,1.50,0.68,0.39,0.149,0.081,0.059,0.049,0.044};
  //  double exp_cutbased[]={57.859, 3.9779, 1.0519, 0.53319, 0.21489, 0.084086, 0.044633, 0.022932, 0.016569, 0.013224};
  double exp_NoMET[]={108.2, 5.0796, 1.7926, 0.5492,  0.23782, 0.10276, 0.057311, 0.03187, 0.021408, 0.017871};
  //  double exp_MET50[]={};

  double exp_cutbased[]={66.311, 3.2982, 0.97261, 0.51563, 0.25895, 0.11514, 0.060715, 0.030493,  0.015645, 0.016056 };

  //  double exp_BDT_0_5[]={77.155,2.7914,0.8448,0.41567,0.22821,0.083933,0.056209,0.031651,0.018463,0.017046};

  double exp_BDT_0_5[]={88.192, 3.4212, 1.2252, 0.45617, 0.20764, 0.086102, 0.053189, 0.030256, 0.017972, 0.015798};
  double exp_BDT_0_75[]={97.55, 3.143, 0.96065, 0.45031, 0.21301, 0.08847, 0.054107, 0.029533, 0.018271, 0.015397};
  double exp_BDT_0_95[]={154.26, 3.6987, 0.895, 0.42891, 0.20001, 0.085054, 0.053696, 0.029307, 0.01744, 0.014599 };
 

  

  TMultiGraph *mg_limits = new TMultiGraph();
  TGraph *exp_lim_2015 = new TGraph (10, Zprime_mass, exp_2015);
  exp_lim_2015->SetLineColor(1);
  exp_lim_2015->SetLineWidth(2);
  exp_lim_2015->SetLineStyle(2);
  exp_lim_2015->SetMarkerColor(1);
  exp_lim_2015->SetMarkerStyle(22);
  mg_limits->Add(exp_lim_2015,"lp");

  TGraph *exp_lim_cutbased = new TGraph (10, Zprime_mass, exp_cutbased);
  exp_lim_cutbased->SetLineColor(kRed+1);
  exp_lim_cutbased->SetLineWidth(2);
  exp_lim_cutbased->SetMarkerColor(kRed+1);
  exp_lim_cutbased->SetMarkerStyle(20);
  mg_limits->Add(exp_lim_cutbased,"lp");

 TGraph *exp_lim_NoMET = new TGraph (10, Zprime_mass, exp_NoMET);
  exp_lim_NoMET->SetLineColor(kRed-7);
  exp_lim_NoMET->SetLineWidth(2);
  exp_lim_NoMET->SetMarkerColor(kRed-7);
  exp_lim_NoMET->SetMarkerStyle(20);
  mg_limits->Add(exp_lim_NoMET,"lp");

  TGraph *exp_lim_BDT_0_5 = new TGraph (10, Zprime_mass, exp_BDT_0_5);
  exp_lim_BDT_0_5->SetLineColor(kBlue-7);
  exp_lim_BDT_0_5->SetLineWidth(2);
  exp_lim_BDT_0_5->SetMarkerColor(kBlue-7);
  exp_lim_BDT_0_5->SetMarkerStyle(21);
  mg_limits->Add(exp_lim_BDT_0_5,"lp");

  TGraph *exp_lim_BDT_0_75 = new TGraph (10, Zprime_mass, exp_BDT_0_75);
  exp_lim_BDT_0_75->SetLineColor(kBlue-5);
  exp_lim_BDT_0_75->SetLineWidth(2);
  exp_lim_BDT_0_75->SetMarkerColor(kBlue-5);
  exp_lim_BDT_0_75->SetMarkerStyle(21);
  mg_limits->Add(exp_lim_BDT_0_75,"lp");

 TGraph *exp_lim_BDT_0_95 = new TGraph (10, Zprime_mass, exp_BDT_0_95);
  exp_lim_BDT_0_95->SetLineColor(kBlue-2);
  exp_lim_BDT_0_95->SetLineWidth(2);
  exp_lim_BDT_0_95->SetMarkerColor(kBlue-2);
  exp_lim_BDT_0_95->SetMarkerStyle(21);
  mg_limits->Add(exp_lim_BDT_0_95,"lp");

  TLegend *leg = new TLegend(0.55,0.6,0.87,0.87);
  //  leg->SetHeader("Z'(1%)","C"); // option "C" allows to center the header
  leg->SetHeader("Z'(1%)");
  leg->AddEntry(exp_lim_2015,"Result with 2015 data","lep");
  leg->AddEntry(exp_lim_NoMET,"MET>0","lep");
  leg->AddEntry(exp_lim_cutbased,"MET>120","lep");
  leg->AddEntry(exp_lim_BDT_0_5,"MET>50, BDT_{QCD}>0.5","lep");
  leg->AddEntry(exp_lim_BDT_0_75,"MET>50, BDT_{QCD}>0.75","lep");
  leg->AddEntry(exp_lim_BDT_0_95,"MET>50, BDT_{QCD}>0.95","lep");

  Double_t w = 600;
  Double_t h = 600;
  TCanvas * c1 = new TCanvas("c", "c", w, h);
  c1->SetLogy(); 
  //  exp_lim_cutbased->Draw("AL");
  mg_limits->Draw("AL");
  mg_limits->GetXaxis()->SetTitle("M_{Z'} (GeV)");
  mg_limits->GetYaxis()->SetTitle("Upper limit on #sigma_{Z'} #times Br(Z'#rightarrow t#bar{t}) [pb]");
  leg->Draw();

}
