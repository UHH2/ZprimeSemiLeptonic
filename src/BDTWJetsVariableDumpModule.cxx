#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/TopPtReweight.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/DileptonHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/EffyTTbarRECOHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/SF_elec.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_ttagging.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_WjetsREWGT.h>
#include <UHH2/ZprimeSemiLeptonic/include/jacobi_eigenvalue.h>
#include <TMVA/Tools.h>
#include <TMVA/Reader.h>
#include <TMVA/MethodCuts.h>




class VariableDumpModule: public ModuleBASE{
    
public:
    explicit VariableDumpModule(uhh2::Context&);
    virtual bool process(uhh2::Event&) override;
    
protected:
    enum lepton {muon, elec};
    lepton channel_;
    // selections    
    std::unique_ptr<uhh2::Selection> jet2_sel;
    std::unique_ptr<uhh2::Selection> jet1_sel;
    std::unique_ptr<uhh2::Selection> met_sel;
    std::unique_ptr<uhh2::Selection> htlep_sel;
    std::unique_ptr<uhh2::Selection> ttagevt_sel;
    std::unique_ptr<uhh2::Selection> topleppt_sel;
    std::unique_ptr<uhh2::Selection> chi2_sel;
    
    // ttbar reconstruction
    std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
    std::unique_ptr<uhh2::AnalysisModule> reco_primlep;
    
    std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag0;
    std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag1;
    std::unique_ptr<Chi2Discriminator>     ttbar_chi2__ttag0;
    std::unique_ptr<Chi2DiscriminatorTTAG> ttbar_chi2__ttag1;
    
    uhh2::Event::Handle<TTbarGen> h_ttbar_gen;
    uhh2::Event::Handle<std::vector<ReconstructionHypothesis> > h_ttbar_hyps;
    
    // ttbar reco hyp
    Event::Handle<float>          h_rec_chi2;
    Event::Handle<TLorentzVector> h_rec_tlep;
    Event::Handle<TLorentzVector> h_rec_thad;
    //
    
    JetId btag_ID_;
    CSVBTag::wp b_working_point;
    std::unique_ptr<Hists> h_btagMCeffi;
    
    bool use_ttagging_;
    TopJetId ttag_ID_;
    float    ttag_minDR_jet_;

    
    int it_num;
    int rot_num;
    
    
    Event::Handle<float>          h_s11;                //1
    Event::Handle<float>          h_s12;                //2
    Event::Handle<float>          h_s13;                //3
    Event::Handle<float>          h_s22;                //4
    Event::Handle<float>          h_s23;                //5
    Event::Handle<float>          h_s33;                //6
    Event::Handle<float>        h_aplanarity;           //7
    Event::Handle<float>        h_sphericity;           //8
    Event::Handle<float>    h_jet1_pt;                 //9
     Event::Handle<float>    h_jet2_pt;                 //10
     Event::Handle<float>    h_lep1__pTrel_jet_norm;     //11
     Event::Handle<float>    h_ht_met_lep_norm;          //12
     Event::Handle<float>    h_jet1_csv;                //13
     Event::Handle<float>    h_jet2_csv;                //14
     Event::Handle<float>    h_DRpt;                     //15
     Event::Handle<int>      h_njets;                    //16
     Event::Handle<float>    h_jet1_m;                  //17
     Event::Handle<float>    h_jet2_m;                  //18
     Event::Handle<float>    h_lep1__minDR_norm;   //19


};



VariableDumpModule::VariableDumpModule(uhh2::Context& ctx){
    
    //// CONFIGURATION
    
    const std::string& channel = ctx.get("channel", "");
    if     (channel == "muon") channel_ = muon;
    else if(channel == "elec") channel_ = elec;
    else {
        
        std::string log("VariableDumpModule -- ");
        log += "VariableDumpModule -- invalid argument for 'channel' key in xml file (must be 'muon' or 'elec'): \""+channel+"\"";
        
        throw std::runtime_error(log);
    }


    float jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);
    bool topleppt_cut(false);
    if(channel_ == muon){
        
       
        jet1_pt  = 150.;
        jet2_pt  =  50.;
        
        MET      =  50.;
        HT_lep   =  150.;
        topleppt_cut = false;
        
    }
    else if(channel_ == elec){
        
       
        jet1_pt  = 170.;
        jet2_pt  =  70.;
        
        MET      =  80.;
        HT_lep   =  150.;
        topleppt_cut = false;
        
    }

    
    jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
    jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
    met_sel  .reset(new METCut  (MET   , uhh2::infinity));
    htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));
    
    
    /* b-tagging */
    const std::string& btag_wp = ctx.get("btag_wp");
    
    if     (btag_wp == "CSVL") btag_ID_ = CSVBTag(CSVBTag::WP_LOOSE);
    else if(btag_wp == "CSVM") btag_ID_ = CSVBTag(CSVBTag::WP_MEDIUM);
    else if(btag_wp == "CSVT") btag_ID_ = CSVBTag(CSVBTag::WP_TIGHT);
    
    if     (btag_wp == "CSVL") b_working_point = CSVBTag::WP_LOOSE;
    else if(btag_wp == "CSVM") b_working_point = CSVBTag::WP_MEDIUM;
    else if(btag_wp == "CSVT") b_working_point = CSVBTag::WP_TIGHT;
    
    h_btagMCeffi.reset(new BTagMCEfficiencyHists(ctx,"chi2__BTAG",b_working_point));
    
    /*************/
    
    /* t-tagging */
    const std::string& ttag_wp = ctx.get("ttag_wp");
    
    ttag_ID_ = TopTagID_SoftDrop(ttag_wp);
    ttag_minDR_jet_ = 1.2;
    
    ttagevt_sel.reset(new TopTagEventSelection(ttag_ID_, ttag_minDR_jet_));
    /*************/
    
    //// TTBAR KINEMATICAL RECO
    
    const std::string ttbar_gen_label ("ttbargen");
    const std::string ttbar_hyps_label("TTbarReconstruction");
    const std::string ttbar_chi2_label("Chi2");
    
    ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));
    h_ttbar_gen = ctx.get_handle<TTbarGen>   (ttbar_gen_label);
    
    reco_primlep.reset(new PrimaryLepton(ctx));
    
    ttbar_reco__ttag0.reset(new HighMassTTbarReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label));
    ttbar_reco__ttag1.reset(new        TopTagReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label, ttag_ID_, ttag_minDR_jet_));
    
    ttbar_chi2__ttag0.reset(new Chi2Discriminator(ctx, ttbar_hyps_label));
    ttbar_chi2__ttag0->set_Mtlep_mean (175.);
    ttbar_chi2__ttag0->set_Mtlep_sigma( 19.);
    ttbar_chi2__ttag0->set_Mthad_mean (177.);
    ttbar_chi2__ttag0->set_Mthad_sigma( 16.);
    
    ttbar_chi2__ttag1.reset(new Chi2DiscriminatorTTAG(ctx, ttbar_hyps_label));
    ttbar_chi2__ttag1->set_Mtlep_mean (175.);
    ttbar_chi2__ttag1->set_Mtlep_sigma( 19.);
    ttbar_chi2__ttag1->set_Mthad_mean (173.);
    ttbar_chi2__ttag1->set_Mthad_sigma( 15.);
    ttbar_chi2__ttag1->use_subjet_mass(false);
    
    h_ttbar_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis> >(ttbar_hyps_label);
    ////  ////
    
    if(topleppt_cut){
        
        if     (channel_ == elec) topleppt_sel.reset(new LeptonicTopPtCut(ctx, 140., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label));
        else if(channel_ == muon) topleppt_sel.reset(new uhh2::AndSelection(ctx));
    }
    else topleppt_sel.reset(new uhh2::AndSelection(ctx));
    
    chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., 30., ttbar_hyps_label, ttbar_chi2_label));

    
    ctx.undeclare_all_event_output();
    
    //BDT Dump variables
    
    h_jet1_pt          = ctx.declare_event_output<float>("jet1_pt");  //1
    h_jet2_pt          = ctx.declare_event_output<float>("jet2_pt");  //2
    h_ht_met_lep_norm   = ctx.declare_event_output<float>("ht_met_lep_norm"); //3
    h_jet1_csv         = ctx.declare_event_output<float>("jet1_csv"); //4
    h_jet2_csv         = ctx.declare_event_output<float>("jet2_csv");//5
    h_njets             = ctx.declare_event_output<int> ("njets");///6
    h_DRpt              = ctx.declare_event_output<float>("DRpt"); //7
    h_lep1__pTrel_jet_norm = ctx.declare_event_output<float>("lep1__pTrel_jet_norm"); //8
    h_jet1_m         = ctx.declare_event_output<float>("jet1_m"); //9
    h_jet2_m        = ctx.declare_event_output<float>("jet2_m"); //10
    h_s11             = ctx.declare_event_output<float>("s11"); //11
    h_s12             = ctx.declare_event_output<float>("s12"); //12
    h_s13             = ctx.declare_event_output<float>("s13"); //13
    h_s22             = ctx.declare_event_output<float>("s22"); //14
    h_s23             = ctx.declare_event_output<float>("s23"); //15
    h_s33             = ctx.declare_event_output<float>("s33"); //16
    h_sphericity      = ctx.declare_event_output<float>("sphericity"); //17
    h_aplanarity      = ctx.declare_event_output<float>("aplanarity"); //18
    h_lep1__minDR_norm = ctx.declare_event_output<float>("lep1__minDR_jet");//19

}


bool VariableDumpModule::process(uhh2::Event& event){
    
    //set dummy initial values
    
    event.set(h_s11,0); //1
    event.set(h_s12,0); //2
    event.set(h_s13,0); //3
    event.set(h_s22,0); //4
    event.set(h_s23,0); //5
    event.set(h_s33,0); //6
    event.set(h_aplanarity,0); //7
    event.set(h_sphericity,0); //8
    event.set(h_jet1_pt,0); //9
    event.set(h_jet1_m,0);  //10
    event.set(h_jet1_csv,0);  //11
    event.set(h_jet2_pt,0);  //12
    event.set(h_jet2_m,0);  //13
    event.set(h_jet2_csv,0);  //15
    event.set(h_njets,0); //16
    event.set(h_ht_met_lep_norm,0);  //17
    event.set(h_lep1__pTrel_jet_norm,0); //18
    event.set(h_lep1__minDR_norm,0); //19
    
    // OF lepton veto
    bool pass_lepV(0);
    if     (channel_ == muon) pass_lepV = ((event.electrons->size() == 0));
    else if(channel_ == elec) pass_lepV = ((event.muons    ->size() == 0));
    if(!pass_lepV) return false;
    //
    
    // lepton multiplicity
    int lepN(-1);
    if     (channel_ == muon) lepN = int(event.muons    ->size());
    else if(channel_ == elec) lepN = int(event.electrons->size());
    if(!(lepN >= 1)) return false;
    //
    
    // pt-leading lepton selection
    const Particle* lep1 = leading_lepton(event);
    if(!(lep1->pt() >50)) return false;
    //
    
    ////
    
    //// JET selection
    
    /* 2nd AK4 jet selection */
    const bool pass_jet2 = jet2_sel->passes(event);
    if(!pass_jet2) return false;
    if(!lepN == 1) return false;
    
    /* 1st AK4 jet selection */
    const bool pass_jet1 = jet1_sel->passes(event);
    if(!pass_jet1) return false;
   
    /*Passes loose MET cut*/
    const bool pass_met = met_sel->passes(event);
    if(!pass_met) return false;
    
    /*Passes loose HTlep cut*/
    const bool pass_htlep = htlep_sel->passes(event);
    if(!pass_htlep)return false;
    
    float lep1__minDR_jet(-1.), lep1__pTrel_jet(-1.);
     TLorentzVector lep1__p4(0.,0.,0.,0.);
    if(channel_ == muon){

        lep1__minDR_jet = ((Muon*) lep1)->get_tag(Muon::twodcut_dRmin);
        lep1__pTrel_jet = ((Muon*) lep1)->get_tag(Muon::twodcut_pTrel);
        lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());
    }
    else if(channel_ == elec){
        
        lep1__minDR_jet = ((Electron*) lep1)->get_tag(Electron::twodcut_dRmin);
        lep1__pTrel_jet = ((Electron*) lep1)->get_tag(Electron::twodcut_pTrel);
        lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());   
    }
    
    //// TTBAR KIN RECO
    
    /* TOPTAG-EVENT boolean */
    const bool pass_ttagevt = ttagevt_sel->passes(event) && use_ttagging_;
    
    const std::string ttag_posx = (pass_ttagevt ? "t1" : "t0");
    /************************/
    
    reco_primlep->process(event);
    
    if(!pass_ttagevt){ ttbar_reco__ttag0->process(event); ttbar_chi2__ttag0->process(event); }
    else             { ttbar_reco__ttag1->process(event); ttbar_chi2__ttag1->process(event); }
    
    std::vector<ReconstructionHypothesis>& ttbar_hyps = event.get(h_ttbar_hyps);
    
    ////
    
    //// LEPTONIC-TOP pt selection
    const bool pass_topleppt = topleppt_sel->passes(event);
    if(!pass_topleppt) return false;

    ////
    
    //// FINAL selection
    
    /* ttagN counters */
    int ttagN(0);
    for(const auto& tj : *event.topjets) if(ttag_ID_(tj, event)) ++ttagN;
    
    
    /* btagN counters */
    int jetbtagN(0), subjbtagN(0);
    
    if(!pass_ttagevt){
        
        for(const auto& j : *event.jets) if(btag_ID_(j, event)) ++jetbtagN;
    }
    else {
        
        const ReconstructionHypothesis* ttbar_hyp = get_best_hypothesis(ttbar_hyps, "Chi2");
        
        const TopJet* thad = ttbar_hyp->tophad_topjet_ptr();
        
        for(const auto& j : thad->subjets()) if(btag_ID_(j, event)) ++subjbtagN;
        
        for(const auto& j : *event.jets){
            
            if(!(uhh2::deltaR(*thad, j) > ttag_minDR_jet_)) continue;
            if(btag_ID_(j, event)) ++jetbtagN;
        }
    }
    
    const int btagN = jetbtagN + subjbtagN;
    
    // ttbar reco hyp
    const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");
    if(!rec_ttbar) throw std::runtime_error("TTbarLJAnalysisLiteModule::process -- logic error: ttbar reconstruction hypothesis (\"get_best_hypothesis\", discr=Chi2) not found");
    const float rec_chi2 = rec_ttbar->discriminator("Chi2");

    
  TLorentzVector jet1__p4(event.jets->at(0).v4().Px(), event.jets->at(0).v4().Py(), event.jets->at(0).v4().Pz(), event.jets->at(0).v4().E());
  TLorentzVector jet2__p4(event.jets->at(1).v4().Px(), event.jets->at(1).v4().Py(), event.jets->at(1).v4().Pz(), event.jets->at(1).v4().E());
    ///////////SAVE VARIABLES///////////////////
    
    float s11 = 0.0;
    float s12 = 0.0;
    float s13 = 0.0;
    float s22 = 0.0;
    float s23 = 0.0;
    float s33 = 0.0;
    float s11d = 0.0;
    float s12d = 0.0;
    float s13d = 0.0;
    float s22d = 0.0;
    float s23d = 0.0;
    float s33d =0.0;
    float mag = 0.0;
    float ht=0.0;
    for (auto jet : *event.jets){
        if (jet.pt()>30.0){
            ht+=jet.pt();
            s11d += jet.v4().Px()*jet.v4().Px();
            mag  += (jet.v4().Px()*jet.v4().Px()+jet.v4().Py()*jet.v4().Py()+jet.v4().Pz()*jet.v4().Pz());
            s22d += jet.v4().Py()*jet.v4().Py();
            s12d += jet.v4().Px()*jet.v4().Py();
            s13d += jet.v4().Px()*jet.v4().Pz();
            s23d += jet.v4().Py()*jet.v4().Pz();
            s33d += jet.v4().Pz()*jet.v4().Pz();
        }
    }
    s11 =  s11d/mag;
    s12 =  s12d/mag;
    s13 =  s13d/mag;
    s22 =  s22d/mag;
    s23 =  s23d/mag;
    s33 =  s33d/mag;
    const float j1CSV    = event.jets->at(0).btag_combinedSecondaryVertex();
    const float j2CSV    = event.jets->at(1).btag_combinedSecondaryVertex();
    if (abs(j1CSV)>1.2) return false;
    if (abs(j2CSV)>1.2) return false;
    const float njets    = event.jets->size();
    const float j1M      = jet1__p4.M();
    const float j2M      = jet2__p4.M();
    //std::cout << ht << std::endl; 
    const float jet1pt_norm = jet1__p4.Pt()/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
    const float jet2pt_norm = jet2__p4.Pt()/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
    const float ptrel_norm =  lep1__pTrel_jet/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
    const float htmetlep_norm = (ht+lep1__p4.Pt()+event.met->pt())/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
    //std::cout << htmetlep_norm<< std::endl;
    const float DRpt_norm = lep1__minDR_jet*jet1__p4.Pt()/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());


    event.set(h_DRpt, DRpt_norm);//1
     event.set(h_ht_met_lep_norm, htmetlep_norm);//2
     event.set(h_lep1__minDR_norm, lep1__minDR_jet);//3
     event.set(h_lep1__pTrel_jet_norm, ptrel_norm);//4
     event.set(h_jet1_pt,jet1pt_norm);//5
     event.set(h_jet2_pt,jet2pt_norm);//6
     event.set(h_jet1_csv, j1CSV );//7
     event.set(h_jet2_csv, j2CSV );//8
     event.set(h_njets, njets); //9
     event.set(h_jet1_m,  j1M/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M())); //10
     event.set(h_jet2_m,  j2M/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M())); //11

     # define N 3
    double d[N];
    double sph_mat[N*N] = {
        s11, s12, s13,
        s12, s22, s23,
        s13, s23, s33
    };
    double v[N*N];
    int n = 3;
    int it_max = 100;
    jacobi_eigenvalue( n, sph_mat, it_max, v, d, it_num, rot_num);
    const float sphericity = 1.5*(d[1]+d[2]);
    const float aplanarity = 1.5*d[0];
    event.set(h_aplanarity, aplanarity); //12
    event.set(h_sphericity, sphericity); //13
    event.set(h_s11,s11); //14
    event.set(h_s12,s12); //15
    event.set(h_s13,s13); //16
    event.set(h_s22,s22); //17
    event.set(h_s23,s23); //18
    event.set(h_s33,s33); //19

    

     return true;
    
}

UHH2_REGISTER_ANALYSIS_MODULE(VariableDumpModule)
