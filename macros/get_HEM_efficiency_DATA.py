#!/usr/bin/env python2

import ROOT as root

year = 'UL18'

channels = [
    # 'electron',
    'muon'
]

sample = 'DATA'


for channel in channels:
    print('channel: ' + channel)
    file_name = 'uhh2.AnalysisModuleRunner.DATA.' + sample + '.root'

    file_dir_noHEM = '/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/02_baseline/' + year + '_noHEMselection/' + channel + '/'
    root_file_noHEM = root.TFile(file_dir_noHEM + file_name, 'READ')
    hist_noHEM = root_file_noHEM.Get('NNInputsBeforeReweight_General/sum_event_weights')
    events_noHEM = hist_noHEM.GetBinContent(1)
    # print(events_noHEM)

    file_dir = '/nfs/dust/cms/group/zprime-uhh/Analysis_' + year + '/' + channel + '/'
    root_file = root.TFile(file_dir + file_name, 'READ')
    hist = root_file.Get('NNInputsBeforeReweight_General/sum_event_weights')
    events = hist.GetBinContent(1)
    # print(events)

    efficiency = events / events_noHEM
    percentage = (1 - efficiency) * 100
    print(str(sample) + ': {:.1f}%'.format(percentage))

    root_file_noHEM.Close()
    root_file.Close()


    # hist_after = root_file.Get('DNN_output0_General/sum_event_weights')
    # events_after = hist_after.GetBinContent(1)
    #
    # efficiency = events_after / events_noHEM
    # percentage = efficiency * 100
    # print(str(sample) + ': {:.1f}%'.format(percentage))
