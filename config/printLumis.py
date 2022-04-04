import sys
sys.path.insert(1, '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/common/UHH2-datasets/')

from CrossSectionHelper import *

year = "UL18" # choose: UL16preVFP, UL16postVFP, UL17, UL18
print("---------- " + year + " ----------")

samples = [
    "TTToSemiLeptonic",
    "TTToHadronic",
    "TTTo2L2Nu",
    "WJetsToLNu_HT-70to100",
    "WJetsToLNu_HT-100to200",
    "WJetsToLNu_HT-200to400",
    "WJetsToLNu_HT-400to600",
    "WJetsToLNu_HT-600to800",
    "WJetsToLNu_HT-800to1200",
    "WJetsToLNu_HT-1200to2500",
    "WJetsToLNu_HT-2500toInf",
    "DYJetsToLL_M-50_HT-70to100",
    "DYJetsToLL_M-50_HT-100to200",
    "DYJetsToLL_M-50_HT-200to400",
    "DYJetsToLL_M-50_HT-400to600",
    "DYJetsToLL_M-50_HT-600to800",
    "DYJetsToLL_M-50_HT-800to1200",
    "DYJetsToLL_M-50_HT-1200to2500",
    "DYJetsToLL_M-50_HT-2500toInf",
    "WW",
    "WZ",
    "ZZ",
    "ST_tW_antitop_5f_inclusiveDecays",
    "ST_tW_top_5f_inclusiveDecays",
    "ST_tW_antitop_5f_NoFullyHadronicDecays",
    "ST_tW_top_5f_NoFullyHadronicDecays",
    "ST_t-channel_antitop_4f_InclusiveDecays",
    "ST_t-channel_top_4f_InclusiveDecays",
    "ST_s-channel_4f_leptonDecays",
    "QCD_HT50to100",
    "QCD_HT100to200",
    "QCD_HT200to300",
    "QCD_HT300to500",
    "QCD_HT500to700",
    "QCD_HT700to1000",
    "QCD_HT1000to1500",
    "QCD_HT1500to2000",
    "QCD_HT2000toInf",
    "ALP_ttbar_signal",
    "ALP_ttbar_interference"
]

helper = MCSampleValuesHelper()

for sample in samples:
    print(sample + ": " + str(helper.get_lumi(sample,"13TeV",year)))
