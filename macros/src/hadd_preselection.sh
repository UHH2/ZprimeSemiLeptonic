#!/bin/bash

year="UL17" # UL16preVFP / UL16postVFP / UL17 / UL18
input_dir="/nfs/dust/cms/group/zprime-uhh/Presel_${year}/workdir_Preselection_${year}/"
output_dir="/nfs/dust/cms/group/zprime-uhh/Presel_${year}/"

echo "hadding: year=${year}"

# DATA
if [ ${year} = "UL18" ]; then
  hadd -T ${output_dir}uhh2.AnalysisModuleRunner.DATA.DATA.root ${input_dir}uhh2.AnalysisModuleRunner.DATA.EGamma_Run*.root ${input_dir}uhh2.AnalysisModuleRunner.DATA.SingleMuon_Run*.root
else
  hadd -T ${output_dir}uhh2.AnalysisModuleRunner.DATA.DATA.root ${input_dir}uhh2.AnalysisModuleRunner.DATA.DATA_SingleElectron_Run*.root ${input_dir}uhh2.AnalysisModuleRunner.DATA.DATA_SinglePhoton_Run*.root ${input_dir}uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run*.root
fi

# MC
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.TTbar.root ${input_dir}uhh2.AnalysisModuleRunner.MC.TTTo*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ST.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ST_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.WJets.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WJetsToLNu_HT-*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.DY.root ${input_dir}uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT-*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.QCD.root ${input_dir}uhh2.AnalysisModuleRunner.MC.QCD_HT*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.Diboson.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WW_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WZ_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZZ_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ALP_ttbar_signal.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ALP_ttbar_signal_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ALP_ttbar_interference.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ALP_ttbar_interference_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w91p25_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w91p25_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w100p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w100p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w125p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w125p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w150p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w150p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w200p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w200p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w250p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w36p5_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w36p5_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w40p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w40p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w50p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w50p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w60p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w60p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w80p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w80p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w100p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w9p125_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w9p125_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w10p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w10p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w12p5_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w12p5_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w15p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w15p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w20p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w20p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w25p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w91p25_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w91p25_int*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w100p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w100p0_int*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w125p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w125p0_int*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w150p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w150p0_int*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w200p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w200p0_int*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w250p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w250p0_int*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w36p5_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w36p5_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w40p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w40p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w50p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w50p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w60p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w60p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w80p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w80p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w100p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w9p125_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m365_w9p125_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w10p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m400_w10p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w12p5_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m500_w12p5_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w15p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m600_w15p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w20p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m800_w20p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w25p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w91p25_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w91p25_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w100p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w100p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w125p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w125p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w150p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w150p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w200p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w200p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w250p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w250p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w36p5_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w36p5_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w40p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w40p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w50p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w50p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w60p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w60p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w80p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w80p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w100p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w100p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w9p125_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w9p125_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w10p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w10p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w12p5_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w12p5_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w15p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w15p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w20p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w20p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w25p0_res.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w25p0_res_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w91p25_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w91p25_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w100p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w100p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w125p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w125p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w150p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w150p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w200p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w200p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w250p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w250p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w36p5_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w36p5_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w40p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w40p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w50p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w50p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w60p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w60p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w80p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w80p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w100p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w100p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w9p125_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m365_w9p125_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w10p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m400_w10p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w12p5_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m500_w12p5_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w15p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m600_w15p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w20p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m800_w20p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w25p0_int.root ${input_dir}uhh2.AnalysisModuleRunner.MC.HscalarToTTTo1L1Nu2J_m1000_w25p0_int_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-500.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-500_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-1000.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-1000_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-1500.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-1500_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-2000.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-2000_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-2500.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-2500_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-3000.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-3000_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-3500.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-3500_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-4000.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-4000_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-4500.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-4500_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-5000.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-5000_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-5500.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-5500_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-6000.root ${input_dir}uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M-6000_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M400_W40.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M400_W40_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M500_W50.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M500_W50_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M600_W60.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M600_W60_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M700_W70.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M700_W70_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M800_W80.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M800_W80_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M900_W90.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M900_W90_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1000_W100.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1000_W100_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1200_W120.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1200_W120_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1400_W140.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1400_W140_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1600_W160.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1600_W160_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1800_W180.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1800_W180_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2000_W200.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2000_W200_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2500_W250.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2500_W250_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3000_W300.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3000_W300_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3500_W350.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3500_W350_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4000_W400.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4000_W400_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4500_W450.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4500_W450_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M5000_W500.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M5000_W500_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M6000_W600.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M6000_W600_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M7000_W700.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M7000_W700_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M8000_W800.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M8000_W800_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M9000_W900.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M9000_W900_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M400_W120.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M400_W120_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M500_W150.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M500_W150_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M600_W180.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M600_W180_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M700_W210.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M700_W210_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M800_W240.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M800_W240_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M900_W270.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M900_W270_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1000_W300.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1000_W300_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1200_W360.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1200_W360_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1400_W420.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1400_W420_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1600_W480.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1600_W480_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1800_W540.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1800_W540_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2000_W600.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2000_W600_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2500_W750.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2500_W750_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3000_W900.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3000_W900_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3500_W1050.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3500_W1050_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4000_W1200.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4000_W1200_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4500_W1350.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4500_W1350_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M5000_W1500.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M5000_W1500_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M6000_W1800.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M6000_W1800_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M7000_W2100.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M7000_W2100_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M8000_W2400.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M8000_W2400_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M9000_W2700.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M9000_W2700_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M400_W4.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M400_W4_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M500_W5.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M500_W5_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M600_W6.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M600_W6_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M700_W7.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M700_W7_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M800_W8.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M800_W8_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M900_W9.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M900_W9_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1000_W10.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1000_W10_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1200_W12.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1200_W12_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1400_W14.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1400_W14_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1600_W16.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1600_W16_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1800_W18.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M1800_W18_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2000_W20.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2000_W20_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2500_W25.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M2500_W25_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3000_W30.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3000_W30_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3500_W35.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M3500_W35_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4000_W40.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4000_W40_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4500_W45.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M4500_W45_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M5000_W50.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M5000_W50_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M6000_W60.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M6000_W60_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M7000_W70.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M7000_W70_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M8000_W80.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M8000_W80_*.root
hadd -T ${output_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M9000_W90.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZPrimeToTT_M9000_W90_*.root
