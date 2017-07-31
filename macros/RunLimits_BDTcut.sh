#!/bin/bash
cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_QCD_MET0_2D_cutElecID_BDT_NOtoptagSFs/elec
~/theta/utils2/theta-auto.py ~/RunLimits_Zprime/Limits/bayesianlimits.py &> limits_log_MET_0
cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_QCD_MET50_2D_cutElecID_noBDT_NOtoptagSFs/elec/
~/theta/utils2/theta-auto.py ~/RunLimits_Zprime/Limits/bayesianlimits.py &> limits_log_MET_50
#~/RunLimits_Zprime/CreateTemplates/createtemplates_ele_2016_EstmLimits_noTopTagSFs.py
#~/RunLimits_Zprime/CreateTemplates/rebin.py
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_QCD_MET50_2D_cutElecID_BDT_0_5_NOtoptagSFs/elec
# ~/theta/utils2/theta-auto.py ~/RunLimits_Zprime/Limits/bayesianlimits.py &> limits_log_BDT_0_5
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_QCD_MET50_2D_cutElecID_BDT_0_75_NOtoptagSFs/elec
# ~/theta/utils2/theta-auto.py ~/RunLimits_Zprime/Limits/bayesianlimits.py &> limits_log_BDT_0_75
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_QCD_MET50_2D_cutElecID_BDT_0_95_NOtoptagSFs/elec
# ~/theta/utils2/theta-auto.py ~/RunLimits_Zprime/Limits/bayesianlimits.py &> limits_log_BDT_0_95
