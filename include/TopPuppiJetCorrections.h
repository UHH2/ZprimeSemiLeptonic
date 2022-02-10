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

class TopPuppiJetCorrections: public uhh2::AnalysisModule {
public:
    TopPuppiJetCorrections();

    virtual bool process(uhh2::Event & event) override;
    void init(uhh2::Context & ctx);

private:
    void fail_if_init() const;

    std::unique_ptr<YearSwitcher> tpuppijet_corrector_MC, tpuppijet_subjet_corrector_MC, tpuppijet_JLC_MC;
    std::unique_ptr<YearSwitcher> tpuppijet_corrector_data, tpuppijet_subjet_corrector_data, tpuppijet_JLC_data;
    std::shared_ptr<RunSwitcher> tpuppijec_switcher_UL16preVFP,tpuppijec_switcher_UL16postVFP, tpuppijec_switcher_UL17, tpuppijec_switcher_UL18;
    std::shared_ptr<RunSwitcher> tpuppijec_subjet_switcher_UL16preVFP, tpuppijec_subjet_switcher_UL16postVFP, tpuppijec_subjet_switcher_UL17, tpuppijec_subjet_switcher_UL18; 
    std::shared_ptr<RunSwitcher> tpuppijec_JLC_switcher_UL16preVFP, tpuppijec_JLC_switcher_UL16postVFP, tpuppijec_JLC_switcher_UL17, tpuppijec_JLC_switcher_UL18; 
    std::unique_ptr<GenericJetResolutionSmearer> tpuppijet_resolution_smearer;

    bool is_mc, is_data;
    bool init_done = false;

    Year year;

    // Parameters for JEC & JLC sets
    std::string tpuppijec_tag_UL16preVFP, tpuppijec_ver_UL16preVFP;
    std::string tpuppijec_tag_UL16postVFP, tpuppijec_ver_UL16postVFP;
    std::string tpuppijec_tag_UL17, tpuppijec_ver_UL17;
    std::string tpuppijec_tag_UL18, tpuppijec_ver_UL18;
    std::string tpuppijec_tjet_coll, tpuppijec_subjet_coll;
};

