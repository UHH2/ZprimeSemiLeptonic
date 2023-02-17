# Analysis Code of the pp → X → tt (lepton + jets) Analysis

This is the branch is for the full Run 2 analysis using UL datasets.
The main changes with respect to the previous CMS result (2016 data, B2G-17-017) are:

- full Run 2 data set
- top-tagging with DeepAK8 (or HOTVR): the tagger can be chosen in the ZprimeAnalysisModule via a boolean
- add isolated lepton triggers + lower lepton and jet pT-thresholds
- add b-tagging with DeepJet
- use DNN (instead of BDT) to categorize events
- add signal interpretations: heavy Higgses, axion-like particles

## Workflow
- run PreselectionModule
- calculate custom 2D b-tagging SFs (run AnalysisModule without electron trigger SFs, 2D b-tagging SFs and chi^2)
- calculate electron trigger SFs (run AnalysisModule without electron trigger SFs and chi^2)
- run AnalysisModule
- calculate chi^2 parameters
- run AnalysisModule to save the variables for the DNN
- DNN:
  - convert data from UHH2 e.g. to numpy: see e.g. https://github.com/jabuschh/MLCorner
  - training: see e.g. https://github.com/jabuschh/ZprimeClassifier
- run AnalysisModule_applyNN

## Some Links

- CADI line: https://cms.cern.ch/iCMS/analysisadmin/cadilines?line=B2G-22-006
- review twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/B2G22006Review
