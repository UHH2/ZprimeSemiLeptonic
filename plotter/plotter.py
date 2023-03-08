#!/usr/bin/env python2

from __future__ import print_function

import os
import sys
# import argparse
import math
from copy import deepcopy

import ROOT as root
from ctypes import c_int
import numpy as np
# from timeit import default_timer as timer



class Process():

    def __init__(self, name, legend=None, tcolor=None, scale=1., xsec_uncert=0.):
        self.name = name
        self.legend = legend or name
        self.tcolor = tcolor or root.kBlack
        self.scale = scale or 1.
        self.xsec_uncert = xsec_uncert or 0.


def transform_TH1_to_TGraphAsymmErrors(th1, poisson_errors=False, n_sigma=1., bin_width=False):
    '''
    poisson_errors: Only makes sense if bin contents are raw integer counts (not (!) divided by bin width for example (dividing by bin width can be done in a subsequent step, though))
    n_sigma: The sigma used to calculate the Poisson confidence interval, default: 1 sigma (= ca. 68% CL)
    '''
    graph = root.TGraphAsymmErrors(th1)
    if poisson_errors:
        beta = math.erf(n_sigma / math.sqrt(2.)) # CL percentage
        alpha = 1. - beta
        for i_point in range(graph.GetN()):
            n_obs = graph.GetY()[i_point]
            lower = 0. if n_obs == 0 else root.Math.gamma_quantile(alpha / 2., n_obs, 1.);
            upper = root.Math.gamma_quantile_c(alpha / 2., n_obs + 1, 1.)
            graph.SetPointEYlow(i_point, n_obs - lower)
            graph.SetPointEYhigh(i_point, upper - n_obs)
            if not bin_width:
                graph.SetPointEXlow(i_point, 0.)
                graph.SetPointEXhigh(i_point, 0.)
    return graph

# Thanks to https://stackoverflow.com/a/45846841/10828154
def human_format(num):
    num = float('{:.3g}'.format(num))
    magnitude = 0
    while abs(num) >= 1000:
        magnitude += 1
        num /= 1000.0
    return '{}{}'.format('{:f}'.format(num).rstrip('0').rstrip('.'), ['', 'k', 'M', 'G', 'T', 'P', 'E'][magnitude])


class CoordinateConverter():

    def __init__(self, left, right, bottom, top):
        self.pad_margin_l = left
        self.pad_margin_r = right
        self.pad_margin_b = bottom
        self.pad_margin_t = top
        self.graph_width = 1. - self.pad_margin_l - self.pad_margin_r
        self.graph_height = 1. - self.pad_margin_b - self.pad_margin_t

    def graph_to_pad_x(self, graph_x):
        return self.pad_margin_l + graph_x * self.graph_width

    def graph_to_pad_y(self, graph_y):
        return self.pad_margin_b + graph_y * self.graph_height

class Counter_TObject():
    '''
    Hacky helper class used to have a counter that can be appended to TObject names (e.g. TCanvas) such that we don't get ROOT warning about "Deleting Canvas with same name" etc.
    '''
    count = 0
    @classmethod
    def increment(self):
        self.count += 1
        return self.count

class NiceStackWithRatio():

    def __init__(self,
        infile_path,
        infile_directory = '', # the directory within the ROOT file
        # inhist_name = '',
        x_axis_title = '',
        x_axis_unit = None,
        prepostfit = 'prefitRaw',
        processes = [],
        signals = [],
        syst_names = [],
        lumi_unc = None,
        divide_by_bin_width = True,
        include_underflow = False,
        include_overflow = False,
        data_name = 'data_obs',
        totalprocs_name = 'TotalProcs',
        text_prelim = 'Work in Progress',
        text_top_left = None,
        text_top_right = None,
        nostack = False,
        logy = False,
        blind_data = False,
        debug = False
    ):
        '''
        prepostfit options: 'prefitRaw', 'prefitCombine', 'postfitCombine'
        '''

        root.gStyle.SetLineWidth(1)
        root.gStyle.SetOptStat(0)

        self.prepostfit = prepostfit

        self.canvas_height = 600
        self.canvas_width = 600
        self.canvas_margin_l = 0.15
        self.canvas_margin_r = 0.05
        self.canvas_margin_t = 0.08
        self.canvas_margin_b = 0.12
        self.border_y = 0.28 # defines where to split main pad and ratio pad
        self.border_width = 0.03 # border width in percent of canvas height
        self.tick_length = 0.015 # fraction of canvas width/height
        # self.maximum_main = -np.inf
        self.syst_names = syst_names # list of strings
        self.lumi_unc = lumi_unc or 0.
        self.show_bin_width_on_data = False
        self.max_ratio_data_outliers = 3
        self.nostack = nostack

        self.y_axis_scale_factor = 1.
        self.y_axis_title = None
        self.counted_objects = 'Events' # could also be 'Jets' for example if plotting pT of all jets in an event
        self.x_axis_unit = x_axis_unit
        self.x_axis_title = x_axis_title + (' [{0}]'.format(self.x_axis_unit) if self.x_axis_unit != None else '')
        self.is_multiplicity_plot = 'number of ' in self.x_axis_title.lower() or ' multiplicity' in self.x_axis_title.lower()
        self.text_size = 0.035
        self.text_prelim = text_prelim
        self.text_top_left = text_top_left
        self.text_top_right = text_top_right

        self.draw_ratio_mc_stat = (self.prepostfit == 'prefitRaw')
        self.separate_stack_by_lines = False

        self.debug = debug

        self.coord = CoordinateConverter(self.canvas_margin_l, self.canvas_margin_r, self.canvas_margin_b, self.canvas_margin_t)

        # self.raw_hists = None
        self.processes = processes
        self.signals = signals
        self.infile_path = infile_path
        self.infile = root.TFile.Open(self.infile_path, 'READ')
        self.infile_directory = infile_directory
        # self.inhist_name = inhist_name
        self.divide_by_bin_width = False if self.is_multiplicity_plot else divide_by_bin_width
        self.include_underflow = include_underflow
        self.include_overflow = include_overflow

        self.data_name = data_name
        self.totalprocs_name = totalprocs_name
        self.totalprocs_tcolor = root.kBlack

        self.binning = None

        self.logy = logy
        self.blind_data = blind_data

    def setup_canvas(self):
        self.canvas = root.TCanvas('canvas', 'canvas title', self.canvas_height, self.canvas_width)
        self.canvas.cd()
        self.pad_main = root.TPad('pad_main', 'main pad title', 0, self.border_y, 1, 1)
        self.pad_main.SetTopMargin(self.canvas_margin_t / (1. - self.border_y))
        self.pad_main.SetBottomMargin(0.5 * self.border_width / (1. - self.border_y))
        if self.debug: self.pad_main.SetFrameFillColor(root.kGreen)
        self.pad_main.Draw()
        if self.logy: self.pad_main.SetLogy()
        self.canvas.cd()
        self.pad_ratio = root.TPad('pad_ratio', 'ratio pad title', 0, 0, 1, self.border_y)
        self.pad_ratio.SetTopMargin(0.5 * self.border_width / self.border_y)
        self.pad_ratio.SetBottomMargin(self.canvas_margin_b / self.border_y)
        if self.debug: self.pad_ratio.SetFrameFillColor(root.kOrange)
        self.pad_ratio.Draw()
        for pad in [self.pad_main, self.pad_ratio]:
            pad.SetLeftMargin(self.canvas_margin_l)
            pad.SetRightMargin(self.canvas_margin_r)
            pad.SetTickx(1)
            pad.SetTicky(1)

    def preprocess_hist(self, hist, disable_bin_width_division=False, th1_for_bin_widths=None):
        if isinstance(hist, root.TH1):
            n_bins = hist.GetNbinsX()
            if self.include_overflow:
                hist.SetBinContent(n_bins, hist.GetBinContent(n_bins) + hist.GetBinContent(n_bins + 1))
                hist.SetBinError(n_bins, math.sqrt(hist.GetBinError(n_bins)**2 + hist.GetBinError(n_bins + 1)**2))
            if self.include_underflow:
                hist.SetBinContent(1, hist.GetBinContent(1) + hist.GetBinContent(0))
                hist.SetBinError(1, math.sqrt(hist.GetBinError(1)**2 + hist.GetBinError(0)**2))
            if self.divide_by_bin_width and not disable_bin_width_division:
                for i_bin in range(1, n_bins + 1):
                    hist.SetBinContent(i_bin, hist.GetBinContent(i_bin) / hist.GetBinWidth(i_bin))
                    hist.SetBinError(i_bin, hist.GetBinError(i_bin) / hist.GetBinWidth(i_bin))
        elif isinstance(hist, root.TGraphAsymmErrors):
            n_points = hist.GetN()
            if self.divide_by_bin_width and not disable_bin_width_division:
                for i_point in range(0, n_points):
                    if th1_for_bin_widths:
                        i_bin = i_point + 1
                        bin_width = th1_for_bin_widths.GetBinWidth(i_bin)
                    else:
                        bin_width = hist.GetErrorXlow(i_point) + hist.GetErrorXhigh(i_point)
                        if bin_width <= 0:
                            sys.exit('Bin width of TGraphAsymmErrors <= 0. Maybe you want to provide a TH1 with proper bin widths to this function')
                    point_x, point_y = hist.GetX()[i_point], hist.GetY()[i_point]
                    hist.SetPoint(i_point, point_x, point_y / bin_width)
                    hist.SetPointEYhigh(i_point, hist.GetErrorYhigh(i_point) / bin_width)
                    hist.SetPointEYlow(i_point, hist.GetErrorYlow(i_point) / bin_width)

    def get_binning(self, hist):
        binning = np.array([], dtype=np.float32)
        n_bins = hist.GetNbinsX()
        for i_bin in range(1, n_bins + 1):
            binning = np.append(binning, [ hist.GetXaxis().GetBinLowEdge(i_bin) ])
        binning = np.append(binning, [ hist.GetXaxis().GetBinUpEdge(n_bins) ])
        if self.binning and self.binning != binning:
                sys.exit('Binnings are not compatible with each other')
        self.binning = binning
        return self.binning

    def add_hists(self, hist_list):
        self.get_binning(hist_list[0])
        hist_total = root.TH1F('')

    def create_stack(self):
        if self.nostack:
            self.stack = []
            for i_process, process in enumerate(self.processes):
                hist = self.infile.Get(os.path.join(self.infile_directory, process.name))
                self.preprocess_hist(hist)
                hist.SetLineColor(process.tcolor)
                hist.SetLineWidth(1)
                hist.SetMarkerSize(0)
                self.stack.append(deepcopy(hist))
            self.stack_hist = self.stack[0]
            self.get_binning(self.stack[0])
            # Important: self.totalprocs must contain only MC stat uncertainty, such that prefitRaw ratio MC stat plots are correct!
            self.totalprocs = root.TH1F(self.totalprocs_name, '', len(self.binning)-1, self.binning)
            for i_bin in range(0, self.totalprocs.GetNbinsX() + 2):
                binc = 0.
                err2 = 0.
                for hist in self.stack:
                    binc += hist.GetBinContent(i_bin)
                    err2 += hist.GetBinError(i_bin)**2
                self.totalprocs.SetBinContent(i_bin, binc)
                self.totalprocs.SetBinError(i_bin, math.sqrt(err2))

            self.totalprocs.SetLineColor(self.totalprocs_tcolor)
            self.totalprocs.SetLineWidth(1)
            self.totalprocs.SetMarkerSize(0)
            self.stack_hist = self.stack[0]
        else:
            self.stack = root.THStack('stack', '')
            for i_process, process in enumerate(self.processes):
                print(os.path.join(self.infile_directory, process.name))
                hist = self.infile.Get(os.path.join(self.infile_directory, process.name))
                self.preprocess_hist(hist)
                hist.SetFillColorAlpha(process.tcolor, 1.)
                hist.SetLineColor(root.kWhite)
                hist.SetLineWidth(1 if (self.separate_stack_by_lines and i_process != len(self.processes) - 1) else 0)
                hist.SetMarkerSize(0)
                self.stack.Add(deepcopy(hist))
            self.totalprocs = self.stack.GetStack().Last()
            self.pad_main.cd()
            self.stack.Draw() # need to draw the stack once, else GetHistogram returns a nullptr
            self.stack_hist = self.stack.GetHistogram()
            self.get_binning(self.totalprocs)
        return self.stack

    def create_signals(self):
        self.signal_hists = []
        for i_signal, signal in enumerate(self.signals):
            hist = self.infile.Get(os.path.join(self.infile_directory, signal.name))
            self.preprocess_hist(hist)
            hist.SetLineColor(signal.tcolor)
            hist.SetLineWidth(2)
            hist.SetLineStyle(7)
            print(signal.name + " scaled with factor " + str(signal.scale))
            hist.Scale(signal.scale)
            self.signal_hists.append(hist)
        return self.signal_hists

    def create_data(self):
        self.data_hist = self.infile.Get(os.path.join(self.infile_directory, self.data_name))
        self.data_hist.SetLineWidth(1)
        self.data_hist.SetLineColor(root.kBlack)
        self.data_hist.SetMarkerStyle(8)
        self.preprocess_hist(self.data_hist, disable_bin_width_division=True)
        self.data = transform_TH1_to_TGraphAsymmErrors(self.data_hist, poisson_errors=False, bin_width=self.show_bin_width_on_data)
        self.preprocess_hist(self.data, th1_for_bin_widths=self.data_hist)
        self.data.SetLineWidth(1)
        self.data.SetLineColor(root.kBlack)
        self.data.SetMarkerStyle(8)
        return self.data

    def get_syst_unc_for_bin(self, i_bin, direction):
        # if not len(self.syst_names):
        #     return 0.
        err2 = 0.
        for process in self.processes:
            hist_nominal = self.infile.Get(os.path.join(self.infile_directory, process.name))
            nominal = hist_nominal.GetBinContent(i_bin)
            err2 += (nominal * process.xsec_uncert)**2
            for syst in self.syst_names:
                hist_syst_down = self.infile.Get(os.path.join(self.infile_directory, process.name+'_'+syst+'Down'))
                hist_syst_up = self.infile.Get(os.path.join(self.infile_directory, process.name+'_'+syst+'Up'))
                err_down = hist_syst_down.GetBinContent(i_bin) - nominal
                err_up = hist_syst_up.GetBinContent(i_bin) - nominal
                err_down_positive = err_down >= 0.
                err_up_positive = err_up >= 0.
                if direction == 'plus':
                    if err_up_positive and not err_down_positive:
                        err2 += err_up**2
                    elif err_down_positive and not err_up_positive:
                        err2 += err_down**2
                    elif err_up_positive and err_down_positive:
                        err2 += max(err_up, err_down)**2
                    else: pass # nothing added to plus error
                elif direction == 'minus':
                    if err_up_positive and not err_down_positive:
                        err2 += err_down**2
                    elif err_down_positive and not err_up_positive:
                        err2 += err_up**2
                    elif not err_up_positive and not err_down_positive:
                        err2 += min(err_up, err_down)**2
                    else: pass # nothing added to minus error
                else:
                    sys.exit('invalid direction: {0}'.format(direction))
        return math.sqrt(err2)

    def create_stack_unc(self):
        arr_x = np.array([], dtype=np.float32)
        arr_y = np.array([], dtype=np.float32)
        arr_exl = np.array([], dtype=np.float32)
        arr_exh = np.array([], dtype=np.float32)
        arr_eyl = np.array([], dtype=np.float32)
        arr_eyh = np.array([], dtype=np.float32)

        if self.nostack or self.prepostfit == 'prefitCombine' or self.prepostfit == 'postfitCombine':
            if self.nostack:
                hist_totalprocs = self.totalprocs
            else:
                hist_totalprocs = self.infile.Get(os.path.join(self.infile_directory, self.totalprocs_name))
            n_bins = hist_totalprocs.GetNbinsX()
            for i_bin in range(1, n_bins + 1):
                i_point = i_bin - 1
                bin_width = hist_totalprocs.GetBinWidth(i_bin)
                arr_x = np.append(arr_x, [hist_totalprocs.GetBinCenter(i_bin)])
                arr_y = np.append(arr_y, [hist_totalprocs.GetBinContent(i_bin) * self.y_axis_scale_factor / (bin_width if self.divide_by_bin_width else 1.)])
                arr_exl = np.append(arr_exl, [bin_width / 2.])
                arr_exh = np.append(arr_exh, [bin_width / 2.])
                arr_eyl = np.append(arr_eyl, [hist_totalprocs.GetBinError(i_bin) * self.y_axis_scale_factor / (bin_width if self.divide_by_bin_width else 1.)])
                arr_eyh = np.append(arr_eyh, [hist_totalprocs.GetBinError(i_bin) * self.y_axis_scale_factor / (bin_width if self.divide_by_bin_width else 1.)])

        elif self.prepostfit == 'prefitRaw':
            # last = self.stack.GetStack().Last()
            last = self.totalprocs
            n_bins = last.GetNbinsX()
            for i_bin in range(1, n_bins + 1):
                i_point = i_bin - 1
                bin_width = last.GetBinWidth(i_bin)
                arr_x = np.append(arr_x, [last.GetBinCenter(i_bin)])
                arr_y = np.append(arr_y, [last.GetBinContent(i_bin)]) * self.y_axis_scale_factor
                arr_exl = np.append(arr_exl, [bin_width / 2.])
                arr_exh = np.append(arr_exh, [bin_width / 2.])
                arr_eyl = np.append(arr_eyl, [
                    math.sqrt(
                        ( last.GetBinError(i_bin) * (bin_width if self.divide_by_bin_width else 1.) )**2 \
                        + ( self.get_syst_unc_for_bin(i_bin, 'minus') )**2 \
                        + ( self.lumi_unc * last.GetBinContent(i_bin) * (bin_width if self.divide_by_bin_width else 1.) )**2
                    ) * self.y_axis_scale_factor / (bin_width if self.divide_by_bin_width else 1.)
                ])
                arr_eyh = np.append(arr_eyh, [
                    math.sqrt(
                        ( last.GetBinError(i_bin) * (bin_width if self.divide_by_bin_width else 1.) )**2 \
                        + ( self.get_syst_unc_for_bin(i_bin, 'plus') )**2 \
                        + ( self.lumi_unc * last.GetBinContent(i_bin) * (bin_width if self.divide_by_bin_width else 1.) )**2
                    ) * self.y_axis_scale_factor / (bin_width if self.divide_by_bin_width else 1.)
                ])

        self.stack_unc = root.TGraphAsymmErrors(n_bins, arr_x, arr_y, arr_exl, arr_exh, arr_eyl, arr_eyh)
        self.stack_unc.SetLineWidth(0)
        self.stack_unc.SetFillColor(root.kGray + 1)
        self.stack_unc.SetFillStyle(3254)
        return self.stack_unc

    def cosmetics_main(self):
        # Segmentation violation if stack is not drawn before calling the following cosmetics settings
        self.pad_main.cd()
        # self.pad_main.Update()
        # root.gPad.Update()

        # last = self.stack.GetStack().Last()
        last = self.totalprocs
        hist = self.stack_hist
        hist.SetTitle('')


        maximum_stack = last.GetBinContent(last.GetMaximumBin())
        minimum_stack = last.GetBinContent(last.GetMinimumBin())
        maximum = maximum_stack
        minimum = minimum_stack


        if not self.blind_data:
            maximum_data = max(self.data.GetY())
            maximum = max(maximum_data, maximum_stack)
            minimum_data = min(self.data.GetY())
            minimum = min(minimum_data, minimum_stack)

        if maximum == 0.0: # set default when there is no MC and data (e.g. due to electron/muon channel)
            maximum = 100

        if self.logy:
            new_minimum = 1 # could also be one order of magnitude or so below the minimum bin value of the process that is lowest in the stack
            new_minimum = max(new_minimum, minimum * 0.1) # how it should be, but y axis range is somehow not correctly set to this value
            print('new_minimum:', new_minimum)
            new_maximum = math.pow(10, 2.5 * (math.log(maximum, 10) - math.log(new_minimum, 10))) # how it should be, but y axis range is somehow not correctly set to this value
            print('new_maximum:', new_maximum)
        else:
            new_minimum = 0.
            new_maximum = 2.0 * maximum
        last.SetMaximum(new_maximum) # this updates the axis maximum
        hist.SetMaximum(new_maximum)
        last.SetMinimum(new_minimum)
        hist.SetMinimum(new_minimum)
        # last.GetYaxis().SetRangeUser(new_minimum, new_maximum)
        # hist.GetYaxis().SetRangeUser(new_minimum, new_maximum)

        if not self.logy:
            #####################
            # Do the re-labeling of y axis if values get too large
            if self.nostack:
                self.stack[0].GetYaxis().SetLimits(new_minimum, new_maximum) # needed to find correct number of labels
            else:
                hist.GetYaxis().SetLimits(new_minimum, new_maximum) # needed to find correct number of labels
            hist.GetYaxis().SetMaxDigits(99) # never use ugly "x 10^N" notation
            ndiv = hist.GetYaxis().GetNdivisions()
            if ndiv > 0:
                divxo = c_int()
                x1o = root.Double()
                x2o = root.Double()
                bwx = root.Double()
                root.THLimitsFinder.Optimize(hist.GetYaxis().GetXmin(), hist.GetYaxis().GetXmax(), ndiv%100, x1o, x2o, divxo, bwx, '')
                n_labels = divxo.value + 1
            else:
                divx = -ndiv
                n_labels = divx%100 + 1
            # print(n_labels) # number of labels
            # print(x1o) # min label
            # print(x2o) # max label
            # print(bwx) # label value difference
            if x2o >= 10000.:
                label_values = np.linspace(x1o, x2o, n_labels)
                for i_label in range(0, n_labels):
                    hist.GetYaxis().ChangeLabel(i_label+1, -1, -1, -1, -1, -1, human_format(label_values[i_label]))
                # sometimes, the highest label is not yet fixed, so we need this additional line (that has no effect if it is not needed??):
                hist.GetYaxis().ChangeLabel(n_labels+1, -1, -1, -1, -1, -1, human_format(label_values[n_labels-1] + bwx))
            #####################

        has_fixed_binning = True
        n_bins = last.GetNbinsX()
        for i_bin in range(1, n_bins):
            if last.GetBinWidth(i_bin) != last.GetBinWidth(i_bin + 1):
                has_fixed_binning = False
                break
        if self.y_axis_title != None:
            y_axis_title = self.y_axis_title
        elif has_fixed_binning and not self.divide_by_bin_width and not self.is_multiplicity_plot:
            bin_width_string = ('%f' % last.GetBinWidth(1)).rstrip('0').rstrip('.')
            y_axis_title = self.counted_objects+' / '+bin_width_string+(' '+self.x_axis_unit if self.x_axis_unit else '')
        elif self.divide_by_bin_width:
            y_axis_title = self.counted_objects+' / '+(self.x_axis_unit if self.x_axis_unit else 'unity')
        else:
            y_axis_title = self.counted_objects+' / bin'
        hist.GetYaxis().SetTitle(y_axis_title)
        hist.GetYaxis().SetTitleSize(self.text_size / (1. - self.border_y))
        hist.GetYaxis().SetLabelSize(self.text_size / (1. - self.border_y))
        hist.GetYaxis().SetLabelOffset(0.01)
        hist.GetXaxis().SetLabelOffset(999) # hack: let x axis title/labels vanish under pad_ratio
        hist.GetXaxis().SetTitle('')
        if self.is_multiplicity_plot:
            hist.GetXaxis().SetNdivisions(hist.GetNbinsX())

        # Fix inconsistent tick lengths:
        # https://root-forum.cern.ch/t/inconsistent-tick-length/18563/8
        self.pad_main.Update()
        tickScaleX = (self.pad_main.GetUxmax() - self.pad_main.GetUxmin()) / (self.pad_main.GetX2() - self.pad_main.GetX1()) * (self.pad_main.GetWh() * self.pad_main.GetAbsHNDC())
        tickScaleY = (self.pad_main.GetUymax() - self.pad_main.GetUymin()) / (self.pad_main.GetY2() - self.pad_main.GetY1()) * (self.pad_main.GetWw() * self.pad_main.GetAbsWNDC())
        self.stack_hist.GetXaxis().SetTickLength(self.canvas.GetWh() * self.tick_length / tickScaleX)
        self.stack_hist.GetYaxis().SetTickLength(self.canvas.GetWw() * self.tick_length / tickScaleY)

        root.gPad.Update()
        root.gPad.RedrawAxis()

    def create_ratio_null_hist(self):
        # This works for THStack:
        # self.ratio_null_hist = root.TH1F(self.stack.GetHistogram())
        # This is more general (cannot just use copy constructor on self.totalprocs = self.stack.GetStack.Last(), since Last() returns a TObject*, not TH1F* and I don't know how to type-cast this in pyROOT)
        self.ratio_null_hist = root.TH1F('ratio_null_hist', '', len(self.binning)-1, self.binning)
        self.ratio_null_hist.Reset()
        self.ratio_null_hist.SetTitle('')
        # self.ratio_null_hist.Draw()
        return self.ratio_null_hist

    def create_ratio_mc_stat(self):
        # last = self.stack.GetStack().Last()
        last = self.totalprocs
        hist = self.stack_hist
        self.ratio_mc_stat = root.TH1F('ratio_mc_stat', '', len(self.binning)-1, self.binning)
        n_bins = self.ratio_mc_stat.GetNbinsX()
        for i_bin in range(0, n_bins + 2):
            self.ratio_mc_stat.SetBinContent(i_bin, 1.)
            if last.GetBinContent(i_bin) <= 0:
                self.ratio_mc_stat.SetBinError(i_bin, 0.)
            else:
                self.ratio_mc_stat.SetBinError(i_bin, last.GetBinError(i_bin) / last.GetBinContent(i_bin))
        self.ratio_mc_stat.SetFillColor(root.kGray)
        self.ratio_mc_stat.SetFillStyle(1001)
        self.ratio_mc_stat.SetTitle('MC stat. unc.')
        self.ratio_mc_stat.SetLineWidth(0)
        self.ratio_mc_stat.SetMarkerStyle(0)
        return self.ratio_mc_stat

    def create_ratio_unc(self):
        n_points = self.stack_unc.GetN()
        self.ratio_unc = root.TGraphAsymmErrors(n_points)
        for i_point in range(0, n_points):
            point_x, point_y = self.stack_unc.GetX()[i_point], self.stack_unc.GetY()[i_point]
            self.ratio_unc.SetPoint(i_point, point_x, 1.)
            if point_y <= 0.:
                self.ratio_unc.SetPointError(i_point, self.stack_unc.GetErrorXlow(i_point), self.stack_unc.GetErrorXhigh(i_point), 0., 0.) # like SFramePlotter's IgnoreEmptyBins
            else:
                self.ratio_unc.SetPointError(i_point, self.stack_unc.GetErrorXlow(i_point), self.stack_unc.GetErrorXhigh(i_point), self.stack_unc.GetErrorYlow(i_point) / point_y, self.stack_unc.GetErrorYhigh(i_point) / point_y)
        self.ratio_unc.SetFillColor(root.kGray + 1)
        self.ratio_unc.SetFillStyle(3254)
        self.ratio_unc.SetLineWidth(0)
        self.ratio_unc.SetMarkerStyle(0)
        return self.ratio_unc

    def create_ratio_data(self):
        # last = self.stack.GetStack().Last()
        last = self.totalprocs
        self.ratio_data = root.TGraphAsymmErrors(self.data)
        n_points = self.ratio_data.GetN()
        for i_point in range(0, n_points):
            i_bin = i_point + 1
            point_x, point_y = self.data.GetX()[i_point], self.data.GetY()[i_point]
            prediction = last.GetBinContent(i_bin)
            # if prediction <= 0. or point_y <= 0.: continue
            if prediction <= 0.:
                # Force data points to ratio=-1 with error=0 if no prediction in this bin. Outlier markers for ratio=-1 will be skipped
                self.ratio_data.SetPoint(i_point, point_x, -1.)
                self.ratio_data.SetPointError(i_point, self.data.GetErrorXlow(i_point), self.data.GetErrorXhigh(i_point), 0., 0.)
            else:
                self.ratio_data.SetPoint(i_point, point_x, point_y / prediction)
                self.ratio_data.SetPointError(i_point, self.data.GetErrorXlow(i_point), self.data.GetErrorXhigh(i_point), self.data.GetErrorYlow(i_point) / prediction, self.data.GetErrorYhigh(i_point) / prediction)
        return self.ratio_data

    def create_ratio_signal(self):
        self.signal_ratiohists = []
        for signal in self.signal_hists:
            signal_hist = signal.Clone()
            signal_hist.Divide(self.totalprocs)
            self.signal_ratiohists.append(signal_hist)
        return self.signal_ratiohists


    def cosmetics_ratio(self):
        self.pad_ratio.cd()

        self.ratio_null_hist.GetXaxis().SetLabelSize(self.text_size / self.border_y)
        self.ratio_null_hist.GetXaxis().SetLabelOffset(20. / self.stack_hist.GetXaxis().GetLabelOffset())
        self.ratio_null_hist.GetXaxis().SetTitleSize(self.text_size / self.border_y)
        self.ratio_null_hist.GetXaxis().SetTitle(self.x_axis_title)
        self.ratio_null_hist.GetXaxis().SetTitleOffset(1.3)
        self.ratio_null_hist.GetXaxis().SetNdivisions(self.stack_hist.GetXaxis().GetNdivisions())

        self.ratio_null_hist.GetYaxis().SetTitle('Data / pred.')
        self.ratio_null_hist.GetYaxis().SetLabelSize(self.text_size / self.border_y)
        self.ratio_null_hist.GetYaxis().SetLabelOffset(0.01)
        self.ratio_null_hist.GetYaxis().SetTitleSize(self.text_size / self.border_y)
        self.ratio_null_hist.GetYaxis().SetTitleOffset(0.45)
        self.ratio_null_hist.GetYaxis().CenterTitle()
        # self.ratio_null_hist.SetMinimum(0.7)
        # self.ratio_null_hist.SetMaximum(1.3)
        # self.ratio_null_hist.GetYaxis().SetNdivisions(403)
        self.ratio_null_hist.SetMinimum(0.3)
        self.ratio_null_hist.SetMaximum(1.7)
        self.ratio_null_hist.GetYaxis().SetNdivisions(503)

        # Fix inconsistent tick lengths:
        # https://root-forum.cern.ch/t/inconsistent-tick-length/18563/8
        self.pad_ratio.Update()
        tickScaleX = (self.pad_ratio.GetUxmax() - self.pad_ratio.GetUxmin()) / (self.pad_ratio.GetX2() - self.pad_ratio.GetX1()) * (self.pad_ratio.GetWh() * self.pad_ratio.GetAbsHNDC())
        tickScaleY = (self.pad_ratio.GetUymax() - self.pad_ratio.GetUymin()) / (self.pad_ratio.GetY2() - self.pad_ratio.GetY1()) * (self.pad_ratio.GetWw() * self.pad_ratio.GetAbsWNDC())
        self.ratio_null_hist.GetXaxis().SetTickLength(self.canvas.GetWh() * self.tick_length / tickScaleX)
        self.ratio_null_hist.GetYaxis().SetTickLength(self.canvas.GetWw() * self.tick_length / tickScaleY)

        self.ratio_line = root.TLine(self.ratio_null_hist.GetXaxis().GetXmin(), 1., self.ratio_null_hist.GetXaxis().GetXmax(), 1.)
        self.ratio_line.SetLineStyle(2)
        self.ratio_line.Draw()

        if not self.blind_data:
            # Minimize the "outlier" data points in ratio plot by adjusting the y axis range
            n_points = self.ratio_data.GetN()
            # n_ratio_data_outliers = 0
            # for i_point in range(0, n_points):
            #     point_y = self.ratio_data.GetY()[i_point]
            #     if point_y <= 0.: continue # ignore data points which are zero for this algorithm
            #     if point_y < self.ratio_null_hist.GetMinimum() or point_y > self.ratio_null_hist.GetMaximum():
            #         n_ratio_data_outliers += 1
            # if n_ratio_data_outliers > self.max_ratio_data_outliers:
            #     self.ratio_null_hist.SetMinimum(0.3)
            #     self.ratio_null_hist.SetMaximum(1.7)
            #     self.ratio_null_hist.GetYaxis().SetNdivisions(503)
            # n_ratio_data_outliers = 0
            # for i_point in range(0, n_points):
            #     point_y = self.ratio_data.GetY()[i_point]
            #     if point_y <= 0.: continue # ignore data points which are zero for this algorithm
            #     if point_y < self.ratio_null_hist.GetMinimum() or point_y > self.ratio_null_hist.GetMaximum():
            #         n_ratio_data_outliers += 1
            # if n_ratio_data_outliers > self.max_ratio_data_outliers:
            #     self.ratio_null_hist.SetMinimum(0.0)
            #     self.ratio_null_hist.SetMaximum(2.0)
            #     self.ratio_null_hist.GetYaxis().SetNdivisions(503)

            # Now set "arrow" markers for all remaining outliers at the upper/lower edge of ratio plot:
            for i_point in range(0, n_points):
                point_x, point_y = self.ratio_data.GetX()[i_point], self.ratio_data.GetY()[i_point]
                if point_y > self.ratio_null_hist.GetMaximum():
                    marker = root.TMarker()
                    marker.SetMarkerStyle(22)
                    marker.SetMarkerSize(self.ratio_data.GetMarkerSize())
                    marker.DrawMarker(point_x, self.ratio_null_hist.GetMaximum())
                elif point_y < self.ratio_null_hist.GetMinimum() and point_y > -1: # Outlier markes where ratio=-1 will be skipped; ratio=-1 means that there is no prediction in this bin
                    marker = root.TMarker()
                    marker.SetMarkerStyle(23)
                    marker.SetMarkerSize(self.ratio_data.GetMarkerSize())
                    marker.DrawMarker(point_x, self.ratio_null_hist.GetMinimum())

        root.gPad.Update()
        root.gPad.RedrawAxis()

    def draw_texts(self):
        self.canvas.cd()

        if self.text_top_left:
            self.tlatex_top_left = root.TLatex(self.canvas_margin_l, 1. - self.canvas_margin_t + 0.01, self.text_top_left)
            self.tlatex_top_left.SetTextAlign(11) # left bottom
            self.tlatex_top_left.SetTextFont(42)
            self.tlatex_top_left.SetTextSize(self.text_size)
            self.tlatex_top_left.SetNDC()
            self.tlatex_top_left.Draw()

        if self.text_top_right:
            self.tlatex_top_right = root.TLatex(1. - self.canvas_margin_r, 1. - self.canvas_margin_t + 0.01, self.text_top_right)
            self.tlatex_top_right.SetTextAlign(31) # right bottom
            self.tlatex_top_right.SetTextFont(42)
            self.tlatex_top_right.SetTextSize(self.text_size)
            self.tlatex_top_right.SetNDC()
            self.tlatex_top_right.Draw()

        self.tlatex_cms = root.TLatex(self.coord.graph_to_pad_x(0.05), self.coord.graph_to_pad_y(0.95), 'CMS')
        self.tlatex_cms.SetTextAlign(13) # left top
        self.tlatex_cms.SetTextFont(62)
        self.tlatex_cms.SetTextSize(0.05)
        self.tlatex_cms.SetNDC()
        self.tlatex_cms.Draw()

        self.tlatex_prelim = root.TLatex(self.coord.graph_to_pad_x(0.05), self.coord.graph_to_pad_y(0.89), self.text_prelim)
        self.tlatex_prelim.SetTextAlign(13) # left top
        self.tlatex_prelim.SetTextFont(52)
        self.tlatex_prelim.SetTextSize(self.text_size)
        self.tlatex_prelim.SetNDC()
        self.tlatex_prelim.Draw()

        if self.draw_ratio_mc_stat:
            # draw a "legend" for MC stat. uncertainty band in ratio plot
            self.tlatex_mcstat = root.TLatex(1. - self.canvas_margin_r + 0.02, 0.75 * self.border_y, self.ratio_mc_stat.GetTitle())
            self.tlatex_mcstat.SetTextAlign(22) # center center
            self.tlatex_mcstat.SetTextFont(42)
            self.tlatex_mcstat.SetTextSize(0.018)
            self.tlatex_mcstat.SetTextAngle(90)
            self.tlatex_mcstat.SetNDC()
            self.tlatex_mcstat.Draw()

            self.tbox_mcstat = root.TBox(1. - self.canvas_margin_r + 0.012, 0.45 * self.border_y, 1. - self.canvas_margin_r + 0.030, 0.53 * self.border_y)
            self.tbox_mcstat.SetFillColor(self.ratio_mc_stat.GetFillColor())
            self.tbox_mcstat.SetLineWidth(self.ratio_mc_stat.GetLineWidth())
            self.tbox_mcstat.Draw()

    def plot(self):
        # if not self.canvas: self.setup_canvas()
        self.setup_canvas()
        self.pad_main.cd()
        # self.create_stack().Draw('hist nostack' if self.nostack else 'hist')
        if self.nostack:
            self.create_stack()
            for i_hist in range(len(self.stack)):
                self.stack[i_hist].Draw('same hist')
            self.totalprocs.Draw('same hist')
        else:
            self.create_stack().Draw('hist')
        self.create_stack_unc().Draw('2')

        self.create_signals()
        for signal_hist in self.signal_hists:
            signal_hist.Draw('hist same')

        # self.create_data().Draw('same e x0') # if self.data would be a TH1
        if not self.blind_data: self.create_data().Draw('pz0')
        self.pad_ratio.cd()
        self.create_ratio_null_hist().Draw()
        if self.draw_ratio_mc_stat:
            self.create_ratio_mc_stat().Draw('same e2')
        self.create_ratio_unc().Draw('same 2')

        self.create_ratio_signal()
        for signal_ratio in self.signal_ratiohists:
            signal_ratio.Draw('same hist')

        # self.create_ratio_data().Draw('same e x0') # if ratio data would be a TH1
        if not self.blind_data: self.create_ratio_data().Draw('pz0')
        self.cosmetics_main()
        self.cosmetics_ratio()
        self.draw_texts()

    def save_plot(self, filename, directory=None):
        if not self.canvas:
            sys.exit('No canvas to save. Did you call "plot()"?')
        if directory:
            filepath = os.path.join(directory, filename)
            os.system('mkdir -p '+directory)
        else:
            filepath = filename
        self.canvas.SaveAs(filepath)
