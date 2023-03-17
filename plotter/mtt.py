#!/usr/bin/env python2

import sys
sys.argv.append("-b") # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS
from constants_mtt import _VARIABLES


year = "UL17"
channels = [
    "electron",
    "muon"
]

systematics = [
    # "pdf",
    # "mcscale",
    # "pu",
    # "prefiring",
    # "mu_id",
    # "mu_iso",
    # "mu_reco",
    # "mu_trigger",
    # "ele_id",
    # "ele_reco",
    # "ele_trigger",
    # "isr",
    # "fsr",
    # "btag_cferr1",
    # "btag_cferr2",
    # "btag_hf",
    # "btag_hfstats1",
    # "btag_hfstats2",
    # "btag_lf",
    # "btag_lfstats1",
    # "btag_lfstats2",
]

print "year: " + year
for channel in channels:
    print "channel: " + channel
    for key, var in _VARIABLES.items():

        # SM processes
        processes_Plotter = [
            Process(var.get("name") + "_TTbar", "t#bar{t}", root.kPink-3),
            Process(var.get("name") + "_WJets", "W+jets", root.kSpring-3),
            Process(var.get("name") + "_DY", "Drell-Yan", root.kOrange),
            Process(var.get("name") + "_ST", "Single t", root.kBlue),
            Process(var.get("name") + "_QCD", "QCD", root.kAzure+10),
            Process(var.get("name") + "_Diboson", "Diboson", root.kMagenta),
        ]
        processes_Plotter_temp = OrderedDict()
        for index, p in enumerate(processes_Plotter):
            p.index = index
            processes_Plotter_temp[p.name] = p
            processes_Plotter = processes_Plotter_temp

        # signal
        signals_Plotter = [
            # Process(var.get("name") + "_ALP_ttbar_signal", "ALP signal #times 100", root.kBlack, 100),
            # Process(var.get("name") + "_HpseudoToTTTo1L1Nu2J_m500_w125p0_res", "A res 500 GeV #times 1000", root.kOrange, 1000),
            Process(var.get("name") + "_HscalarToTTTo1L1Nu2J_m500_w125p0_res", "H res 500 GeV #times 2000", root.kBlue, 2000),
            # Process(var.get("name") + "_RSGluonToTT_M-1000", "g_{KK} 1 TeV (1 nb)", root.kRed, 1000),
            Process(var.get("name") + "_ZPrimeToTT_M1000_W100", "Z' 1 TeV (1 nb)", root.kGreen, 1000),
        ]
        signals_Plotter_temp = OrderedDict()
        for index, s in enumerate(signals_Plotter):
            s.index = index
            signals_Plotter_temp[s.name] = s
            signals_Plotter = signals_Plotter_temp


        nice = NiceStackWithRatio(
            infile_path = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/systematics/" + year + "/" + channel + "/combine_input_after_dnn.root",
            # infile_directory = "", # the directory within the ROOT file
            x_axis_title = var.get("x_axis_title"),
            x_axis_unit = var.get("x_axis_unit"),
            prepostfit = "prefitRaw",
            processes = processes_Plotter.values(),
            signals = signals_Plotter.values(),
            syst_names = systematics,
            lumi_unc = _YEARS.get(year).get("lumi_unc"),
            divide_by_bin_width = False,
            data_name = var.get("name") + "_DATA",
            text_prelim = "Private Work",
            text_top_left = channel + " channel (" + year + ")",
            text_top_right = _YEARS.get(year).get("lumi_fb_display") + " fb^{#minus1} (13 TeV)",
            nostack = False,
            logy = True,
            blind_data = True,
            debug = False,
        )

        nice.plot()
        nice.canvas.cd()

        nice.ratio_null_hist.SetMinimum(0.0)
        nice.ratio_null_hist.SetMaximum(2.0)
        # nice.ratio_null_hist.GetYaxis().SetNdivisions(-402)

        # legend
        leg_offset_x = 0.10
        leg_offset_y = 0.23
        legend = root.TLegend(nice.coord.graph_to_pad_x(0.45+leg_offset_x), nice.coord.graph_to_pad_y(0.45+leg_offset_y), nice.coord.graph_to_pad_x(0.70+leg_offset_x), nice.coord.graph_to_pad_y(0.73+leg_offset_y))
        if not nice.blind_data: legend.AddEntry(nice.data_hist, "Data", "ep")
        legend.SetNColumns(1);
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_TTbar"].index), processes_Plotter[var.get("name") + "_TTbar"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_WJets"].index), processes_Plotter[var.get("name") + "_WJets"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_DY"].index), processes_Plotter[var.get("name") + "_DY"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_ST"].index), processes_Plotter[var.get("name") + "_ST"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_QCD"].index), processes_Plotter[var.get("name") + "_QCD"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_Diboson"].index), processes_Plotter[var.get("name") + "_Diboson"].legend, "f")
        # legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_ALP_ttbar_signal"].index], signals_Plotter[var.get("name") + "_ALP_ttbar_signal"].legend, "l")
        # legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_HpseudoToTTTo1L1Nu2J_m500_w125p0_res"].index], signals_Plotter[var.get("name") + "_HpseudoToTTTo1L1Nu2J_m500_w125p0_res"].legend, "l")
        legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_HscalarToTTTo1L1Nu2J_m500_w125p0_res"].index], signals_Plotter[var.get("name") + "_HscalarToTTTo1L1Nu2J_m500_w125p0_res"].legend, "l")
        # legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_RSGluonToTT_M-1000"].index], signals_Plotter[var.get("name") + "_RSGluonToTT_M-1000"].legend, "l")
        legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_ZPrimeToTT_M1000_W100"].index], signals_Plotter[var.get("name") + "_ZPrimeToTT_M1000_W100"].legend, "l")

        legend.SetTextSize(0.025)
        legend.SetBorderSize(0)
        legend.SetFillStyle(0)
        legend.Draw()

        nice.save_plot("03_dnn/" + year + "/" + channel + "/" + var.get("name") + ".pdf")
        nice.canvas.Close()
