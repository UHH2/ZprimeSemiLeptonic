#!/usr/bin/env python2

import sys
sys.argv.append('-b') # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS

# year
year = 'Run2'

# SM processes
processes_Plotter = [
    Process('mtt_TTToSemiLeptonic', 't#bar{t} (POWHEG P8 CP5)', root.kPink-3),
]
processes_Plotter_temp = OrderedDict()
for index, p in enumerate(processes_Plotter):
    p.index = index
    processes_Plotter_temp[p.name] = p
    processes_Plotter = processes_Plotter_temp

# signal
signals_Plotter = [
    Process('mtt_SIB_sqrtmu_plus2', 't#bar{t} + ALP incl. neg. int. (#sqrt{#mu} = +2)', root.kBlue),
    Process('mtt_SIB_sqrtmu_minus2', 't#bar{t} + ALP incl. pos. int. (#sqrt{#mu} = -2)', root.kGreen),
]
signals_Plotter_temp = OrderedDict()
for index, s in enumerate(signals_Plotter):
    s.index = index
    signals_Plotter_temp[s.name] = s
    signals_Plotter = signals_Plotter_temp

# systematics
systematics = [
    'datasyst',
    'mcscale',
    # 'pdf',
    # 'pu',
    # 'isr',
    # 'fsr'
]

nice = NiceStackWithRatio(
    infile_path = '/nfs/dust/cms/user/jabuschh/combine/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/TOP-20-001/mtt/inputHistograms_fullRun2_fa3500.root',
    # infile_directory = '', # the directory within the ROOT file
    x_axis_title = 'm(t#bar{t})',
    x_axis_unit = 'GeV',
    prepostfit = 'prefitRaw',
    processes = processes_Plotter.values(),
    signals = signals_Plotter.values(),
    syst_names = systematics,
    lumi_unc = _YEARS.get(year).get('lumi_unc'),
    divide_by_bin_width = False,
    data_name = 'mtt_data_obs',
    text_prelim = 'Private Work',
    text_top_left = 'parton level, e/#mu + jets (' + year + ')',
    text_top_right = _YEARS.get(year).get('lumi_fb_display') + ' fb^{#minus1} (13 TeV)',
    nostack = False,
    logy = True,
    blind_data = False,
)

nice.plot()
nice.canvas.cd()

# legend
leg_offset_x = 0.05
leg_offset_y = 0.23
legend = root.TLegend(nice.coord.graph_to_pad_x(0.45+leg_offset_x), nice.coord.graph_to_pad_y(0.45+leg_offset_y), nice.coord.graph_to_pad_x(0.7+leg_offset_x), nice.coord.graph_to_pad_y(0.73+leg_offset_y))
if not nice.blind_data: legend.AddEntry(nice.data_hist, 'Data (PRD 104, 092013)', 'ep')
legend.AddEntry(nice.stack.GetStack().At(processes_Plotter['mtt_TTToSemiLeptonic'].index), processes_Plotter['mtt_TTToSemiLeptonic'].legend, 'f')
legend.AddEntry(nice.signal_hists[signals_Plotter['mtt_SIB_sqrtmu_plus2'].index], signals_Plotter['mtt_SIB_sqrtmu_plus2'].legend, 'l')
legend.AddEntry(nice.signal_hists[signals_Plotter['mtt_SIB_sqrtmu_minus2'].index], signals_Plotter['mtt_SIB_sqrtmu_minus2'].legend, 'l')
legend.SetTextSize(0.025)
legend.SetBorderSize(0)
legend.SetFillStyle(0)
legend.Draw()

nice.save_plot('TOP-20-001/TOP-20-001_mtt.pdf')
