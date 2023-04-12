#!/bin/bash

year="UL18" # UL16preVFP UL16postVFP UL17 UL18
channel="muon" # electron / muon

# where UHH2 code is installed
UHH_dir=/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/

#where (NOT MERGED) trees after preselection stored
input_dir="/nfs/dust/cms/group/zprime-uhh/Analysis_${year}/${channel}/workdir_Analysis_${year}_${channel}/uhh2.AnalysisModuleRunner."

# output dir
output_dir=$UHH_dir/ZprimeSemiLeptonic/data/Skimming_datasets_${year}_${channel}

if [ -d "${output_dir}" ]; then
    echo "output directory exists, will be deleted..."
    rm -r ${output_dir}
fi
echo "(re)create output directory..."
mkdir ${output_dir}
cd ${output_dir}

# MC
for mc_name in TTToSemiLeptonic_${year} TTToHadronic_${year} TTTo2L2Nu_${year} WJetsToLNu_HT-70To100_${year} WJetsToLNu_HT-100To200_${year} WJetsToLNu_HT-200To400_${year} WJetsToLNu_HT-400To600_${year} WJetsToLNu_HT-600To800_${year} WJetsToLNu_HT-800To1200_${year} WJetsToLNu_HT-1200To2500_${year} WJetsToLNu_HT-2500ToInf_${year} DYJetsToLL_M-50_HT-70to100_${year} DYJetsToLL_M-50_HT-100to200_${year} DYJetsToLL_M-50_HT-200to400_${year} DYJetsToLL_M-50_HT-400to600_${year} DYJetsToLL_M-50_HT-600to800_${year} DYJetsToLL_M-50_HT-800to1200_${year} DYJetsToLL_M-50_HT-1200to2500_${year} DYJetsToLL_M-50_HT-2500toInf_${year} WW_${year} WZ_${year} ZZ_${year} ST_tW_antitop_5f_NoFullyHadronicDecays_${year} ST_tW_top_5f_NoFullyHadronicDecays_${year} ST_t-channel_antitop_4f_InclusiveDecays_${year} ST_t-channel_top_4f_InclusiveDecays_${year} ST_s-channel_4f_leptonDecays_${year} QCD_HT50to100_${year} QCD_HT100to200_${year} QCD_HT200to300_${year} QCD_HT300to500_${year} QCD_HT500to700_${year} QCD_HT700to1000_${year} QCD_HT1000to1500_${year} QCD_HT1500to2000_${year} QCD_HT2000toInf_${year} ALP_ttbar_signal_${year} ALP_ttbar_interference_${year} HscalarToTTTo1L1Nu2J_m365_w36p5_res_${year} HscalarToTTTo1L1Nu2J_m400_w40p0_res_${year} HscalarToTTTo1L1Nu2J_m500_w50p0_res_${year} HscalarToTTTo1L1Nu2J_m600_w60p0_res_${year} HscalarToTTTo1L1Nu2J_m800_w80p0_res_${year} HscalarToTTTo1L1Nu2J_m1000_w100p0_res_${year} HpseudoToTTTo1L1Nu2J_m365_w36p5_res_${year} HpseudoToTTTo1L1Nu2J_m400_w40p0_res_${year} HpseudoToTTTo1L1Nu2J_m500_w50p0_res_${year} HpseudoToTTTo1L1Nu2J_m600_w60p0_res_${year} HpseudoToTTTo1L1Nu2J_m800_w80p0_res_${year} HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_${year}  HscalarToTTTo1L1Nu2J_m365_w91p25_res_${year} HscalarToTTTo1L1Nu2J_m400_w100p0_res_${year} HscalarToTTTo1L1Nu2J_m500_w125p0_res_${year} HscalarToTTTo1L1Nu2J_m600_w150p0_res_${year} HscalarToTTTo1L1Nu2J_m800_w200p0_res_${year} HscalarToTTTo1L1Nu2J_m1000_w250p0_res_${year} HpseudoToTTTo1L1Nu2J_m365_w91p25_res_${year} HpseudoToTTTo1L1Nu2J_m400_w100p0_res_${year} HpseudoToTTTo1L1Nu2J_m500_w125p0_res_${year} HpseudoToTTTo1L1Nu2J_m600_w150p0_res_${year} HpseudoToTTTo1L1Nu2J_m800_w200p0_res_${year} HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_${year} HscalarToTTTo1L1Nu2J_m365_w9p125_res_${year} HscalarToTTTo1L1Nu2J_m400_w10p0_res_${year} HscalarToTTTo1L1Nu2J_m500_w12p5_res_${year} HscalarToTTTo1L1Nu2J_m600_w15p0_res_${year} HscalarToTTTo1L1Nu2J_m800_w20p0_res_${year} HscalarToTTTo1L1Nu2J_m1000_w25p0_res_${year}  HpseudoToTTTo1L1Nu2J_m365_w9p125_res_${year} HpseudoToTTTo1L1Nu2J_m400_w10p0_res_${year} HpseudoToTTTo1L1Nu2J_m500_w12p5_res_${year} HpseudoToTTTo1L1Nu2J_m600_w15p0_res_${year} HpseudoToTTTo1L1Nu2J_m800_w20p0_res_${year} HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_${year} RSGluonToTT_M-500_${year} RSGluonToTT_M-1000_${year} RSGluonToTT_M-1500_${year} RSGluonToTT_M-2000_${year} RSGluonToTT_M-2500_${year} RSGluonToTT_M-3000_${year} RSGluonToTT_M-3500_${year} RSGluonToTT_M-4000_${year} RSGluonToTT_M-4500_${year} RSGluonToTT_M-5000_${year} RSGluonToTT_M-5500_${year} RSGluonToTT_M-6000_${year} ZPrimeToTT_M400_W40_${year} ZPrimeToTT_M500_W50_${year} ZPrimeToTT_M600_W60_${year} ZPrimeToTT_M700_W70_${year} ZPrimeToTT_M800_W80_${year} ZPrimeToTT_M900_W90_${year} ZPrimeToTT_M1000_W100_${year} ZPrimeToTT_M1200_W120_${year} ZPrimeToTT_M1400_W140_${year} ZPrimeToTT_M1600_W160_${year} ZPrimeToTT_M1800_W180_${year} ZPrimeToTT_M2000_W200_${year} ZPrimeToTT_M2500_W250_${year} ZPrimeToTT_M3000_W300_${year} ZPrimeToTT_M3500_W350_${year} ZPrimeToTT_M4000_W400_${year} ZPrimeToTT_M4500_W450_${year} ZPrimeToTT_M5000_W500_${year} ZPrimeToTT_M6000_W600_${year} ZPrimeToTT_M7000_W700_${year} ZPrimeToTT_M8000_W800_${year} ZPrimeToTT_M9000_W900_${year} ZPrimeToTT_M400_W120_${year} ZPrimeToTT_M500_W150_${year} ZPrimeToTT_M600_W180_${year} ZPrimeToTT_M700_W210_${year} ZPrimeToTT_M800_W240_${year} ZPrimeToTT_M900_W270_${year} ZPrimeToTT_M1000_W300_${year} ZPrimeToTT_M1200_W360_${year} ZPrimeToTT_M1400_W420_${year} ZPrimeToTT_M1600_W480_${year} ZPrimeToTT_M1800_W540_${year} ZPrimeToTT_M2000_W600_${year} ZPrimeToTT_M2500_W750_${year} ZPrimeToTT_M3000_W900_${year} ZPrimeToTT_M3500_W1050_${year} ZPrimeToTT_M4000_W1200_${year} ZPrimeToTT_M4500_W1350_${year} ZPrimeToTT_M5000_W1500_${year} ZPrimeToTT_M6000_W1800_${year} ZPrimeToTT_M7000_W2100_${year} ZPrimeToTT_M8000_W2400_${year} ZPrimeToTT_M9000_W2700_${year} ZPrimeToTT_M400_W4_${year} ZPrimeToTT_M500_W5_${year} ZPrimeToTT_M600_W6_${year} ZPrimeToTT_M700_W7_${year} ZPrimeToTT_M800_W8_${year} ZPrimeToTT_M900_W9_${year} ZPrimeToTT_M1000_W10_${year} ZPrimeToTT_M1200_W12_${year} ZPrimeToTT_M1400_W14_${year} ZPrimeToTT_M1600_W16_${year} ZPrimeToTT_M1800_W18_${year} ZPrimeToTT_M2000_W20_${year} ZPrimeToTT_M2500_W25_${year} ZPrimeToTT_M3000_W30_${year} ZPrimeToTT_M3500_W35_${year} ZPrimeToTT_M4000_W40_${year} ZPrimeToTT_M4500_W45_${year} ZPrimeToTT_M5000_W50_${year} ZPrimeToTT_M6000_W60_${year} ZPrimeToTT_M7000_W70_${year} ZPrimeToTT_M8000_W80_${year} ZPrimeToTT_M9000_W90_${year} HscalarToTTTo1L1Nu2J_m365_w36p5_int_pos_${year} HscalarToTTTo1L1Nu2J_m400_w40p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m500_w50p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m600_w60p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m800_w80p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m1000_w100p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m365_w36p5_int_pos_${year} HpseudoToTTTo1L1Nu2J_m400_w40p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m500_w50p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m600_w60p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m800_w80p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m365_w91p25_int_pos_${year} HscalarToTTTo1L1Nu2J_m400_w100p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m500_w125p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m600_w150p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m800_w200p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m1000_w250p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m365_w91p25_int_pos_${year} HpseudoToTTTo1L1Nu2J_m400_w100p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m500_w125p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m600_w150p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m800_w200p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m365_w9p125_int_pos_${year} HscalarToTTTo1L1Nu2J_m400_w10p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m500_w12p5_int_pos_${year} HscalarToTTTo1L1Nu2J_m600_w15p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m800_w20p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m1000_w25p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m365_w9p125_int_pos_${year} HpseudoToTTTo1L1Nu2J_m400_w10p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m500_w12p5_int_pos_${year} HpseudoToTTTo1L1Nu2J_m600_w15p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m800_w20p0_int_pos_${year} HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_pos_${year} HscalarToTTTo1L1Nu2J_m365_w36p5_int_neg_${year} HscalarToTTTo1L1Nu2J_m400_w40p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m500_w50p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m600_w60p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m800_w80p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m1000_w100p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m365_w36p5_int_neg_${year} HpseudoToTTTo1L1Nu2J_m400_w40p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m500_w50p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m600_w60p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m800_w80p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m365_w91p25_int_neg_${year} HscalarToTTTo1L1Nu2J_m400_w100p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m500_w125p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m600_w150p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m800_w200p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m1000_w250p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m365_w91p25_int_neg_${year} HpseudoToTTTo1L1Nu2J_m400_w100p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m500_w125p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m600_w150p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m800_w200p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m365_w9p125_int_neg_${year} HscalarToTTTo1L1Nu2J_m400_w10p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m500_w12p5_int_neg_${year} HscalarToTTTo1L1Nu2J_m600_w15p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m800_w20p0_int_neg_${year} HscalarToTTTo1L1Nu2J_m1000_w25p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m365_w9p125_int_neg_${year} HpseudoToTTTo1L1Nu2J_m400_w10p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m500_w12p5_int_neg_${year} HpseudoToTTTo1L1Nu2J_m600_w15p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m800_w20p0_int_neg_${year} HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_neg_${year}
do
    echo $mc_name
    $UHH_dir/scripts/create-dataset-xmlfile ${input_dir}"MC."${mc_name}"*.root" "MC_"$mc_name.xml
    nice -n 10 python $UHH_dir/scripts/crab/readaMCatNloEntries.py 10 "MC_"$mc_name.xml True
done

# DATA
if [ ${channel} = "electron" ]; then
    if [ ${year} = "UL18" ]; then
        for data_name in EGamma_RunA_${year} EGamma_RunB_${year} EGamma_RunC_${year} EGamma_RunD_${year}
        do
            echo $data_name
            $UHH_dir/scripts/create-dataset-xmlfile ${input_dir}"DATA."${data_name}"*.root" $data_name.xml
            nice -n 10 python $UHH_dir/scripts/crab/readaMCatNloEntries.py 10 DATA_$data_name.xml True
        done
    elif [ ${year} = "UL16postVFP" ]; then
        for data_name in DATA_SingleElectron_RunF_${year} DATA_SingleElectron_RunG_${year} DATA_SingleElectron_RunH_${year}
        do
            echo $data_name
            $UHH_dir/scripts/create-dataset-xmlfile ${input_dir}"DATA."${data_name}"*.root" $data_name.xml
            nice -n 10 python $UHH_dir/scripts/crab/readaMCatNloEntries.py 10 $data_name.xml True
        done
    else
        for data_name in DATA_SingleElectron_RunB_${year} DATA_SingleElectron_RunC_${year} DATA_SingleElectron_RunD_${year} DATA_SingleElectron_RunE_${year} DATA_SingleElectron_RunF_${year} DATA_SinglePhoton_RunB_${year} DATA_SinglePhoton_RunC_${year} DATA_SinglePhoton_RunD_${year} DATA_SinglePhoton_RunE_${year} DATA_SinglePhoton_RunF_${year}
        do
            echo $data_name
            $UHH_dir/scripts/create-dataset-xmlfile ${input_dir}"DATA."${data_name}"*.root" $data_name.xml
            nice -n 10 python $UHH_dir/scripts/crab/readaMCatNloEntries.py 10 $data_name.xml True
        done
    fi
elif [ ${channel} = "muon" ]; then
    if [ ${year} = "UL18" ]; then
        for data_name in SingleMuon_RunA_${year} SingleMuon_RunB_${year} SingleMuon_RunC_${year} SingleMuon_RunD_${year}
        do
            echo $data_name
            $UHH_dir/scripts/create-dataset-xmlfile ${input_dir}"DATA."${data_name}"*.root" $data_name.xml
            nice -n 10 python $UHH_dir/scripts/crab/readaMCatNloEntries.py 10 $data_name.xml True
        done
    elif [ ${year} = "UL16postVFP" ]; then
        for data_name in SingleMuon_RunF_${year} SingleMuon_RunG_${year} SingleMuon_RunH_${year}
        do
            echo $data_name
            $UHH_dir/scripts/create-dataset-xmlfile ${input_dir}"DATA."${data_name}"*.root" $data_name.xml
            nice -n 10 python $UHH_dir/scripts/crab/readaMCatNloEntries.py 10 $data_name.xml True
        done
    else
        for data_name in DATA_SingleMuon_RunB_${year} DATA_SingleMuon_RunC_${year} DATA_SingleMuon_RunD_${year} DATA_SingleMuon_RunE_${year} DATA_SingleMuon_RunF_${year}
        do
            echo $data_name
            $UHH_dir/scripts/create-dataset-xmlfile ${input_dir}"DATA."${data_name}"*.root" $data_name.xml
            nice -n 10 python $UHH_dir/scripts/crab/readaMCatNloEntries.py 10 $data_name.xml True
        done
    fi
fi

echo "output dir: ${output_dir}"
cd $UHH_dir/ZprimeSemiLeptonic/macros
