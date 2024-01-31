#!/usr/bin/env python2

import sys
sys.argv.append("-b") # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS
from constants_costhetastar import _VARIABLES


years = [
    # 'UL16preVFP',
    # 'UL16postVFP',
    # 'UL17',
    # 'UL18',
    'Run2'
]

for year in years:
    print("year: " + year)

    systematics = [
    # 'pdf',
    # 'mcscale',
    # 'pu',
    # 'prefiring',
    # 'mu_id',
    # 'mu_iso',
    # 'mu_reco',
    # 'mu_trigger',
    # 'ele_id',
    # 'ele_reco',
    # 'ele_trigger',
    # 'btag_cferr1',
    # 'btag_cferr2',
    # 'btag_hf',
    # 'btag_hfstats1_' + year,
    # 'btag_hfstats2_' + year,
    # 'btag_lf',
    # 'btag_lfstats1_' + year,
    # 'btag_lfstats2_' + year,
    # 'ttag_corr',
    # 'ttag_uncorr_' + year,
    # 'tmistag',
    # 'jec',
    # 'jer',
    # 'isr',
    # 'fsr',
    ]

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
            Process(var.get("name") + "_ALP_ttbar_signal", "ALP signal #times 10", root.kBlack, 10),
            Process(var.get("name") + "_ALP_ttbar_interference", "pos. ALP interference #times 10", root.kGray, -10),
        ]
        signals_Plotter_temp = OrderedDict()
        for index, s in enumerate(signals_Plotter):
            s.index = index
            signals_Plotter_temp[s.name] = s
            signals_Plotter = signals_Plotter_temp


        nice = NiceStackWithRatio(
            infile_path = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/systematics/" + year + "/combine_input_after_baseline_selection.root",
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
            text_top_left = year,
            text_top_right = _YEARS.get(year).get("lumi_fb_display") + " fb^{#minus1} (13 TeV)",
            y_axis_min = 0,
            y_axis_max = 150000,
            nostack = False,
            logy = False,
            blind_data = True,
            show_ratio = False,
            debug = False,
        )

        nice.plot()
        nice.canvas.cd()

        # nice.

        # nice.ratio_null_hist.SetMinimum(0.0)
        # nice.ratio_null_hist.SetMaximum(2.0)
        # nice.ratio_null_hist.GetYaxis().SetNdivisions(-402)

        # legend
        leg_offset_x = 0.0
        leg_offset_y = 0.23
        legend = root.TLegend(nice.coord.graph_to_pad_x(0.45+leg_offset_x), nice.coord.graph_to_pad_y(0.45+leg_offset_y), nice.coord.graph_to_pad_x(0.70+leg_offset_x), nice.coord.graph_to_pad_y(0.73+leg_offset_y))
        if not nice.blind_data: legend.AddEntry(nice.data_hist, "Data", "ep")
        legend.SetNColumns(1)
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_TTbar"].index), processes_Plotter[var.get("name") + "_TTbar"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_WJets"].index), processes_Plotter[var.get("name") + "_WJets"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_DY"].index), processes_Plotter[var.get("name") + "_DY"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_ST"].index), processes_Plotter[var.get("name") + "_ST"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_QCD"].index), processes_Plotter[var.get("name") + "_QCD"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_Diboson"].index), processes_Plotter[var.get("name") + "_Diboson"].legend, "f")
        legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_ALP_ttbar_signal"].index], signals_Plotter[var.get("name") + "_ALP_ttbar_signal"].legend, "l")
        legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_ALP_ttbar_interference"].index], signals_Plotter[var.get("name") + "_ALP_ttbar_interference"].legend, "l")
        # legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_HpseudoToTTTo1L1Nu2J_m500_w125p0_res"].index], signals_Plotter[var.get("name") + "_HpseudoToTTTo1L1Nu2J_m500_w125p0_res"].legend, "l")
        # legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_HscalarToTTTo1L1Nu2J_m500_w125p0_res"].index], signals_Plotter[var.get("name") + "_HscalarToTTTo1L1Nu2J_m500_w125p0_res"].legend, "l")
        # legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_RSGluonToTT_M-1000"].index], signals_Plotter[var.get("name") + "_RSGluonToTT_M-1000"].legend, "l")
        # legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_ZPrimeToTT_M1000_W100"].index], signals_Plotter[var.get("name") + "_ZPrimeToTT_M1000_W100"].legend, "l")

        legend.SetTextSize(0.025)
        legend.SetBorderSize(0)
        legend.SetFillStyle(0)
        legend.Draw()

        nice.save_plot("02_baseline_selection/" + year + "/" + var.get("name") + ".pdf")
        nice.canvas.Close()
