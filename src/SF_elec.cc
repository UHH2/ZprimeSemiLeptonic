#include <UHH2/ZprimeSemiLeptonic/include/SF_elec.h>

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <algorithm>

weightcalc_elecID::weightcalc_elecID(uhh2::Context& ctx, const std::string& objs, const std::string& sfacF, const std::string& sfacH, const float sys_pct){

  verbose_ = false;

  // object collection
  h_objs_ = ctx.get_handle<std::vector<Electron>>(objs);

  // scale-factors
  sfac__tfile_ = TFile::Open(sfacF.c_str());
  if(!sfac__tfile_) throw std::runtime_error("weightcalc_elecID::weightcalc_elecID -- failed to locate input file for elec-ID SFs: "+sfacF);

  sfac__thist_ = (TH2F*) sfac__tfile_->Get(sfacH.c_str());
  if(!sfac__thist_) throw std::runtime_error("weightcalc_elecID::weightcalc_elecID -- uninitialized reference to TH2F object for elec-ID SFs: "+sfacF+"/"+sfacH);

//  if     (sfacH.find("abseta_pt_ratio") != std::string::npos) sfac__input_ = "abseta_vs_pt";
//  else if(sfacH.find("pt_abseta_ratio") != std::string::npos) sfac__input_ = "pt_vs_abseta";
//  else throw std::runtime_error("weightcalc_elecID::weightcalc_elecID -- failed to initialize key for elec-ID SF type: "+sfacF+"/"+sfacH);
  sfac__input_ = "et_vs_absetaSC";

  if(0.<=sys_pct && sys_pct<1.) sys_pct_ = sys_pct;
  else throw std::runtime_error("weightcalc_elecID::weightcalc_elecID -- invalid value for additional systematic uncertainty: sys_pct="+std::to_string(sys_pct));
}

weightcalc_elecID::~weightcalc_elecID(){

  if(sfac__tfile_) sfac__tfile_->Close();
}

float weightcalc_elecID::elec_SFac(const Electron& ele, const std::string& sys_key) const {

  float sf(1.);

  float valX(0.), valY(0.);
  if(sfac__input_ == "absetaSC_vs_et"){

    valX = fabs(ele.supercluster_eta());
    valY = ele.v4().Et();
  }
  else if(sfac__input_ == "et_vs_absetaSC"){

    valX = ele.v4().Et();
    valY = fabs(ele.supercluster_eta());
  }
  else throw std::runtime_error("weightcalc_elecID::elec_SFac -- undefined key for SF input format: "+sfac__input_);

  bool out_of_range(false);

  int binX(sfac__thist_->GetXaxis()->FindBin(valX));
  if     (binX > sfac__thist_->GetXaxis()->GetNbins()){ binX = sfac__thist_->GetXaxis()->GetNbins(); out_of_range = true; }
  else if(!binX)                                      { binX = 1;                                    out_of_range = true; }

  int binY(sfac__thist_->GetYaxis()->FindBin(valY));
  if     (binY > sfac__thist_->GetYaxis()->GetNbins()){ binY = sfac__thist_->GetYaxis()->GetNbins(); out_of_range = true; }
  else if(!binY)                                      { binY = 1;                                    out_of_range = true; }

  const float val(sfac__thist_->GetBinContent(binX, binY));
  const float err(sfac__thist_->GetBinError  (binX, binY));

  if     (sys_key == "CT") sf = val;
  else if(sys_key == "UP") sf = val + (1+int(out_of_range)) * ( sqrt(pow(err,2) + pow(sys_pct_*val,2)) );
  else if(sys_key == "DN") sf = val - (1+int(out_of_range)) * ( sqrt(pow(err,2) + pow(sys_pct_*val,2)) );
  else throw std::runtime_error("weightcalc_elecID::elec_SFac -- undefined key for systematic variation: "+sys_key);

  return sf;
}

float weightcalc_elecID::weight(const uhh2::Event& evt_, const std::string& sys_key) const {

  float wgt(1.);

  const auto& objs = evt_.get(h_objs_);

  for(unsigned int i=0; i<objs.size(); ++i){

    const float sfac = elec_SFac(objs.at(i), sys_key);

    if(verbose_){

      std::cout << " elec: ";
      std::cout <<   " pt=" << objs.at(i).pt();
      std::cout <<  " eta=" << objs.at(i).eta();
      std::cout <<   " SF=" << sfac;
      std::cout << " (sys=" << sys_key << ")";
      std::cout << std::endl;
    }

    wgt *= sfac;
  }

  return wgt;
}
