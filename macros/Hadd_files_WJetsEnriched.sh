#!/bin/bash
# remove samples with low stat from MLE/Limits calculation

# # # #electron
inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330/T1_v06/elec/"
jecupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330_jec_up/T1_v06/elec/" 
jecdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330_jec_down/T1_v06/elec/"
jerupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330_jer_up/T1_v06/elec/"  
jerdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330_jer_down/T1_v06/elec/"



#for path in $inputdir $jecupdir $jecdowndir $jerupdir $jerdowndir
for path in $inputdir
do
cd $path
rm uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT-100to200.root
rm uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-000To050__L.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__B.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__B.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__L.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__L.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__C.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__C.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__ALL.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*.root

# mv uhh2.AnalysisModuleRunner.MC.QCD_Pt120to170_EMEnriched.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt120to170_EMEnriched.root
# mv uhh2.AnalysisModuleRunner.MC.QCD_Pt170to300_EMEnriched.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt170to300_EMEnriched.root
# mv uhh2.AnalysisModuleRunner.MC.QCD_Pt50to80_EMEnriched.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt50to80_EMEnriched.root
# mv uhh2.AnalysisModuleRunner.MC.QCD_Pt80to120_EMEnriched.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt80to120_EMEnriched.root
# mv uhh2.AnalysisModuleRunner.MC.QCD_Pt_80to170_bcToE.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt_80to170_bcToE.root

rm uhh2.AnalysisModuleRunner.MC.QCD_Pt.root
hadd uhh2.AnalysisModuleRunner.MC.QCD_Pt.root uhh2.AnalysisModuleRunner.MC.QCD_Pt*
# rm uhh2.AnalysisModuleRunner.MC.ST_+_DY_+_VV.root
# hadd -f uhh2.AnalysisModuleRunner.MC.ST_+_DY_+_VV.root uhh2.AnalysisModuleRunner.MC.ST_* uhh2.AnalysisModuleRunner.MC.DY* uhh2.AnalysisModuleRunner.MC.WW.root uhh2.AnalysisModuleRunner.MC.WZ.root uhh2.AnalysisModuleRunner.MC.ZZ.root

rm uhh2.AnalysisModuleRunner.MC.ST.root uhh2.AnalysisModuleRunner.MC.DY.root uhh2.AnalysisModuleRunner.MC.VV.root
hadd uhh2.AnalysisModuleRunner.MC.ST.root uhh2.AnalysisModuleRunner.MC.ST_s.root uhh2.AnalysisModuleRunner.MC.ST_t*.root  
hadd uhh2.AnalysisModuleRunner.MC.DY.root uhh2.AnalysisModuleRunner.MC.DY* 
hadd uhh2.AnalysisModuleRunner.MC.VV.root uhh2.AnalysisModuleRunner.MC.WW.root uhh2.AnalysisModuleRunner.MC.WZ.root uhh2.AnalysisModuleRunner.MC.ZZ.root
done

# #muon
inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330/T1_v06/muon/"
jecupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330_jec_up/T1_v06/muon/" 
jecdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330_jec_down/T1_v06/muon/"
jerupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330_jer_up/T1_v06/muon/"  
jerdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/MisTopTagSF__antiWJetsBDT_woBtag_MET120_20180330_jer_down/T1_v06/muon/"
#for path in $inputdir $jecupdir $jecdowndir $jerupdir $jerdowndir
for path in $inputdir
do
cd $path
rm uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT-100to200.root
rm uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-000To050__L.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__B.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__B.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__L.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__L.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__C.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__C.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__ALL.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*.root

mv uhh2.AnalysisModuleRunner.MC.QCD_Pt-50to80_MuEnrichedPt5.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt-50to80_MuEnrichedPt5.root
mv uhh2.AnalysisModuleRunner.MC.QCD_Pt-80to120_MuEnrichedPt5.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt-80to120_MuEnrichedPt5.root
mv uhh2.AnalysisModuleRunner.MC.QCD_Pt-120to170_MuEnrichedPt5.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt-120to170_MuEnrichedPt5.root
mv uhh2.AnalysisModuleRunner.MC.QCD_Pt-170to300_MuEnrichedPt5.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt-170to300_MuEnrichedPt5.root
rm uhh2.AnalysisModuleRunner.MC.QCD_Pt.root
hadd uhh2.AnalysisModuleRunner.MC.QCD_Pt.root uhh2.AnalysisModuleRunner.MC.QCD_Pt*
rm uhh2.AnalysisModuleRunner.MC.ST.root uhh2.AnalysisModuleRunner.MC.DY.root uhh2.AnalysisModuleRunner.MC.VV.root
hadd uhh2.AnalysisModuleRunner.MC.ST.root uhh2.AnalysisModuleRunner.MC.ST_s.root uhh2.AnalysisModuleRunner.MC.ST_t*.root  
hadd uhh2.AnalysisModuleRunner.MC.DY.root uhh2.AnalysisModuleRunner.MC.DY* 
hadd uhh2.AnalysisModuleRunner.MC.VV.root uhh2.AnalysisModuleRunner.MC.WW.root uhh2.AnalysisModuleRunner.MC.WZ.root uhh2.AnalysisModuleRunner.MC.ZZ.root
done

pwd
cd /nfs/dust/cms/user/karavdia/CMSSW_8_0_27/src/UHH2/ZprimeSemiLeptonic/macros
