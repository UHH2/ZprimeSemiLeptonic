#!bash
nevents=10000
root -l -b -q CompareTrees_80Xvs102X.C\(\"Muon1pt\",\"lep_pt\",\"lep1_pt\",true,90,0,900,$nevents\)
root -l -b -q CompareTrees_80Xvs102X.C\(\"Muon1eta\",\"lep_eta\",\"lep1_eta\",true,50,-2.5,2.5,$nevents\)

# root -l -b -q CompareTrees_80Xvs102X.C\(\"MET\",\"met_pt\",\"met_pt\",true,90,0,900,$nevents\)
# root -l -b -q CompareTrees_80Xvs102X.C\(\"AK4Jet1pt\",\"ljet_pt\",\"ak4jet1_pt\",true,90,0,900,$nevents\)
# root -l -b -q CompareTrees_80Xvs102X.C\(\"AK4Jet1eta\",\"ljet_eta\",\"ak4jet1_eta\",true,50,-2.5,2.5,$nevents\)
# #root -l -b -q CompareTrees_80Xvs102X.C\(\"Electron1pt\",\"lep_pt\",\"lep1_pt\",true,90,0,900,$nevents\)
# #root -l -b -q CompareTrees_80Xvs102X.C\(\"Electron1eta\",\"lep_eta\",\"lep1_eta\",true,50,-2.5,2.5,$nevents\)

# #root -l -b -q CompareTrees_80Xvs102X.C\(\"AK8Jet1pt\",\"ljet_pt\",\"ak8jet1_pt\",true,90,0,900,$nevents\)
# #root -l -b -q CompareTrees_80Xvs102X.C\(\"AK8Jet1eta\",\"ljet_eta\",\"ak8jet1_eta\",true,50,-2.5,2.5,$nevents\)

# root -l -b -q CompareTrees_80Xvs102X.C\(\"chi2\",\"rec_chi2\",\"rec_chi2\",true,200,0,100,$nevents\)
# root -l -b -q CompareTrees_80Xvs102X.C\(\"Mttbar\",\"Mttbar\",\"Mttbar\",true,300,0,6000,$nevents\)

# #root -l -b -q CompareTrees_80Xvs102X.C\(\"MuonIDsf\",\"weight_sfmu_ID\",\"weight_sfmu_MuonID\",true,50,0,1.5,$nevents\)
# #root -l -b -q CompareTrees_80Xvs102X.C\(\"MuonHLTsf\",\"weight_sfmu_HLT\",\"weight_sfmu_MuonTrigger\",true,50,0,1.5,$nevents\)

# root -l -b -q CompareTrees_80Xvs102X.C\(\"NPV\",\"pvN\",\"NPV\",false,100,0,100,$nevents\)


