#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/common/include/PrintingModules.h"
#include "UHH2/common/include/MCWeight.h"
#include "UHH2/common/include/PSWeights.h"

#include "UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h"
#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_TTbarGen.h"
#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_TTbarGenHists.h"
#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_SystematicsHists.h"
#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_PDFHists.h"

using namespace std;
using namespace uhh2;

class TOP20001_RecastModule: public AnalysisModule{
public:

  explicit TOP20001_RecastModule(Context & ctx);
  virtual bool process(Event & event) override;

private:
  string Sys_PU;
  unique_ptr<AnalysisModule> printer, PUWeight_module, LumiWeight_module, MCScale_module, ttgenprod;
  unique_ptr<PSWeights> ps_weights;
  unique_ptr<Hists> ttgenhists, systhists, pdfhists;
  Event::Handle<TOP20001_TTbarGen> h_ttbargen;
};

TOP20001_RecastModule::TOP20001_RecastModule(Context & ctx){
  Sys_PU = ctx.get("Sys_PU");
  printer.reset(new GenParticlesPrinter(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  MCScale_module.reset(new MCScaleVariation(ctx));
  ps_weights.reset(new PSWeights(ctx));
  ttgenprod.reset(new TOP20001_TTbarGenProducer(ctx, "ttbargen", true));
  h_ttbargen = ctx.get_handle<TOP20001_TTbarGen>("ttbargen");
  ttgenhists.reset(new TOP20001_TTbarGenHists(ctx, "ttgenhists"));
  pdfhists.reset(new TOP20001_PDFHists(ctx, "PDFHists"));
  systhists.reset(new TOP20001_SystematicsHists(ctx, "SystematicsHists"));
}

bool TOP20001_RecastModule::process(Event & event){
  // printer->process(event);
  ttgenprod->process(event);
  PUWeight_module->process(event);
  LumiWeight_module->process(event);
  MCScale_module->process(event);
  ps_weights->process(event);
  ttgenhists->fill(event);
  pdfhists->fill(event);
  systhists->fill(event);
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TOP20001_RecastModule)
