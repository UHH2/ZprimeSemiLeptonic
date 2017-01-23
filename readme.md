TTbarLJ workflow
----------------
This branch is for the full dataset towards Moriond 17
* TTbarLJSkimmingModule
This module takes ntuples and cleans leptons and jets and applies preliminary cuts
  * input: NtupleWriter output
  * object reconstruction (leptons, jets, MET)
  * preselection:
    * \>=1 lepton + \>=2 jets + MET
    * lower thresholds for MET and jet pTs, compared to final analysis selection

* BDTWJetsVariableDumpModule
This module takes the root file output from the skimming modules and dumps the variables needed for 
BDT training and testing into the AnalysisTree
  * input:  TTbarLJSkimmingModule output

* TTbarLJAnalysisLiteModule
  * input: TTbarLJSkimmingModule output
  * final l+jets analysis selection
  * sub-ntuple with minimal set of variables and weights
