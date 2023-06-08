#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"

TString dir = "/nfs/dust/cms/group/zprime-uhh/AnalysisDNN_UL17/electron/"; // electron / muon

TList *FileList;
TFile *Target;
vector<double> v_weights;

void MergeRootfile(TDirectory *target, TList *sourcelist, vector<double> v_weights);

void hadd_ALPsignals(){

  int sqrtmu = 5;
  stringstream ss_sqrtmu;
  ss_sqrtmu << sqrtmu;
  string s_sqrtmu;
  if(sqrtmu > 0){
    s_sqrtmu = "plus";
    s_sqrtmu += (string) ss_sqrtmu.str();
  }
  else if(sqrtmu < 0){
    s_sqrtmu = "minus";
    s_sqrtmu += (string) ss_sqrtmu.str();
    s_sqrtmu.erase(remove(s_sqrtmu.begin(), s_sqrtmu.end(), '-'), s_sqrtmu.end());
  }
  cout << "sqrtmu: " << s_sqrtmu << endl;

  // interference is already scaled by (-1) in the analysis!!!
  double mu = pow(sqrtmu, 2);
  v_weights = {1., 1., 1., 1., 1., mu, (double) 1. * sqrtmu}; // weights for samples in the FileList (starting with the 2nd)

  Target = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.ALP_sqrtmu_" + s_sqrtmu + ".root", "RECREATE");

  FileList = new TList();
  FileList->Add(TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.TTbar.root"));
  FileList->Add(TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.WJets.root"));
  FileList->Add(TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.ST.root"));
  FileList->Add(TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.DY.root"));
  FileList->Add(TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.Diboson.root"));
  FileList->Add(TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.QCD.root"));
  FileList->Add(TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.ALP_ttbar_signal.root"));
  FileList->Add(TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.ALP_ttbar_interference.root"));

  // TOP-20-001 recast
  // FileList->Add(TFile::Open("uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic.root"));
  // FileList->Add(TFile::Open("uhh2.AnalysisModuleRunner.MC.ALP_ttbar_signal.root"));
  // FileList->Add(TFile::Open("uhh2.AnalysisModuleRunner.MC.ALP_ttbar_interference.root"));

  MergeRootfile(Target, FileList, v_weights);
}


void MergeRootfile(TDirectory *target, TList *sourcelist, vector<double> v_weights){

  //  cout << "Target path: " << target->GetPath() << endl;
  TString path( (char*)strstr( target->GetPath(), ":" ) );
  path.Remove( 0, 2 );

  TFile *first_source = (TFile*)sourcelist->First();

  first_source->cd( path );
  TDirectory *current_sourcedir = gDirectory;
  //gain time, do not add the objects in the list in memory
  Bool_t status = TH1::AddDirectoryStatus();
  TH1::AddDirectory(kFALSE);

  // loop over all keys in this directory
  TChain *globChain = 0;
  TIter nextkey( current_sourcedir->GetListOfKeys() );
  TKey *key, *oldkey=0;
  while ( (key = (TKey*)nextkey())) {

    //keep only the highest cycle number for each key
    if (oldkey && !strcmp(oldkey->GetName(),key->GetName())) continue;

    // read object from first source file
    first_source->cd( path );
    TObject *obj = key->ReadObj();

    if ( obj->IsA()->InheritsFrom( TH1::Class() ) ) {
      // descendant of TH1 -> merge it

      //      cout << "Merging histogram " << obj->GetName() << endl;
      TH1 *h1 = (TH1*)obj;

      // loop over all source files and add the content of the
      // correspondant histogram to the one pointed to by "h1"
      TFile *nextsource = (TFile*)sourcelist->After( first_source );
      int index = 0;
      while ( nextsource ) {

        // make sure we are at the correct directory level by cd'ing to path
        nextsource->cd( path );
        TKey *key2 = (TKey*)gDirectory->GetListOfKeys()->FindObject(h1->GetName());
        if (key2) {
          TH1 *h2 = (TH1*)key2->ReadObj();
          h1->Add(h2, v_weights.at(index));
          delete h2;
        }

        nextsource = (TFile*)sourcelist->After( nextsource );
        index++;
      }
    }
    // else if ( obj->IsA()->InheritsFrom( TTree::Class() ) ) {
    //
    //   // loop over all source files create a chain of Trees "globChain"
    //   const char* obj_name= obj->GetName();
    //
    //   globChain = new TChain(obj_name);
    //   globChain->Add(first_source->GetName());
    //   TFile *nextsource = (TFile*)sourcelist->After( first_source );
    //   //      const char* file_name = nextsource->GetName();
    //   // cout << "file name  " << file_name << endl;
    //   while ( nextsource ) {
    //
    //     globChain->Add(nextsource->GetName());
    //     nextsource = (TFile*)sourcelist->After( nextsource );
    //   }
    //
    // }
    else if ( obj->IsA()->InheritsFrom( TDirectory::Class() ) ) {
      // it's a subdirectory

      cout << "Found subdirectory " << obj->GetName() << endl;

      // create a new subdir of same name and title in the target file
      target->cd();
      TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );

      // newdir is now the starting point of another round of merging
      // newdir still knows its depth within the target file via
      // GetPath(), so we can still figure out where we are in the recursion
      MergeRootfile(newdir, sourcelist, v_weights);

    } else {

      // object is of no type that we know or can handle
      cout << "Unknown object type, name: "
      << obj->GetName() << " title: " << obj->GetTitle() << endl;
    }

    // now write the merged histogram (which is "in" obj) to the target file
    // note that this will just store obj in the current directory level,
    // which is not persistent until the complete directory itself is stored
    // by "target->Write()" below
    if ( obj ) {
      target->cd();

      //!!if the object is a tree, it is stored in globChain...
      // if(obj->IsA()->InheritsFrom( TTree::Class() ))
      // globChain->Merge(target->GetFile(),0,"keep");
      // else
      obj->Write( key->GetName() );
    }

  } // while ( ( TKey *key = (TKey*)nextkey() ) )

  // save modifications to target file
  target->SaveSelf(kTRUE);
  TH1::AddDirectory(status);
}
