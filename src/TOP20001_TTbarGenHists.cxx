#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"

#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_TTbarGenHists.h"

using namespace std;
using namespace uhh2;

TOP20001_TTbarGenHists::TOP20001_TTbarGenHists(uhh2::Context & ctx, const std::string & dirname): Hists(ctx, dirname){

  h_ttbargen = ctx.get_handle<TOP20001_TTbarGen>("ttbargen");

  // binnings from: https://www.hepdata.net/record/ins1901295
  vector<float> bins_pt_thad = {0.0,40.0,80.0,120.0,160.0,200.0,250.0,300.0,350.0,400.0,450.0,500.0,600.0,700.0,800.0,950.0,1100.0,1600.0};
  vector<float> bins_pt_tlep = {0.0,40.0,80.0,120.0,160.0,200.0,250.0,300.0,350.0,400.0,450.0,500.0,600.0,700.0,850.0,1000.0,1500.0};
  vector<float> bins_ST = {0.0,50.0,100.0,150.0,200.0,250.0,300.0,350.0,400.0,450.0,500.0,550.0,600.0,700.0,800.0,900.0,1000.0,1150.0,1300.0,1500.0,1700.0,4000.0};
  vector<float> bins_absy = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.5};
  vector<float> bins_deltaabsy_ttbar = {-2.5,-1.6,-1.2,-0.8,-0.4,0.0,0.4,0.8,1.2,1.6,2.5};
  vector<float> bins_absdeltay_ttbar = {0.0,0.25,0.5,0.75,1.0,1.25,1.5,1.75,2.0,2.25,2.5,3.0,3.5};
  vector<float> bins_m_ttbar = {250,400,480,560,640,720,800,900,1000,1150,1300,1500,1700,2000,2300,3500};
  vector<float> bins_pt_ttbar = {0.0,50.0,100.0,150.0,200.0,300.0,400.0,500.0,600.0,800.0,1200.0};
  vector<float> bins_absy_ttbar = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.4};
  vector<float> bins_phi_ttbar = {0.0,40.0,80.0,120.0,140.0,150.0,160.0,170.0,180.0};
  vector<float> bins_cts = {-1,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0};
  vector<float> bins_cts_mtt = {-1,-0.65,-0.3,0.0,0.3,0.65,1.0};

  pt_thad = book<TH1F>("pt_thad","p_{T}(t_{h}) [GeV]",bins_pt_thad.size()-1,&bins_pt_thad[0]);
  pt_tlep = book<TH1F>("pt_tlep","p_{T}(t_{l}) [GeV]",bins_pt_tlep.size()-1,&bins_pt_tlep[0]);
  ST = book<TH1F>("ST","S_{T} [GeV]",bins_ST.size()-1,&bins_ST[0]);
  absy_thad = book<TH1F>("absy_thad","|y(t_{h})|",bins_absy.size()-1,&bins_absy[0]);
  absy_tlep = book<TH1F>("absy_tlep","|y(t_{l})|",bins_absy.size()-1,&bins_absy[0]);
  deltaabsy_ttbar = book<TH1F>("deltaabsy_ttbar","#Delta|y_{t/#bar{t}}|",bins_deltaabsy_ttbar.size()-1,&bins_deltaabsy_ttbar[0]);
  absdeltay_ttbar = book<TH1F>("absdeltay_ttbar","|#Deltay_{t/#bar{t}}|",bins_absdeltay_ttbar.size()-1,&bins_absdeltay_ttbar[0]);
  m_ttbar = book<TH1F>("m_ttbar","m(t#bar{t}) [GeV]",bins_m_ttbar.size()-1,&bins_m_ttbar[0]);
  pt_ttbar = book<TH1F>("pt_ttbar","p_{T}(t#bar{t}) [GeV]",bins_pt_ttbar.size()-1,&bins_pt_ttbar[0]);
  absy_ttbar = book<TH1F>("absy_ttbar","|y(t#bar{t})|",bins_absy_ttbar.size()-1,&bins_absy_ttbar[0]);
  phi_ttbar = book<TH1F>("phi_ttbar","#phi_{t/#bar{t}} [#circ]",bins_phi_ttbar.size()-1,&bins_phi_ttbar[0]);
  cts = book<TH1F>("cts","cos(#theta*)",bins_cts.size()-1,&bins_cts[0]);
  cts_mtt250To420 = book<TH1F>("cts_mtt250To420","cos(#theta*)",bins_cts_mtt.size()-1,&bins_cts_mtt[0]);
  cts_mtt420To520 = book<TH1F>("cts_mtt420To520","cos(#theta*)",bins_cts_mtt.size()-1,&bins_cts_mtt[0]);
  cts_mtt520To620 = book<TH1F>("cts_mtt520To620","cos(#theta*)",bins_cts_mtt.size()-1,&bins_cts_mtt[0]);
  cts_mtt620To800 = book<TH1F>("cts_mtt620To800","cos(#theta*)",bins_cts_mtt.size()-1,&bins_cts_mtt[0]);
  cts_mtt800To1000 = book<TH1F>("cts_mtt800To1000","cos(#theta*)",bins_cts_mtt.size()-1,&bins_cts_mtt[0]);
  cts_mtt1000To3500 = book<TH1F>("cts_mtt1000To3500","cos(#theta*)",bins_cts_mtt.size()-1,&bins_cts_mtt[0]);
}


void TOP20001_TTbarGenHists::fill(const uhh2::Event & e){
  //do not fill histograms if ttbargen information has not been filled
  if(!e.is_valid(h_ttbargen)){
    return;
  }

  const auto & ttbargen = e.get(h_ttbargen);

  LorentzVector top = ttbargen.Top().v4();
  LorentzVector antitop = ttbargen.Antitop().v4();

  double mttbar_gen = (top+antitop).M();
  double ptttbar_gen = (top+antitop).Pt();

  TLorentzVector top_ttframe(0,0,0,0);
  top_ttframe.SetPtEtaPhiE(top.pt(), top.eta(), top.phi(), top.E());
  TLorentzVector antitop_ttframe(0,0,0,0);
  antitop_ttframe.SetPtEtaPhiE(antitop.pt(), antitop.eta(), antitop.phi(), antitop.E());
  TLorentzVector ttbar(0,0,0,0);
  ttbar.SetPtEtaPhiE((top+antitop).pt(), (top+antitop).eta(), (top+antitop).phi(), (top+antitop).E());

  top_ttframe.Boost(-ttbar.BoostVector());
  antitop_ttframe.Boost(-ttbar.BoostVector());

  if(ttbargen.IsSemiLeptonicDecay()){

    LorentzVector leptop, hadtop;

    if(ttbargen.Wdecay1().pdgId() == -11 || ttbargen.Wdecay1().pdgId() == -13 || ttbargen.Wdecay2().pdgId() == -11 || ttbargen.Wdecay2().pdgId() == -13){
      leptop = top;
      hadtop = antitop;
    }
    else if(ttbargen.WMinusdecay1().pdgId() == 11 ||  ttbargen.WMinusdecay1().pdgId() == 13 || ttbargen.WMinusdecay2().pdgId() == 11 ||  ttbargen.WMinusdecay2().pdgId() == 13){
      leptop = antitop;
      hadtop = top;
    }
    else cout << "don't consider taus" << endl;

    TLorentzVector leptop_ttframe(0,0,0,0);
    leptop_ttframe.SetPtEtaPhiE(leptop.pt(),leptop.eta(),leptop.phi(),leptop.E());
    TLorentzVector hadtop_ttframe(0,0,0,0);
    hadtop_ttframe.SetPtEtaPhiE(hadtop.pt(),hadtop.eta(),hadtop.phi(),hadtop.E());
    TLorentzVector ttbar(0,0,0,0);
    ttbar.SetPtEtaPhiE((leptop+hadtop).pt(),(leptop+hadtop).eta(),(leptop+hadtop).phi(),(leptop+hadtop).E());

    leptop_ttframe.Boost(-ttbar.BoostVector());
    hadtop_ttframe.Boost(-ttbar.BoostVector());

    double tops_deltaabsy = fabs(top.Rapidity()) - fabs(antitop.Rapidity());
    double tops_absdeltay = fabs(top.Rapidity() - antitop.Rapidity());

    double ditop_absy = fabs((top+antitop).Rapidity());
    double ditop_phi = fabs(top.phi() - antitop.phi());
    if(ditop_phi > M_PI) ditop_phi = 2 * M_PI - ditop_phi;
    ditop_phi = ditop_phi / (2 * M_PI) * 360;

    pt_thad->Fill(hadtop.pt(),e.weight);
    pt_tlep->Fill(leptop.pt(),e.weight);
    ST->Fill(hadtop.pt()+leptop.pt(),e.weight);
    absy_thad->Fill(fabs(hadtop.Rapidity()),e.weight);
    absy_tlep->Fill(fabs(leptop.Rapidity()),e.weight);
    deltaabsy_ttbar->Fill(tops_deltaabsy,e.weight);
    absdeltay_ttbar->Fill(tops_absdeltay,e.weight);

    m_ttbar->Fill(mttbar_gen,e.weight);
    pt_ttbar->Fill(ptttbar_gen,e.weight);
    absy_ttbar->Fill(ditop_absy,e.weight);
    phi_ttbar->Fill(ditop_phi,e.weight);

    const TLorentzVector Top(top.px(), top.py(), top.pz(), top.E());
    const TLorentzVector Antitop(antitop.px(), antitop.py(), antitop.pz(), antitop.E());
    const TLorentzVector TTbar = Top + Antitop;
    TLorentzVector Topcms = Top;
    Topcms.Boost(-1.*TTbar.BoostVector());
    double costhetastar = TTbar.Vect().Dot(Topcms.Vect())/TTbar.P()/Topcms.P();

    cts->Fill(costhetastar,e.weight);

    if(mttbar_gen < 250.){} // do nothing: underflow bin
    else if(mttbar_gen < 420.) cts_mtt250To420->Fill(costhetastar,e.weight);
    else if(mttbar_gen < 520.) cts_mtt420To520->Fill(costhetastar,e.weight);
    else if(mttbar_gen < 620.) cts_mtt520To620->Fill(costhetastar,e.weight);
    else if(mttbar_gen < 800.) cts_mtt620To800->Fill(costhetastar,e.weight);
    else if(mttbar_gen < 1000.) cts_mtt800To1000->Fill(costhetastar,e.weight);
    else if(mttbar_gen < 3500.) cts_mtt1000To3500->Fill(costhetastar,e.weight);
    else{} // do nothing: overflow bin
  }
}
