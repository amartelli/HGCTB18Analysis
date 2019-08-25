//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 23 14:43:06 2019 by ROOT version 6.14/09
// from TTree AnaTree/HGCalTB Analysed Tree
// found on file: HGCTBAnaOutput_MC.root
//////////////////////////////////////////////////////////

#ifndef HGCTBHisto_h
#define HGCTBHisto_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// C++ Header
#include <iostream>
// Header file for the classes stored in the TTree if any.
#include "vector"

using namespace std;

class HGCTBHisto {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t           nLayer;
   Float_t         sumEAll;
   vector<float>   *sumELayer;
   vector<float>   *maxELayer;
   vector<float>   *E1Layer;
   vector<float>   *E7Layer;
   vector<float>   *E19Layer;
   vector<float>   *E37Layer;

   // List of branches
   TBranch        *b_nLayer;   //!
   TBranch        *b_sumEAll;   //!
   TBranch        *b_sumELayer;   //!
   TBranch        *b_maxELayer;   //!
   TBranch        *b_E1Layer;   //!
   TBranch        *b_E7Layer;   //!
   TBranch        *b_E19Layer;   //!
   TBranch        *b_E37Layer;   //!

   HGCTBHisto(string infile, TTree *tree=0);
   virtual ~HGCTBHisto();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(string outputfile, int nMaxEvt, int nPrintEvent, float beamE);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HGCTBHisto_cxx
HGCTBHisto::HGCTBHisto(string infile, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
/*
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("HGCTBAnaOutput_MC.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("HGCTBAnaOutput_MC.root");
      }
      f->GetObject("AnaTree",tree);

   }
*/

  TString inputfile = infile;
  cout<<"Input file : " << inputfile << endl;

  if (tree == 0) {
    TFile *f = TFile::Open(inputfile);
    f->GetObject("AnaTree",tree);
  }

   Init(tree);
}

HGCTBHisto::~HGCTBHisto()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HGCTBHisto::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HGCTBHisto::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HGCTBHisto::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   sumELayer = 0;
   maxELayer = 0;
   E1Layer = 0;
   E7Layer = 0;
   E19Layer = 0;
   E37Layer = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nLayer", &nLayer, &b_nLayer);
   fChain->SetBranchAddress("sumEAll", &sumEAll, &b_sumEAll);
   fChain->SetBranchAddress("sumELayer", &sumELayer, &b_sumELayer);
   fChain->SetBranchAddress("maxELayer", &maxELayer, &b_maxELayer);
   fChain->SetBranchAddress("E1Layer", &E1Layer, &b_E1Layer);
   fChain->SetBranchAddress("E7Layer", &E7Layer, &b_E7Layer);
   fChain->SetBranchAddress("E19Layer", &E19Layer, &b_E19Layer);
   fChain->SetBranchAddress("E37Layer", &E37Layer, &b_E37Layer);
   Notify();
}

Bool_t HGCTBHisto::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HGCTBHisto::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HGCTBHisto::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HGCTBHisto_cxx
