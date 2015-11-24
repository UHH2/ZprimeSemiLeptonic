#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>

void HistsBASE::book_TH1F(const std::string& name_, const int xnbins_, const double xmin_, const double xmax_){

  if(h1.find(name_) == h1.end()) h1[name_] = book<TH1F>(name_.c_str(), name_.c_str(), xnbins_, xmin_, xmax_);
  else throw std::runtime_error("HistsBASE::book_TH1F -- histogram key already existing: "+name_);

  return;
}

void HistsBASE::book_TH1F(const std::string& name_, const int xnbins_, const double* xbin_ls_){

  if(h1.find(name_) == h1.end()) h1[name_] = book<TH1F>(name_.c_str(), name_.c_str(), xnbins_, xbin_ls_);
  else throw std::runtime_error("HistsBASE::book_TH1F -- histogram key already existing: "+name_);

  return;
}

void HistsBASE::book_TH2F(const std::string& name_, const int xnbins_, const double xmin_, const double xmax_, const int ynbins_, const double ymin_, const double ymax_){

  if(h2.find(name_) == h2.end()) h2[name_] = book<TH2F>(name_.c_str(), name_.c_str(), xnbins_, xmin_, xmax_, ynbins_, ymin_, ymax_);
  else throw std::runtime_error("HistsBASE::book_TH2F -- histogram key already existing: "+name_);

  return;
}

void HistsBASE::book_TH2F(const std::string& name_, const int xnbins_, const double* xbin_ls_, const int ynbins_, const double* ybin_ls_){

  if(h2.find(name_) == h2.end()) h2[name_] = book<TH2F>(name_.c_str(), name_.c_str(), xnbins_, xbin_ls_, ynbins_, ybin_ls_);
  else throw std::runtime_error("HistsBASE::book_TH2F -- histogram key already existing: "+name_);

  return;
}

TH1F* HistsBASE::H1(const std::string& key_){

  TH1F* h(0);

  if(h1.find(key_) != h1.end()) h = h1[key_];
  else throw std::runtime_error("HistsBASE::H1 -- histogram key not found: "+key_);

  return h;
}

TH2F* HistsBASE::H2(const std::string& key_){

  TH2F* h(0);

  if(h2.find(key_) != h2.end()) h = h2[key_];
  else throw std::runtime_error("HistsBASE::H2 -- histogram key not found: "+key_);

  return h;
}
