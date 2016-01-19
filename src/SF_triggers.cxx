#include <UHH2/ZprimeSemiLeptonic/include/SF_triggers.h>

weightcalc_triggers::weightcalc_triggers(const std::string& sffit_file){

   //ele45_pfjet200_pfjet50
   f_sffit = TFile::Open(sffit_file.c_str());
   if(!f_sffit) throw std::runtime_error("weightcalc_trigger failed to locate sf fit file");
   SFfit = (TF1*) f_sffit->Get("fit_200_50");
  if (!SFfit) throw std::runtime_error("weightcalc_trigger failed to locate TF1 of the fit");
  
}

weightcalc_triggers::~weightcalc_triggers(){

   f_sffit->Close();
}

float weightcalc_triggers::weight(const uhh2::Event& evt) const{

   if(!evt.isRealData) return 1.;
   float wgt(1.);
  
   float arg = evt.jets->at(0).pt();  
   if(arg < SFfit->GetXmin()){ arg = SFfit->GetXmin(); }
   else if(arg > SFfit->GetXmax()){ arg = SFfit->GetXmax(); }

   wgt = SFfit->Eval(arg);
  
   return wgt;
}
