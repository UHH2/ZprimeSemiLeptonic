{

  vector<float> masses = {500, 750, 1000, 1250, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000};
  vector<TString> masses_str = {};
  for(unsigned int i=0; i<masses.size(); i++){
    TString t = "";
    t += masses[i];
    masses_str.emplace_back(t);
  }

  TString filename_base = "/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/2017_Initial/NOMINAL/uhh2.AnalysisModuleRunner.MC.RSGluon_M";

  vector<float> before_matchable, before_correct_matchable, after_matchable, after_correct_matchable;
  for(unsigned int i=0; i<masses.size(); i++){

    TString filename = filename_base + masses_str[i] + ".root";

    TFile* f_in = new TFile(filename, "READ");

    // Get number of events, matchable, and correctly matched before and after the chi2
    float n_before           = ((TH1F*)(f_in->Get("STlepPlusMet_General/sum_event_weights")))->Integral();
    float n_before_matchable = ((TH1F*)(f_in->Get("MatchableBeforeChi2Cut_General/sum_event_weights")))->Integral();
    float n_before_correct   = ((TH1F*)(f_in->Get("CorrectMatchBeforeChi2Cut_General/sum_event_weights")))->Integral();
    float n_after           = ((TH1F*)(f_in->Get("Chi2_General/sum_event_weights")))->Integral();
    float n_after_matchable = ((TH1F*)(f_in->Get("Matchable_General/sum_event_weights")))->Integral();
    float n_after_correct   = ((TH1F*)(f_in->Get("CorrectMatch_General/sum_event_weights")))->Integral();

    // Calculate fractions
    float frac_matchable_before = n_before_matchable / n_before;
    before_matchable.emplace_back(frac_matchable_before);

    float frac_correct_matchable_before = n_before_correct / n_before_matchable;
    before_correct_matchable.emplace_back(frac_correct_matchable_before);

    float frac_matchable_after = n_after_matchable / n_after;
    after_matchable.emplace_back(frac_matchable_after);

    float frac_correct_matchable_after = n_after_correct / n_after_matchable;
    after_correct_matchable.emplace_back(frac_correct_matchable_after);

    // cout << "Before chi2: " << frac_matchable_before*100. << "% are matchable, out of which " << frac_correct_matchable_before*100. << "% are correctly matched. " << endl;
    // cout << "After chi2: " << frac_matchable_after*100. << "% are matchable, out of which " << frac_correct_matchable_after*100. << "% are correctly matched. " << endl << endl;

  }

  // Put everything in TGraphs
  TGraph* g_before_matchable = new TGraph(before_matchable.size(), &masses[0], &before_matchable[0]);
  TGraph* g_before_correct_matchable = new TGraph(before_correct_matchable.size(), &masses[0], &before_correct_matchable[0]);
  TGraph* g_after_matchable = new TGraph(after_matchable.size(), &masses[0], &after_matchable[0]);
  TGraph* g_after_correct_matchable = new TGraph(after_correct_matchable.size(), &masses[0], &after_correct_matchable[0]);

  g_before_matchable->SetLineWidth(2);
  g_before_matchable->SetLineColor(kRed-4);
  g_before_matchable->GetYaxis()->SetRangeUser(0., 1.);
  g_before_matchable->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
  g_before_matchable->GetYaxis()->SetTitle("Fraction of matchable events");
  g_before_matchable->GetYaxis()->SetTitleSize(0.042);
  g_before_matchable->GetYaxis()->SetTitleOffset(1.2);
  g_before_matchable->GetXaxis()->SetTitleSize(0.042);
  g_before_matchable->SetTitle("");

  g_after_matchable->SetLineWidth(2);
  g_after_matchable->SetLineColor(kAzure+1);

  g_before_correct_matchable->SetLineWidth(2);
  g_before_correct_matchable->SetLineColor(kRed-4);
  g_before_correct_matchable->GetYaxis()->SetRangeUser(0., 1.);
  g_before_correct_matchable->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
  g_before_correct_matchable->GetYaxis()->SetTitle("Fraction of correctly matched events (wrt. matchable)");
  g_before_correct_matchable->GetYaxis()->SetTitleSize(0.042);
  g_before_correct_matchable->GetYaxis()->SetTitleOffset(1.2);
  g_before_correct_matchable->GetXaxis()->SetTitleSize(0.042);
  g_before_correct_matchable->SetTitle("");

  g_after_correct_matchable->SetLineWidth(2);
  g_after_correct_matchable->SetLineColor(kAzure+1);

  TCanvas* c = new TCanvas("c", "c", 600, 600);
  g_before_matchable->Draw("AL");
  g_after_matchable->Draw("SAME L");

  c->SetRightMargin(0.02);
  c->SetTopMargin(0.02);

  TLegend* leg1 = new TLegend(0.5, 0.75, 0.95, 0.95);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.042);
  leg1->AddEntry(g_before_matchable, "Before cut on #chi^{2} < 30", "L");
  leg1->AddEntry(g_after_matchable, "After cut on #chi^{2} < 30", "L");
  leg1->Draw("SAME");

  c->SaveAs("Plots/ReconstructionQuality_Matchable.eps");
  c->SaveAs("Plots/ReconstructionQuality_Matchable.pdf");

  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);
  g_before_correct_matchable->Draw("AL");
  g_after_correct_matchable->Draw("SAME L");

  c2->SetRightMargin(0.02);
  c2->SetTopMargin(0.02);

  TLegend* leg2 = new TLegend(0.5, 0.75, 0.95, 0.95);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.042);
  leg2->AddEntry(g_before_correct_matchable, "Before cut on #chi^{2} < 30", "L");
  leg2->AddEntry(g_after_correct_matchable, "After cut on #chi^{2} < 30", "L");
  leg2->Draw("SAME");

  c2->SaveAs("Plots/ReconstructionQuality_CorrectlyMatched.eps");
  c2->SaveAs("Plots/ReconstructionQuality_CorrectlyMatched.pdf");


}
