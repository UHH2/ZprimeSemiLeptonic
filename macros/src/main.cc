#include <cmath>
#include <iostream>
#include "../include/Tools.h"
#include <TString.h>

using namespace std;

int main(int argc, char* argv[]){

  // Parse arguments
  if(argc != 2) throw runtime_error("Expected exactly one argument.");
  cout << "Argument given: " << argv[1] << endl;


  // General settings
  bool do_puppi = true;



  // Do the stuff
  AnalysisTool Analysis(do_puppi);
  if(!strcmp(argv[1], "CalculateReconstructionQuality") || !strcmp(argv[1], "All")) Analysis.CalculateReconstructionQuality();
  if(!strcmp(argv[1], "CalculateChi2Values") || !strcmp(argv[1], "All")) Analysis.CalculateChi2Values();
  if(!strcmp(argv[1], "CompareCHSPuppi") || !strcmp(argv[1], "All")) Analysis.CompareCHSPuppi();
  if(!strcmp(argv[1], "PlotLimits") || !strcmp(argv[1], "All")) Analysis.PlotLimits();
  if(!strcmp(argv[1], "PlotPostfitDistributions") || !strcmp(argv[1], "All")) Analysis.PlotPostfitDistributions();
  if(!strcmp(argv[1], "PlotPostfitParameters") || !strcmp(argv[1], "All")) Analysis.PlotPostfitParameters();


  cout << "Finished main(). Good-bye." << endl;
}
