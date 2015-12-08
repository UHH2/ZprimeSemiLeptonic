TTbarLJ workflow
----------------

* TTbarLJSkimmingModule
  * input: NtupleWriter output
  * object reconstruction (leptons, jets, MET)
  * preselection:
    * \>=1 lepton + \>=2 jets + MET
    * lower thresholds for MET and jet pTs, compared to final analysis selection

* TTbarLJAnalysisLiteModule
  * input: TTbarLJSkimmingModule output
  * final l+jets analysis selection
  * sub-ntuple with minimal set of variables and weights
