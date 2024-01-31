#!/usr/bin/env python2

import sys
sys.argv.append('-b') # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS
from constants_TOP20001 import _SAMPLES, _VARIABLES

year = 'Run2'
LUMI = _YEARS.get(year).get('lumi_pb')

# recreate file with histograms in expected format
outputfile = root.TFile('TOP-20-001/partonlevelhists.root', 'RECREATE')
outputfile.Close()
for key, sample in _SAMPLES.items():
    samplename = sample.get('name')
    filename = sample.get('file_name')
    inputfile = root.TFile(filename, 'READ')

    xsec = sample.get('xsec')
    br = sample.get('br')
    nevt = sample.get('nevt')

    for key, var in _VARIABLES.items():
        histname = var.get('name')

        hist = inputfile.Get('ttgenhists/' + histname)
        hist.SetName(histname + '_' + samplename)
        hist.Scale(LUMI)
        hist.Scale(xsec * br / nevt)
        outputfile = root.TFile('TOP-20-001/partonlevelhists.root', 'UPDATE')
        hist.Write()
        outputfile.Close()
    inputfile.Close()


for key, var in _VARIABLES.items():
    histname = var.get('name')
    print(histname)

    outputfile = root.TFile('TOP-20-001/partonlevelhists.root', 'UPDATE')
    hist_ttbar = outputfile.Get(histname + '_TTToSemiLeptonic')
    hist_signal = outputfile.Get(histname + '_ALP_ttbar_signal')
    hist_interference = outputfile.Get(histname + '_ALP_ttbar_interference')

    for poi in [1, 2, 3]:
        for scenario in ['posint', 'negint']:
            hist = hist_ttbar.Clone()
            hist.Add(hist_signal, poi**2)
            if scenario == 'posint':
                hist.Add(hist_interference, poi)
            else:
                hist.Add(hist_interference, -poi)
            hist.SetName(histname + '_SIB_sqrtmu' + str(poi) + '_' + scenario)
            hist.Write()
    outputfile.Close()



for key, var in _VARIABLES.items():

    processes_Plotter = [
        Process(var.get('name') + '_TTToSemiLeptonic', 't#bar{t}', root.kPink-3, 1.),
    ]
    processes_Plotter_temp = OrderedDict()
    for index, p in enumerate(processes_Plotter):
        p.index = index
        processes_Plotter_temp[p.name] = p
        processes_Plotter = processes_Plotter_temp

    signals_Plotter = [
        Process(var.get('name') + '_ALP_ttbar_signal', 'ALP signal (#sqrt{#mu} = #pm1)', root.kBlack, 1.),
        Process(var.get('name') + '_ALP_ttbar_interference', 'pos. ALP-SM interference (#sqrt{#mu} = #minus1)', root.kGray, 1.),
        Process(var.get('name') + '_SIB_sqrtmu3_negint', 't#bar{t} + ALP incl. neg. int. (#sqrt{#mu} = #plus3)', root.kBlue, 1.),
        Process(var.get('name') + '_SIB_sqrtmu3_posint', 't#bar{t} + ALP incl. pos. int. (#sqrt{#mu} = #minus3)', root.kGreen, 1.),
    ]
    signals_Plotter_temp = OrderedDict()
    for index, s in enumerate(signals_Plotter):
        s.index = index
        signals_Plotter_temp[s.name] = s
        signals_Plotter = signals_Plotter_temp



    nice = NiceStackWithRatio(
        infile_path = '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/plotter/TOP-20-001/partonlevelhists.root',
        # infile_directory = '', # the directory within the ROOT file
        x_axis_title = var.get('x_axis_title'),
        x_axis_unit = var.get('x_axis_unit'),
        y_axis_min = 1E+04,
        y_axis_max = 1E+09,
        prepostfit = 'prefitRaw',
        processes = processes_Plotter.values(),
        signals = signals_Plotter.values(),
        syst_names = [],
        # lumi_unc = _YEARS.get(year).get('lumi_unc'),
        divide_by_bin_width = False,
        # data_name = var.get('name') + '_DATA',
        text_prelim = 'Private Work',
        text_top_left = 'parton level, e/#mu+jets',
        text_top_right = _YEARS.get(year).get('lumi_fb_display') + ' fb^{#minus1} (13 TeV)',
        nostack = False,
        logy = True,
        blind_data = True,
        show_ratio = True,
        ratio_label = 'ratio' # 't#bar{t}+ALP / t#bar{t}'
        # debug = True,
    )

    # nice.ratio_null_hist.GetYaxis().SetTitle('SM+ALP / SM')
    nice.plot()
    nice.canvas.cd()

    # legend
    leg_offset_x = 0.10
    leg_offset_y = 0.20
    legend = root.TLegend(nice.coord.graph_to_pad_x(0.35+leg_offset_x), nice.coord.graph_to_pad_y(0.5+leg_offset_y), nice.coord.graph_to_pad_x(0.7+leg_offset_x), nice.coord.graph_to_pad_y(0.7+leg_offset_y))
    if not nice.blind_data: legend.AddEntry(nice.data_hist, 'Data', 'ep')
    legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[var.get('name') + '_TTToSemiLeptonic'].index), processes_Plotter[var.get('name') + '_TTToSemiLeptonic'].legend, 'f')
    legend.AddEntry(nice.signal_hists[signals_Plotter[var.get('name') + '_ALP_ttbar_signal'].index], signals_Plotter[var.get('name') + '_ALP_ttbar_signal'].legend, 'l')
    legend.AddEntry(nice.signal_hists[signals_Plotter[var.get('name') + '_ALP_ttbar_interference'].index], signals_Plotter[var.get('name') + '_ALP_ttbar_interference'].legend, 'l')
    legend.AddEntry(nice.signal_hists[signals_Plotter[var.get('name') + '_SIB_sqrtmu3_negint'].index], signals_Plotter[var.get('name') + '_SIB_sqrtmu3_negint'].legend, 'l')
    legend.AddEntry(nice.signal_hists[signals_Plotter[var.get('name') + '_SIB_sqrtmu3_posint'].index], signals_Plotter[var.get('name') + '_SIB_sqrtmu3_posint'].legend, 'l')
    legend.SetTextSize(0.025)
    legend.SetBorderSize(0)
    legend.SetFillStyle(0)
    legend.Draw()

    nice.save_plot('TOP-20-001/' + var.get('name') + '.pdf')
    nice.canvas.Close()
