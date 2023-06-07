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
            Process(var.get("name") + "_TTbar_SR", "t#bar{t}", root.kPink-3, 1, 0.2),
            Process(var.get("name") + "_WJets_SR", "W+jets", root.kSpring-3, 1, 0.5),
            Process(var.get("name") + "_ST_SR", "Single t", root.kBlue, 1, 0.5),
            Process(var.get("name") + "_DY_SR", "Drell-Yan", root.kOrange, 1, 0.3),
            Process(var.get("name") + "_Diboson_SR", "Diboson", root.kMagenta, 1, 0.5),
            Process(var.get("name") + "_QCD_SR", "QCD", root.kAzure+10, 1, 0.5),
        ]
        processes_Plotter_temp = OrderedDict()
        for index, p in enumerate(processes_Plotter):
            p.index = index
            processes_Plotter_temp[p.name] = p
            processes_Plotter = processes_Plotter_temp

        # signal
        signals_Plotter = [
            Process(var.get("name") + "_ALP_sqrtmu_plus5_SR", "SM + ALP incl. neg. int. (#sqrt{#mu} = +5)", root.kBlack, 1),
            Process(var.get("name") + "_ALP_sqrtmu_minus5_SR", "SM + ALP incl. pos. int. (#sqrt{#mu} = -5)", root.kGray+2, 1),
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
            show_cms_logo = False,
            text_prelim = '#splitline{Private Work}{(CMS Simulation)}',
            text_top_left = "SR: " + channel + " channel (" + year + ")",
            text_top_right = _YEARS.get(year).get("lumi_fb_display") + " fb^{#minus1} (13 TeV)",
            nostack = False,
            logy = True,
            blind_data = True,
            show_ratio = True
        )

        nice.plot()
        nice.canvas.cd()

        nice.ratio_null_hist.SetMinimum(0.0)
        nice.ratio_null_hist.SetMaximum(2.0)
        # nice.ratio_null_hist.GetYaxis().SetNdivisions(-402)

        # legend
        leg_offset_x = 0.05
        leg_offset_y = 0.23
        legend = root.TLegend(nice.coord.graph_to_pad_x(0.45+leg_offset_x), nice.coord.graph_to_pad_y(0.45+leg_offset_y), nice.coord.graph_to_pad_x(0.70+leg_offset_x), nice.coord.graph_to_pad_y(0.73+leg_offset_y))
        if not nice.blind_data: legend.AddEntry(nice.data_hist, "Data", "ep")
        legend.SetNColumns(1);
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_TTbar_SR"].index), processes_Plotter[var.get("name") + "_TTbar_SR"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_WJets_SR"].index), processes_Plotter[var.get("name") + "_WJets_SR"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_DY_SR"].index), processes_Plotter[var.get("name") + "_DY_SR"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_ST_SR"].index), processes_Plotter[var.get("name") + "_ST_SR"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_QCD_SR"].index), processes_Plotter[var.get("name") + "_QCD_SR"].legend, "f")
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get("name") + "_Diboson_SR"].index), processes_Plotter[var.get("name") + "_Diboson_SR"].legend, "f")
        legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_ALP_sqrtmu_plus5_SR"].index], signals_Plotter[var.get("name") + "_ALP_sqrtmu_plus5_SR"].legend, "l")
        legend.AddEntry(nice.signal_hists[signals_Plotter[var.get("name") + "_ALP_sqrtmu_minus5_SR"].index], signals_Plotter[var.get("name") + "_ALP_sqrtmu_minus5_SR"].legend, "l")

        legend.SetTextSize(0.025)
        legend.SetBorderSize(0)
        legend.SetFillStyle(0)
        legend.Draw()

        nice.save_plot("03_dnn/" + year + "/" + channel + "/" + var.get("name") + "_ALP.pdf")
        nice.canvas.Close()
