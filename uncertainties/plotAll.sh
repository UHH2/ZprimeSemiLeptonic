#!/bin/bash

#root -l -b -q topPtReweighting.cxx
#root -l -b -q PDF.cxx
#root -l -b -q MCScale.cxx
root -l -b -q pdf_new.cxx
root -l -b -q mcscale_new.cxx
root -l -b -q pileUp.cxx
# root -l -b -q partonShower.cxx
root -l -b -q muonSFs.cxx
root -l -b -q electronSFs.cxx
root -l -b -q prefiring.cxx
root -l -b -q btagSFs.cxx
