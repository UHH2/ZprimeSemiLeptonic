#!/usr/bin/env python2

from collections import OrderedDict

_SAMPLES = OrderedDict([
    ('TTToSemiLeptonic', {
        'name': 'TTToSemiLeptonic',
        'xsec': 831.76,
        'br': 0.438,
        'nevt': 327148781380.1,
        'file_name': '/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/TOP-20-001/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic.root'
    }),
    ('ALP_ttbar_signal', {
        'name': 'ALP_ttbar_signal',
        'xsec': 7.048,
        'br': 1.0, # inclusive ttbar decay
        'nevt': 29131000.0,
        'file_name': '/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/TOP-20-001/uhh2.AnalysisModuleRunner.MC.ALP_ttbar_signal.root'
    }),
    ('ALP_ttbar_interference', {
        'name': 'ALP_ttbar_interference',
        'xsec': -28.24802, # use as positive interference
        'br': 1.0, # inclusive ttbar decay
        'nevt': 29389940.0,
        'file_name': '/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/TOP-20-001/uhh2.AnalysisModuleRunner.MC.ALP_ttbar_interference.root'
    }),
])

_VARIABLES = OrderedDict([
    # ('pt_thad', {
    #     'name': 'pt_thad',
    #     'x_axis_title': 'p_{T}(t_{had})',
    #     'x_axis_unit': 'GeV',
    # }),
    # ('pt_tlep', {
    #     'name': 'pt_tlep',
    #     'x_axis_title': 'p_{T}(t_{lep})',
    #     'x_axis_unit': 'GeV',
    # }),
    # ('ST', {
    #     'name': 'ST',
    #     'x_axis_title': 'S_{T}',
    #     'x_axis_unit': 'GeV',
    # }),
    # ('absy_thad', {
    #     'name': 'absy_thad',
    #     'x_axis_title': '|y(t_{had})|',
    #     'x_axis_unit': None,
    # }),
    # ('absy_tlep', {
    #     'name': 'absy_tlep',
    #     'x_axis_title': '|y(t_{lep})|',
    #     'x_axis_unit': None,
    # }),
    # ('deltaabsy_ttbar', {
    #     'name': 'deltaabsy_ttbar',
    #     'x_axis_title': '#Delta|y_{t/#bar{t}}|',
    #     'x_axis_unit': None,
    # }),
    # ('absdeltay_ttbar', {
    #     'name': 'absdeltay_ttbar',
    #     'x_axis_title': '|#Deltay_{t/#bar{t}}|',
    #     'x_axis_unit': None,
    # }),
    ('m_ttbar', {
        'name': 'm_ttbar',
        'x_axis_title': 'm(t#bar{t})',
        'x_axis_unit': 'GeV',
    }),
    # ('pt_ttbar', {
    #     'name': 'pt_ttbar',
    #     'x_axis_title': 'p_{T}(t#bar{t})',
    #     'x_axis_unit': 'GeV',
    # }),
    # ('absy_ttbar', {
    #     'name': 'absy_ttbar',
    #     'x_axis_title': '|y(t#bar{t})|',
    #     'x_axis_unit': None,
    # }),
    # ('phi_ttbar', {
    #     'name': 'phi_ttbar',
    #     'x_axis_title': '#phi_{t/#bar{t}}',
    #     'x_axis_unit': '#circ',
    # }),
    # ('cts', {
    #     'name': 'cts',
    #     'x_axis_title': 'cos(#theta*)',
    #     'x_axis_unit': None,
    # }),
])
