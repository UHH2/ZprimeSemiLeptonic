#!/bin/bash

#path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJSkimming/Selas2015_27fb/workdir_Skimming/uhh2.AnalysisModuleRunner.
#path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJSkimming/Selas2015_36fb_271036_284044_JSON_PromtReco_METcorrect_eleIDSpring16/workdir_Skimming/uhh2.AnalysisModuleRunner.
# path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming/CutBased/workdir_Skimming/uhh2.AnalysisModuleRunner.
# mkdir -p /afs/desy.de/user/k/karavdia/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets_RunII_80X_v3/
# cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets_RunII_80X_v3/

path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming/CutBased_eleIDMVA/workdir_Skimming/uhh2.AnalysisModuleRunner.
mkdir -p /afs/desy.de/user/k/karavdia/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets_RunII_80X_v3_eleIDMVA/
cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets_RunII_80X_v3_eleIDMVA/

# # echo "MC.QCD_Pt_15to20_bcToE"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt_15to20_bcToE*.root" MC_QCD_Pt_15to20_bcToE.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt_15to20_bcToE*.root" MC_QCD_Pt_15to20_bcToE.xml

# # echo "MC.QCD_Pt_20to30_bcToE"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt_20to30_bcToE*.root" MC_QCD_Pt_20to30_bcToE.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt_20to30_bcToE*.root" MC_QCD_Pt_20to30_bcToE.xml
# # echo "MC.QCD_Pt_30to80_bcToE"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt_30to80_bcToE*.root" MC_QCD_Pt_30to80_bcToE.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt_30to80_bcToE*.root" MC_QCD_Pt_30to80_bcToE.xml
# # echo "MC.QCD_Pt_80to170_bcToE"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt_80to170_bcToE*.root" MC_QCD_Pt_80to170_bcToE.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt_80to170_bcToE*.root" MC_QCD_Pt_80to170_bcToE.xml
# # echo "MC.QCD_Pt_170to250_bcToE"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt_170to250_bcToE*.root" MC_QCD_Pt_170to250_bcToE.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt_170to250_bcToE*.root" MC_QCD_Pt_170to250_bcToE.xml
# # echo "MC.QCD_Pt_250toInf_bcToE"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt_250toInf_bcToE*.root" MC_QCD_Pt_250toInf_bcToE.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt_250toInf_bcToE*.root" MC_QCD_Pt_250toInf_bcToE.xml
# # echo "MC.QCD_Pt20to30_EMEnriched"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt20to30_EMEnriched*.root" MC_QCD_Pt20to30_EMEnriched.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt20to30_EMEnriched*.root" MC_QCD_Pt20to30_EMEnriched.xml
# # echo "MC.QCD_Pt30to50_EMEnriched"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt30to50_EMEnriched*.root" MC_QCD_Pt30to50_EMEnriched.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt30to50_EMEnriched*.root" MC_QCD_Pt30to50_EMEnriched.xml
# # echo "MC.QCD_Pt50to80_EMEnriched"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt50to80_EMEnriched*.root" MC_QCD_Pt50to80_EMEnriched.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt50to80_EMEnriched*.root" MC_QCD_Pt50to80_EMEnriched.xml
# # echo "MC.QCD_Pt80to120_EMEnriched"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt80to120_EMEnriched*.root" MC_QCD_Pt80to120_EMEnriched.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt80to120_EMEnriched*.root" MC_QCD_Pt80to120_EMEnriched.xml
# # echo "MC.QCD_Pt300toInf_EMEnriched"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt300toInf_EMEnriched*.root" MC_QCD_Pt300toInf_EMEnriched.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_Pt300toInf_EMEnriched*.root" MC_QCD_Pt300toInf_EMEnriched.xml
# # echo "MC.GJets_HT-100To200"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT-100To200*.root" MC_GJets_HT-100To200.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.GJets_HT-100To200*.root" MC_GJets_HT-100To200.xml
# # echo "MC.GJets_HT-200To400"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT-200To400*.root" MC_GJets_HT-200To400.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.GJets_HT-200To400*.root" MC_GJets_HT-200To400.xml
# # echo "MC.GJets_HT-400To600"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT-400To600*.root" MC_GJets_HT-400To600.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.GJets_HT-400To600*.root" MC_GJets_HT-400To600.xml
# # echo "MC.GJets_HT-600ToInf"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT-600ToInf*.root" MC_GJets_HT-600ToInf.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.GJets_HT-600ToInf*.root" MC_GJets_HT-600ToInf.xml
# # echo "MC.GJets_HT-40To100"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT-40To100*.root" MC_GJets_HT-40To100.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.GJets_HT-40To100*.root" MC_GJets_HT-40To100.xml



# echo "DATA.SingleElectron"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"DATA.DATA_SingleElectron_Run2016*.root" DATA_SingleElectron_Run2016.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"DATA.DATA_SingleElectron_Run2016*.root" DATA_SingleElectron_Run2016.xml

# # echo "DATA.SingleMuon"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"DATA.DATA_SingleMuon_Run2016*.root" DATA_SingleMuon_Run2016.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"DATA.DATA_SingleMuon_Run2016*.root" DATA_SingleMuon_Run2016.xml

# # echo "MC.TTbar"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.TTbar_*.root" MC_TTbar_TuneCUETP8M2T4.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.TTbar_*.root" MC_TTbar_TuneCUETP8M2T4.xml

# echo "MC.WJets_LNu_HT100To200__All"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_HT-100To200*" MC_WJetsToLNu_HT-100To200.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_HT-100To200*" MC_WJetsToLNu_HT-100To200.xml
# echo "MC.WJetsToLNu_HT-200To400"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_HT-200To400*" MC_WJetsToLNu_HT-200To400.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_HT-200To400*" MC_WJetsToLNu_HT-200To400.xml
# echo "MC.WJetsToLNu_HT-400To600"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_HT-400To600*" MC_WJetsToLNu_HT-400To600.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_HT-400To600*" MC_WJetsToLNu_HT-400To600.xml
# echo "MC.WJetsToLNu_HT-600To800"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_HT-600To800*" MC_WJetsToLNu_HT-600To800.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_HT-600To800*" MC_WJetsToLNu_HT-600To800.xml
# echo "MC.WJetsToLNu_HT-800To1200"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_HT-800To1200*" MC_WJetsToLNu_HT-800To1200.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_HT-800To1200*" MC_WJetsToLNu_HT-800To1200.xml
# echo "MC.WJetsToLNu_HT-1200To2500"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_HT-1200To2500*" MC_WJetsToLNu_HT-1200To2500.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_HT-1200To2500*" MC_WJetsToLNu_HT-1200To2500.xml
# echo "MC.WJetsToLNu_HT-2500ToInf"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_HT-2500ToInf*" MC_WJetsToLNu_HT-2500ToInf.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_HT-2500ToInf*" MC_WJetsToLNu_HT-2500ToInf.xml

# echo "MC.WW"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WW*" MC_WW.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WW*" MC_WW.xml
# echo "MC.WZ"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WZ*" MC_WZ.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WZ*" MC_WZ.xml
# echo "MC.ZZ"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.ZZ*" MC_ZZ.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.ZZ*" MC_ZZ.xml

# echo "MC.ST_s"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.ST_s*" MC_ST_s.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.ST_s*" MC_ST_s.xml
# echo "MC.ST_tW_antitop"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.ST_tW_antitop*" MC_ST_tW_antitop.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.ST_tW_antitop*" MC_ST_tW_antitop.xml
# echo "MC.ST_tW_top"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.ST_tW_top*" MC_ST_tW_top.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.ST_tW_top*" MC_ST_tW_top.xml
# echo "MC.ST_t-channel_top"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.ST_t-channel_top*" MC_ST_t-channel_top.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.ST_t-channel_top*" MC_ST_t-channel_top.xml
# echo "MC.ST_t-channel_antitop"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.ST_t-channel_antitop*" MC_ST_t-channel_antitop.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.ST_t-channel_antitop*" MC_ST_t-channel_antitop.xml

# echo "MC.DYJetsToLL_M-50_HT-70to100"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_M-50_HT-70to100*" MC_DYJetsToLL_M-50_HT-70to100.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.DYJetsToLL_M-50_HT-70to100*" MC_DYJetsToLL_M-50_HT-70to100.xml
# echo "MC.DYJetsToLL_M-50_HT-100to200"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_M-50_HT-100to200*" MC_DYJetsToLL_M-50_HT-100to200.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.DYJetsToLL_M-50_HT-100to200*" MC_DYJetsToLL_M-50_HT-100to200.xml
# echo "MC.DYJetsToLL_M-50_HT-200to400"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_M-50_HT-200to400*" MC_DYJetsToLL_M-50_HT-200to400.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.DYJetsToLL_M-50_HT-200to400*" MC_DYJetsToLL_M-50_HT-200to400.xml
# echo "MC.DYJetsToLL_M-50_HT-400to600"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.DYJetsToLL_M-50_HT-400to600*" MC_DYJetsToLL_M-50_HT-400to600.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_M-50_HT-400to600*" MC_DYJetsToLL_M-50_HT-400to600.xml
# echo "MC.DYJetsToLL_M-50_HT-600to800"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.DYJetsToLL_M-50_HT-600to800*" MC_DYJetsToLL_M-50_HT-600to800.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_M-50_HT-600to800*" MC_DYJetsToLL_M-50_HT-600to800.xml
# echo "MC.DYJetsToLL_M-50_HT-800to1200"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.DYJetsToLL_M-50_HT-800to1200*" MC_DYJetsToLL_M-50_HT-800to1200.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_M-50_HT-800to1200*" MC_DYJetsToLL_M-50_HT-800to1200.xml
# echo "MC.DYJetsToLL_M-50_HT-1200to2500"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.DYJetsToLL_M-50_HT-1200to2500*" MC_DYJetsToLL_M-50_HT-1200to2500.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_M-50_HT-1200to2500*" MC_DYJetsToLL_M-50_HT-1200to2500.xml
# echo "MC.DYJetsToLL_M-50_HT-2500toInf"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.DYJetsToLL_M-50_HT-2500toInf*" MC_DYJetsToLL_M-50_HT-2500toInf.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_M-50_HT-2500toInf*" MC_DYJetsToLL_M-50_HT-2500toInf.xml

# # echo "MC.QCD_HT2000toInf"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_HT2000toInf*" MC_QCD_HT2000toInf.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT2000toInf*" MC_QCD_HT2000toInf.xml
# # echo "MC.QCD_HT1500to2000"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_HT1500to2000*" MC_QCD_HT1500to2000.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT1500to2000*" MC_QCD_HT1500to2000.xml
# # echo "MC.QCD_HT1000to1500"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_HT1000to1500*" MC_QCD_HT1000to1500.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT1000to1500*" MC_QCD_HT1000to1500.xml
# # echo "MC.QCD_HT700to1000"
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.QCD_HT700to1000*" MC_QCD_HT700to1000.xml
# # ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT700to1000*" MC_QCD_HT700to1000.xml

# echo "MC.TTbar_part1"
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.TTbar_part1_*.root" MC_TTbar_TuneCUETP8M2T4_part1.xml
# ~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.TTbar_part1*.root" MC_TTbar_TuneCUETP8M2T4_part1.xml

echo "MC.WJetsToLNu_Pt-100To250"
~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_Pt-100To250*" MC_WJetsToLNu_Pt-100To250.xml
~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_Pt-100To250*" MC_WJetsToLNu_Pt-100To250.xml

echo "MC.WJetsToLNu_Pt-250To400"
~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_Pt-250To400*" MC_WJetsToLNu_Pt-250To400.xml
~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_Pt-250To400*" MC_WJetsToLNu_Pt-250To400.xml

echo "MC.WJetsToLNu_Pt-400To600"
~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_Pt-400To600*" MC_WJetsToLNu_Pt-400To600.xml
~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_Pt-400To600*" MC_WJetsToLNu_Pt-400To600.xml

echo "MC.WJetsToLNu_Pt-600ToInf"
~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJetsToLNu_Pt-600ToInf*" MC_WJetsToLNu_Pt-600ToInf.xml
~/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py $path"MC.WJetsToLNu_Pt-600ToInf*" MC_WJetsToLNu_Pt-600ToInf.xml

rm uhh2.AnalysisModuleRunner.*
rm TEMPLATE_*
cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/config/
