#!/usr/bin/env python2

from collections import OrderedDict

_VARIABLES = OrderedDict([
    ('M_tophad_ttag', {
        'name': 'M_tophad_ttag',
        'x_axis_title': 'm_{t_{had}} (1 t-tag)',
        'x_axis_unit': 'GeV'
    }),
    ('M_toplep_ttag', {
        'name': 'M_toplep_ttag',
        'x_axis_title': 'm_{t_{lep}} (1 t-tag)',
        'x_axis_unit': 'GeV'
    }),
    ('M_tophad_ak4', {
        'name': 'M_tophad_ak4',
        'x_axis_title': 'm_{t_{had}} (0 t-tag)',
        'x_axis_unit': 'GeV'
    }),
    ('M_toplep_ak4', {
        'name': 'M_toplep_ak4',
        'x_axis_title': 'm_{t_{lep}} (0 t-tag)',
        'x_axis_unit': 'GeV'
    }),
])
