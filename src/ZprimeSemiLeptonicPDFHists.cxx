#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicPDFHists.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/JetIds.h"
#include <math.h>
#include <sstream>

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <UHH2/core/include/LorentzVector.h>
#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;

ZprimeSemiLeptonicPDFHists::ZprimeSemiLeptonicPDFHists(uhh2::Context & ctx, const std::string& dirname): 
Hists(ctx, dirname){
 
  is_mc = ctx.get("dataset_type") == "MC";
  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");

  for(int i=0; i<100; i++){
    std::stringstream ss_name;
    ss_name << "M_Zprime_PDF_" << i+1;

    stringstream ss_title;
    ss_title << "M_{t#bar{t}} [GeV] for PDF No. "  << i+1 << " out of 100" ;

    std::string s_name = ss_name.str();
    std::string s_title = ss_title.str();
    const char* char_name = s_name.c_str();
    const char* char_title = s_title.c_str();
 
    hist_names[i] = s_name;

    vector<float> bins_Zprime = {0,400,600,800,1000,1200,1400,1600,1800,2000,2200,2400,2600,2800,3000,3200,3400,3600,3800,4000,4400,4800,5200,5600,6000,6100};

    book<TH1F>(char_name, char_title,  bins_Zprime.size()-1, &bins_Zprime[0]);

  }
}

void ZprimeSemiLeptonicPDFHists::fill(const Event & event){

  double weight = event.weight;

  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
  if(is_zprime_reconstructed_chi2 && is_mc){
    ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);
    float Mreco = BestZprimeCandidate->Zprime_v4().M();

    if(event.genInfo->systweights().size()){
    float orig_weight = event.genInfo->originalXWGTUP();
    int MY_FIRST_INDEX = 9;
      for(int i=0; i<100; i++){
        double pdf_weight = event.genInfo->systweights().at(i+MY_FIRST_INDEX);
        const char* name = hist_names[i].c_str();
        hist(name)->Fill(Mreco,weight * pdf_weight / orig_weight);
      }
    }
  }

}

ZprimeSemiLeptonicPDFHists::~ZprimeSemiLeptonicPDFHists(){}
