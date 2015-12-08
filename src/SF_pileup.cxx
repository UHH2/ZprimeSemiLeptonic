#include <UHH2/ZprimeSemiLeptonic/include/SF_pileup.h>

weightcalc_pileup::weightcalc_pileup(const std::string& pu_file_DATA, const std::string& pu_file_MC, const std::string& pu_hist_DATA, const std::string& pu_hist_MC){

  // DATA
  f_pileupDATA_ = TFile::Open(pu_file_DATA.c_str());
  if(!f_pileupDATA_) throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- failed to locate input file for DATA pileup distribution: "+pu_file_DATA);

  h_pileupDATA_ = (TH1F*) f_pileupDATA_->Get(pu_hist_DATA.c_str());
  if(!h_pileupDATA_) throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- failed to load TH1 object for DATA pileup distribution: "+pu_hist_DATA);

  // MC
  f_pileupMC_ = TFile::Open(pu_file_MC.c_str());
  if(!f_pileupMC_) throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- failed to locate input file for MC pileup distribution: "+pu_file_MC);

  h_pileupMC_ = (TH1F*) f_pileupMC_->Get(pu_hist_MC.c_str());
  if(!h_pileupMC_) throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- failed to load TH1 object for MC pileup distribution: "+pu_hist_MC);

  // input validation
  if(h_pileupDATA_->GetNbinsX() != h_pileupMC_->GetNbinsX()){
    throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- DATA and MC pileup histograms have different numbers of bins");
  }

  if(h_pileupDATA_->GetXaxis()->GetXmin() != h_pileupMC_->GetXaxis()->GetXmin()){
    throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- DATA and MC pileup histograms have different minimum value on the x-axis");
  }

  if(h_pileupDATA_->GetXaxis()->GetXmax() != h_pileupMC_->GetXaxis()->GetXmax()){
    throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- DATA and MC pileup histograms have different maximum value on the x-axis");
  }

  // input rescaling
  if(!h_pileupDATA_->Integral(0,-1)) throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- null integral for DATA pileup histogram");
  if(!h_pileupMC_  ->Integral(0,-1)) throw std::runtime_error("weightcalc_pileup::weightcalc_pileup -- null integral for MC pileup histogram");

  h_pileupDATA_->Scale(1./h_pileupDATA_->Integral(0,-1));
  h_pileupMC_  ->Scale(1./h_pileupMC_  ->Integral(0,-1));
}

weightcalc_pileup::~weightcalc_pileup(){

  if(f_pileupDATA_) f_pileupDATA_->Close();
  if(f_pileupMC_)   f_pileupMC_  ->Close();
}

float weightcalc_pileup::weight(const uhh2::Event& evt_) const {

  if(evt_.isRealData) return 1.;

  if(!evt_.genInfo) throw std::runtime_error("weightcalc_pileup::weight -- null pointer in uhh2::Event::genInfo");

  float wgt(1.);

  const int bin_num = h_pileupMC_->GetXaxis()->FindBin(evt_.genInfo->pileup_TrueNumInteractions());
  if(h_pileupMC_->GetBinContent(bin_num)) wgt = (h_pileupDATA_->GetBinContent(bin_num) / h_pileupMC_->GetBinContent(bin_num));

  return wgt;
}
