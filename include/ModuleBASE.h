#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Hists.h>

class ModuleBASE: public uhh2::AnalysisModule {

 public:
  explicit ModuleBASE() {}
  explicit ModuleBASE(uhh2::Context&) {}
  virtual bool process(uhh2::Event&);

 protected:
  typedef std::unordered_map<std::string, std::unique_ptr<uhh2::Hists> >::iterator hfolder_itr;
          std::unordered_map<std::string, std::unique_ptr<uhh2::Hists> > hfolder_;

  template<typename F> void book_HFolder(const std::string&, F*);
  template<typename F=uhh2::Hists> F* HFolder(const std::string&);
};

template<typename F>
void ModuleBASE::book_HFolder(const std::string& dname_, F* f_ptr){

  if(hfolder_.find(dname_) != hfolder_.end()) throw std::runtime_error("ModuleBASE::book_HFolder -- already existing folder key: "+dname_);
  else {

    hfolder_[dname_].reset(f_ptr);
  }

  return;
}

template<typename F>
F* ModuleBASE::HFolder(const std::string& key_){

  F* f(0);

  if(hfolder_.find(key_) != hfolder_.end()) f = static_cast<F*>(hfolder_[key_].get());
  else throw std::runtime_error("ModuleBASE::HFolder -- folder key not found: "+key_);

  if(!f) throw std::runtime_error("ModuleBASE::HFolder -- null pointer to folder: "+key_);

  return f;
}
