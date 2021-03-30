#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicMulticlassNNHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;

ZprimeSemiLeptonicMulticlassNNHists::ZprimeSemiLeptonicMulticlassNNHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {

  h_NNoutput0 = ctx.get_handle<double>("NNoutput0");
  h_NNoutput1 = ctx.get_handle<double>("NNoutput1");
  h_NNoutput2 = ctx.get_handle<double>("NNoutput2");
  init();
}

void ZprimeSemiLeptonicMulticlassNNHists::init(){

NN_out0 = book<TH1F>("NN_out0", "NN output 0", 100, 0, 1);
NN_out1 = book<TH1F>("NN_out1", "NN output 1", 100, 0, 1);
NN_out2 = book<TH1F>("NN_out2", "NN output 2", 100, 0, 1);
}

void ZprimeSemiLeptonicMulticlassNNHists::fill(const Event & event){

double weight = event.weight;
double NNoutput0 = event.get(h_NNoutput0);
double NNoutput1 = event.get(h_NNoutput1);
double NNoutput2 = event.get(h_NNoutput2);

NN_out0->Fill(NNoutput0, weight);
NN_out1->Fill(NNoutput1, weight);
NN_out2->Fill(NNoutput2, weight);

}

ZprimeSemiLeptonicMulticlassNNHists::~ZprimeSemiLeptonicMulticlassNNHists(){}
