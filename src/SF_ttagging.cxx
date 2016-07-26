#include <UHH2/ZprimeSemiLeptonic/include/SF_ttagging.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <algorithm>

weightcalc_ttagging::weightcalc_ttagging(const std::string& sfac_csvfile , const std::string& ttagWP_key,
                                         const std::string& meas_key_jetL, const std::string& meas_key_jetT,
                                         const std::string& syst_key_jetL, const std::string& syst_key_jetT,
                                         const std::string& effyTF, const std::string& effyTG__jetL, const std::string& effyTG__jetT,
                                         const bool v){

  verbose_ = v;

  tjet_maxDR_gentop_ = 0.8;

  // scale-factors
  measurement_type__jetL_ = meas_key_jetL;
  measurement_type__jetT_ = meas_key_jetT;

  ttagWP_ = TopTagID_SoftDrop(ttagWP_key);

  if     (syst_key_jetL == "CT") sys_key__jetL_ = "central";
  else if(syst_key_jetL == "UP") sys_key__jetL_ = "up";
  else if(syst_key_jetL == "DN") sys_key__jetL_ = "down";
  else throw std::runtime_error("weightcalc_ttagging::weightcalc_ttagging -- invalid key for t-tagging SF systematic (flavor=L): "+syst_key_jetL);

  if     (syst_key_jetT == "CT") sys_key__jetT_ = "central";
  else if(syst_key_jetT == "UP") sys_key__jetT_ = "up";
  else if(syst_key_jetT == "DN") sys_key__jetT_ = "down";
  else throw std::runtime_error("weightcalc_ttagging::weightcalc_ttagging -- invalid key for t-tagging SF systematic (flavor=T): "+syst_key_jetT);

  ttagSF_vec_.clear();
  load_SFac(ttagWP_key, sfac_csvfile);

  // efficiencies
  effy__tfile_ = TFile::Open(effyTF.c_str());
  if(!effy__tfile_) throw std::runtime_error("weightcalc_ttagging::weightcalc_ttagging -- failed to locate input file for jet t-tagging efficiencies");

  effy__graph__jet_l_ = (TGraphAsymmErrors*) effy__tfile_->Get(effyTG__jetL.c_str());
  effy__graph__jet_t_ = (TGraphAsymmErrors*) effy__tfile_->Get(effyTG__jetT.c_str());

  if(!effy__graph__jet_l_) throw std::runtime_error("weightcalc_ttagging::weightcalc_ttagging -- uninitialized reference to jet t-tagging efficiencies (flavor=L)");
  if(!effy__graph__jet_t_) throw std::runtime_error("weightcalc_ttagging::weightcalc_ttagging -- uninitialized reference to jet t-tagging efficiencies (flavor=T)");
}

weightcalc_ttagging::~weightcalc_ttagging(){

  if(effy__tfile_) effy__tfile_->Close();
}

void weightcalc_ttagging::load_SFac(const std::string& ttagWP_key, const std::string& sfac_csvfile){

  // scale-factors
  const std::string op_point(ttagWP_key);

  if(ttagSF_vec_.size()) throw std::runtime_error("weightcalc_ttagging::load_SFac -- logic error: list of t-tagging SF values not empty");

  std::ifstream csv_file;
  csv_file.open(sfac_csvfile.c_str());

  if(csv_file.fail()){

    throw std::runtime_error("weightcalc_ttagging::load_SFac -- failed to locate input file: "+sfac_csvfile);
  }
  else {

    csv_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    while(std::getline(csv_file, line)){

      std::stringstream line_ss(line);

      weightcalc_ttagging::ttagSF ttag_sf;

      import_entry(line_ss, ',', ttag_sf.OperatingPoint);
      if(ttag_sf.OperatingPoint != op_point) continue;

      import_entry(line_ss, ',', ttag_sf.measurementType);

      import_entry(line_ss, ',', ttag_sf.sysType);

      import_entry(line_ss, ',', ttag_sf.jetFlavor);

      if(ttag_sf.jetFlavor == 2 && ttag_sf.measurementType != measurement_type__jetL_) continue;
      if(ttag_sf.jetFlavor == 0 && ttag_sf.measurementType != measurement_type__jetT_) continue;

      if(ttag_sf.jetFlavor == 2 && ttag_sf.sysType != sys_key__jetL_) continue;
      if(ttag_sf.jetFlavor == 0 && ttag_sf.sysType != sys_key__jetT_) continue;

      import_entry(line_ss, ',', ttag_sf.etaMin);
      import_entry(line_ss, ',', ttag_sf.etaMax);
      import_entry(line_ss, ',', ttag_sf.ptMin);
      import_entry(line_ss, ',', ttag_sf.ptMax);

      std::string formula("");
      import_entry(line_ss, ',', formula);
      formula = std::string(formula, 1, formula.length()-2);
      if(formula.find("y") == std::string::npos) formula += "+(y-y)";
      ttag_sf.function = TF2("f2", formula.c_str());

      ttagSF_vec_.push_back(ttag_sf);
    }
  }

  csv_file.close();

  if(!ttagSF_vec_.size()){

    std::string log("");
    log += "weightcalc_ttagging::load_SFac";
    log += " -- logic error: no entries in the list of t-tagging SF:";
    log +=     " operating_point="+op_point;
    log += " measurement_type(L)="+measurement_type__jetL_;
    log += " measurement_type(T)="+measurement_type__jetT_;
    log +=          " sys_key(L)="+sys_key__jetL_;
    log +=          " sys_key(T)="+sys_key__jetT_;

    throw std::runtime_error(log);
  }

  if(verbose_){

    for(const auto& sf : ttagSF_vec_){

      std::cout <<         sf.OperatingPoint;
      std::cout << ", " << sf.measurementType;
      std::cout << ", " << sf.sysType;
      std::cout << ", " << sf.jetFlavor;
      std::cout << ", " << sf.etaMin;
      std::cout << ", " << sf.etaMax;
      std::cout << ", " << sf.ptMin;
      std::cout << ", " << sf.ptMax;
      std::cout << ", " << std::string(sf.function.GetExpFormula());
      std::cout << "\n";
    }

    std::cout << "\n";
  }

  return;
}

void weightcalc_ttagging::import_entry(std::stringstream& sstrm, const char delim, int& val) const {

  std::string entry;
  std::getline(sstrm, entry, delim);
  entry.erase(std::remove(entry.begin(), entry.end(), ' '), entry.end());

  val = atoi(entry.c_str());

  return;
}

void weightcalc_ttagging::import_entry(std::stringstream& sstrm, const char delim, float& val) const {

  std::string entry;
  std::getline(sstrm, entry, delim);
  entry.erase(std::remove(entry.begin(), entry.end(), ' '), entry.end());

  val = atof(entry.c_str());

  return;
}

void weightcalc_ttagging::import_entry(std::stringstream& sstrm, const char delim, std::string& val) const {

  std::string entry;
  std::getline(sstrm, entry, delim);
  entry.erase(std::remove(entry.begin(), entry.end(), ' '), entry.end());

  val = std::string(entry);

  return;
}

int weightcalc_ttagging::jet_flavor(const TopJet& jet_, const uhh2::Event& evt_) const {

  int jfla(0);

  if(!evt_.isRealData){

    assert(evt_.genparticles);

    for(const auto& genp : *evt_.genparticles){

      if(std::abs(genp.pdgId()) != 6) continue;

      if(uhh2::deltaR(jet_, genp) < tjet_maxDR_gentop_){

        jfla = genp.pdgId();
        break;
      }
    }
  }

  return jfla;
}

float weightcalc_ttagging::jet_effy(const TopJet& jet_, const uhh2::Event& evt_) const {

  TGraphAsymmErrors* geff(0);

  const int jetFlavor = jet_flavor(jet_, evt_);
  //  std::cout<<" jetFlavor = "<<jetFlavor<<std::endl;
  if     (std::abs(jetFlavor) == 6) geff = effy__graph__jet_t_;
  else if(std::abs(jetFlavor) == 0) geff = effy__graph__jet_l_;
  else throw std::runtime_error("weightcalc_ttagging::jet_effy -- failed to locate graph for jet t-tagging efficiency: "+std::to_string(jetFlavor));
  //  geff->Print();//TEST
  if(!geff) throw std::runtime_error("weightcalc_ttagging::jet_effy -- uninitialized reference to jet t-tagging efficiencies");         

  const float jet_PT = jet_.pt();
  //  std::cout<<"jet_PT = "<<jet_PT<<" geff->GetN() = "<<geff->GetN()<<std::endl;
  float eff(0.); 
  //  {

  float pt_min(std::numeric_limits<float>::infinity()), pt_max(-1.);
    for(int i=0; i<geff->GetN(); ++i){

      double x(-1.), y(-1.);
      geff->GetPoint(i, x, y);
      //      std::cout<<" "<<i<<" "<<x<<" "<<y<<std::endl;
      const float pt_lo = (x-geff->GetErrorXlow(i));
      const float pt_hi = (x+geff->GetErrorXhigh(i));

      if     (pt_lo <  jet_PT && jet_PT < pt_hi){ eff = y; break; }
      else if(pt_lo >= jet_PT && pt_min > pt_lo){ eff = y; pt_min = pt_lo; }
      else if(pt_hi <= jet_PT && pt_max < pt_hi){ eff = y; pt_max = pt_hi; }
      //      std::cout<<" eff = "<<eff<<std::endl;
    }
    //  }

  if(verbose_) std::cout << " eff=" << eff;

  return eff;
}

float weightcalc_ttagging::jet_SFac(const TopJet& jet_, const uhh2::Event& evt_) const {

  int jet_FLAV(-1);

  const int jetFlavor = jet_flavor(jet_, evt_);
  if     (std::abs(jetFlavor) == 6) jet_FLAV = 0;
  else if(std::abs(jetFlavor) == 0) jet_FLAV = 2;
  else throw std::runtime_error("weightcalc_ttagging::jet_SFac -- unknown jet flavor for jet t-tagging efficiency: "+std::to_string(jetFlavor));

  const float jet_pt  = jet_.pt();
  const float jet_ETA = jet_.eta();

  float jet_PT(jet_pt), sf(1.); {

    int idx(-1); {

      float pt_min(std::numeric_limits<float>::infinity()), pt_max(-1.);
      for(unsigned int i=0; i<ttagSF_vec_.size(); ++i){

        const weightcalc_ttagging::ttagSF& ttag_sf = ttagSF_vec_.at(i);

        if(ttag_sf.jetFlavor == jet_FLAV){

          if(ttag_sf.etaMin<jet_ETA && jet_ETA<ttag_sf.etaMax){

            const float pt_lo = ttag_sf.ptMin;
            const float pt_hi = ttag_sf.ptMax;

            if     (pt_lo <  jet_pt && jet_pt <  pt_hi){ idx = i; jet_PT = jet_pt; break; }
            else if(pt_lo >= jet_pt && pt_min >= pt_lo){ idx = i; jet_PT = pt_lo; pt_min = pt_lo; }
            else if(pt_hi <= jet_pt && pt_max <= pt_hi){ idx = i; jet_PT = pt_hi; pt_max = pt_hi; }
          }
        }
      }
    }

    if(idx == -1) sf = 1.;
    else {

      sf = ttagSF_vec_.at(idx).function.Eval(jet_PT, jet_ETA);
    }

    if(verbose_){

      std::cout <<   " SF_idx=" << idx;
      std::cout <<   " jet_PT=" << jet_PT;
      std::cout <<  " jet_ETA=" << jet_ETA;
      std::cout << " jet_FLAV=" << jet_FLAV;
      std::cout <<       " sf=" << sf;
    }
  }

  return sf;
}

float weightcalc_ttagging::weight(const uhh2::Event& evt_) const {

  float wgt(1.);

  assert(evt_.jets);

  for(const auto& jet : *evt_.topjets){

    const float sfac =          jet_SFac(jet, evt_);
    //    const float effy = std::min(jet_effy(jet, evt_), float(0.99999));
    const float effy = std::min(jet_effy(jet, evt_), float(0.95));

    const bool pass_ttagWP(ttagWP_(jet, evt_));

    if(verbose_) std::cout << " pass_ttagWP=" << pass_ttagWP << std::endl;

    if(pass_ttagWP) wgt *=     sfac;
    else            wgt *= (1.-sfac*effy) / (1.-effy);
    //    std::cout<<"wgt = "<<wgt<<" pass_ttagWP = "<<pass_ttagWP<<" sfac = "<<sfac<<" effy = "<<effy<<" jet_effy(jet, evt_) = "<<jet_effy(jet, evt_)<<std::endl;
  }

  if(verbose_){

    std::string log("--- ttagSF.weight="+std::to_string(wgt));
    log += " [meas(L)="+measurement_type__jetL_;
    log += ", meas(T)="+measurement_type__jetT_;
    log += ", syst(L)="+sys_key__jetL_;
    log += ", syst(T)="+sys_key__jetT_;
    log += "]";

    std::cout << log << "\n\n";
  }

  return wgt;
}
