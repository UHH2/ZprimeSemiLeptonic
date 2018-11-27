#pragma once

#include "UHH2/core/include/Particle.h"
#include "UHH2/core/include/TopJet.h"
#include <map>

class ZprimeCandidate{

public:

  // Getter
  LorentzVector Zprime_v4() const{return m_Zprime_v4;}
  LorentzVector top_leptonic_v4() const{return m_top_leptonic_v4;}
  LorentzVector top_hadronic_v4() const{return m_top_hadronic_v4;}
  std::vector<Particle> jets_hadronic() const{return m_jets_hadronic;}
  std::vector<Particle> jets_leptonic() const{return m_jets_leptonic;}
  const TopJet* tophad_topjet_ptr() const{return m_tophad_topjet_ptr;}
  Particle lepton() const{return m_lepton;}
  LorentzVector neutrino_v4() const{return m_neutrino_v4;}
  unsigned int neutrinoindex() {return m_neutrinoindex;}
  bool is_toptag_reconstruction() const{return m_is_toptag_reconstruction;}
  bool is_puppi_reconstruction() const{return m_is_puppi_reconstruction;}
  float discriminator(const TString & l) const {
    auto it = m_discriminators.find(l);
    if(it == m_discriminators.end()) throw std::runtime_error("ZprimeCandidate::discriminator(): discriminator with label '" + l + "' not set");
    return it->second;
  }
  bool has_discriminator(const std::string & label) const {return m_discriminators.find(label) != m_discriminators.end();}

  // Setters
  void set_Zprime_v4(LorentzVector x) {m_Zprime_v4=x;}
  void set_top_leptonic_v4(LorentzVector x) {m_top_leptonic_v4=x;}
  void set_top_hadronic_v4(LorentzVector x) {m_top_hadronic_v4=x;}
  void set_jets_hadronic(std::vector<Particle> x) {m_jets_hadronic=x;}
  void set_jets_leptonic(std::vector<Particle> x) {m_jets_leptonic=x;}
  void set_tophad_topjet_ptr(const TopJet* const tjp){m_tophad_topjet_ptr = tjp;}
  void set_lepton(Particle x) {m_lepton=x;}
  void set_neutrino_v4(LorentzVector x) {m_neutrino_v4=x;}
  void set_neutrinoindex(unsigned int x) {m_neutrinoindex = x;}
  void set_is_toptag_reconstruction(bool x) {m_is_toptag_reconstruction=x;}
  void set_is_puppi_reconstruction(bool x) {m_is_puppi_reconstruction=x;}
  void set_discriminators(const TString & label, float discr) { m_discriminators[label] = discr;}


private:


  LorentzVector m_Zprime_v4;
  LorentzVector m_top_leptonic_v4;
  LorentzVector m_top_hadronic_v4;
  std::vector<Particle> m_jets_hadronic;
  std::vector<Particle> m_jets_leptonic;
  const TopJet* m_tophad_topjet_ptr;
  Particle m_lepton;
  LorentzVector m_neutrino_v4;
  unsigned int m_neutrinoindex;

  bool m_is_toptag_reconstruction;
  bool m_is_puppi_reconstruction;
  std::map<TString, float> m_discriminators;

};
