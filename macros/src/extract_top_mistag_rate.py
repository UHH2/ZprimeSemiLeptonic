#!/usr/bin/env python2

import ROOT
import os
import json
import numpy as np
from collections import OrderedDict

path_base = "/nfs/dust/cms/group/zprime-uhh/AnalysisDNN_"

years = [
    "UL16preVFP",
    "UL16postVFP",
    "UL17",
    "UL18",
]

channels = [
    "electron",
    "muon",
]

# initialize values with zero
processes = OrderedDict([
    ("DATA", {
        "process_name": "DATA",
        "sample_name": "DATA",
        "hist_name": "pt_AK8jet1",
        "n": 0.0,
        "n_err": 0.0,
        "n_tagged": 0.0,
        "n_tagged_err": 0.0,
    }),
    ("TTbar_t", {
        "process_name": "TTbar_t",
        "sample_name": "TTbar",
        "hist_name": "pt_AK8Topjet1",
        "n": 0.0,
        "n_err": 0.0,
        "n_tagged": 0.0,
        "n_tagged_err": 0.0,
    }),
    ("TTbar_l", {
        "process_name": "TTbar_l",
        "sample_name": "TTbar",
        "hist_name": "pt_AK8Lightjet1",
        "n": 0.0,
        "n_err": 0.0,
        "n_tagged": 0.0,
        "n_tagged_err": 0.0,
    }),
    ("ST_t", {
        "process_name": "ST_t",
        "sample_name": "ST",
        "hist_name": "pt_AK8Topjet1",
        "n": 0.0,
        "n_err": 0.0,
        "n_tagged": 0.0,
        "n_tagged_err": 0.0,
    }),
    ("ST_l", {
        "process_name": "ST_l",
        "sample_name": "ST",
        "hist_name": "pt_AK8Lightjet1",
        "n": 0.0,
        "n_err": 0.0,
        "n_tagged": 0.0,
        "n_tagged_err": 0.0,

    }),
    ("WJets", {
        "process_name": "WJets",
        "sample_name": "WJets",
        "hist_name": "pt_AK8jet1",
        "n": 0.0,
        "n_err": 0.0,
        "n_tagged": 0.0,
        "n_tagged_err": 0.0,

    }),
    ("DY", {
        "process_name": "DY",
        "sample_name": "DY",
        "hist_name": "pt_AK8jet1",
        "n": 0.0,
        "n_err": 0.0,
        "n_tagged": 0.0,
        "n_tagged_err": 0.0,

    }),
    ("QCD", {
        "process_name": "QCD",
        "sample_name": "QCD",
        "hist_name": "pt_AK8jet1",
        "n": 0.0,
        "n_err": 0.0,
        "n_tagged": 0.0,
        "n_tagged_err": 0.0,

    }),
])


output = OrderedDict([
    ("UL16preVFP", {
        "scale_factor": 0.0,
        "error": 0.0
    }),
    ("UL16postVFP", {
        "scale_factor": 0.0,
        "error": 0.0
    }),
    ("UL17", {
        "scale_factor": 0.0,
        "error": 0.0
    }),
    ("UL18", {
        "scale_factor": 0.0,
        "error": 0.0
    })
])



histograms = []


for year in years:
    print(year)
    el_SF = 0.0
    el_SF_err = 0.0
    mu_SF = 0.0
    mu_SF_err = 0.0

    for channel in channels:
        print(channel)

        for key, process in processes.items():
            process_name = process.get("process_name")
            sample_name = process.get("sample_name")
            hist_name = process.get("hist_name")
            print(process_name)

            file_path = path_base + year + "/Mistag_rate/" + channel + "/uhh2.AnalysisModuleRunner."
            if sample_name == "DATA":
                file_path += "DATA"
            else:
                file_path += "MC"
            file_path += "." + sample_name + ".root"

            # get values from input file
            input_file = ROOT.TFile(file_path)
            n = input_file.Get("Mistag/" + hist_name).Integral()
            n_tagged = input_file.Get("Mistag/" + hist_name + "_tagged").Integral()
            input_file.Close()

            # calculate errors
            n_err = np.sqrt(n)
            n_tagged_err = np.sqrt(n_tagged)

            # update values in dict
            processes[process_name]["n"] = n
            processes[process_name]["n_err"] = n_err
            processes[process_name]["n_tagged"] = n_tagged
            processes[process_name]["n_tagged_err"] = n_tagged_err
            print("       events: " + str(n) + " +/- " + str(n_err))
            print("tagged events: " + str(n_tagged) + " +/- " + str(n_tagged_err))

        # efficiency in DATA
        efficiency_data = (processes["DATA"]["n_tagged"] - processes["TTbar_t"]["n_tagged"] - processes["ST_t"]["n_tagged"]) / (processes["DATA"]["n"] - processes["TTbar_t"]["n"] - processes["ST_t"]["n"])
        efficiency_err_data = np.sqrt((processes["DATA"]["n_tagged_err"]**2 + processes["TTbar_t"]["n_tagged_err"]**2 + processes["ST_t"]["n_tagged_err"]**2) / (processes["DATA"]["n"] - processes["TTbar_t"]["n"] - processes["ST_t"]["n"])**2  +
        ((processes["DATA"]["n_err"]**2 + processes["TTbar_t"]["n_err"]**2 + processes["ST_t"]["n_err"]**2)) * (processes["DATA"]["n_tagged"] - processes["TTbar_t"]["n_tagged"] - processes["ST_t"]["n_tagged"])**2 / (processes["DATA"]["n"] - processes["TTbar_t"]["n"] - processes["ST_t"]["n"])**4)
        print("efficiency data: " + str(efficiency_data) + " +/- " + str(efficiency_err_data))

        # efficiency in MC
        efficiency_mc = (processes["WJets"]["n_tagged"] + processes["TTbar_l"]["n_tagged"] + processes["ST_l"]["n_tagged"] + processes["DY"]["n_tagged"] + processes["QCD"]["n_tagged"]) / (processes["WJets"]["n"] + processes["TTbar_l"]["n"] + processes["ST_l"]["n"] + processes["DY"]["n"] + processes["QCD"]["n"])
        efficiency_err_mc = np.sqrt((processes["WJets"]["n_tagged_err"]**2 + processes["TTbar_l"]["n_tagged_err"]**2 + processes["ST_l"]["n_tagged_err"]**2 + processes["DY"]["n_tagged_err"]**2 + processes["QCD"]["n_tagged_err"]**2) / (processes["WJets"]["n"] + processes["TTbar_l"]["n"] + processes["ST_l"]["n"] + processes["DY"]["n"] + processes["QCD"]["n"])**2 +
        (processes["WJets"]["n_err"]**2 + processes["TTbar_l"]["n_err"]**2 + processes["ST_l"]["n_err"]**2 + processes["DY"]["n_err"]**2 + processes["QCD"]["n_err"]**2) * (processes["WJets"]["n_tagged"] + processes["TTbar_l"]["n_tagged"] + processes["ST_l"]["n_tagged"] + processes["DY"]["n_tagged"] + processes["QCD"]["n_tagged"])**2 / (processes["WJets"]["n"] + processes["TTbar_l"]["n"] + processes["ST_l"]["n"] + processes["DY"]["n"] + processes["QCD"]["n"])**4)
        print("  efficiency mc: " + str(efficiency_mc) + " +/- " + str(efficiency_err_mc))

        scale_factor = efficiency_data / efficiency_mc
        scale_factor_err = np.sqrt((efficiency_err_data / efficiency_mc)**2 + efficiency_err_mc**2 * efficiency_data**2 / efficiency_mc**4)
        print("   scale factor: " +  str(scale_factor) + " +/- " + str(scale_factor_err))
        if channel == "electron":
            el_SF = scale_factor
            el_SF_err = scale_factor_err
        else:
            mu_SF = scale_factor
            mu_SF_err = scale_factor_err

    SF = (el_SF + mu_SF) / 2.
    SF_err = np.sqrt(el_SF_err**2 + mu_SF_err**2)
    print("----------")
    print("scale factor (" + year + "): " + str(SF) + " +/- " + str(SF_err))

    output[year]["scale_factor"] = SF
    output[year]["error"] = SF_err

    histogram = ROOT.TH1F(year, year, 1, 0, 1)
    histogram.SetBinContent(1, SF)
    histogram.SetBinError(1, SF_err)
    histograms.append(histogram)


# output: root
output_root = ROOT.TFile(os.getcwd() + "/../../data/top_mistag_scale_factors.root", "RECREATE")
for histogram in histograms:
    histogram.Write()
output_root.Close()


# output: json
output_json_name = os.getcwd() + "/../../data/top_mistag_scale_factors.json"
output_json = json.dumps(output, indent=4)
print(output_json)
with open(output_json_name, "w") as json_file:
    json_file.write(output_json)
print("saved to: " + output_json_name)
