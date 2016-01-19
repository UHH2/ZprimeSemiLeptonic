#pragma once
#include <string>
#include <TFile.h>
#include <TF1.h>
#include <UHH2/core/include/Event.h>

class weightcalc_triggers{

   public:
     explicit weightcalc_triggers(const std::string&);
     virtual ~weightcalc_triggers();
     virtual float weight(const uhh2::Event&) const;


   protected:
     TFile* f_sffit;
     TF1* SFfit;
};

