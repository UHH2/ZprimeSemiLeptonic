#!/usr/bin/env python2

import sys
sys.argv.append('-b') # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS
from constants_dnn_output_scores import _VARIABLES


year = 'UL17'
channels = [
    'electron',
    'muon'
]

systematics = [

]

print('year: ' + year)
for channel in channels:
    print('channel: ' + channel)
    for key, var in _VARIABLES.items():

        # SM processes
        processes_Plotter = [
            Process(var.get('name') + '_QCD', 'QCD', root.kAzure+10, 1, 0.5),
            Process(var.get('name') + '_Diboson', 'Diboson', root.kMagenta, 1, 0.5),
            Process(var.get('name') + '_ST', 'Single t', root.kBlue, 1, 0.3),
            Process(var.get('name') + '_DY', 'Drell-Yan', root.kOrange, 1, 0.5),
            Process(var.get('name') + '_WJets', 'W+jets', root.kSpring-3, 1, 0.5),
            Process(var.get('name') + '_TTbar', 't#bar{t}', root.kPink-3, 1, 0.2),
        ]
        processes_Plotter_temp = OrderedDict()
        for index, p in enumerate(processes_Plotter):
            p.index = index
            processes_Plotter_temp[p.name] = p
            processes_Plotter = processes_Plotter_temp

        # signal
        signals_Plotter = [
            Process(var.get('name') + '_ALP_ttbar_signal', 'ALP signal', root.kBlack),
            Process(var.get('name') + '_ALP_ttbar_interference', 'ALP-SM interference', root.kGray+2),
        ]
        signals_Plotter_temp = OrderedDict()
        for index, s in enumerate(signals_Plotter):
            s.index = index
            signals_Plotter_temp[s.name] = s
            signals_Plotter = signals_Plotter_temp


        nice = NiceStackWithRatio(
            infile_path = '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/systematics/' + year + '/' + channel + '/combine_input_after_dnn.root',
            # infile_directory = '', # the directory within the ROOT file
            x_axis_title = var.get('x_axis_title'),
            x_axis_unit = var.get('x_axis_unit'),
            prepostfit = 'prefitRaw',
            processes = processes_Plotter.values(),
            signals = [],
            syst_names = systematics,
            lumi_unc = _YEARS.get(year).get('lumi_unc'),
            divide_by_bin_width = False,
            data_name = var.get('name') + '_DATA',
            text_prelim = 'Private Work',
            text_top_left = channel + ' channel (' + year + ')',
            text_top_right = _YEARS.get(year).get('lumi_fb_display') + ' fb^{#minus1} (13 TeV)',
            nostack = False,
            logy = True,
            blind_data = False,
        )

        nice.plot()
        nice.canvas.cd()

        # legend
        leg_offset_x = 0.30
        leg_offset_y = 0.23
        legend = root.TLegend(nice.coord.graph_to_pad_x(0.45+leg_offset_x), nice.coord.graph_to_pad_y(0.45+leg_offset_y), nice.coord.graph_to_pad_x(0.7+leg_offset_x), nice.coord.graph_to_pad_y(0.73+leg_offset_y))
        if not nice.blind_data: legend.AddEntry(nice.data_hist, 'Data', 'ep')
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get('name') + '_TTbar'].index), processes_Plotter[var.get('name') + '_TTbar'].legend, 'f')
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get('name') + '_WJets'].index), processes_Plotter[var.get('name') + '_WJets'].legend, 'f')
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get('name') + '_DY'].index), processes_Plotter[var.get('name') + '_DY'].legend, 'f')
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get('name') + '_ST'].index), processes_Plotter[var.get('name') + '_ST'].legend, 'f')
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get('name') + '_Diboson'].index), processes_Plotter[var.get('name') + '_Diboson'].legend, 'f')
        legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get('name') + '_QCD'].index), processes_Plotter[var.get('name') + '_QCD'].legend, 'f')
        legend.SetTextSize(0.025)
        legend.SetBorderSize(0)
        legend.SetFillStyle(0)
        legend.Draw()

        nice.save_plot('03_dnn/' + year + '/' + channel + '/' + var.get('name') + '.pdf')
        nice.canvas.Close()
