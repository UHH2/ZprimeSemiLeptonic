#include <iostream>
#include <memory>

#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSystematicsModule.h>

using namespace std;
using namespace uhh2;

void ZprimeSemiLeptonicSystematicsModule::book_histograms(Context& ctx, vector<string> v_tags){
  for(const auto & tag : v_tags){
    // cout << "booking histograms with tag: " << tag << endl;
    book_HFolder(tag, new ZprimeSemiLeptonicHists(ctx, tag));
  }
}

void ZprimeSemiLeptonicSystematicsModule::fill_histograms(Event& event, string tag){
  HFolder(tag)->fill(event);
}

ZprimeSemiLeptonicSystematicsModule::ZprimeSemiLeptonicSystematicsModule(Context& ctx){
  for(auto & kv : ctx.get_all()) cout << " " << kv.first << " = " << kv.second << endl;

  is_MC = (ctx.get("dataset_type") == "MC");
  dataset_version = ctx.get("dataset_version");

  h_ttIsReconstructed = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  eventweight_nominal = ctx.get_handle<float>("eventweight");
  isDifferentPDFSet = false;
  if(dataset_version.Contains("WJetsToLNu_HT-") || dataset_version.Contains("DYJetsToLL_M-50_HT-") || dataset_version.Contains("QCD_HT") || dataset_version.Contains("ALP_ttbar_") || dataset_version.Contains("HscalarToTTTo1L1Nu2J_") || dataset_version.Contains("HpseudoToTTTo1L1Nu2J_") || dataset_version.Contains("ZPrimeToTT_")){
    isDifferentPDFSet = true;
    cout << " is nonstandard pdf set = true" << endl;
  }

  v_systs = {"pu", "prefiring", "mu_id", "mu_iso", "mu_reco", "mu_trigger", "ele_id", "ele_reco", "ele_trigger", "btag_cferr1", "btag_cferr2", "btag_hf", "btag_hfstats1", "btag_hfstats2", "btag_lf", "btag_lfstats1", "btag_lfstats2", "ttag_corr", "ttag_uncorr"};
  v_syst_handlenames = {"weight_pu", "prefiringWeight", "weight_sfmu_id", "weight_sfmu_iso", "weight_sfmu_reco", "weight_sfmu_trigger", "weight_sfelec_id", "weight_sfelec_reco", "weight_sfelec_trigger", "weight_btagdisc_cferr1", "weight_btagdisc_cferr2", "weight_btagdisc_hf", "weight_btagdisc_hfstats1", "weight_btagdisc_hfstats2", "weight_btagdisc_lf", "weight_btagdisc_lfstats1", "weight_btagdisc_lfstats2", "weight_toptagsf_corr", "weight_toptagsf_uncorr"};
  v_psscales = {"isr", "fsr"};
  v_psscale_handlenames = {"weight_isr_2", "weight_fsr_2"};
  v_variations = {"up", "down"};
  v_mcscale_vars = {"upup", "upnone", "noneup", "nonedown", "downnone", "downdown"};

  // nominal
  v_nominal_dirtags = {"nominal"};
  book_histograms(ctx, v_nominal_dirtags);

  // simple up/down variations
  v_syst_dirtags = {};
  if(v_systs.size() != v_syst_handlenames.size()) throw runtime_error("In ZprimeSemiLeptonicSystematicsModule.cxx: Length of v_systs and v_syst_handlenames is not equal.");
  for(unsigned int i=0; i<v_systs.size(); ++i){
    for(unsigned int j=0; j<v_variations.size(); ++j){
      TString handlename_nominal = v_syst_handlenames[i];
      TString handlename_shift = v_syst_handlenames[i] + "_" + v_variations[j];

      if(v_systs[i] == "prefiring"){ // prefiringWeight has different syntax
        handlename_shift = v_syst_handlenames[i];
        if(v_variations[j] == "up") handlename_shift = handlename_shift + "Up";
        else if(v_variations[j] == "down") handlename_shift = handlename_shift + "Down";
        else throw runtime_error("In ZprimeSemiLeptonicSystematicsModule.cxx: Variation is neither up nor down.");
      }
      else if(v_systs[i].Contains("btag")){ // all btag variations have the same nominal
        handlename_nominal = "weight_btagdisc_central";
      }
      else if(v_systs[i].Contains("ttag")){ // ttag variations have the same nominal
        handlename_nominal = "weight_toptagsf";
      }

      uhh2::Event::Handle<float> handle_nominal = ctx.declare_event_output<float>((string) handlename_nominal);
      uhh2::Event::Handle<float> handle_shift = ctx.declare_event_output<float>((string) handlename_shift);

      v_systhandles_nominal.emplace_back(handle_nominal);
      v_systhandles_var.emplace_back(handle_shift);

      TString dirname = v_systs[i] + "_" + v_variations[j];
      v_syst_dirtags.emplace_back(dirname);
    }
  }
  book_histograms(ctx, v_syst_dirtags);

  // ps scale: isr + fsr
  if(v_psscales.size() != v_psscale_handlenames.size()) throw runtime_error("In ZprimeSemiLeptonicSystematicsModule.cxx: Length of v_psscales and v_psscale_handlenames is not equal.");
  for(unsigned int i=0; i<v_psscales.size(); ++i){
    for(unsigned int j=0; j<v_variations.size(); ++j){
      TString handlename_shift = v_psscale_handlenames[i] + "_" + v_variations[j];
      uhh2::Event::Handle<float> handle_shift = ctx.declare_event_output<float>((string) handlename_shift);
      v_psscalehandles.emplace_back(handle_shift);
      TString dirname = v_psscales[i] + "_" + v_variations[j];
      v_psscale_dirtags.emplace_back(dirname);
    }
  }
  book_histograms(ctx, v_psscale_dirtags);

  // mc scale
  for(unsigned int i=0; i<v_mcscale_vars.size(); ++i){
    TString handlename_shift = "weight_murmuf_" + v_mcscale_vars[i];
    uhh2::Event::Handle<float> handle_shift = ctx.declare_event_output<float>((string) handlename_shift);
    v_mcscalehandles.emplace_back(handle_shift);
    TString dirname = "murmuf_" + v_mcscale_vars[i];
    v_mcscale_dirtags.emplace_back(dirname);
  }
  book_histograms(ctx, v_mcscale_dirtags);

  // pdf
  for(unsigned int i=0; i<100; ++i){
    stringstream ss_i;
    ss_i << i;
    TString dirname = "pdf" + ss_i.str();
    v_pdf_dirtags.emplace_back(dirname);
  }
  book_histograms(ctx, v_pdf_dirtags);
}

bool ZprimeSemiLeptonicSystematicsModule::process(Event& event){

  bool ttIsReconstructed = event.get(h_ttIsReconstructed);
  if(!ttIsReconstructed) throw runtime_error("In ZprimeSemiLeptonicSystematicsModule.cxx: TTbar not reconstructed!");

  float weight_nominal = event.get(eventweight_nominal);
  event.weight = weight_nominal;

  // nominal
  fill_histograms(event, "nominal");

  if(is_MC){ // fill systematic hists for MC only
    // simple up/down variations
    for(unsigned int i=0; i<v_systs.size(); ++i){
      for(unsigned int j=0; j<v_variations.size(); ++j){
        int index = 2 * i + j;
        float weight_systnominal = event.get(v_systhandles_nominal[index]);
        float weight_systvar = event.get(v_systhandles_var[index]);
        event.weight = weight_nominal * weight_systvar / weight_systnominal;
        TString tag = v_systs[i] + "_" + v_variations[j];
        fill_histograms(event, (string) tag);
      }
    }
    // psscale: isr + fsr
    for(unsigned int i=0; i<v_psscales.size(); ++i){
      for(unsigned int j=0; j<v_variations.size(); ++j){
        float weight_psscalevar = event.get(v_psscalehandles[i]);
        event.weight = weight_nominal * weight_psscalevar;
        TString tag = v_psscales[i] + "_" + v_variations[j];
        fill_histograms(event, (string) tag);
      }
    }
    // mc scale
    for(unsigned int i=0; i<v_mcscale_vars.size(); ++i){
      float weight_mcscalevar = event.get(v_mcscalehandles[i]);
      event.weight = weight_nominal * weight_mcscalevar;
      TString tag = "murmuf_" + v_mcscale_vars[i];
      fill_histograms(event, (string) tag);
    }
    // pdf
    int startindex = 9;
    if(isDifferentPDFSet) startindex = 47;
    if(event.genInfo->systweights().size() > (unsigned int) startindex + 100){ // there are some events without proper systweights which are ignored here (otherwise code will crash)
      for(unsigned int i=0; i<100; ++i){
        float weight_pdfnominal = event.genInfo->originalXWGTUP();
        float weight_pdfvar = event.genInfo->systweights().at(startindex + i);
        event.weight = weight_nominal * weight_pdfvar / weight_pdfnominal;
        stringstream ss_i;
        ss_i << i;
        TString tag = "pdf" + ss_i.str();
        fill_histograms(event, (string) tag);
      }
    }
  }

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeSemiLeptonicSystematicsModule)
