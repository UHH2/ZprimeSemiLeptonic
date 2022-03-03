import sys
sys.path.insert(1, '/nfs/dust/cms/user/deleokse/MC_UL_prod/CMSSW_10_6_28/src/UHH2/common/UHH2-datasets/')

from CrossSectionHelperSignals import *

year = "UL16postVFP" # choose: UL16preVFP, UL16postVFP, UL17, UL18
print("---------- " + year + " ----------")

samples = [
    "HpseudoToTTTo1L1Nu2J_m365_w91p25_res",
    "HpseudoToTTTo1L1Nu2J_m400_w100p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w125p0_res",
    "HpseudoToTTTo1L1Nu2J_m600_w150p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w200p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_36p5_res",
    "HpseudoToTTTo1L1Nu2J_m400_w40p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w50p0_res",
    "HpseudoToTTTo1L1Nu2J_m600_w60p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w80p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_w9p125_res",
    "HpseudoToTTTo1L1Nu2J_m400_w10p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w12p5_res",
    "HpseudoToTTTo1L1Nu2J_m600_w15p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w20p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_w91p25_int",
    "HpseudoToTTTo1L1Nu2J_m400_w100p0_int",
    "HpseudoToTTTo1L1Nu2J_m500_w125p0_int",
    "HpseudoToTTTo1L1Nu2J_m600_w150p0_int",
    "HpseudoToTTTo1L1Nu2J_m800_w200p0_int",
    "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int",
    "HpseudoToTTTo1L1Nu2J_m365_36p5_int",
    "HpseudoToTTTo1L1Nu2J_m400_w40p0_int",
    "HpseudoToTTTo1L1Nu2J_m500_w50p0_int",
    "HpseudoToTTTo1L1Nu2J_m600_w60p0_int",
    "HpseudoToTTTo1L1Nu2J_m800_w80p0_int",
    "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int",
    "HpseudoToTTTo1L1Nu2J_m365_w9p125_int",
    "HpseudoToTTTo1L1Nu2J_m400_w10p0_int",
    "HpseudoToTTTo1L1Nu2J_m500_w12p5_int",
    "HpseudoToTTTo1L1Nu2J_m600_w15p0_int",
    "HpseudoToTTTo1L1Nu2J_m800_w20p0_int",
    "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int",
    "HscalarToTTTo1L1Nu2J_m365_w91p25_res",
    "HscalarToTTTo1L1Nu2J_m400_w100p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w125p0_res",
    "HscalarToTTTo1L1Nu2J_m600_w150p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w200p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w250p0_res",
    "HscalarToTTTo1L1Nu2J_m365_36p5_res",
    "HscalarToTTTo1L1Nu2J_m400_w40p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w50p0_res",
    "HscalarToTTTo1L1Nu2J_m600_w60p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w80p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w100p0_res",
    "HscalarToTTTo1L1Nu2J_m365_w9p125_res",
    "HscalarToTTTo1L1Nu2J_m400_w10p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w12p5_res",
    "HscalarToTTTo1L1Nu2J_m600_w15p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w20p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w25p0_res",
    "HscalarToTTTo1L1Nu2J_m365_w91p25_int",
    "HscalarToTTTo1L1Nu2J_m400_w100p0_int",
    "HscalarToTTTo1L1Nu2J_m500_w125p0_int",
    "HscalarToTTTo1L1Nu2J_m600_w150p0_int",
    "HscalarToTTTo1L1Nu2J_m800_w200p0_int",
    "HscalarToTTTo1L1Nu2J_m1000_w250p0_int",
    "HscalarToTTTo1L1Nu2J_m365_36p5_int",
    "HscalarToTTTo1L1Nu2J_m400_w40p0_int",
    "HscalarToTTTo1L1Nu2J_m500_w50p0_int",
    "HscalarToTTTo1L1Nu2J_m600_w60p0_int",
    "HscalarToTTTo1L1Nu2J_m800_w80p0_int",
    "HscalarToTTTo1L1Nu2J_m1000_w100p0_int",
    "HscalarToTTTo1L1Nu2J_m365_w9p125_int",
    "HscalarToTTTo1L1Nu2J_m400_w10p0_int",
    "HscalarToTTTo1L1Nu2J_m500_w12p5_int",
    "HscalarToTTTo1L1Nu2J_m600_w15p0_int",
    "HscalarToTTTo1L1Nu2J_m800_w20p0_int",
    "HscalarToTTTo1L1Nu2J_m1000_w25p0_int",

    "RSGluonToTT_M-500",
    "RSGluonToTT_M-1000",
    "RSGluonToTT_M-1500",
    "RSGluonToTT_M-2000",
    "RSGluonToTT_M-2500",
    "RSGluonToTT_M-3000",
    "RSGluonToTT_M-3500",
    "RSGluonToTT_M-4000",
    "RSGluonToTT_M-4500",
    "RSGluonToTT_M-5000",
    "RSGluonToTT_M-5500",
    "RSGluonToTT_M-6000",

    "ZPrimeToTT_M400_W40",
    "ZPrimeToTT_M500_W50",
    "ZPrimeToTT_M600_W60",
    "ZPrimeToTT_M700_W70",
    "ZPrimeToTT_M800_W80",
    "ZPrimeToTT_M900_W90",
    "ZPrimeToTT_M1000_W100",
    "ZPrimeToTT_M1200_W120",
    "ZPrimeToTT_M1400_W140",
    "ZPrimeToTT_M1600_W160",
    "ZPrimeToTT_M1800_W180",
    "ZPrimeToTT_M2000_W200",
    "ZPrimeToTT_M2500_W250",
    "ZPrimeToTT_M3000_W300",
    "ZPrimeToTT_M3500_W350",
    "ZPrimeToTT_M4000_W400",
    "ZPrimeToTT_M4500_W450",
    "ZPrimeToTT_M5000_W500",
    "ZPrimeToTT_M6000_W600",
    "ZPrimeToTT_M7000_W700",
    "ZPrimeToTT_M8000_W800",
    "ZPrimeToTT_M9000_W900",

    "ZPrimeToTT_M400_W120",
    "ZPrimeToTT_M500_W150",
    "ZPrimeToTT_M600_W180",
    "ZPrimeToTT_M700_W210",
    "ZPrimeToTT_M800_W240",
    "ZPrimeToTT_M900_W270",
    "ZPrimeToTT_M1000_W300",
    "ZPrimeToTT_M1200_W360",
    "ZPrimeToTT_M1400_W420",
    "ZPrimeToTT_M1600_W480",
    "ZPrimeToTT_M1800_W540",
    "ZPrimeToTT_M2000_W600",
    "ZPrimeToTT_M2500_W750",
    "ZPrimeToTT_M3000_W900",
    "ZPrimeToTT_M3500_W1050",
    "ZPrimeToTT_M4000_W1200",
    "ZPrimeToTT_M4500_W1350",
    "ZPrimeToTT_M5000_W1500",
    "ZPrimeToTT_M6000_W1800",
    "ZPrimeToTT_M7000_W2100",
    "ZPrimeToTT_M8000_W2400",
    "ZPrimeToTT_M9000_W2700",
]

helper = MCSampleValuesHelper()

for sample in samples:
    print(sample + ": " + str(helper.get_lumi(sample,"13TeV",year)))
