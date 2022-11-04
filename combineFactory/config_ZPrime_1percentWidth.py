#!/usr/bin/env python2

import ROOT
import collections
import os
import shutil
from collections import OrderedDict

inputdirs = {
    # "UL16": {
    #     "electron": "",
    #     "muon": ""
    # },
    # "UL17": {
    #     "electron": "",
    #     "muon": ""
    # },
    "UL18": {
        # "electron": "",
        # "muon": "" # TODO: put your input directory here!
    }
}

inputbasedir_pdf = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/hists_pdf/"
inputbasedir_mcscale = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/hists_mcscale/"

process_prefix = "uhh2.AnalysisModuleRunner.MC."

signal_name = "ZPrime_1percentWidth"

signals = [
    "ZPrimeToTT_M400_W4",
    "ZPrimeToTT_M500_W5",
    "ZPrimeToTT_M600_W6",
    "ZPrimeToTT_M700_W7",
    "ZPrimeToTT_M800_W8",
    "ZPrimeToTT_M900_W9",
    "ZPrimeToTT_M1000_W10",
    "ZPrimeToTT_M1200_W12",
    "ZPrimeToTT_M1400_W14",
    "ZPrimeToTT_M1600_W16",
    "ZPrimeToTT_M1800_W18",
    "ZPrimeToTT_M2000_W20",
    "ZPrimeToTT_M2500_W25",
    "ZPrimeToTT_M3000_W30",
    "ZPrimeToTT_M3500_W35",
    "ZPrimeToTT_M4000_W40",
    "ZPrimeToTT_M4500_W45",
    "ZPrimeToTT_M5000_W50",
    "ZPrimeToTT_M6000_W60",
    "ZPrimeToTT_M7000_W70",
    "ZPrimeToTT_M8000_W80",
    "ZPrimeToTT_M9000_W90"
]

backgrounds = [
    "TTbar",
    "ST",
    "WJets",
    "others", # DY + Diboson + QCD
]

data = [
    "data_obs" # Asimov data for now
]

processes = backgrounds + 1

regions = OrderedDict()
regions["SRbin1_TopTag"] = "Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin1"
regions["SRbin1_NoTopTag"] = "Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin1"
regions["SRbin2_TopTag"] = "Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin2"
regions["SRbin2_NoTopTag"] = "Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin2"
regions["SRbin3"] = "Zprime_SystVariations_DNN_output0_thetastar_bin3"
regions["SRbin4"] = "Zprime_SystVariations_DNN_output0_thetastar_bin4"
regions["CR1"] = "Zprime_SystVariations_DNN_output1"
regions["CR2"] = "Zprime_SystVariations_DNN_output2"

vars = {
    "M_Zprime"
}

# normalization systematics
rates = OrderedDict()
rates["ttbar_rate"] = 1.2
rates["st_rate"] = 1.3
rates["wjets_rate"] = 1.5
rates["others_rate"] = 2.0
rates["lumi_13TeV_uncorrelated_UL16"] = 1.010
rates["lumi_13TeV_uncorrelated_UL17"] = 1.020
rates["lumi_13TeV_uncorrelated_UL18"] = 1.015
rates["lumi_13TeV_correlated_UL16_UL17_UL18"] = {"UL16": 1.006, "UL17": 1.009, "UL18": 1.02}
rates["lumi_13TeV_correlated_UL17_UL18"] = {"UL16": '-', "UL17": 1.006, "UL18": 1.002}

# shape systematics: up/down variations
shapes = OrderedDict()
shapes["pdf"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # pdf uncertainty
# shapes["mcscale"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # mcscale uncertainty: envelope of muR and muF up/down combinations
shapes["pu"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # pileup
# TODO: add JEC + JER
shapes["prefiring"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # prefiring
shapes["mu_id"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # muon id
shapes["mu_iso"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # muon isolation
shapes["mu_reco"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # muon reconstruction
shapes["mu_trigger"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # muon trigger
shapes["ele_id"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # electron id
shapes["ele_reco"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # electron reconstruction
# TODO: add ele trigger
# TODO: add top tagging
shapes["btag_cferr1"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # charm jet uncertainty 1
shapes["btag_cferr2"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # charm jet uncertainty 1
shapes["btag_hf"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # heavy flavor purity uncertainty
shapes["btag_hfstats1"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # heavy flavor statistical uncertainty
shapes["btag_hfstats2"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # heavy flavor statistical uncertainty
shapes["btag_lf"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # light flavor purity uncertainty
shapes["btag_lfstats1"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # light flavor statistical uncertainty
shapes["btag_lfstats2"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # light flavor statistical uncertainty
# shapes["isr"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # initial state radiation
# shapes["fsr"] = ["TTbar","ST","WJets","others","ZPrimeToTT_M400_W4","ZPrimeToTT_M500_W5","ZPrimeToTT_M600_W6","ZPrimeToTT_M700_W7","ZPrimeToTT_M800_W8","ZPrimeToTT_M900_W9","ZPrimeToTT_M1000_W10","ZPrimeToTT_M1200_W12","ZPrimeToTT_M1400_W14","ZPrimeToTT_M1600_W16","ZPrimeToTT_M1800_W18","ZPrimeToTT_M2000_W20","ZPrimeToTT_M2500_W25","ZPrimeToTT_M3000_W30","ZPrimeToTT_M3500_W35","ZPrimeToTT_M4000_W40","ZPrimeToTT_M4500_W45","ZPrimeToTT_M5000_W50","ZPrimeToTT_M6000_W60","ZPrimeToTT_M7000_W70","ZPrimeToTT_M8000_W80","ZPrimeToTT_M9000_W90"] # final state radiation


# characters per column
N1 = max([len(rate) for rate in rates] + [len(shape) for shape in shapes] + [1]) + 2
N2 = 8
N3 = max([len(region) for region in regions]) + 2
N4 = max([len(process) for process in processes] + [len(region) for region in regions]) + 2


def nested_dict_iter(nested):
    for key, value in nested.iteritems():
        if isinstance(value, collections.Mapping):
            for inner_key, inner_value in nested_dict_iter(value):
                yield key, inner_key, inner_value
        else:
            yield key, value

def check_file(file_path):
    if not os.path.isfile(file_path):
        raise ValueError("file does not exist: " + str(file_path))

def pad(s, n_pad):
    s = str(s)
    n_pad = n_pad - len(s)
    return s + n_pad * " "


def createCombineInput():
    print("will create input files for:")
    list_inputdirs = list(nested_dict_iter(inputdirs))

    for entry in list_inputdirs:
        year = entry[0]
        channel = entry[1]
        inputdir = entry[2]
        print(year + " " + channel)

        for signal in signals:

            filename_out = "inputHistograms_" + signal + "_" + year + "_" + channel + ".root"
            file_out = ROOT.TFile(signal_name + "/" + filename_out, "RECREATE")

            for region in regions:
                for process in processes + data:
                    filename_in = inputdir + process_prefix + process + ".root"
                    check_file(filename_in)
                    file_in = ROOT.TFile(filename_in)
                    if not process == "data_obs":
                        filename_in_pdf = inputbasedir_pdf + year + "/" + channel + "/" + process_prefix + process + ".root"
                        check_file(filename_in_pdf)
                        file_in_pdf = ROOT.TFile(filename_in_pdf)
                        filename_in_mcscale = inputbasedir_mcscale + year + "/" + channel + "/" + process_prefix + process + ".root"
                        check_file(filename_in_mcscale)
                        file_in_mcscale = ROOT.TFile(filename_in_mcscale)

                    for var in vars:
                        hist_in = file_in.Get(regions[region] + "/" + var)
                        file_out.cd()
                        hist_out = hist_in.Clone()

                        hist_out.Write(region + "_" + process)
                        if process == "data_obs": continue

                        for shape in shapes:
                            if str(channel) == "muon" and shape.startswith("ele_"): continue
                            if str(channel) == "electron" and shape.startswith("mu_"): continue
                            if process in shapes[shape]:
                                if shape == "pdf":
                                    hist_syst_up_in = file_in_pdf.Get(regions[region] + "/" + var + "_" + shape + "_up")
                                    hist_syst_down_in = file_in_pdf.Get(regions[region] + "/" + var + "_" + shape + "_down")
                                elif shape == "mcscale":
                                    hist_syst_up_in = file_in_mcscale.Get(regions[region] + "/" + var + "_" + shape + "_up")
                                    hist_syst_down_in = file_in_mcscale.Get(regions[region] + "/" + var + "_" + shape + "_down")
                                else:
                                    hist_syst_up_in = file_in.Get(regions[region] + "/" + var + "_" + shape + "_up")
                                    hist_syst_down_in = file_in.Get(regions[region] + "/" + var + "_" + shape + "_down")
                                hist_syst_up_out = hist_syst_up_in.Clone()
                                hist_syst_down_out = hist_syst_down_in.Clone()
                                hist_syst_up_out.Write(region + "_" + process + "_" + shape + "Up")
                                hist_syst_down_out.Write(region + "_" + process + "_" + shape + "Down")
                        file_in.Close()

            datacard_name = signal_name + "/" + "datacard_" + signal + "_" + year + "_" + channel + ".dat"
            with open(datacard_name, 'w') as datacard:
                datacard.write("# PARAMETERS\n")
                datacard.write("imax " + str(len(regions)) + " number of regions\n")
                datacard.write("jmax " + str(len(processes) - 1) + " number of processes -1\n")
                datacard.write("kmax *\n")
                datacard.write("shapes * * " + filename_out + " $CHANNEL_$PROCESS $CHANNEL_$PROCESS_$SYSTEMATIC\n")
                datacard.write((N1 + N2 - 2) * "-" + "\n")
                datacard.write("# regions\n")
                datacard.write("bin          " + "".join([pad(region, N3) for region in regions]) + "\n")
                datacard.write("observation  " + "".join([pad("-1", N3) for region in regions]) + "\n")
                datacard.write((N1 + N2 - 2) * "-" + "\n")
                datacard.write("# PROCESSES\n")
                datacard.write(pad("bin", N1 + N2) + "".join([pad(region, N4) for region in regions for process in processes]) + "\n")
                datacard.write(pad("process", N1 + N2) + "".join([pad(process, N4) for region in regions for process in processes]) + "\n")
                datacard.write(pad("process", N1 + N2) + ("".join([pad("-1", N4) + [pad(str(b+1), N4) for b in range(len(backgrounds))])) * len(regions) + "\n")
                datacard.write(pad("rate", N1 + N2) + "".join([pad("-1", N4)  for region in regions for process in processes]) + "\n")
                datacard.write((N1 + N2 - 2) * "-" + "\n")
                datacard.write("# SYSTEMATICS\n")

                # normalization systematics
                for rate in rates:
                    datacard.write(pad(rate, N1) + pad("lnN", N2))
                    for region in regions:
                        for process in processes:
                            if "uncorrelated" in rate and year in rate: # uncorrelated lumi
                                datacard.write(pad(rates[rate], N4))
                            elif "correlated" in rate and year in rate: # correlated lumi
                                datacard.write(pad(rates[rate][year], N4))
                            elif process.lower() + "_rate" == rate: # cross sections
                                datacard.write(pad(rates[rate], N4))
                            else: # other
                                datacard.write(pad("-", N4))
                    datacard.write("\n")

                # shape systematics
                for shape in shapes:
                    if str(channel) == "muon" and shape.startswith("ele_"): continue
                    if str(channel) == "electron" and shape.startswith("mu_"): continue
                    datacard.write(pad(shape, N1) + pad("shape", N2))
                    for region in regions:
                        for process in processes:
                            if process in shapes[shape]:
                                datacard.write(pad("1.0", N4))
                            else:
                                datacard.write(pad("-", N4))
                    datacard.write("\n")

                datacard.write((N1 + N2 - 2) * "-" + "\n")
                datacard.write("* autoMCStats 0 0 1")

    print("done.")


if __name__ == "__main__":
    createCombineInput()
