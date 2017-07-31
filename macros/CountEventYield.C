// this macro compares event yield between 2015 and 2016 versions of the analysis
void CountEventYield(){
  /*  //after pre-selection
  TString names[2] = {"SingleMUON","SingleEG"};
 TString path_2015 = "/afs/desy.de/user/k/karavdia/CMSSW_8_0_8_patch1/src/UHH2/ZprimeSemiLeptonic/macros/2015/";
 TString path_2016 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJSkimming/Selas2015_4fb_20160708/";
 for(int chI = 0; chI <2; chI++){
  TString fname_2015 = path_2015+"/uhh2.AnalysisModuleRunner.DATA."+names[chI]+".root";
  TFile *input_2015 = TFile::Open(fname_2015);
  TH1D *hpvN_lep_2015 = (TH1D*)input_2015->Get("lep1/pvN");
  int lep_2015 = hpvN_lep_2015->GetEntries();
  TH1D *hpvN_jet2_2015 = (TH1D*)input_2015->Get("jet2/pvN");
  int jet2_2015 = hpvN_jet2_2015->GetEntries();
  TH1D *hpvN_jet1_2015 = (TH1D*)input_2015->Get("jet1/pvN");
  int jet1_2015 = hpvN_jet1_2015->GetEntries();
  TH1D *hpvN_met_2015 = (TH1D*)input_2015->Get("met/pvN");
  int met_2015 = hpvN_met_2015->GetEntries();
  TH1D *hpvN_twodcut_2015 = (TH1D*)input_2015->Get("twodcut/pvN");
  int twodcut_2015 = hpvN_twodcut_2015->GetEntries();
  cout<<names[chI]<<" 2015: lep= "<<lep_2015<<" jet2= "<<jet2_2015<<" jet1= "<<jet1_2015<<" met= "<<met_2015<<" twodcut= "<<twodcut_2015<<endl;
  TString fname_2016 = path_2016+"/uhh2.AnalysisModuleRunner.DATA."+names[chI]+".root";
  TFile *input_2016 = TFile::Open(fname_2016);
 TH1D *hpvN_lep_2016 = (TH1D*)input_2016->Get("lep1/pvN");
  int lep_2016 = hpvN_lep_2016->GetEntries();
  TH1D *hpvN_jet2_2016 = (TH1D*)input_2016->Get("jet2/pvN");
  int jet2_2016 = hpvN_jet2_2016->GetEntries();
  TH1D *hpvN_jet1_2016 = (TH1D*)input_2016->Get("jet1/pvN");
  int jet1_2016 = hpvN_jet1_2016->GetEntries();
  TH1D *hpvN_met_2016 = (TH1D*)input_2016->Get("met/pvN");
  int met_2016 = hpvN_met_2016->GetEntries();
  TH1D *hpvN_twodcut_2016 = (TH1D*)input_2016->Get("twodcut/pvN");
  int twodcut_2016 = hpvN_twodcut_2016->GetEntries();
  cout<<names[chI]<<" 2016: lep= "<<lep_2016<<" ("<<100.*lep_2016/lep_2015<<") jet2= "<<jet2_2016<<"("
      <<100.*jet2_2016/jet2_2015<<") jet1= "<<jet1_2016<<"("<<100.*jet1_2016/jet1_2015<<") met= "<<met_2016<<"("
      <<100.*met_2016/met_2015<<") twodcut= "<<twodcut_2016<<" ("<<100.*twodcut_2016/twodcut_2015<<")"<<endl;
 } */

  //after full selection
  TString path_2015 = "/nfs/dust/cms/user/missirol/Analysis7XY/ttbar_semilep_13TeV/run2_25ns/v02/ttbarLJAnalysis/160218/T1_v01/";
  TString path_2016 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJAnalysis/Selas2015_4fb_20160708/";
  TString channels[2] = {"muon","elec"};
  TString names[2] = {"SingleMU__BLINDED","SingleEG__BLINDED"};
  for(int chI = 0; chI <2; chI++){
    cout<<"    "<<endl;
    cout<<"Number of events in "<<channels[chI]<<" channel: "<<endl;
    TString fname_2015 = path_2015+channels[chI]+"/uhh2.AnalysisModuleRunner.DATA."+names[chI]+".root";
    TFile *input_2015 = TFile::Open(fname_2015);
    TTree *TTree_2015 = (TTree*)input_2015->Get("AnalysisTree");
    TH1 *hmet = new TH1D("hmet","",100,0,10000);
     Long64_t  Nevents_2015_all = TTree_2015->GetEntries();
    Long64_t  Nevents_2015 = TTree_2015->Project("hmet","MET.Pt()","rec_chi2<30.");
    Long64_t  Nevents_2015_t0b0 = TTree_2015->Project("hmet","MET.Pt()","btagN==0 && ttagN ==0 && rec_chi2<30.");
    Long64_t  Nevents_2015_t0b1 = TTree_2015->Project("hmet","MET.Pt()","btagN==1 && ttagN ==0 && rec_chi2<30.");
    Long64_t  Nevents_2015_t1 = TTree_2015->Project("hmet","MET.Pt()","ttagN ==1 && rec_chi2<30.");
    cout<<" 2015: Total= "<< Nevents_2015_all<<" ; after chi2: "<<Nevents_2015<<" t0b0= "<<Nevents_2015_t0b0<<" t0b1= "<<Nevents_2015_t0b1<<" t1= "<<Nevents_2015_t1<<endl;
    TString fname_2016 = path_2016+channels[chI]+"/uhh2.AnalysisModuleRunner.DATA."+names[chI]+".root";
    TFile *input_2016 = TFile::Open(fname_2016);
    TTree *TTree_2016 = (TTree*)input_2016->Get("AnalysisTree");
    Long64_t  Nevents_2016_all = TTree_2016->GetEntries();
    Long64_t  Nevents_2016 = TTree_2016->Project("hmet","MET.Pt()","rec_chi2<30.");
    Long64_t  Nevents_2016_t0b0 = TTree_2016->Project("hmet","MET.Pt()","btagN==0 && ttagN ==0 && rec_chi2<30.");
    Long64_t  Nevents_2016_t0b1 = TTree_2016->Project("hmet","MET.Pt()","btagN==1 && ttagN ==0 && rec_chi2<30.");
    Long64_t  Nevents_2016_t1 = TTree_2016->Project("hmet","MET.Pt()","ttagN ==1 && rec_chi2<30.");
    cout<<" 2016: Total= "<< Nevents_2016_all<<" ("<<100.*Nevents_2016_all/Nevents_2015_all
	<<") ; after chi2: "<<Nevents_2016<<" ("<<100.*Nevents_2016/Nevents_2015<<") t0b0= "<<Nevents_2016_t0b0<<" ("
	<<100.*Nevents_2016_t0b0/Nevents_2015_t0b0<<") t0b1= "
	<<Nevents_2016_t0b1<<" ("<<100.*Nevents_2016_t0b1/Nevents_2015_t0b1<<") t1= "<<Nevents_2016_t1<<"("<<100.*Nevents_2016_t1/Nevents_2015_t1<<")"<<endl;
  }
  
 
}
