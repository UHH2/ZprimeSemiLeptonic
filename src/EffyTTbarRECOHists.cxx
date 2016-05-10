#include <UHH2/ZprimeSemiLeptonic/include/EffyTTbarRECOHists.h>

#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

EffyTTbarRECOHists::EffyTTbarRECOHists(uhh2::Context& ctx, const std::string& dir, const std::string& ttgen, const std::string& hyps, const std::string& disc):
  HistsBASE(ctx, dir) {

  h_ttbar_gen  = ctx.get_handle<TTbarGen>(ttgen);
  h_ttbar_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis> >(hyps);
  disc_name_ = disc;

  init();
}

void EffyTTbarRECOHists::init(){

  book_TH1F("gen_ttbar__M" , 600, 0, 6000);
  book_TH1F("gen_ttbar__pt", 300, 0, 3000);

  book_TH1F("gen_thad__M" , 360, 0, 360);
  book_TH1F("gen_thad__pt", 180, 0, 1800);

  book_TH1F("gen_tlep__M" , 360, 0, 360);
  book_TH1F("gen_tlep__pt", 180, 0, 1800);
  book_TH1F("gen_tlep__px", 120, -1200, 1200);
  book_TH1F("gen_tlep__py", 120, -1200, 1200);
  book_TH1F("gen_tlep__pz", 120, -1200, 1200);

  book_TH1F("gen_tops__DR" , 60, 0, 6);
  book_TH1F("gen_tops__Dpt", 180, -450, 450);

  book_TH1F("gen_Wlep__M" , 120, 74, 86);
  book_TH1F("gen_Wlep__Mt", 180, 0, 180);
  book_TH1F("gen_Wlep__pt", 180, 0, 1800);
  book_TH1F("gen_Wlep__px", 120, -1200, 1200);
  book_TH1F("gen_Wlep__py", 120, -1200, 1200);
  book_TH1F("gen_Wlep__pz", 120, -1200, 1200);

  book_TH1F("gen_lep__pt"       , 120, 0, 1200);
  book_TH1F("gen_lep__eta"      , 60, -6, 6);
  book_TH1F("gen_lep__phi"      , 60, -3.15, 3.15);
  book_TH1F("gen_lep__cosThetaX", 40, -1, 1);

  book_TH1F("gen_neu__pt"       , 120, 0, 1200);
  book_TH1F("gen_neu__phi"      , 60, -3.15, 3.15);
  book_TH1F("gen_neu__px"       , 120, -600, 600);
  book_TH1F("gen_neu__py"       , 120, -600, 600);
  book_TH1F("gen_neu__pz"       , 120, -600, 600);
  book_TH1F("gen_neu__cosThetaX", 40, -1, 1);

  book_TH1F("gen_blep__pt"       , 120, 0, 1200);
  book_TH1F("gen_blep__eta"      , 60, -6, 6);
  book_TH1F("gen_blep__phi"      , 60, -3.15, 3.15);
  book_TH1F("gen_blep__px"       , 120, -1200, 1200);
  book_TH1F("gen_blep__py"       , 120, -1200, 1200);
  book_TH1F("gen_blep__pz"       , 120, -1200, 1200);
  book_TH1F("gen_blep__cosThetaX", 40, -1, 1);

  book_TH1F("rec_chi2", 200, 0, 600);
  book_TH2F("rec_chi2__VS__rec_ttbar__M", 300, 0, 600, 600, 0, 6000);

  book_TH1F("rec_ttbar__M"          , 300, 0, 6000);
  book_TH1F("rec_ttbar__pt"         , 150, 0, 3000);
  book_TH1F("rec_ttbar__gen_DM"     , 120, -600, 600);
  book_TH1F("rec_ttbar__gen_Dpt"    , 120, -600, 600);
  book_TH1F("rec_ttbar__gen_DM_pct" , 120, -1.2, 1.2);
  book_TH1F("rec_ttbar__gen_Dpt_pct", 120, -1.2, 1.2);

  book_TH1F("rec_thad__M"            , 360, 0, 360);
  book_TH1F("rec_thad__Mgro"         , 360, 0, 360);
  book_TH1F("rec_thad__Mpru"         , 360, 0, 360);
  book_TH1F("rec_thad__Msdp"         , 360, 0, 360);
  book_TH1F("rec_thad__pt"           , 180, 0, 1800);
  book_TH1F("rec_thad__jetN"         , 7, 0, 7);
  book_TH1F("rec_thad__gen_DM"       , 240, -120, 120);
  book_TH1F("rec_thad__gen_DMgro"    , 240, -120, 120);
  book_TH1F("rec_thad__gen_DMpru"    , 240, -120, 120);
  book_TH1F("rec_thad__gen_DMsdp"    , 240, -120, 120);
  book_TH1F("rec_thad__gen_Dpt"      , 120, -600, 600);
  book_TH1F("rec_thad__gen_Deta"     , 120, -1.2, 1.2);
  book_TH1F("rec_thad__gen_Dphi"     , 60, 0, 3.15);
  book_TH1F("rec_thad__gen_DR"       , 60, 0, 3);
  book_TH1F("rec_thad__gen_DM_pct"   , 120, -1.2, 1.2);
  book_TH1F("rec_thad__gen_DMgro_pct", 120, -1.2, 1.2);
  book_TH1F("rec_thad__gen_DMpru_pct", 120, -1.2, 1.2);
  book_TH1F("rec_thad__gen_DMsdp_pct", 120, -1.2, 1.2);
  book_TH1F("rec_thad__gen_Dpt_pct"  , 120, -1.2, 1.2);

  book_TH1F("rec_tlep__M"          , 360, 0, 360);
  book_TH1F("rec_tlep__pt"         , 180, 0, 1800);
  book_TH1F("rec_tlep__px"         , 120, -1200, 1200);
  book_TH1F("rec_tlep__py"         , 120, -1200, 1200);
  book_TH1F("rec_tlep__pz"         , 120, -1200, 1200);
  book_TH1F("rec_tlep__jetN"       , 4, 0, 4);
  book_TH1F("rec_tlep__gen_DM"     , 240, -120, 120);
  book_TH1F("rec_tlep__gen_Dpt"    , 120, -600, 600);
  book_TH1F("rec_tlep__gen_Dpx"    , 120, -600, 600);
  book_TH1F("rec_tlep__gen_Dpy"    , 120, -600, 600);
  book_TH1F("rec_tlep__gen_Dpz"    , 120, -600, 600);
  book_TH1F("rec_tlep__gen_Deta"   , 120, -1.2, 1.2);
  book_TH1F("rec_tlep__gen_Dphi"   , 60, 0, 3.15);
  book_TH1F("rec_tlep__gen_DR"     , 60, 0, 3);
  book_TH1F("rec_tlep__gen_DM_pct" , 120, -1.2, 1.2);
  book_TH1F("rec_tlep__gen_Dpt_pct", 120, -1.2, 1.2);
  book_TH1F("rec_tlep__gen_Dpx_pct", 120, -1.2, 1.2);
  book_TH1F("rec_tlep__gen_Dpy_pct", 120, -1.2, 1.2);
  book_TH1F("rec_tlep__gen_Dpz_pct", 120, -1.2, 1.2);

  book_TH1F("rec_tops__DR" , 60, 0, 6);
  book_TH1F("rec_tops__Dpt", 180, -450, 450);

  book_TH1F("rec_Wlep__M"          , 360, 0, 360);
  book_TH1F("rec_Wlep__Mt"         , 360, 0, 360);
  book_TH1F("rec_Wlep__pt"         , 180, 0, 1800);
  book_TH1F("rec_Wlep__px"         , 120, -1200, 1200);
  book_TH1F("rec_Wlep__py"         , 120, -1200, 1200);
  book_TH1F("rec_Wlep__pz"         , 120, -1200, 1200);
  book_TH1F("rec_Wlep__gen_DM"     , 240, -120, 120);
  book_TH1F("rec_Wlep__gen_DMt"    , 240, -120, 120);
  book_TH1F("rec_Wlep__gen_Dpt"    , 120, -600, 600);
  book_TH1F("rec_Wlep__gen_Dpx"    , 120, -600, 600);
  book_TH1F("rec_Wlep__gen_Dpy"    , 120, -600, 600);
  book_TH1F("rec_Wlep__gen_Dpz"    , 120, -600, 600);
  book_TH1F("rec_Wlep__gen_DM_pct" , 120, -1.2, 1.2);
  book_TH1F("rec_Wlep__gen_DMt_pct", 120, -1.2, 1.2);
  book_TH1F("rec_Wlep__gen_Dpt_pct", 120, -1.2, 1.2);
  book_TH1F("rec_Wlep__gen_Dpx_pct", 120, -1.2, 1.2);
  book_TH1F("rec_Wlep__gen_Dpy_pct", 120, -1.2, 1.2);
  book_TH1F("rec_Wlep__gen_Dpz_pct", 120, -1.2, 1.2);

  book_TH1F("rec_lep__pt"            , 120, 0, 1200);
  book_TH1F("rec_lep__eta"           , 60, -6, 6);
  book_TH1F("rec_lep__phi"           , 60, -3.15, 3.15);
  book_TH1F("rec_lep__cosThetaX"     , 40, -1, 1);
  book_TH1F("rec_lep__gen_DR"        , 60, 0, .06);
  book_TH1F("rec_lep__gen_Dpt"       , 60, -150, 150);
  book_TH1F("rec_lep__gen_Deta"      , 60, -.06, .06);
  book_TH1F("rec_lep__gen_Dphi"      , 60, 0., .06);
  book_TH1F("rec_lep__gen_DcosThetaX", 36, -1.8, 1.8);
  book_TH1F("rec_lep__gen_Dpt_pct"   , 60, -.6, .6);
  book_TH1F("rec_lep__gen_Deta_pct"  , 60, -.06, .06);

  book_TH1F("rec_neu__pt"            , 120, 0, 1200);
  book_TH1F("rec_neu__phi"           , 60, -3.15, 3.15);
  book_TH1F("rec_neu__px"            , 120, -600, 600);
  book_TH1F("rec_neu__py"            , 120, -600, 600);
  book_TH1F("rec_neu__pz"            , 120, -600, 600);
  book_TH1F("rec_neu__cosThetaX"     , 40, -1, 1);
  book_TH1F("rec_neu__gen_DR"        , 60, 0, 6);
  book_TH1F("rec_neu__gen_Dpt"       , 120, -600, 600);
  book_TH1F("rec_neu__gen_Dphi"      , 60, 0., 3.15);
  book_TH1F("rec_neu__gen_Dpx"       , 120, -600, 600);
  book_TH1F("rec_neu__gen_Dpy"       , 120, -600, 600);
  book_TH1F("rec_neu__gen_Dpz"       , 120, -600, 600);
  book_TH1F("rec_neu__gen_DcosThetaX", 36, -1.8, 1.8);
  book_TH1F("rec_neu__gen_Dpt_pct"   , 120, -1.2, 1.2);
  book_TH1F("rec_neu__gen_Dpx_pct"   , 120, -1.2, 1.2);
  book_TH1F("rec_neu__gen_Dpy_pct"   , 120, -1.2, 1.2);
  book_TH1F("rec_neu__gen_Dpz_pct"   , 120, -1.2, 1.2);

  book_TH1F("rec_blep__pt"            , 120, 0, 1200);
  book_TH1F("rec_blep__eta"           , 60, -6, 6);
  book_TH1F("rec_blep__phi"           , 60, -3.15, 3.15);
  book_TH1F("rec_blep__px"            , 120, -1200, 1200);
  book_TH1F("rec_blep__py"            , 120, -1200, 1200);
  book_TH1F("rec_blep__pz"            , 120, -1200, 1200);
  book_TH1F("rec_blep__CSV"           , 100, 0, 1);
  book_TH1F("rec_blep__cosThetaX"     , 40, -1, 1);
  book_TH1F("rec_blep__gen_DR"        , 60, 0, 3);
  book_TH1F("rec_blep__gen_Dpt"       , 60, -300, 300);
  book_TH1F("rec_blep__gen_Deta"      , 60, -.6, .6);
  book_TH1F("rec_blep__gen_Dphi"      , 60, 0., 3.15);
  book_TH1F("rec_blep__gen_Dpx"       , 60, -300, 300);
  book_TH1F("rec_blep__gen_Dpy"       , 60, -300, 300);
  book_TH1F("rec_blep__gen_Dpz"       , 60, -300, 300);
  book_TH1F("rec_blep__gen_DcosThetaX", 36, -1.8, 1.8);
  book_TH1F("rec_blep__gen_Dpt_pct"   , 60, -1.2, 1.2);
  book_TH1F("rec_blep__gen_Deta_pct"  , 60, -.3, .3);
  book_TH1F("rec_blep__gen_Dpx_pct"   , 60, -1.2, 1.2);
  book_TH1F("rec_blep__gen_Dpy_pct"   , 60, -1.2, 1.2);
  book_TH1F("rec_blep__gen_Dpz_pct"   , 60, -1.2, 1.2);

  book_TH1F("rec_lep__cosThetaX__X__rec_blep__cosThetaX", 40, -1, 1);
  book_TH1F("rec_lep__cosThetaX__X__rec_neu__cosThetaX" , 40, -1, 1);
  book_TH1F("rec_neu__cosThetaX__X__rec_blep__cosThetaX", 40, -1, 1);

  book_TH1F("rec_top__cosThetaCS", 40, -1, 1);

  book_TH1F("deltaR__gen_lep__gen_neu"   , 60, 0., 6.);
  book_TH1F("deltaPhi__gen_lep__gen_neu" , 60, 0., 3.15);
  book_TH1F("deltaR__gen_blep__gen_neu"  , 60, 0., 6.);
  book_TH1F("deltaPhi__gen_blep__gen_neu", 60, 0., 3.15);
  book_TH1F("deltaR__gen_lep__gen_blep"  , 60, 0., 6.);
  book_TH1F("deltaR__gen_lep__gen_thad"  , 60, 0., 6.);
  book_TH1F("deltaRsum__gen_thad_jets"   , 60, 0., 6.);

  book_TH1F("deltaR__rec_lep__rec_neu"   , 60, 0., 6.);
  book_TH1F("deltaPhi__rec_lep__rec_neu" , 60, 0., 3.15);
  book_TH1F("deltaR__rec_blep__rec_neu"  , 60, 0., 6.);
  book_TH1F("deltaPhi__rec_blep__rec_neu", 60, 0., 3.15);
  book_TH1F("deltaR__rec_lep__rec_blep"  , 60, 0., 6.);
  book_TH1F("deltaR__rec_lep__rec_thad"  , 60, 0., 6.);
  book_TH1F("deltaRsum__rec_thad_jets"   , 60, 0., 6.);
}

void EffyTTbarRECOHists::fill(const uhh2::Event& evt){

  const float weight(evt.weight);

  const TTbarGen* ttbargen(0);
  if(!evt.isRealData){

    const auto& ttgen = evt.get(h_ttbar_gen);
    ttbargen = &ttgen;
  }

  const ReconstructionHypothesis* hyp(0);
  float hyp_val(0.);
  if(evt.is_valid(h_ttbar_hyps)){

    const auto& ttbar_hyps = evt.get(h_ttbar_hyps);

    hyp = get_best_hypothesis(ttbar_hyps, disc_name_);
    if(!hyp) throw std::runtime_error("EffyTTbarRECOHists::fill -- null pointer to ReconstructionHypothesis object (from \"get_best_hypothesis\")");

    hyp_val = hyp->discriminator(disc_name_);
  }

  fill(hyp, hyp_val, ttbargen, weight);

  return;
}

void EffyTTbarRECOHists::fill(const ReconstructionHypothesis* hyp, const float hyp_val, const TTbarGen* ttgen, const double weight){

  bool ttljets(false);

  float gen_ttbar_M(-1.), gen_ttbar_pt(-1.);
  float gen_thad_M(-1.), gen_thad_pt(-1.);
  float gen_tlep_M(-1.), gen_tlep_pt(-1.), gen_tlep_px(-1.), gen_tlep_py(-1.), gen_tlep_pz(-1.);
  float gen_Wlep_M(-1.), gen_Wlep_pt(-1.), gen_Wlep_px(-1.), gen_Wlep_py(-1.), gen_Wlep_pz(-1.), gen_Wlep_Mt(-1.);
  float gen_lep_pt(-1.), gen_lep_eta(-1.), gen_lep_phi(-1.), gen_lep_cosThetaX(-10.);
  float gen_neu_pt(-1.), gen_neu_phi(-1.), gen_neu_px(-1.), gen_neu_py(-1.), gen_neu_pz(-1.), gen_neu_cosThetaX(-10.);
  float gen_blep_pt(-1.), gen_blep_eta(-1.), gen_blep_phi(-1.), gen_blep_px(-1.), gen_blep_py(-1.), gen_blep_pz(-1.), gen_blep_cosThetaX(-10.);

  if(ttgen){

    ttljets = (ttgen->DecayChannel() == TTbarGen::e_muhad || ttgen->DecayChannel() == TTbarGen::e_ehad);

    LorentzVector gen_ttbar = ttgen->Top().v4()+ttgen->Antitop().v4();

    gen_ttbar_M  = gen_ttbar.M();
    gen_ttbar_pt = gen_ttbar.Pt();
    H1("gen_ttbar__M") ->Fill(gen_ttbar_M , weight);
    H1("gen_ttbar__pt")->Fill(gen_ttbar_pt, weight);

    if(ttljets){

      gen_thad_M  = ttgen->TopHad().v4().M();
      gen_thad_pt = ttgen->TopHad().v4().Pt();

      gen_tlep_M  = ttgen->TopLep().v4().M();
      gen_tlep_pt = ttgen->TopLep().v4().Pt();
      gen_tlep_px = ttgen->TopLep().v4().Px();
      gen_tlep_py = ttgen->TopLep().v4().Py();
      gen_tlep_pz = ttgen->TopLep().v4().Pz();

      gen_Wlep_M  = ttgen->WLep().v4().M();
      gen_Wlep_Mt = sqrt(2*ttgen->ChargedLepton().pt()*ttgen->Neutrino().pt()*(1.-cos(delta_phi(ttgen->ChargedLepton().phi(), ttgen->Neutrino().phi()))));
      gen_Wlep_pt = ttgen->WLep().v4().Pt();
      gen_Wlep_px = ttgen->WLep().v4().Px();
      gen_Wlep_py = ttgen->WLep().v4().Py();
      gen_Wlep_pz = ttgen->WLep().v4().Pz();

      gen_lep_pt        = ttgen->ChargedLepton().v4().Pt();
      gen_lep_eta       = ttgen->ChargedLepton().v4().Eta();
      gen_lep_phi       = ttgen->ChargedLepton().v4().Phi();
      gen_lep_cosThetaX = cosThetaX(ttgen->ChargedLepton().v4(), ttgen->TopLep().v4(), gen_ttbar);

      gen_neu_pt        = ttgen->Neutrino().v4().Pt();
      gen_neu_phi       = ttgen->Neutrino().v4().Phi();
      gen_neu_px        = ttgen->Neutrino().v4().Px();
      gen_neu_py        = ttgen->Neutrino().v4().Py();
      gen_neu_pz        = ttgen->Neutrino().v4().Pz();
      gen_neu_cosThetaX = cosThetaX(ttgen->Neutrino().v4(), ttgen->TopLep().v4(), gen_ttbar);

      gen_blep_pt        = ttgen->BLep().v4().Pt();
      gen_blep_eta       = ttgen->BLep().v4().Eta();
      gen_blep_phi       = ttgen->BLep().v4().Phi();
      gen_blep_px        = ttgen->BLep().v4().Px();
      gen_blep_py        = ttgen->BLep().v4().Py();
      gen_blep_pz        = ttgen->BLep().v4().Pz();
      gen_blep_cosThetaX = cosThetaX(ttgen->BLep().v4(), ttgen->TopLep().v4(), gen_ttbar);
      ///

      H1("gen_thad__M") ->Fill(gen_thad_M , weight);
      H1("gen_thad__pt")->Fill(gen_thad_pt, weight);

      H1("gen_tlep__M") ->Fill(gen_tlep_M , weight);
      H1("gen_tlep__pt")->Fill(gen_tlep_pt, weight);
      H1("gen_tlep__px")->Fill(gen_tlep_px, weight);
      H1("gen_tlep__py")->Fill(gen_tlep_py, weight);
      H1("gen_tlep__pz")->Fill(gen_tlep_pz, weight);

      H1("gen_tops__Dpt")->Fill(gen_tlep_pt-gen_thad_pt, weight);
      H1("gen_tops__DR") ->Fill(uhh2::deltaR(ttgen->TopLep(), ttgen->TopHad()), weight);

      H1("gen_Wlep__M") ->Fill(gen_Wlep_M , weight);
      H1("gen_Wlep__Mt")->Fill(gen_Wlep_Mt, weight);
      H1("gen_Wlep__pt")->Fill(gen_Wlep_pt, weight);
      H1("gen_Wlep__px")->Fill(gen_Wlep_px, weight);
      H1("gen_Wlep__py")->Fill(gen_Wlep_py, weight);
      H1("gen_Wlep__pz")->Fill(gen_Wlep_pz, weight);

      H1("gen_lep__pt")       ->Fill(gen_lep_pt       , weight);
      H1("gen_lep__eta")      ->Fill(gen_lep_eta      , weight);
      H1("gen_lep__phi")      ->Fill(gen_lep_phi      , weight);
      H1("gen_lep__cosThetaX")->Fill(gen_lep_cosThetaX, weight);

      H1("gen_neu__pt")       ->Fill(gen_neu_pt       , weight);
      H1("gen_neu__phi")      ->Fill(gen_neu_phi      , weight);
      H1("gen_neu__px")       ->Fill(gen_neu_px       , weight);
      H1("gen_neu__py")       ->Fill(gen_neu_py       , weight);
      H1("gen_neu__pz")       ->Fill(gen_neu_pz       , weight);
      H1("gen_neu__cosThetaX")->Fill(gen_neu_cosThetaX, weight);

      H1("gen_blep__pt")       ->Fill(gen_blep_pt       , weight);
      H1("gen_blep__eta")      ->Fill(gen_blep_eta      , weight);
      H1("gen_blep__phi")      ->Fill(gen_blep_phi      , weight);
      H1("gen_blep__px")       ->Fill(gen_blep_px       , weight);
      H1("gen_blep__py")       ->Fill(gen_blep_py       , weight);
      H1("gen_blep__pz")       ->Fill(gen_blep_pz       , weight);
      H1("gen_blep__cosThetaX")->Fill(gen_blep_cosThetaX, weight);
    }
  }

  if(hyp){

    // ttbar
    const float rec_ttbar_M ((hyp->top_v4()+hyp->antitop_v4()).M());
    const float rec_ttbar_pt((hyp->top_v4()+hyp->antitop_v4()).Pt());

//!!    const float& hyp_val = hyp->discriminator(hyp_disc);

    H1("rec_chi2")->Fill(hyp_val, weight);
    H2("rec_chi2__VS__rec_ttbar__M")->Fill(hyp_val, rec_ttbar_M, weight);

    H1("rec_ttbar__M")      ->Fill(rec_ttbar_M , weight);
    H1("rec_ttbar__pt")     ->Fill(rec_ttbar_pt, weight);
    H1("rec_ttbar__gen_DM") ->Fill(rec_ttbar_M -gen_ttbar_M , weight);
    H1("rec_ttbar__gen_Dpt")->Fill(rec_ttbar_pt-gen_ttbar_pt, weight);
    if(gen_ttbar_M)  H1("rec_ttbar__gen_DM_pct") ->Fill((rec_ttbar_M -gen_ttbar_M) /fabs(gen_ttbar_M) , weight);
    if(gen_ttbar_pt) H1("rec_ttbar__gen_Dpt_pct")->Fill((rec_ttbar_pt-gen_ttbar_pt)/fabs(gen_ttbar_pt), weight);

    // thad
    float rec_thad_M (hyp->tophad_v4().M());
    float rec_thad_pt(hyp->tophad_v4().Pt());
    H1("rec_thad__M")   ->Fill(rec_thad_M , weight);
    H1("rec_thad__pt")  ->Fill(rec_thad_pt, weight);
    H1("rec_thad__jetN")->Fill(hyp->tophad_jets().size(), weight);
    if(ttljets){
      H1("rec_thad__gen_DM")  ->Fill(rec_thad_M -gen_thad_M , weight);
      H1("rec_thad__gen_Dpt") ->Fill(rec_thad_pt-gen_thad_pt, weight);
      H1("rec_thad__gen_Deta")->Fill(             hyp->tophad_v4().Eta()- ttgen->TopHad().v4().Eta() , weight);
      H1("rec_thad__gen_Dphi")->Fill(delta_phi(   hyp->tophad_v4().Phi(), ttgen->TopHad().v4().Phi()), weight);
      H1("rec_thad__gen_DR")  ->Fill(uhh2::deltaR(hyp->tophad_v4()      , ttgen->TopHad().v4())      , weight);
      if(gen_thad_M)  H1("rec_thad__gen_DM_pct") ->Fill((rec_thad_M -gen_thad_M) /fabs(gen_thad_M) , weight);
      if(gen_thad_pt) H1("rec_thad__gen_Dpt_pct")->Fill((rec_thad_pt-gen_thad_pt)/fabs(gen_thad_pt), weight);
    }

    const TopJet* tjet = hyp->tophad_topjet_ptr();
    if(tjet){

      LorentzVector tjet_subjet_sum;
      for(const auto& subj : tjet->subjets()) tjet_subjet_sum += subj.v4();

      const float rec_thad_Mgro(tjet_subjet_sum.M());
      const float rec_thad_Mpru(tjet->prunedmass());
      const float rec_thad_Msdp(tjet->softdropmass());

      H1("rec_thad__Mgro")->Fill(rec_thad_Mgro, weight);
      H1("rec_thad__Mpru")->Fill(rec_thad_Mpru, weight);
      H1("rec_thad__Msdp")->Fill(rec_thad_Msdp, weight);
      if(ttljets){
        H1("rec_thad__gen_DMgro")->Fill(rec_thad_Mgro-gen_thad_M, weight);
        H1("rec_thad__gen_DMpru")->Fill(rec_thad_Mpru-gen_thad_M, weight);
        H1("rec_thad__gen_DMsdp")->Fill(rec_thad_Msdp-gen_thad_M, weight);
        if(gen_thad_M) H1("rec_thad__gen_DMgro_pct")->Fill((rec_thad_Mgro-gen_thad_M)/fabs(gen_thad_M), weight);
        if(gen_thad_M) H1("rec_thad__gen_DMpru_pct")->Fill((rec_thad_Mpru-gen_thad_M)/fabs(gen_thad_M), weight);
        if(gen_thad_M) H1("rec_thad__gen_DMsdp_pct")->Fill((rec_thad_Msdp-gen_thad_M)/fabs(gen_thad_M), weight);
      }
    }

    // tlep
    float rec_tlep_M (hyp->toplep_v4().M());
    float rec_tlep_pt(hyp->toplep_v4().Pt());
    float rec_tlep_px(hyp->toplep_v4().Px());
    float rec_tlep_py(hyp->toplep_v4().Py());
    float rec_tlep_pz(hyp->toplep_v4().Pz());
    H1("rec_tlep__M")   ->Fill(rec_tlep_M               , weight);
    H1("rec_tlep__pt")  ->Fill(rec_tlep_pt              , weight);
    H1("rec_tlep__px")  ->Fill(rec_tlep_px              , weight);
    H1("rec_tlep__py")  ->Fill(rec_tlep_py              , weight);
    H1("rec_tlep__pz")  ->Fill(rec_tlep_pz              , weight);
    H1("rec_tlep__jetN")->Fill(hyp->toplep_jets().size(), weight);
    if(ttljets){
      H1("rec_tlep__gen_DM")  ->Fill(rec_tlep_M -gen_tlep_M , weight);
      H1("rec_tlep__gen_Dpt") ->Fill(rec_tlep_pt-gen_tlep_pt, weight);
      H1("rec_tlep__gen_Dpx") ->Fill(rec_tlep_px-gen_tlep_px, weight);
      H1("rec_tlep__gen_Dpy") ->Fill(rec_tlep_py-gen_tlep_py, weight);
      H1("rec_tlep__gen_Dpz") ->Fill(rec_tlep_pz-gen_tlep_pz, weight);
      H1("rec_tlep__gen_Deta")->Fill(             hyp->toplep_v4().Eta()- ttgen->TopLep().v4().Eta() , weight);
      H1("rec_tlep__gen_Dphi")->Fill(delta_phi(   hyp->toplep_v4().Phi(), ttgen->TopLep().v4().Phi()), weight);
      H1("rec_tlep__gen_DR")  ->Fill(uhh2::deltaR(hyp->toplep_v4()      , ttgen->TopLep().v4())      , weight);

      if(gen_tlep_M)  H1("rec_tlep__gen_DM_pct") ->Fill((rec_tlep_M -gen_tlep_M) /fabs(gen_tlep_M) , weight);
      if(gen_tlep_pt) H1("rec_tlep__gen_Dpt_pct")->Fill((rec_tlep_pt-gen_tlep_pt)/fabs(gen_tlep_pt), weight);
      if(gen_tlep_px) H1("rec_tlep__gen_Dpx_pct")->Fill((rec_tlep_px-gen_tlep_px)/fabs(gen_tlep_px), weight);
      if(gen_tlep_py) H1("rec_tlep__gen_Dpy_pct")->Fill((rec_tlep_py-gen_tlep_py)/fabs(gen_tlep_py), weight);
      if(gen_tlep_pz) H1("rec_tlep__gen_Dpz_pct")->Fill((rec_tlep_pz-gen_tlep_pz)/fabs(gen_tlep_pz), weight);
    }

    H1("rec_tops__Dpt")->Fill(rec_tlep_pt-rec_thad_pt, weight);
    H1("rec_tops__DR") ->Fill(uhh2::deltaR(hyp->toplep_v4(), hyp->tophad_v4()), weight);

    // Wlep
    float rec_Wlep_M (hyp->wlep_v4().M());
    float rec_Wlep_Mt(sqrt(2*hyp->lepton().pt()*hyp->neutrino_v4().Pt()*(1.-cos(delta_phi(hyp->lepton().phi(), hyp->neutrino_v4().Phi())))));
    float rec_Wlep_pt(hyp->wlep_v4().Pt());
    float rec_Wlep_px(hyp->wlep_v4().Px());
    float rec_Wlep_py(hyp->wlep_v4().Py());
    float rec_Wlep_pz(hyp->wlep_v4().Pz());
    H1("rec_Wlep__M") ->Fill(rec_Wlep_M , weight);
    H1("rec_Wlep__Mt")->Fill(rec_Wlep_Mt, weight);
    H1("rec_Wlep__pt")->Fill(rec_Wlep_pt, weight);
    H1("rec_Wlep__px")->Fill(rec_Wlep_px, weight);
    H1("rec_Wlep__py")->Fill(rec_Wlep_py, weight);
    H1("rec_Wlep__pz")->Fill(rec_Wlep_pz, weight);
    if(ttljets){
      H1("rec_Wlep__gen_DM") ->Fill(rec_Wlep_M -gen_Wlep_M , weight);
      H1("rec_Wlep__gen_DMt")->Fill(rec_Wlep_Mt-gen_Wlep_Mt, weight);
      H1("rec_Wlep__gen_Dpt")->Fill(rec_Wlep_pt-gen_Wlep_pt, weight);
      H1("rec_Wlep__gen_Dpx")->Fill(rec_Wlep_px-gen_Wlep_px, weight);
      H1("rec_Wlep__gen_Dpy")->Fill(rec_Wlep_py-gen_Wlep_py, weight);
      H1("rec_Wlep__gen_Dpz")->Fill(rec_Wlep_pz-gen_Wlep_pz, weight);
      if(gen_Wlep_M)  H1("rec_Wlep__gen_DM_pct") ->Fill((rec_Wlep_M -gen_Wlep_M) /fabs(gen_Wlep_M) , weight);
      if(gen_Wlep_Mt) H1("rec_Wlep__gen_DMt_pct")->Fill((rec_Wlep_Mt-gen_Wlep_Mt)/fabs(gen_Wlep_Mt), weight);
      if(gen_Wlep_pt) H1("rec_Wlep__gen_Dpt_pct")->Fill((rec_Wlep_pt-gen_Wlep_pt)/fabs(gen_Wlep_pt), weight);
      if(gen_Wlep_px) H1("rec_Wlep__gen_Dpx_pct")->Fill((rec_Wlep_px-gen_Wlep_px)/fabs(gen_Wlep_px), weight);
      if(gen_Wlep_py) H1("rec_Wlep__gen_Dpy_pct")->Fill((rec_Wlep_py-gen_Wlep_py)/fabs(gen_Wlep_py), weight);
      if(gen_Wlep_pz) H1("rec_Wlep__gen_Dpz_pct")->Fill((rec_Wlep_pz-gen_Wlep_pz)/fabs(gen_Wlep_pz), weight);
    }

    // lepton
    const LorentzVector& rec_lep = hyp->lepton().v4();

    float rec_lep_pt (rec_lep.Pt());
    float rec_lep_eta(rec_lep.Eta());
    float rec_lep_phi(rec_lep.Phi());
    float rec_lep_cosThetaX(cosThetaX(rec_lep, hyp->toplep_v4(), (hyp->top_v4()+hyp->antitop_v4())));
    H1("rec_lep__pt")       ->Fill(rec_lep_pt       , weight);
    H1("rec_lep__eta")      ->Fill(rec_lep_eta      , weight);
    H1("rec_lep__phi")      ->Fill(rec_lep_phi      , weight);
    H1("rec_lep__cosThetaX")->Fill(rec_lep_cosThetaX, weight);
    if(ttljets){
      H1("rec_lep__gen_DR")        ->Fill(uhh2::deltaR(rec_lep, ttgen->ChargedLepton()), weight);
      H1("rec_lep__gen_Dpt")       ->Fill(rec_lep_pt -gen_lep_pt                      , weight);
      H1("rec_lep__gen_Deta")      ->Fill(rec_lep_eta-gen_lep_eta                     , weight);
      H1("rec_lep__gen_Dphi")      ->Fill(delta_phi(rec_lep_phi, gen_lep_phi)         , weight);
      H1("rec_lep__gen_DcosThetaX")->Fill(rec_lep_cosThetaX-gen_lep_cosThetaX         , weight);
      if(gen_lep_pt)  H1("rec_lep__gen_Dpt_pct") ->Fill((rec_lep_pt -gen_lep_pt) /fabs(gen_lep_pt) , weight);
      if(gen_lep_eta) H1("rec_lep__gen_Deta_pct")->Fill((rec_lep_eta-gen_lep_eta)/fabs(gen_lep_eta), weight);
    }

    // neutrino
    const LorentzVector& rec_neu = hyp->neutrino_v4();

    float rec_neu_pt (rec_neu.Pt());
    float rec_neu_phi(rec_neu.Phi());
    float rec_neu_px (rec_neu.Px());
    float rec_neu_py (rec_neu.Py());
    float rec_neu_pz (rec_neu.Pz());
    float rec_neu_cosThetaX(cosThetaX(rec_neu, hyp->toplep_v4(), (hyp->top_v4()+hyp->antitop_v4())));
    H1("rec_neu__pt")       ->Fill(rec_neu_pt       , weight);
    H1("rec_neu__phi")      ->Fill(rec_neu_phi      , weight);
    H1("rec_neu__px")       ->Fill(rec_neu_px       , weight);
    H1("rec_neu__py")       ->Fill(rec_neu_py       , weight);
    H1("rec_neu__pz")       ->Fill(rec_neu_pz       , weight);
    H1("rec_neu__cosThetaX")->Fill(rec_neu_cosThetaX, weight);
    if(ttljets){
      H1("rec_neu__gen_DR")        ->Fill(uhh2::deltaR(rec_neu, ttgen->Neutrino()), weight);
      H1("rec_neu__gen_Dpt")       ->Fill(rec_neu_pt-gen_neu_pt                  , weight);
      H1("rec_neu__gen_Dphi")      ->Fill(delta_phi(rec_neu_phi, gen_neu_phi)    , weight);
      H1("rec_neu__gen_Dpx")       ->Fill(rec_neu_px-gen_neu_px                  , weight);
      H1("rec_neu__gen_Dpy")       ->Fill(rec_neu_py-gen_neu_py                  , weight);
      H1("rec_neu__gen_Dpz")       ->Fill(rec_neu_pz-gen_neu_pz                  , weight);
      H1("rec_neu__gen_DcosThetaX")->Fill(rec_neu_cosThetaX-gen_neu_cosThetaX    , weight);
      if(gen_neu_pt) H1("rec_neu__gen_Dpt_pct")->Fill((rec_neu_pt-gen_neu_pt)/fabs(gen_neu_pt), weight);
      if(gen_neu_px) H1("rec_neu__gen_Dpx_pct")->Fill((rec_neu_px-gen_neu_px)/fabs(gen_neu_px), weight);
      if(gen_neu_py) H1("rec_neu__gen_Dpy_pct")->Fill((rec_neu_py-gen_neu_py)/fabs(gen_neu_py), weight);
      if(gen_neu_pz) H1("rec_neu__gen_Dpz_pct")->Fill((rec_neu_pz-gen_neu_pz)/fabs(gen_neu_pz), weight);
    }

    // blep
    const LorentzVector& rec_blep = (hyp->toplep_v4()-hyp->wlep_v4());

    float rec_blep_pt (rec_blep.Pt());
    float rec_blep_eta(rec_blep.Eta());
    float rec_blep_phi(rec_blep.Phi());
    float rec_blep_px (rec_blep.Px());
    float rec_blep_py (rec_blep.Py());
    float rec_blep_pz (rec_blep.Pz());
    float rec_blep_CSV((hyp->toplep_jets().size() == 1) ? hyp->toplep_jets().at(0).btag_combinedSecondaryVertex() : -1.);
    float rec_blep_cosThetaX(cosThetaX(rec_blep, hyp->toplep_v4(), (hyp->top_v4()+hyp->antitop_v4())));
    H1("rec_blep__pt")       ->Fill(rec_blep_pt       , weight);
    H1("rec_blep__eta")      ->Fill(rec_blep_eta      , weight);
    H1("rec_blep__phi")      ->Fill(rec_blep_phi      , weight);
    H1("rec_blep__px")       ->Fill(rec_blep_px       , weight);
    H1("rec_blep__py")       ->Fill(rec_blep_py       , weight);
    H1("rec_blep__pz")       ->Fill(rec_blep_pz       , weight);
    H1("rec_blep__CSV")      ->Fill(rec_blep_CSV      , weight);
    H1("rec_blep__cosThetaX")->Fill(rec_blep_cosThetaX, weight);
    if(ttljets){
      H1("rec_blep__gen_DR")        ->Fill(uhh2::deltaR(rec_blep, ttgen->BLep()) , weight);
      H1("rec_blep__gen_Dpt")       ->Fill(rec_blep_pt -gen_blep_pt             , weight);
      H1("rec_blep__gen_Deta")      ->Fill(rec_blep_eta-gen_blep_eta            , weight);
      H1("rec_blep__gen_Dphi")      ->Fill(delta_phi(rec_blep_phi, gen_blep_phi), weight);
      H1("rec_blep__gen_Dpx")       ->Fill(rec_blep_px -gen_blep_px             , weight);
      H1("rec_blep__gen_Dpy")       ->Fill(rec_blep_py -gen_blep_py             , weight);
      H1("rec_blep__gen_Dpz")       ->Fill(rec_blep_pz -gen_blep_pz             , weight);
      H1("rec_blep__gen_DcosThetaX")->Fill(rec_blep_cosThetaX-gen_blep_cosThetaX, weight);
      if(gen_blep_pt)  H1("rec_blep__gen_Dpt_pct") ->Fill((rec_blep_pt -gen_blep_pt) /fabs(gen_blep_pt) , weight);
      if(gen_blep_eta) H1("rec_blep__gen_Deta_pct")->Fill((rec_blep_eta-gen_blep_eta)/fabs(gen_blep_eta), weight);
      if(gen_blep_px)  H1("rec_blep__gen_Dpx_pct") ->Fill((rec_blep_px -gen_blep_px) /fabs(gen_blep_px) , weight);
      if(gen_blep_py)  H1("rec_blep__gen_Dpy_pct") ->Fill((rec_blep_py -gen_blep_py) /fabs(gen_blep_py) , weight);
      if(gen_blep_pz)  H1("rec_blep__gen_Dpz_pct") ->Fill((rec_blep_pz -gen_blep_pz) /fabs(gen_blep_pz) , weight);
    }

    // xobj -- deltaR
    float rec_top_cosThetaCS(cosThetaCS(hyp->top_v4(), (hyp->top_v4()+hyp->antitop_v4())));
    H1("rec_top__cosThetaCS")->Fill(rec_top_cosThetaCS, weight);

    H1("rec_lep__cosThetaX__X__rec_blep__cosThetaX")->Fill(rec_lep_cosThetaX * rec_blep_cosThetaX, weight);
    H1("rec_lep__cosThetaX__X__rec_neu__cosThetaX") ->Fill(rec_lep_cosThetaX * rec_neu_cosThetaX , weight);
    H1("rec_neu__cosThetaX__X__rec_blep__cosThetaX")->Fill(rec_neu_cosThetaX * rec_blep_cosThetaX, weight);

    if(ttljets){

      H1("deltaR__gen_lep__gen_neu") ->Fill(uhh2::deltaR(ttgen->ChargedLepton(), ttgen->Neutrino()), weight);
      H1("deltaR__gen_lep__gen_blep")->Fill(uhh2::deltaR(ttgen->ChargedLepton(), ttgen->BLep())    , weight);
      H1("deltaR__gen_lep__gen_thad")->Fill(uhh2::deltaR(ttgen->ChargedLepton(), ttgen->TopHad())  , weight);
      H1("deltaR__gen_blep__gen_neu")->Fill(uhh2::deltaR(ttgen->BLep()         , ttgen->Neutrino()), weight);

      H1("deltaPhi__gen_lep__gen_neu") ->Fill(delta_phi(ttgen->ChargedLepton().v4().Phi(), ttgen->Neutrino().v4().Phi()), weight);
      H1("deltaPhi__gen_blep__gen_neu")->Fill(delta_phi(ttgen->BLep()         .v4().Phi(), ttgen->Neutrino().v4().Phi()), weight);
    }

    H1("deltaR__rec_lep__rec_neu") ->Fill(uhh2::deltaR(rec_lep , rec_neu)         , weight);
    H1("deltaR__rec_lep__rec_blep")->Fill(uhh2::deltaR(rec_lep , rec_blep)        , weight);
    H1("deltaR__rec_lep__rec_thad")->Fill(uhh2::deltaR(rec_lep , hyp->tophad_v4()), weight);
    H1("deltaR__rec_blep__rec_neu")->Fill(uhh2::deltaR(rec_blep, rec_neu)         , weight);

    H1("deltaPhi__rec_lep__rec_neu") ->Fill(delta_phi(rec_lep .Phi(), rec_neu.Phi()), weight);
    H1("deltaPhi__rec_blep__rec_neu")->Fill(delta_phi(rec_blep.Phi(), rec_neu.Phi()), weight);

    float deltaRsum__rec_thad_jets(0.);
    for  (unsigned int i=0  ; i<hyp->tophad_jets().size(); ++i){
      for(unsigned int j=i+1; j<hyp->tophad_jets().size(); ++j){

        deltaRsum__rec_thad_jets += uhh2::deltaR(hyp->tophad_jets().at(i), hyp->tophad_jets().at(j));
      }
    }
    if(!deltaRsum__rec_thad_jets) deltaRsum__rec_thad_jets = -1.;
    H1("deltaRsum__rec_thad_jets")->Fill(deltaRsum__rec_thad_jets, weight);
  }

  return;
}

float EffyTTbarRECOHists::delta_phi(const float phi1, const float phi2){

  float a_dphi = fabs(phi1-phi2);
  if(a_dphi > M_PI) a_dphi = 2*M_PI - a_dphi;

  return a_dphi;
}

void EffyTTbarRECOHists::boost_x1_to_x2CM(TLorentzVector& x1, const TLorentzVector& x2){

  if(!x2.E()) return;

  x1.Boost(-x2.Px()/x2.E(), -x2.Py()/x2.E(), -x2.Pz()/x2.E());

  return;
}

float EffyTTbarRECOHists::cosThetaX(const LorentzVector& tprod, const LorentzVector& top, const LorentzVector& ttbar0){

  TLorentzVector top_in_ttbarCM(   top.Px(),    top.Py(),    top.Pz(),    top.E());
  TLorentzVector tprod_in_topCM( tprod.Px(),  tprod.Py(),  tprod.Pz(),  tprod.E());
  TLorentzVector ttbar         (ttbar0.Px(), ttbar0.Py(), ttbar0.Pz(), ttbar0.E());

  boost_x1_to_x2CM(top_in_ttbarCM, ttbar);
  boost_x1_to_x2CM(tprod_in_topCM, ttbar);

  boost_x1_to_x2CM(tprod_in_topCM, top_in_ttbarCM);

  float thetaX = tprod_in_topCM.Angle(top_in_ttbarCM.Vect());

  return cos(thetaX);
}

float EffyTTbarRECOHists::cosThetaCS(const LorentzVector& top, const LorentzVector& ttbar0){

  const float sqrt_s = 13000.;

  TLorentzVector proton1       (         0.,          0.,   .5*sqrt_s,  .5*sqrt_s);
  TLorentzVector proton2       (         0.,          0.,  -.5*sqrt_s,  .5*sqrt_s);
  TLorentzVector top_in_ttbarCM(   top.Px(),    top.Py(),    top.Pz(),    top.E());
  TLorentzVector ttbar         (ttbar0.Px(), ttbar0.Py(), ttbar0.Pz(), ttbar0.E());

  boost_x1_to_x2CM(proton1       , ttbar);
  boost_x1_to_x2CM(proton2       , ttbar);
  boost_x1_to_x2CM(top_in_ttbarCM, ttbar);

  float thetaCS = top_in_ttbarCM.Angle((proton1+proton2).Vect());

  return cos(thetaCS);
}
