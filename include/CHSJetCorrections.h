#pragma once
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/core/include/Utils.h"

#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/YearRunSwitchers.h"

class CHSJetCorrections: public uhh2::AnalysisModule {
public:
    CHSJetCorrections();

    virtual bool process(uhh2::Event & event) override;
    void init(uhh2::Context & ctx);

private:
    void fail_if_init() const;

    uhh2::Event::Handle< std::vector<Jet> > h_CHSjets_branch;
    std::unique_ptr<YearSwitcher> jet_corrector_MC;
    std::shared_ptr<RunSwitcher> jec_switcher_UL16preVFP, jec_switcher_UL16postVFP, jec_switcher_UL17, jec_switcher_UL18;
    std::unique_ptr<GenericJetResolutionSmearer> jet_resolution_smearer;

    bool is_mc, is_data;
    bool init_done = false;

    Year year;

    // Parameters for JEC & JLC sets
    std::string jec_tag_UL16preVFP, jec_ver_UL16preVFP;
    std::string jec_tag_UL16postVFP, jec_ver_UL16postVFP;
    std::string jec_tag_UL17, jec_ver_UL17;
    std::string jec_tag_UL18, jec_ver_UL18;
    std::string jec_jet_coll;
};

