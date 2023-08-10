#!/usr/bin/env python2

import ROOT as root
# from sigfig import round

years = [
    "UL16preVFP",
    "UL16postVFP",
    "UL17",
    "UL18"
]

channels = [
    "electron",
    # "muon"
]

samples = [
    "TTbar",
    "WJets",
    "ST",
    "QCD",
    "DY",
    "Diboson",
]

regions = [
    "DNN_output0_TopTag_thetastar_bin1_General",
    "DNN_output0_NoTopTag_thetastar_bin1_General",
    "DNN_output0_TopTag_thetastar_bin2_General",
    "DNN_output0_NoTopTag_thetastar_bin2_General",
    "DNN_output0_TopTag_thetastar_bin3_General",
    "DNN_output0_NoTopTag_thetastar_bin3_General",
    "DNN_output0_TopTag_thetastar_bin4_General",
    "DNN_output0_NoTopTag_thetastar_bin4_General",
    "DNN_output0_thetastar_bin5_General",
    "DNN_output0_thetastar_bin6_General",
    "DNN_output1_General",
    "DNN_output2_General",
]

for year in years:
    print(year)

    for channel in channels:
        print(channel + "\n")
        print("""& SRbin1\_1T & SRbin1\_0T & SRbin2\_1T & SRbin2\_0T & SRbin3\_1T & SRbin3\_0T & SRbin4\_1T & SRbin4\_0T & SRbin5 & SRbin6 & CR1 & CR2 \\\\ \hline""")

        for sample in samples:
            # print(sample)

            file_name = "/nfs/dust/cms/group/zprime-uhh/AnalysisDNN_" + year + "/" + channel + "/" + "uhh2.AnalysisModuleRunner.MC." + sample + ".root"
            file = root.TFile(file_name, "READ")

            string = sample
            for region in regions:
                # print(region)
                hist = file.Get(region + "/sum_event_weights")
                events = hist.GetBinContent(1)
                events = format(events, '.6g')
                string += " & "
                string += events
            string += " \\\\"


            print(string) # for latex tables
        print("\n")
