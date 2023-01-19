#!/usr/bin/env python2

import sys
sys.argv.append('-b') # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS

# year
year = 'UL17'

# todo: regions

# SM processes
processes_Plotter = [
    Process('SRbin1_TopTag_others', 'DY + Diboson + QCD', root.kAzure+10),
    Process('SRbin1_TopTag_WJets', 'W+jets', root.kSpring-3),
    Process('SRbin1_TopTag_ST', 'Single t', root.kOrange),
    Process('SRbin1_TopTag_TTbar', 't#bar{t}', root.kPink-3),
]
processes_Plotter_temp = OrderedDict()
for index, p in enumerate(processes_Plotter):
    p.index = index
    processes_Plotter_temp[p.name] = p
    processes_Plotter = processes_Plotter_temp

# todo: add signal
signals_Plotter = [
    Process('SRbin1_TopTag_ALP_ttbar_signal', 'ALP signal', root.kBlack),
    Process('SRbin1_TopTag_ALP_ttbar_interference', 'ALP-SM interference', root.kGray+2),
]
signals_Plotter_temp = OrderedDict()
for index, s in enumerate(signals_Plotter):
    s.index = index
    signals_Plotter_temp[s.name] = s
    signals_Plotter = signals_Plotter_temp

# systematics
systematics = [
    'pdf',
    'mcscale',
    'pu',
    'prefiring',
    'mu_id',
    'mu_iso',
    'mu_reco',
    'mu_trigger',
    'btag_cferr1',
    'btag_cferr2',
    'btag_hf',
    'btag_hfstats1_UL17',
    'btag_hfstats2_UL17',
    'btag_lf',
    'btag_lfstats1_UL17',
    'btag_lfstats2_UL17',
]

nice = NiceStackWithRatio(
    infile_path = '/nfs/dust/cms/user/jabuschh/combine/CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit/B2G-22-006/inputHistograms_UL17_muon_fa6100.root',
    # infile_directory = '', # the directory within the ROOT file
    x_axis_title = 'm(t#bar{t})',
    x_axis_unit = 'GeV',
    prepostfit = 'prefitRaw',
    processes = processes_Plotter.values(),
    signals = signals_Plotter.values(),
    syst_names = systematics,
    lumi_unc = _YEARS.get(year).get('lumi_unc'),
    divide_by_bin_width = False,
    data_name = 'SRbin1_TopTag_data_obs',
    text_prelim = 'Private Work',
    text_top_left = 'SR bin 1 + top tag (' + year + ')',
    text_top_right = _YEARS.get(year).get('lumi_fb_display') + ' fb^{#minus1} (13 TeV)',
    nostack = False,
    logy = True,
    blind_data = True,
)

nice.plot()
nice.canvas.cd()

# legend
leg_offset_x = 0.19
leg_offset_y = 0.23
legend = root.TLegend(nice.coord.graph_to_pad_x(0.45+leg_offset_x), nice.coord.graph_to_pad_y(0.45+leg_offset_y), nice.coord.graph_to_pad_x(0.7+leg_offset_x), nice.coord.graph_to_pad_y(0.73+leg_offset_y))
if not nice.blind_data: legend.AddEntry(nice.data_hist, 'Data', 'ep')
legend.AddEntry(nice.stack.GetStack().At(processes_Plotter['SRbin1_TopTag_TTbar'].index), processes_Plotter['SRbin1_TopTag_TTbar'].legend, 'f')
legend.AddEntry(nice.stack.GetStack().At(processes_Plotter['SRbin1_TopTag_ST'].index), processes_Plotter['SRbin1_TopTag_ST'].legend, 'f')
legend.AddEntry(nice.stack.GetStack().At(processes_Plotter['SRbin1_TopTag_WJets'].index), processes_Plotter['SRbin1_TopTag_WJets'].legend, 'f')
legend.AddEntry(nice.stack.GetStack().At(processes_Plotter['SRbin1_TopTag_others'].index), processes_Plotter['SRbin1_TopTag_others'].legend, 'f')
legend.AddEntry(nice.signal_hists[signals_Plotter['SRbin1_TopTag_ALP_ttbar_signal'].index], signals_Plotter['SRbin1_TopTag_ALP_ttbar_signal'].legend, 'l')
legend.AddEntry(nice.signal_hists[signals_Plotter['SRbin1_TopTag_ALP_ttbar_interference'].index], signals_Plotter['SRbin1_TopTag_ALP_ttbar_interference'].legend, 'l')
legend.SetTextSize(0.025)
legend.SetBorderSize(0)
legend.SetFillStyle(0)
legend.Draw()


nice.save_plot('firstTest.pdf')
