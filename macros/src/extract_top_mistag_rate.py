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
        "electron": {
            "scale_factor": 0.0,
            "error": 0.0
        },
        "muon": {
            "scale_factor": 0.0,
            "error": 0.0
        }
    }),
    ("UL16postVFP", {
        "electron": {
            "scale_factor": 0.0,
            "error": 0.0
        },
        "muon": {
            "scale_factor": 0.0,
            "error": 0.0
        }
    }),
    ("UL17", {
        "electron": {
            "scale_factor": 0.0,
            "error": 0.0
        },
        "muon": {
            "scale_factor": 0.0,
            "error": 0.0
        }
    }),
    ("UL18", {
        "electron": {
            "scale_factor": 0.0,
            "error": 0.0
        },
        "muon": {
            "scale_factor": 0.0,
            "error": 0.0
        }
    })
])






for year in years:
    # print(year)

    for channel in channels:
        # print(channel)

        for key, process in processes.items():
            process_name = process.get("process_name")
            sample_name = process.get("sample_name")
            hist_name = process.get("hist_name")
            # print(process_name)

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

        # efficiency in DATA
        efficiency_data = (processes["DATA"]["n_tagged"] - processes["TTbar_t"]["n_tagged"] - processes["ST_t"]["n_tagged"]) / (processes["DATA"]["n"] - processes["TTbar_t"]["n"] - processes["ST_t"]["n"])
        efficiency_err_data = np.sqrt((processes["DATA"]["n_tagged_err"]**2 + processes["TTbar_t"]["n_tagged_err"]**2 + processes["ST_t"]["n_tagged_err"]**2) / (processes["DATA"]["n"] - processes["TTbar_t"]["n"] - processes["ST_t"]["n"])**2  +
        ((processes["DATA"]["n_err"]**2 + processes["TTbar_t"]["n_err"]**2 + processes["ST_t"]["n_err"]**2)) * (processes["DATA"]["n_tagged"] - processes["TTbar_t"]["n_tagged"] - processes["ST_t"]["n_tagged"])**2 / (processes["DATA"]["n"] - processes["TTbar_t"]["n"] - processes["ST_t"]["n"])**4)
        # print("efficiency data: " + str(efficiency_data) + " +/- " + str(efficiency_err_data))

        # efficiency in MC
        efficiency_mc = (processes["WJets"]["n_tagged"] + processes["TTbar_l"]["n_tagged"] + processes["ST_l"]["n_tagged"] + processes["DY"]["n_tagged"] + processes["QCD"]["n_tagged"]) / (processes["WJets"]["n"] + processes["TTbar_l"]["n"] + processes["ST_l"]["n"] + processes["DY"]["n"] + processes["QCD"]["n"])
        efficiency_err_mc = np.sqrt((processes["WJets"]["n_tagged_err"]**2 + processes["TTbar_l"]["n_tagged_err"]**2 + processes["ST_l"]["n_tagged_err"]**2 + processes["DY"]["n_tagged_err"]**2 + processes["QCD"]["n_tagged_err"]**2) / (processes["WJets"]["n"] + processes["TTbar_l"]["n"] + processes["ST_l"]["n"] + processes["DY"]["n"] + processes["QCD"]["n"])**2 +
        (processes["WJets"]["n_err"]**2 + processes["TTbar_l"]["n_err"]**2 + processes["ST_l"]["n_err"]**2 + processes["DY"]["n_err"]**2 + processes["QCD"]["n_err"]**2) * (processes["WJets"]["n_tagged"] + processes["TTbar_l"]["n_tagged"] + processes["ST_l"]["n_tagged"] + processes["DY"]["n_tagged"] + processes["QCD"]["n_tagged"])**2 / (processes["WJets"]["n"] + processes["TTbar_l"]["n"] + processes["ST_l"]["n"] + processes["DY"]["n"] + processes["QCD"]["n"])**4)
        # print("  efficiency mc: " + str(efficiency_mc) + " +/- " + str(efficiency_err_mc))

        scale_factor = efficiency_data / efficiency_mc
        scale_factor_err = np.sqrt((efficiency_err_data / efficiency_mc)**2 + efficiency_err_mc**2 * efficiency_data**2 / efficiency_mc**4)
        # print("   scale factor: " +  str(scale_factor) + " +/- " + str(scale_factor_err))

        output[year][channel]["scale_factor"] = scale_factor
        output[year][channel]["error"] = scale_factor_err

output_json = json.dumps(output, indent=4)
print(output_json)

# setup output directory
output_file_name = os.getcwd() + "/../../data/top_mistag_scale_factors.json"
with open(output_file_name, "w") as json_file:
    json_file.write(output_json)

print("saved to: " + output_file_name)
