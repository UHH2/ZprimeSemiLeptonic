#!/usr/bin/env python2

from collections import OrderedDict

_REGIONS = OrderedDict([
    ('SR', {
        'name': 'SR',
        'text': 't#bar{t} SR, #chi^{2} < 30'
    }),
    ('CR1', {
        'name': 'CR1',
        'text': 'Single t CR'
    }),
    ('CR2', {
        'name': 'CR2',
        'text': 'W#plusjets, Drell-Yan CR'
    }),
])

_VARIABLES = OrderedDict([
    ('N_jets', {
        'name': 'N_jets',
        'x_axis_title': 'N^{jets}',
        'x_axis_unit': None
    }),
    ('pt_jet1', {
        'name': 'pt_jet1',
        'x_axis_title': 'p_{T}^{AK4 jet 1}',
        'x_axis_unit': 'GeV'
    }),
    ('eta_jet1', {
        'name': 'eta_jet1',
        'x_axis_title': '#eta^{AK4 jet 1}',
        'x_axis_unit': None
    }),
    ('pt_mu', {
        'name': 'pt_mu',
        'x_axis_title': 'p_{T}^{#mu}',
        'x_axis_unit': 'GeV'
    }),
    ('eta_mu', {
        'name': 'eta_mu',
        'x_axis_title': '#eta^{#mu}',
        'x_axis_unit': None
    }),
    ('dRmin_mu_jet', {
        'name': 'dRmin_mu_jet',
        'x_axis_title': '#DeltaR_{min}(#mu, AK4 jet)',
        'x_axis_unit': None
    }),
    ('ptrel_mu_jet', {
        'name': 'ptrel_mu_jet',
        'x_axis_title': 'p_{T}^{rel}(#mu, AK4 jet)',
        'x_axis_unit': 'GeV'
    }),
    ('pt_ele', {
        'name': 'pt_ele',
        'x_axis_title': 'p_{T}^{e}',
        'x_axis_unit': 'GeV'
    }),
    ('eta_ele', {
        'name': 'eta_ele',
        'x_axis_title': '#eta^{e}',
        'x_axis_unit': None
    }),
    ('dRmin_ele_jet', {
        'name': 'dRmin_ele_jet',
        'x_axis_title': '#DeltaR_{min}(e, AK4 jet)',
        'x_axis_unit': None
    }),
    ('ptrel_ele_jet', {
        'name': 'ptrel_ele_jet',
        'x_axis_title': 'p_{T}^{rel}(e, AK4 jet)',
        'x_axis_unit': 'GeV'
    }),
    ('MET', {
        'name': 'MET',
        'x_axis_title': 'MET',
        'x_axis_unit': 'GeV'
    }),
    ('pt_AK8PuppiTaggedjet1', {
        'name': 'pt_AK8PuppiTaggedjet1',
        'x_axis_title': 'p_{T}^{t-tagged AK8 jet 1}',
        'x_axis_unit': 'GeV'
    }),
    ('eta_AK8PuppiTaggedjet1', {
        'name': 'eta_AK8PuppiTaggedjet1',
        'x_axis_title': '#eta^{t-tagged AK8 jet 1}',
        'x_axis_unit': None
    }),
])
