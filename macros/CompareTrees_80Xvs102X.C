// investigation of difference between output trees after ntuplewriter or UHH2 AnalysisModule 
// At the moment works only for variables in single branches, i.e does not work for variables from object collections/vectors
// author: A.Karavdina
// date: 03.07.2019
// Run it with following command:
// root -l -b -q CompareTrees_80Xvs102X.C\(\"MET\",\"met_pt\",\"slimmedMETs.m_pt\",true,90,0,900,10\)


void CompareTrees_80Xvs102X(TString var_name="MET",TString branch_name_old="met_pt",TString branch_name_new="met_pt", bool isFloat=false, int nbins=10, double minx=0,double maxx=10, int maxevents=100){
  gStyle->SetOptStat(0);
  gStyle->SetTitleSize(0.045,"x");  
  gStyle->SetTitleSize(0.045,"y");
  gStyle->SetTitleYOffset(0.9);

 double w = 600;
 double h = 600;

 // bool isWeights = true;
 bool isWeights = false;

 //Files after UHH2
 TString path_old = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180331_JERhybrid_topptReweight_oldMuonSF_toptagMLE3_addTTBarRecDebugVars_dRlepAK8_removeAK8/T1_v06/muon/";
 // TString path_old = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180331_JERhybrid_topptReweight_oldMuonSF_toptagMLE3_addTTBarRecDebugVars_dRlepAK8_removeAK8/T1_v06/elec/";
 // TString name_old = "uhh2.AnalysisModuleRunner.MC.TTbar.root";
 // TString name_old = "uhh2.AnalysisModuleRunner.DATA.DATA.root";
 TString name_old = "uhh2.AnalysisModuleRunner.MC.WJets__ALL.root";
 // TString name_old = "uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-600ToInf.root";

 //TString name_old = "uhh2.AnalysisModuleRunner.MC.QCD_Pt.root";

  TString path_new = "/nfs/dust/cms/user/karavdia/ZprimeSemiLeptonic/102X_v1/Analysis/RunII_2016_CHS/CSVBtagtight_PileUpRewight__MuonIDMuonHLT_SFs_HTlepCut_muonTight_eleMedium_1MuHLTpath_FixMttbarParams/muon/";
 // TString path_new = "/nfs/dust/cms/user/karavdia/ZprimeSemiLeptonic/102X_v1/Analysis/RunII_2016_CHS/CSVBtagtight_PileUpRewight__MuonIDMuonHLT_SFs_HTlepCut_muonTight_eleMedium_1MuHLTpath_FixMttbarParams/electron/";
 //  TString name_new = "uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root";
 // TString name_new = "uhh2.AnalysisModuleRunner.DATA.DATA.root";
 TString name_new = "uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt.root";
 //TString name_new = "uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-600ToInf_2016v3.root";

 // TString name_new = "uhh2.AnalysisModuleRunner.MC.QCD_MuEnrichedPt5.root";


 TString gl_label_old = "80X";
 TString gl_label_new = "102X";

 TFile *input_old = TFile::Open(path_old+name_old);
 TTree *TTreeAna_old = (TTree*)input_old->Get("AnalysisTree");
 TFile *input_new = TFile::Open(path_new+name_new);
 TTree *TTreeAna_new = (TTree*)input_new->Get("AnalysisTree");

 int eventID,feventID;
 // long long eventID,feventID;
 int run,frun;
 int lumi,flumi;
 Float_t var_val_f,fval_val_f;
 Int_t var_val_i,fval_val_i;

 TTreeAna_old->SetBranchAddress("event",&eventID);
 TTreeAna_new->SetBranchAddress("event",&feventID);
 TTreeAna_old->SetBranchAddress("run",&run);
 TTreeAna_new->SetBranchAddress("run",&frun);
 TTreeAna_old->SetBranchAddress("lumi_block",&lumi);
 TTreeAna_new->SetBranchAddress("luminosityBlock",&flumi);

 TTreeAna_new->BuildIndex("event");
 TTreeAna_old->BuildIndex("event");

 if(isFloat){
   cout<<"branch_name = "<<branch_name_old.Data()<<" ";
   cout<<TTreeAna_old->GetListOfBranches()->FindObject(branch_name_old)<<endl;
   cout<<"branch_name = "<<branch_name_new.Data()<<" ";
   cout<<TTreeAna_new->GetListOfBranches()->FindObject(branch_name_new)<<endl;
   TTreeAna_old->SetBranchAddress(branch_name_old,&var_val_f);
   TTreeAna_new->SetBranchAddress(branch_name_new,&fval_val_f);
 }
 else{
   cout<<"branch_name = "<<branch_name_old.Data()<<" ";
   cout<<TTreeAna_old->GetListOfBranches()->FindObject(branch_name_old)<<endl;
   TTreeAna_old->SetBranchAddress(branch_name_old,&var_val_i);
   TTreeAna_new->SetBranchAddress(branch_name_new,&fval_val_i);
 }

 TTreeAna_old->AddFriend(TTreeAna_new);


 TH2D *hist_comp = new TH2D("h"+var_name,var_name+";"+gl_label_old+";"+gl_label_new,nbins,minx,maxx,nbins,minx,maxx);

 int nentries = TTreeAna_old->GetEntries();
 int nok = 0;
 if(maxevents>0) nentries = maxevents;
 for (Long64_t i=0;i<nentries;i++) {
   TTreeAna_old->GetEntry(i);
   //   cout<<"feventID = "<<feventID<<end;
   if(feventID==eventID && lumi!=flumi) cout<<"lumi = "<<lumi<<" flumi ="<<flumi<<endl;
   if (feventID==eventID && run==frun && lumi==flumi) {
     //     cout<<"lumi = "<<lumi<<" flumi ="<<flumi<<endl;
     nok++;
     if(isFloat){
       hist_comp->Fill(var_val_f,fval_val_f);
       if(fabs(var_val_f-fval_val_f)/var_val_f>0.5) cout<<"Difference above 50% for eventID="<<eventID<<", run="<<run<<" lumi="<<lumi<<endl;
     }
     else{
       hist_comp->Fill(var_val_i,fval_val_i);
       if(double(fabs(var_val_i-fval_val_i))/var_val_i>0.5) cout<<"Difference above 50% for eventID="<<eventID<<", run="<<run<<" lumi="<<lumi<<endl;
     }
   }
 }
 printf("nok = %d, fentries=%lld\n",nok,TTreeAna_new->GetEntries());

 TCanvas * c1_canvas = new TCanvas("canvas", "c", w, h);
 hist_comp->Draw("colz");
 TLine *line = new TLine(minx,minx,maxx,maxx);
 line->SetLineColor(kRed);
 line->SetLineStyle(2);
 line->Draw();
 // c1_canvas->SaveAs("CompareTrees_PUid/Compare_"+branch_name+"__"+gl_label_old+"_vs_"+gl_label_new+".pdf");
 c1_canvas->SaveAs("CompareTrees_80Xvs102X/Compare_"+var_name+"__"+gl_label_old+"_vs_"+gl_label_new+".pdf");

}
