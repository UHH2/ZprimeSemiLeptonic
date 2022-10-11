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
        # "electron": "testdir",
        "muon": "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/UL18/muon/AnalysisDNN_withSyst/"
    }
}

inputbasedir_pdf = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/hists_pdf/"
inputbasedir_mcscale = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/hists_mcscale/"

process_prefix = "uhh2.AnalysisModuleRunner.MC."

output_tag = "ALP_UL18_muon_withSyst"

signals = [
"ALP_ttbar_signal",
"ALP_ttbar_interference",
]

# bin edges of input histogram
fas = [
    # 400,
    # 600,
    # 800,
    1000,
    # 1200,
    # 1400,
    # 1600,
    # 1800,
    2000,
    # 2200,
    # 2400,
    # 2600,
    # 2800,
    3000,
    # 3200,
    # 3400,
    # 3600,
    # 3800,
    4000,
    # 4400,
    # 4800,
    # 5200,
    # 5600,
    6000,
    # 6100
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

processes = signals + backgrounds

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
shapes["pdf"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # pdf uncertainty
# shapes["mcscale"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # mcscale uncertainty: envelope of muR and muF up/down combinations
# shapes["toppt_a"] = ["TTbar"] # top-pt reweighting parameter a: normalization only -> swallowed by mcscale
shapes["toppt_b"] = ["TTbar"] # top-pt reweighting parameter b
shapes["pu"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # pileup
# TODO: add JEC + JER
shapes["prefiring"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # prefiring
shapes["mu_id"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # muon id
shapes["mu_iso"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # muon isolation
shapes["mu_reco"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # muon reconstruction
shapes["mu_trigger"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # muon trigger
shapes["ele_id"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # electron id
shapes["ele_reco"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # electron reconstruction
# TODO: add ele trigger
# TODO: add top tagging
shapes["btag_cferr1"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # charm jet uncertainty 1
shapes["btag_cferr2"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # charm jet uncertainty 1
shapes["btag_hf"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # heavy flavor purity uncertainty
shapes["btag_hfstats1"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # heavy flavor statistical uncertainty
shapes["btag_hfstats2"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # heavy flavor statistical uncertainty
shapes["btag_lf"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # light flavor purity uncertainty
shapes["btag_lfstats1"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # light flavor statistical uncertainty
shapes["btag_lfstats2"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # light flavor statistical uncertainty
# shapes["isr"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # initial state radiation
# shapes["fsr"] = ["TTbar","ST","WJets","others","ALP_ttbar_signal","ALP_ttbar_interference"] # final state radiation


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

        for fa in fas:

            filename_out = year + "/" + channel + "/" + "inputHistograms_" + year + "_" + channel + "_fa" + str(fa) + ".root"
            file_out = ROOT.TFile(filename_out, "RECREATE")

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
                        if process == "ALP_ttbar_interference":
                            hist_out.Scale(-1)

                        # restrict events to EFT validity region: mttbar <= fa
                        Nbins = hist_out.GetNbinsX() + 2 # add underflow and overflow bin
                        if "M_Zprime" in var:
                            for bin in range(Nbins):
                                if hist_out.GetBinLowEdge(bin) >= fa:
                                    hist_out.SetBinContent(bin, 0.)
                                    hist_out.SetBinError(bin, 0.) # needed for combine to ignore this bin

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
                                if process == "ALP_ttbar_interference":
                                    hist_syst_up_out.Scale(-1)
                                    hist_syst_down_out.Scale(-1)
                                hist_syst_up_out.Write(region + "_" + process + "_" + shape + "Up")
                                hist_syst_down_out.Write(region + "_" + process + "_" + shape + "Down")
                        file_in.Close()

            datacard_name = year + "/" + channel + "/" + "datacard_" + year + "_" + channel + "_fa" + str(fa) + ".dat"
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
                datacard.write(pad("process", N1 + N2) + ("".join([pad(str(-s), N4) for s in range(len(signals))][::-1] + [pad(str(b+1), N4) for b in range(len(backgrounds))])) * len(regions) + "\n")
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
