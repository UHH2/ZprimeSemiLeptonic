#!/usr/bin/env python2

import sys
sys.argv.append('-b') # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS
from constants_dnn_output_scores import _VARIABLES


years = [
    'UL16preVFP',
    'UL16postVFP',
    'UL17',
    'UL18',
    'Run2',
]
channels = [
    'electron',
    'muon',
]

systematics = [

]

for year in years:
    print('year: ' + year)

    for channel in channels:
        print('channel: ' + channel)

        for key, var in _VARIABLES.items():
            variable = var.get('name')

            # SM processes
            processes_Plotter = [
                Process(variable + '_TTbar_outputnodes', 't#bar{t}', root.kPink-3, 1, 0.2),
                Process(variable + '_WJets_outputnodes', 'W+jets', root.kSpring-3, 1, 0.5),
                Process(variable + '_DY_outputnodes', 'Drell-Yan', root.kOrange, 1, 0.5),
                Process(variable + '_ST_outputnodes', 'Single t', root.kBlue, 1, 0.3),
                Process(variable + '_Diboson_outputnodes', 'Diboson', root.kMagenta, 1, 0.5),
                Process(variable + '_QCD_outputnodes', 'QCD', root.kAzure+10, 1, 0.5),
            ]
            processes_Plotter_temp = OrderedDict()
            for index, p in enumerate(processes_Plotter):
                p.index = index
                processes_Plotter_temp[p.name] = p
                processes_Plotter = processes_Plotter_temp

            # # signal
            # signals_Plotter = [
            #     Process(variable + '_ALP_ttbar_signal', 'ALP signal', root.kBlack),
            #     Process(variable + '_ALP_ttbar_interference', 'ALP-SM interference', root.kGray+2),
            # ]
            # signals_Plotter_temp = OrderedDict()
            # for index, s in enumerate(signals_Plotter):
            #     s.index = index
            #     signals_Plotter_temp[s.name] = s
            #     signals_Plotter = signals_Plotter_temp


            nice = NiceStackWithRatio(
                infile_path = '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/systematics/' + year + '/' + channel + '/combine_input_after_dnn.root',
                # infile_directory = '', # the directory within the ROOT file
                x_axis_title = var.get('x_axis_title'),
                x_axis_unit = var.get('x_axis_unit'),
                prepostfit = 'prefitRaw',
                processes = processes_Plotter.values(),
                signals = [], # signals_Plotter.values(),
                syst_names = systematics,
                lumi_unc = _YEARS.get(year).get('lumi_unc'),
                divide_by_bin_width = False,
                data_name = variable + '_DATA_outputnodes',
                text_prelim = 'Private Work',
                text_top_left = channel + ' channel (' + year + ')',
                text_top_right = _YEARS.get(year).get('lumi_fb_display') + ' fb^{#minus1} (13 TeV)',
                nostack = False,
                logy = True,
                blind_data = True,
            )

            nice.plot()
            nice.canvas.cd()

            # legend
            leg_offset_x = 0.30
            leg_offset_y = 0.23
            legend = root.TLegend(nice.coord.graph_to_pad_x(0.45+leg_offset_x), nice.coord.graph_to_pad_y(0.45+leg_offset_y), nice.coord.graph_to_pad_x(0.7+leg_offset_x), nice.coord.graph_to_pad_y(0.73+leg_offset_y))
            if not nice.blind_data: legend.AddEntry(nice.data_hist, 'Data', 'ep')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_TTbar_outputnodes'].index), processes_Plotter[variable + '_TTbar_outputnodes'].legend, 'f')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_WJets_outputnodes'].index), processes_Plotter[variable + '_WJets_outputnodes'].legend, 'f')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_DY_outputnodes'].index), processes_Plotter[variable + '_DY_outputnodes'].legend, 'f')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_ST_outputnodes'].index), processes_Plotter[variable + '_ST_outputnodes'].legend, 'f')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_Diboson_outputnodes'].index), processes_Plotter[variable + '_Diboson_outputnodes'].legend, 'f')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_QCD_outputnodes'].index), processes_Plotter[variable + '_QCD_outputnodes'].legend, 'f')
            legend.SetTextSize(0.025)
            legend.SetBorderSize(0)
            legend.SetFillStyle(0)
            legend.Draw()

            nice.save_plot('03_dnn/' + year + '/' + channel + '/' + variable + '.pdf')
            nice.canvas.Close()
