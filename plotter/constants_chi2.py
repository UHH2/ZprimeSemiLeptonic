#!/usr/bin/env python2

from collections import OrderedDict

_VARIABLES = OrderedDict([
    ('M_tophad_ttag', {
        'name': 'M_tophad_ttag',
        'x_axis_title': 'm_{t_{had}} (1 t-tag)',
        'x_axis_unit': 'GeV'
    }),
    ('chi2_Zprime', {
        'name': 'chi2_Zprime',
        'x_axis_title': '#chi^{2}',
        'x_axis_unit': None
    }),
    # ('chi2_Zprime_ak4_rebin', {
    #     'name': 'chi2_Zprime_ak4_rebin',
    #     'x_axis_title': '#chi^{2} (0 t-tag)',
    #     'x_axis_unit': None
    # }),
    # ('chi2_Zprime_ttag_rebin', {
    #     'name': 'chi2_Zprime_ttag_rebin',
    #     'x_axis_title': '#chi^{2} (1 t-tag)',
    #     'x_axis_unit': None
    # }),
])
