#include <UHH2/ZprimeSemiLeptonic/include/SF_btagging.h>

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <algorithm>

weightcalc_btagging::weightcalc_btagging(const std::string& sfac_csvfile, const std::string& btagWP_key,
                                         const std::string& meas_key_jetL, const std::string& meas_key_jetC, const std::string& meas_key_jetB,
                                         const std::string& syst_key_jetL, const std::string& syst_key_jetC, const std::string& syst_key_jetB,
                                         const std::string& effyTF, const std::string& effyTG__jetL, const std::string& effyTG__jetC, const std::string& effyTG__jetB){

  verbose_ = false;

  // scale-factors
  measurement_type__jetL_ = meas_key_jetL;
  measurement_type__jetC_ = meas_key_jetC;
  measurement_type__jetB_ = meas_key_jetB;

  if     (btagWP_key == "CSVL") btagWP_ = CSVBTag(CSVBTag::WP_LOOSE);
  else if(btagWP_key == "CSVM") btagWP_ = CSVBTag(CSVBTag::WP_MEDIUM);
  else if(btagWP_key == "CSVT") btagWP_ = CSVBTag(CSVBTag::WP_TIGHT);
  else throw std::runtime_error("weightcalc_btagging::weightcalc_btagging -- invalid key for b-tagging working point: "+btagWP_key);

  if     (syst_key_jetL == "CT") sys_key__jetL_ = "central";
  else if(syst_key_jetL == "UP") sys_key__jetL_ = "up";
  else if(syst_key_jetL == "DN") sys_key__jetL_ = "down";
  else throw std::runtime_error("weightcalc_btagging::weightcalc_btagging -- invalid key for b-tagging SF systematic (flavor=L): "+syst_key_jetL);

  if     (syst_key_jetC == "CT") sys_key__jetC_ = "central";
  else if(syst_key_jetC == "UP") sys_key__jetC_ = "up";
  else if(syst_key_jetC == "DN") sys_key__jetC_ = "down";
  else throw std::runtime_error("weightcalc_btagging::weightcalc_btagging -- invalid key for b-tagging SF systematic (flavor=C): "+syst_key_jetC);

  if     (syst_key_jetB == "CT") sys_key__jetB_ = "central";
  else if(syst_key_jetB == "UP") sys_key__jetB_ = "up";
  else if(syst_key_jetB == "DN") sys_key__jetB_ = "down";
  else throw std::runtime_error("weightcalc_btagging::weightcalc_btagging -- invalid key for b-tagging SF systematic (flavor=B): "+syst_key_jetB);

  btagSF_vec_.clear();
  load_SFac(btagWP_key, sfac_csvfile);

  // efficiencies
  effy__tfile_ = TFile::Open(effyTF.c_str());
  if(!effy__tfile_) throw std::runtime_error("weightcalc_btagging::weightcalc_btagging -- failed to locate input file for jet b-tagging efficiencies");

  effy__graph__jet_l_ = (TGraphAsymmErrors*) effy__tfile_->Get(effyTG__jetL.c_str());
  effy__graph__jet_c_ = (TGraphAsymmErrors*) effy__tfile_->Get(effyTG__jetC.c_str());
  effy__graph__jet_b_ = (TGraphAsymmErrors*) effy__tfile_->Get(effyTG__jetB.c_str());

  if(!effy__graph__jet_l_) throw std::runtime_error("weightcalc_btagging::weightcalc_btagging -- uninitialized reference to jet b-tagging efficiencies (flavor=l)");
  if(!effy__graph__jet_c_) throw std::runtime_error("weightcalc_btagging::weightcalc_btagging -- uninitialized reference to jet b-tagging efficiencies (flavor=c)");
  if(!effy__graph__jet_b_) throw std::runtime_error("weightcalc_btagging::weightcalc_btagging -- uninitialized reference to jet b-tagging efficiencies (flavor=b)");
}

weightcalc_btagging::~weightcalc_btagging(){

  if(effy__tfile_) effy__tfile_->Close();
}

void weightcalc_btagging::load_SFac(const std::string& btagWP_key, const std::string& sfac_csvfile){

  // scale-factors
  int op_point(-1);

  if     (btagWP_key == "CSVL") op_point = 0;
  else if(btagWP_key == "CSVM") op_point = 1;
  else if(btagWP_key == "CSVT") op_point = 2;
  else throw std::runtime_error("weightcalc_btagging::load_SFac -- invalid key for b-tagging working point: "+btagWP_key);

  if(btagSF_vec_.size()) throw std::runtime_error("weightcalc_btagging::load_SFac -- logic error: list of b-tagging SF values not empty");

  std::ifstream csv_file;
  csv_file.open(sfac_csvfile.c_str());

  if(csv_file.fail()){

    throw std::runtime_error("weightcalc_btagging::load_SFac -- failed to locate input file: "+sfac_csvfile);
  }
  else {

    csv_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    while(std::getline(csv_file, line)){

      std::stringstream line_ss(line);

      weightcalc_btagging::btagSF btag_sf;

      import_entry(line_ss, ',', btag_sf.OperatingPoint);
      if(btag_sf.OperatingPoint != op_point) continue;

      import_entry(line_ss, ',', btag_sf.measurementType);

      import_entry(line_ss, ',', btag_sf.sysType);

      import_entry(line_ss, ',', btag_sf.jetFlavor);

      if(btag_sf.jetFlavor == 2 && btag_sf.measurementType != measurement_type__jetL_) continue;
      if(btag_sf.jetFlavor == 1 && btag_sf.measurementType != measurement_type__jetC_) continue;
      if(btag_sf.jetFlavor == 0 && btag_sf.measurementType != measurement_type__jetB_) continue;

      if(btag_sf.jetFlavor == 2 && btag_sf.sysType != sys_key__jetL_) continue;
      if(btag_sf.jetFlavor == 1 && btag_sf.sysType != sys_key__jetC_) continue;
      if(btag_sf.jetFlavor == 0 && btag_sf.sysType != sys_key__jetB_) continue;

      import_entry(line_ss, ',', btag_sf.etaMin);
      import_entry(line_ss, ',', btag_sf.etaMax);
      import_entry(line_ss, ',', btag_sf.ptMin);
      import_entry(line_ss, ',', btag_sf.ptMax);
      import_entry(line_ss, ',', btag_sf.discrMin);
      import_entry(line_ss, ',', btag_sf.discrMax);

      std::string formula("");
      import_entry(line_ss, ',', formula);
      formula = std::string(formula, 1, formula.length()-2);
      if(formula.find("y") == std::string::npos) formula += "+(y-y)";
      btag_sf.function = TF2("f2", formula.c_str());

      btagSF_vec_.push_back(btag_sf);
    }
  }

  csv_file.close();

  if(!btagSF_vec_.size()){

    std::string log("");
    log += "weightcalc_btagging::load_SFac";
    log += " -- logic error: no entries in the list of b-tagging SF:";
    log +=     " operating_point="+std::to_string(op_point);
    log += " measurement_type(L)="+measurement_type__jetL_;
    log += " measurement_type(C)="+measurement_type__jetC_;
    log += " measurement_type(B)="+measurement_type__jetB_;
    log +=          " sys_key(L)="+sys_key__jetL_;
    log +=          " sys_key(C)="+sys_key__jetC_;
    log +=          " sys_key(B)="+sys_key__jetB_;

    throw std::runtime_error(log);
  }

  if(verbose_){

    for(const auto& sf : btagSF_vec_){

      std::cout <<         sf.OperatingPoint;
      std::cout << ", " << sf.measurementType;
      std::cout << ", " << sf.sysType;
      std::cout << ", " << sf.jetFlavor;
      std::cout << ", " << sf.etaMin;
      std::cout << ", " << sf.etaMax;
      std::cout << ", " << sf.ptMin;
      std::cout << ", " << sf.ptMax;
      std::cout << ", " << sf.discrMin;
      std::cout << ", " << sf.discrMax;
      std::cout << ", " << std::string(sf.function.GetExpFormula());
      std::cout << std::endl;
    }
  }

  return;
}

void weightcalc_btagging::import_entry(std::stringstream& sstrm, const char delim, int& val) const {

  std::string entry;
  std::getline(sstrm, entry, delim);
  entry.erase(std::remove(entry.begin(), entry.end(), ' '), entry.end());

  val = atoi(entry.c_str());

  return;
}

void weightcalc_btagging::import_entry(std::stringstream& sstrm, const char delim, float& val) const {

  std::string entry;
  std::getline(sstrm, entry, delim);
  entry.erase(std::remove(entry.begin(), entry.end(), ' '), entry.end());

  val = atof(entry.c_str());

  return;
}

void weightcalc_btagging::import_entry(std::stringstream& sstrm, const char delim, std::string& val) const {

  std::string entry;
  std::getline(sstrm, entry, delim);
  entry.erase(std::remove(entry.begin(), entry.end(), ' '), entry.end());

  val = std::string(entry);

  return;
}

float weightcalc_btagging::jet_effy(const Jet& jet_) const {

  TGraphAsymmErrors* geff(0);
  if     (std::abs(jet_.hadronFlavor()) == 5) geff = effy__graph__jet_b_;
  else if(std::abs(jet_.hadronFlavor()) == 4) geff = effy__graph__jet_c_;
  else if(std::abs(jet_.hadronFlavor()) == 0) geff = effy__graph__jet_l_;
  else throw std::runtime_error("weightcalc_btagging::jet_effy -- failed to locate graph for jet b-tagging efficiency: "+std::to_string(jet_.hadronFlavor()));

  if(!geff) throw std::runtime_error("weightcalc_btagging::jet_effy -- uninitialized reference to jet b-tagging efficiencies");         

  const float jet_PT = jet_.pt();

  float eff(0.); {

    float pt_min(std::numeric_limits<float>::infinity()), pt_max(-1.);
    for(int i=0; i<geff->GetN(); ++i){

      double x(-1.), y(-1.);
      geff->GetPoint(i, x, y);

      const float pt_lo = (x-geff->GetErrorXlow(i));
      const float pt_hi = (x+geff->GetErrorXhigh(i));

      if     (pt_lo <  jet_PT && jet_PT < pt_hi){ eff = y; break; }
      else if(pt_lo >= jet_PT && pt_min > pt_lo){ eff = y; pt_min = pt_lo; }
      else if(pt_hi <= jet_PT && pt_max < pt_hi){ eff = y; pt_max = pt_hi; }
    }
  }

  if(verbose_) std::cout << " eff=" << eff;

  return eff;
}

float weightcalc_btagging::jet_SFac(const Jet& jet_) const {

  int jet_FLAV(-1);
  if     (std::abs(jet_.hadronFlavor()) == 5) jet_FLAV = 0;
  else if(std::abs(jet_.hadronFlavor()) == 4) jet_FLAV = 1;
  else if(std::abs(jet_.hadronFlavor()) == 0) jet_FLAV = 2;
  else throw std::runtime_error("weightcalc_btagging::jet_SFac -- failed to assign key for jet flavor");

  const float jet_pt  = jet_.pt();
  const float jet_ETA = jet_.eta();

  float jet_PT(jet_pt), sf(1.); {

    int idx(-1); {

      float pt_min(std::numeric_limits<float>::infinity()), pt_max(-1.);
      for(unsigned int i=0; i<btagSF_vec_.size(); ++i){

        const weightcalc_btagging::btagSF& btag_sf = btagSF_vec_.at(i);

        if(btag_sf.jetFlavor == jet_FLAV){

          if(btag_sf.etaMin<jet_ETA && jet_ETA < btag_sf.etaMax){

            const float pt_lo = btag_sf.ptMin;
            const float pt_hi = btag_sf.ptMax;

            if     (pt_lo <  jet_pt && jet_pt <  pt_hi){ idx = i; jet_PT = jet_pt; break; }
            else if(pt_lo >= jet_pt && pt_min >= pt_lo){ idx = i; jet_PT = pt_lo; pt_min = pt_lo; }
            else if(pt_hi <= jet_pt && pt_max <= pt_hi){ idx = i; jet_PT = pt_hi; pt_max = pt_hi; }
          }
        }
      }
    }

    if(idx == -1) sf = 1.;
    else {

      sf = btagSF_vec_.at(idx).function.Eval(jet_PT, jet_ETA);
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

float weightcalc_btagging::weight(const uhh2::Event& evt_) const {

  float wgt(1.);

  assert(evt_.jets);

  for(const auto& jet : *evt_.jets){

    const float sfac =          jet_SFac(jet);
    const float effy = std::min(jet_effy(jet), float(0.99999));

    if(verbose_) std::cout << std::endl;

    if(btagWP_(jet, evt_)) wgt *=     sfac;
    else                   wgt *= (1.-sfac*effy) / (1.-effy);
  }

  return wgt;
}
