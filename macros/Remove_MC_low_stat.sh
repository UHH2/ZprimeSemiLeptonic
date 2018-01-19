#!/bin/bash
# remove samples with low stat from MLE/Limits calculation

# #electron

inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid/T1_v06/elec/"
jecupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_jec_up/T1_v06/elec/" 
jecdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_jec_down/T1_v06/elec/"                                                                                                                                        
jerupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_jer_up/T1_v06/elec/"  
jerdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_jer_down/T1_v06/elec/"

#inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_BLINDED_20180108_JERhybrid/T1_v06/elec/"
#inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid/T1_v06/elec/"
#inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wNEW2DEleHLTSF_vetoGapElectrons_HLT1HLT2HLT3_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171214_JERhybridSFs/T1_v06/elec/"
#inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wHTlep_NOTBLINED_WJetsOLDbdt_muRmuF_HLT1ORHLT2_updTTAGeff_20171108_jer_jec_nominal_topptreweight/T1_v06/muon/"
#inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wNEW2DEleHLTSF_vetoGapElectrons_HLT1HLT2HLT3_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jer_jec_nominal_topptreweight/T1_v06/elec/"

# inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wNEW2DEleHLTSF_vetoGapElectrons_HLT1HLT2HLT3_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jer_jec_nominal/T1_v06/elec/"
# inputdir2="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wNEW2DEleHLTSF_vetoGapElectrons_HLT1HLT2HLT3_BLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jer_jec_nominal/T1_v06/elec/"

# inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_w2DEleHLTSF_vetoGapElectrons_HLT1HLT2_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jer_jec_nominal/T1_v06/elec/"
# jecupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_w2DEleHLTSF_vetoGapElectrons_HLT1HLT2_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jec_up/T1_v06/elec/"
# jecdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_w2DEleHLTSF_vetoGapElectrons_HLT1HLT2_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jec_down/T1_v06/elec/"
# jerupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_w2DEleHLTSF_vetoGapElectrons_HLT1HLT2_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jer_up/T1_v06/elec/"
# jerdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_w2DEleHLTSF_vetoGapElectrons_HLT1HLT2_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jer_down/T1_v06/elec/"

for path in $inputdir $jecupdir $jecdowndir $jerupdir $jerdowndir
#for path in $inputdir $inputdir2
#for path in $inputdir
do
cd $path
mv uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-000To050__L.root uhh2.AnalysisModuleRunner.MC.SKIP.WJetsToLNu_Pt-000To050__L.root
mv uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-000To050__B.root uhh2.AnalysisModuleRunner.MC.SKIP.WJetsToLNu_Pt-000To050__B.root
mv uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-000To050__C.root uhh2.AnalysisModuleRunner.MC.SKIP.WJetsToLNu_Pt-000To050__C.root
mv uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-050To100__B.root uhh2.AnalysisModuleRunner.MC.SKIP.WJetsToLNu_Pt-050To100__B.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__B.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__B.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__L.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__L.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__C.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__C.root

mv uhh2.AnalysisModuleRunner.MC.QCD_Pt120to170_EMEnriched.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt120to170_EMEnriched.root
mv uhh2.AnalysisModuleRunner.MC.QCD_Pt170to300_EMEnriched.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt170to300_EMEnriched.root
mv uhh2.AnalysisModuleRunner.MC.QCD_Pt50to80_EMEnriched.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt50to80_EMEnriched.root
mv uhh2.AnalysisModuleRunner.MC.QCD_Pt80to120_EMEnriched.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt80to120_EMEnriched.root
mv uhh2.AnalysisModuleRunner.MC.QCD_Pt_80to170_bcToE.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt_80to170_bcToE.root

rm uhh2.AnalysisModuleRunner.MC.QCD_Pt.root
hadd uhh2.AnalysisModuleRunner.MC.QCD_Pt.root uhh2.AnalysisModuleRunner.MC.QCD_Pt*
done

# #muon
inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid/T1_v06/muon/"
jecupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_jec_up/T1_v06/muon/" 
jecdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_jec_down/T1_v06/muon/"   
jerupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_jer_up/T1_v06/muon/"  
jerdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_jer_down/T1_v06/muon/"   
#inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_BLINDED_20180108_JERhybrid/T1_v06/muon/"

#inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wHTlep_NOTBLINED_WJetsOLDbdt_muRmuF_HLT1ORHLT2_updTTAGeff_20171108_jer_jec_nominal_topptreweight/T1_v06/muon/"
# inputdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wHTlep_NOTBLINED_WJetsOLDbdt_muRmuF_HLT1ORHLT2_updTTAGeff_20171108/T1_v06/muon/"
# jecupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wHTlep_NOTBLINED_WJetsOLDbdt_muRmuF_HLT1ORHLT2_updTTAGeff_20171108_jec_up/T1_v06/muon/"
# jecdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wHTlep_NOTBLINED_WJetsOLDbdt_muRmuF_HLT1ORHLT2_updTTAGeff_20171108_jec_down/T1_v06/muon/"
# jerupdir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wHTlep_NOTBLINED_WJetsOLDbdt_muRmuF_HLT1ORHLT2_updTTAGeff_20171108_jer_up/T1_v06/muon/"
# jerdowndir="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wHTlep_NOTBLINED_WJetsOLDbdt_muRmuF_HLT1ORHLT2_updTTAGeff_20171108_jer_down/T1_v06/muon/"
for path in $inputdir $jecupdir $jecdowndir $jerupdir $jerdowndir
#for path in $inputdir
do
cd $path
mv uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-000To050__L.root uhh2.AnalysisModuleRunner.MC.SKIP.WJetsToLNu_Pt-000To050__L.root
mv uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-000To050__B.root uhh2.AnalysisModuleRunner.MC.SKIP.WJetsToLNu_Pt-000To050__B.root
mv uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-000To050__C.root uhh2.AnalysisModuleRunner.MC.SKIP.WJetsToLNu_Pt-000To050__C.root
mv uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt-050To100__B.root uhh2.AnalysisModuleRunner.MC.SKIP.WJetsToLNu_Pt-050To100__B.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__B.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__B.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__L.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__L.root
hadd -f uhh2.AnalysisModuleRunner.MC.WJets__C.root uhh2.AnalysisModuleRunner.MC.WJetsToLNu_Pt*__C.root

mv uhh2.AnalysisModuleRunner.MC.QCD_Pt-50to80_MuEnrichedPt5.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt-50to80_MuEnrichedPt5.root
mv uhh2.AnalysisModuleRunner.MC.QCD_Pt-80to120_MuEnrichedPt5.root uhh2.AnalysisModuleRunner.MC.SKIP.QCD_Pt-80to120_MuEnrichedPt5.root

rm uhh2.AnalysisModuleRunner.MC.QCD_Pt.root
hadd uhh2.AnalysisModuleRunner.MC.QCD_Pt.root uhh2.AnalysisModuleRunner.MC.QCD_Pt*
done

pwd
cd /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros
