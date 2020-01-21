#include <cmath>
#include <iostream>
#include "../include/Tools.h"
#include "TString.h"

using namespace std;

int main(int argc, char* argv[]){

  // Parse arguments, first one defines function(s) to run, second one decides if puppi or CHS
  if(argc != 3) throw runtime_error("Expected exactly two arguments .");

  cout << "Arguments given: ";
  for(int i=1; i<3; i++) cout << argv[i];
  cout << endl;


  // General settings
  bool do_puppi = (!strcmp(argv[2], "true"));
  cout << "do_puppi: " << do_puppi << endl;



  // Do the stuff
  AnalysisTool Analysis(do_puppi);
//  if(!strcmp(argv[1], "CalculateReconstructionQuality") || !strcmp(argv[1], "All")) Analysis.CalculateReconstructionQuality();
  if(!strcmp(argv[1], "CalculateChi2Values") || !strcmp(argv[1], "All")) Analysis.CalculateChi2Values();
//  if(!strcmp(argv[1], "CompareCHSPuppi") || !strcmp(argv[1], "All")) Analysis.CompareCHSPuppi();
//  if(!strcmp(argv[1], "ProduceThetaHistograms") || !strcmp(argv[1], "All")) Analysis.ProduceThetaHistograms();
//  if(!strcmp(argv[1], "PlotLimits") || !strcmp(argv[1], "All")) Analysis.PlotLimits();
//  if(!strcmp(argv[1], "PlotPostfitDistributions") || !strcmp(argv[1], "All")) Analysis.PlotPostfitDistributions();
//  if(!strcmp(argv[1], "PlotPostfitParameters") || !strcmp(argv[1], "All")) Analysis.PlotPostfitParameters();


  cout << "Finished main(). Good-bye." << endl;
}
