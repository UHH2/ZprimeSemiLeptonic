#!/bin/bash

#path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJSkimming/Selas2015_27fb/workdir_Skimming/uhh2.AnalysisModuleRunner.
path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJSkimming/Selas2015_36fb_271036_284044_JSON_PromtReco_METcorrect_eleIDSpring16/workdir_Skimming/uhh2.AnalysisModuleRunner.
#mkdir -p /afs/desy.de/user/k/karavdia/CMSSW_8_0_19_patch2/UHH2/ZprimeSemiLeptonic/Skimming_datasets_36fb_PromtReco_METcorrect_EleIDSpring16
cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_19_patch2/UHH2/ZprimeSemiLeptonic/Skimming_datasets_36fb_PromtReco_METcorrect_EleIDSpring16
#echo "MC.TTbar new tune"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.TTbar_*" MC_TTbar_TuneCUETP8M2T4.xml
#echo "DATA.SingleEG_Run2016H"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_Run2016H*" DATA_SingleEG_Run2016H.xml
#echo "DATA.SingleEG_Run2016B"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_Run2016B*" DATA_SingleEG_Run2016B.xml
#echo "DATA.SingleEG_Run2016C"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_Run2016C*" DATA_SingleEG_Run2016C.xml
#echo "DATA.SingleEG_Run2016D"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_Run2016D*" DATA_SingleEG_Run2016D.xml
#echo "DATA.SingleEG_Run2016E"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_Run2016E*" DATA_SingleEG_Run2016E.xml
#echo "DATA.SingleEG_Run2016F"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_Run2016F*" DATA_SingleEG_Run2016F.xml
#echo "DATA.SingleEG_Run2016G"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_Run2016G*" DATA_SingleEG_Run2016G.xml
 echo "DATA.SingleMUON_Run2016B"
 ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleMUON_Run2016B*" DATA_SingleMUON_Run2016B.xml
 echo "DATA.SingleMUON_Run2016C"
 ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleMUON_Run2016C*" DATA_SingleMUON_Run2016C.xml
 echo "DATA.SingleMUON_Run2016D"
 ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleMUON_Run2016D*" DATA_SingleMUON_Run2016D.xml
 echo "DATA.SingleMUON_Run2016E"
 ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleMUON_Run2016E*" DATA_SingleMUON_Run2016E.xml
 echo "DATA.SingleMUON_Run2016F"
 ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleMUON_Run2016F*" DATA_SingleMUON_Run2016F.xml
 echo "DATA.SingleMUON_Run2016G"
 ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleMUON_Run2016G*" DATA_SingleMUON_Run2016G.xml
#echo "MC.GJets_HT040to100"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT040to100*" MC_GJets_HT040to100.xml
#echo "MC.GJets_HT100to200"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT100to200*" MC_GJets_HT100to200.xml
#echo "MC.GJets_HT200to400"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT200to400*" MC_GJets_HT200to400.xml
#echo "MC.GJets_HT400to600"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT400to600*" MC_GJets_HT400to600.xml
#echo "MC.GJets_HT600toInf"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.GJets_HT600toInf*" MC_GJets_HT600toInf.xml
#echo "MC.QCD_Pt20to30_EMEnriched"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt20to30_EMEnriched_*" MC_QCD_Pt20to30_EMEnriched.xml
#echo "MC.QCD_Pt30to50_EMEnriched"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt30to50_EMEnriched_*" MC_QCD_Pt30to50_EMEnriched.xml
#echo "MC.QCD_Pt50to80_EMEnriched"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt50to80_EMEnriched_*" MC_QCD_Pt50to80_EMEnriched.xml
#echo "MC.QCD_Pt80to120_EMEnriched"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt80to120_EMEnriched_*" MC_QCD_Pt80to120_EMEnriched.xml
#echo "MC.QCD_Pt120to170_EMEnriched"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt120to170_EMEnriched_*" MC_QCD_Pt120to170_EMEnriched.xml
#echo "MC.QCD_Pt170to300_EMEnriched"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt170to300_EMEnriched_*" MC_QCD_Pt170to300_EMEnriched.xml
#echo "MC.QCD_Pt300toInf_EMEnriched"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt300toInf_EMEnriched_*" MC_QCD_Pt300toInf_EMEnriched.xml
#echo "MC.QCD_Pt30to80_bcToE"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt30to80_bcToE_*" MC_QCD_Pt30to80_bcToE.xml
#echo "MC.QCD_Pt80to170_bcToE"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt80to170_bcToE_*" MC_QCD_Pt80to170_bcToE.xml
#echo "MC.QCD_Pt170to250_bcToE"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt170to250_bcToE_*" MC_QCD_Pt170to250_bcToE.xml
#echo "MC.QCD_Pt250toInf_bcToE"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt250toInf_bcToE_*" MC_QCD_Pt250toInf_bcToE.xml

# # echo "MC.WJets_LNu_HT100To200__All"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__All*" MC_WJets_LNu_HT100To200.xml
# # echo "MC.WJets_LNu_HT200To400__All"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400__All*" MC_WJets_LNu_HT200To400.xml
# # echo "MC.WJets_LNu_HT400To600__All"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600__All*" MC_WJets_LNu_HT400To600.xml
# # echo "MC.WJets_LNu_HT600To800__All"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800__All*" MC_WJets_LNu_HT600To800.xml
# # echo "MC.WJets_LNu_HT800To1200__All"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200__All*" MC_WJets_LNu_HT800To1200.xml
# # echo "MC.WJets_LNu_HT1200To2500__All"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500__All*" MC_WJets_LNu_HT1200To2500.xml
# # echo "MC.WJets_LNu_HT2500ToInf__All"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf__All*" MC_WJets_LNu_HT2500ToInf.xml

# echo "MC.WJets_LNu_HT100To200__B"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__B*" MC_WJets_LNu_HT100To200__B.xml
#echo "MC.WJets_LNu_HT200To400__B"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400__B*" MC_WJets_LNu_HT200To400__B.xml
#echo "MC.WJets_LNu_HT400To600__B"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600__B*" MC_WJets_LNu_HT400To600__B.xml
#echo "MC.WJets_LNu_HT600To800__B"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800__B*" MC_WJets_LNu_HT600To800__B.xml
#echo "MC.WJets_LNu_HT800To1200__B"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200__B*" MC_WJets_LNu_HT800To1200__B.xml
#echo "MC.WJets_LNu_HT1200To2500__B"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500__B*" MC_WJets_LNu_HT1200To2500__B.xml
#echo "MC.WJets_LNu_HT2500ToInf__B"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf__B*" MC_WJets_LNu_HT2500ToInf__B.xml
#echo "MC.WJets_LNu_HT100To200__C"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__C*" MC_WJets_LNu_HT100To200__C.xml
#echo "MC.WJets_LNu_HT200To400__C"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400__C*" MC_WJets_LNu_HT200To400__C.xml
#echo "MC.WJets_LNu_HT400To600__C"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600__C*" MC_WJets_LNu_HT400To600__C.xml
#echo "MC.WJets_LNu_HT600To800__C"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800__C*" MC_WJets_LNu_HT600To800__C.xml
#echo "MC.WJets_LNu_HT800To1200__C"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200__C*" MC_WJets_LNu_HT800To1200__C.xml
#echo "MC.WJets_LNu_HT1200To2500__C"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500__C*" MC_WJets_LNu_HT1200To2500__C.xml
#echo "MC.WJets_LNu_HT2500ToInf__C"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf__C*" MC_WJets_LNu_HT2500ToInf__C.xml
#echo "MC.WJets_LNu_HT100To200__L"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__L*" MC_WJets_LNu_HT100To200__L.xml
#echo "MC.WJets_LNu_HT200To400__L"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400__L*" MC_WJets_LNu_HT200To400__L.xml
#echo "MC.WJets_LNu_HT400To600__L"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600__L*" MC_WJets_LNu_HT400To600__L.xml
#echo "MC.WJets_LNu_HT600To800__L"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800__L*" MC_WJets_LNu_HT600To800__L.xml
#echo "MC.WJets_LNu_HT800To1200__L"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200__L*" MC_WJets_LNu_HT800To1200__L.xml
#echo "MC.WJets_LNu_HT1200To2500__L"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500__L*" MC_WJets_LNu_HT1200To2500__L.xml
#echo "MC.WJets_LNu_HT2500ToInf__L"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf__L*" MC_WJets_LNu_HT2500ToInf__L.xml
#echo "MC.WW"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WW_*" MC_WW.xml
#echo "MC.WZ"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WZ_*" MC_WZ.xml
#echo "MC.ZZ"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.ZZ_*" MC_ZZ.xml
#echo "MC.ST_s-channel-4f"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.ST_s-channel-4f_*" MC_ST_s-channel-4f.xml
#echo "MC.ST_t-channel_4f"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.ST_t-channel_4f_*" MC_ST_t-channel_4f.xml
#echo "MC.ST_t-channel_top_4f"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.ST_t-channel_top_4f_*" MC_ST_t-channel_top_4f.xml
#echo "MC.STneg_tW_inc"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.STneg_tW_inc_*" MC_STneg_tW_inc.xml
#echo "MC.STpos_tW_inc"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.STpos_tW_inc_*" MC_STpos_tW_inc.xml
#echo "MC.DYJetsToLL_LO_M50_HT0100to0200"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_LO_M50_HT0100to0200*" MC_DYJetsToLL_LO_M50_HT0100to0200.xml
#echo "MC.DYJetsToLL_LO_M50_HT0200to0400"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_LO_M50_HT0200to0400*" MC_DYJetsToLL_LO_M50_HT0200to0400.xml
#echo "MC.DYJetsToLL_LO_M50_HT0400to0600"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_LO_M50_HT0400to0600*" MC_DYJetsToLL_LO_M50_HT0400to0600.xml
#echo "MC.DYJetsToLL_LO_M50_HT0600toInf"
#~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_LO_M50_HT0600toInf*" MC_DYJetsToLL_LO_M50_HT0600toInf.xml
# # echo "MC.QCD_Pt15to20_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt15to20_MuEnriched*" MC_QCD_Pt15to20_MuEnriched.xml
# # echo "MC.QCD_Pt20to30_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt20to30_MuEnriched*" MC_QCD_Pt20to30_MuEnriched.xml
# # echo "MC.QCD_Pt30to50_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt30to50_MuEnriched*" MC_QCD_Pt30to50_MuEnriched.xml
# # echo "MC.QCD_Pt50to80_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt50to80_MuEnriched*" MC_QCD_Pt50to80_MuEnriched.xml
# # echo "MC.QCD_Pt80to120_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt80to120_MuEnriched*" MC_QCD_Pt80to120_MuEnriched.xml
# # echo "MC.QCD_Pt120to170_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt120to170_MuEnriched*" MC_QCD_Pt120to170_MuEnriched.xml
# # echo "MC.QCD_Pt170to300_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt170to300_MuEnriched*" MC_QCD_Pt170to300_MuEnriched.xml
# # echo "MC.QCD_Pt300to470_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt300to470_MuEnriched*" MC_QCD_Pt300to470_MuEnriched.xml
# # echo "MC.QCD_Pt470to600_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt470to600_MuEnriched*" MC_QCD_Pt470to600_MuEnriched.xml
# # echo "MC.QCD_Pt600to800_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt600to800_MuEnriched*" MC_QCD_Pt600to800_MuEnriched.xml
# # echo "MC.QCD_Pt800to1000_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt800to1000_MuEnriched*" MC_QCD_Pt800to1000_MuEnriched.xml
# # echo "MC.QCD_Pt1000toInf_MuEnriched"
# # ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_Pt1000toInf_MuEnriched*" MC_QCD_Pt1000toInf_MuEnriched.xml
# echo "MC.QCD_HT500to700"
# ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT500to700_*" MC_QCD_HT500to700.xml
# echo "MC.QCD_HT700to1000"
# ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT700to1000_*" MC_QCD_HT700to1000.xml
# echo "MC.QCD_HT1000to1500"
# ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT1000to1500_*" MC_QCD_HT1000to1500.xml
# echo "MC.QCD_HT1500to2000"
# ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT1500to2000_*" MC_QCD_HT1500to2000.xml
# echo "MC.QCD_HT2000toInf"
# ~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT2000toInf_*" MC_QCD_HT2000toInf.xml
cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_19_patch2/UHH2/ZprimeSemiLeptonic/config/
