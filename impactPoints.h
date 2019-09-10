//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Sep 10 10:47:57 2019 by ROOT version 6.18/00
// from TTree impactPoints/impactPoints
// found on file: /eos/cms/store/group/dpg_hgcal/tb_hgcal/forAnalysis/DataNtuple/HGCal_TB18_October_ConfigurationI/v13/Electron/HGCTB18_DataNtuple_EleE30.root
//////////////////////////////////////////////////////////

#ifndef impactPoints_h
#define impactPoints_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class impactPoints {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          event;
   UInt_t          run;
   Int_t           ntracks;
   Float_t         impactX_HGCal_layer_1;
   Float_t         impactY_HGCal_layer_1;
   Float_t         impactX_HGCal_layer_2;
   Float_t         impactY_HGCal_layer_2;
   Float_t         impactX_HGCal_layer_3;
   Float_t         impactY_HGCal_layer_3;
   Float_t         impactX_HGCal_layer_4;
   Float_t         impactY_HGCal_layer_4;
   Float_t         impactX_HGCal_layer_5;
   Float_t         impactY_HGCal_layer_5;
   Float_t         impactX_HGCal_layer_6;
   Float_t         impactY_HGCal_layer_6;
   Float_t         impactX_HGCal_layer_7;
   Float_t         impactY_HGCal_layer_7;
   Float_t         impactX_HGCal_layer_8;
   Float_t         impactY_HGCal_layer_8;
   Float_t         impactX_HGCal_layer_9;
   Float_t         impactY_HGCal_layer_9;
   Float_t         impactX_HGCal_layer_10;
   Float_t         impactY_HGCal_layer_10;
   Float_t         impactX_HGCal_layer_11;
   Float_t         impactY_HGCal_layer_11;
   Float_t         impactX_HGCal_layer_12;
   Float_t         impactY_HGCal_layer_12;
   Float_t         impactX_HGCal_layer_13;
   Float_t         impactY_HGCal_layer_13;
   Float_t         impactX_HGCal_layer_14;
   Float_t         impactY_HGCal_layer_14;
   Float_t         impactX_HGCal_layer_15;
   Float_t         impactY_HGCal_layer_15;
   Float_t         impactX_HGCal_layer_16;
   Float_t         impactY_HGCal_layer_16;
   Float_t         impactX_HGCal_layer_17;
   Float_t         impactY_HGCal_layer_17;
   Float_t         impactX_HGCal_layer_18;
   Float_t         impactY_HGCal_layer_18;
   Float_t         impactX_HGCal_layer_19;
   Float_t         impactY_HGCal_layer_19;
   Float_t         impactX_HGCal_layer_20;
   Float_t         impactY_HGCal_layer_20;
   Float_t         impactX_HGCal_layer_21;
   Float_t         impactY_HGCal_layer_21;
   Float_t         impactX_HGCal_layer_22;
   Float_t         impactY_HGCal_layer_22;
   Float_t         impactX_HGCal_layer_23;
   Float_t         impactY_HGCal_layer_23;
   Float_t         impactX_HGCal_layer_24;
   Float_t         impactY_HGCal_layer_24;
   Float_t         impactX_HGCal_layer_25;
   Float_t         impactY_HGCal_layer_25;
   Float_t         impactX_HGCal_layer_26;
   Float_t         impactY_HGCal_layer_26;
   Float_t         impactX_HGCal_layer_27;
   Float_t         impactY_HGCal_layer_27;
   Float_t         impactX_HGCal_layer_28;
   Float_t         impactY_HGCal_layer_28;
   Float_t         impactX_HGCal_layer_29;
   Float_t         impactY_HGCal_layer_29;
   Float_t         impactX_HGCal_layer_30;
   Float_t         impactY_HGCal_layer_30;
   Float_t         impactX_HGCal_layer_31;
   Float_t         impactY_HGCal_layer_31;
   Float_t         impactX_HGCal_layer_32;
   Float_t         impactY_HGCal_layer_32;
   Float_t         impactX_HGCal_layer_33;
   Float_t         impactY_HGCal_layer_33;
   Float_t         impactX_HGCal_layer_34;
   Float_t         impactY_HGCal_layer_34;
   Float_t         impactX_HGCal_layer_35;
   Float_t         impactY_HGCal_layer_35;
   Float_t         impactX_HGCal_layer_36;
   Float_t         impactY_HGCal_layer_36;
   Float_t         impactX_HGCal_layer_37;
   Float_t         impactY_HGCal_layer_37;
   Float_t         impactX_HGCal_layer_38;
   Float_t         impactY_HGCal_layer_38;
   Float_t         impactX_HGCal_layer_39;
   Float_t         impactY_HGCal_layer_39;
   Float_t         impactX_HGCal_layer_40;
   Float_t         impactY_HGCal_layer_40;
   Float_t         trackChi2_X;
   Float_t         trackChi2_Y;
   Int_t           dwcReferenceType;
   Double_t        m_x;
   Double_t        m_y;
   Double_t        b_x;
   Double_t        b_y;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_run;   //!
   TBranch        *b_ntracks;   //!
   TBranch        *b_impactX_HGCal_layer_1;   //!
   TBranch        *b_impactY_HGCal_layer_1;   //!
   TBranch        *b_impactX_HGCal_layer_2;   //!
   TBranch        *b_impactY_HGCal_layer_2;   //!
   TBranch        *b_impactX_HGCal_layer_3;   //!
   TBranch        *b_impactY_HGCal_layer_3;   //!
   TBranch        *b_impactX_HGCal_layer_4;   //!
   TBranch        *b_impactY_HGCal_layer_4;   //!
   TBranch        *b_impactX_HGCal_layer_5;   //!
   TBranch        *b_impactY_HGCal_layer_5;   //!
   TBranch        *b_impactX_HGCal_layer_6;   //!
   TBranch        *b_impactY_HGCal_layer_6;   //!
   TBranch        *b_impactX_HGCal_layer_7;   //!
   TBranch        *b_impactY_HGCal_layer_7;   //!
   TBranch        *b_impactX_HGCal_layer_8;   //!
   TBranch        *b_impactY_HGCal_layer_8;   //!
   TBranch        *b_impactX_HGCal_layer_9;   //!
   TBranch        *b_impactY_HGCal_layer_9;   //!
   TBranch        *b_impactX_HGCal_layer_10;   //!
   TBranch        *b_impactY_HGCal_layer_10;   //!
   TBranch        *b_impactX_HGCal_layer_11;   //!
   TBranch        *b_impactY_HGCal_layer_11;   //!
   TBranch        *b_impactX_HGCal_layer_12;   //!
   TBranch        *b_impactY_HGCal_layer_12;   //!
   TBranch        *b_impactX_HGCal_layer_13;   //!
   TBranch        *b_impactY_HGCal_layer_13;   //!
   TBranch        *b_impactX_HGCal_layer_14;   //!
   TBranch        *b_impactY_HGCal_layer_14;   //!
   TBranch        *b_impactX_HGCal_layer_15;   //!
   TBranch        *b_impactY_HGCal_layer_15;   //!
   TBranch        *b_impactX_HGCal_layer_16;   //!
   TBranch        *b_impactY_HGCal_layer_16;   //!
   TBranch        *b_impactX_HGCal_layer_17;   //!
   TBranch        *b_impactY_HGCal_layer_17;   //!
   TBranch        *b_impactX_HGCal_layer_18;   //!
   TBranch        *b_impactY_HGCal_layer_18;   //!
   TBranch        *b_impactX_HGCal_layer_19;   //!
   TBranch        *b_impactY_HGCal_layer_19;   //!
   TBranch        *b_impactX_HGCal_layer_20;   //!
   TBranch        *b_impactY_HGCal_layer_20;   //!
   TBranch        *b_impactX_HGCal_layer_21;   //!
   TBranch        *b_impactY_HGCal_layer_21;   //!
   TBranch        *b_impactX_HGCal_layer_22;   //!
   TBranch        *b_impactY_HGCal_layer_22;   //!
   TBranch        *b_impactX_HGCal_layer_23;   //!
   TBranch        *b_impactY_HGCal_layer_23;   //!
   TBranch        *b_impactX_HGCal_layer_24;   //!
   TBranch        *b_impactY_HGCal_layer_24;   //!
   TBranch        *b_impactX_HGCal_layer_25;   //!
   TBranch        *b_impactY_HGCal_layer_25;   //!
   TBranch        *b_impactX_HGCal_layer_26;   //!
   TBranch        *b_impactY_HGCal_layer_26;   //!
   TBranch        *b_impactX_HGCal_layer_27;   //!
   TBranch        *b_impactY_HGCal_layer_27;   //!
   TBranch        *b_impactX_HGCal_layer_28;   //!
   TBranch        *b_impactY_HGCal_layer_28;   //!
   TBranch        *b_impactX_HGCal_layer_29;   //!
   TBranch        *b_impactY_HGCal_layer_29;   //!
   TBranch        *b_impactX_HGCal_layer_30;   //!
   TBranch        *b_impactY_HGCal_layer_30;   //!
   TBranch        *b_impactX_HGCal_layer_31;   //!
   TBranch        *b_impactY_HGCal_layer_31;   //!
   TBranch        *b_impactX_HGCal_layer_32;   //!
   TBranch        *b_impactY_HGCal_layer_32;   //!
   TBranch        *b_impactX_HGCal_layer_33;   //!
   TBranch        *b_impactY_HGCal_layer_33;   //!
   TBranch        *b_impactX_HGCal_layer_34;   //!
   TBranch        *b_impactY_HGCal_layer_34;   //!
   TBranch        *b_impactX_HGCal_layer_35;   //!
   TBranch        *b_impactY_HGCal_layer_35;   //!
   TBranch        *b_impactX_HGCal_layer_36;   //!
   TBranch        *b_impactY_HGCal_layer_36;   //!
   TBranch        *b_impactX_HGCal_layer_37;   //!
   TBranch        *b_impactY_HGCal_layer_37;   //!
   TBranch        *b_impactX_HGCal_layer_38;   //!
   TBranch        *b_impactY_HGCal_layer_38;   //!
   TBranch        *b_impactX_HGCal_layer_39;   //!
   TBranch        *b_impactY_HGCal_layer_39;   //!
   TBranch        *b_impactX_HGCal_layer_40;   //!
   TBranch        *b_impactY_HGCal_layer_40;   //!
   TBranch        *b_trackChi2_X;   //!
   TBranch        *b_trackChi2_Y;   //!
   TBranch        *b_dwcReferenceType;   //!
   TBranch        *b_m_x;   //!
   TBranch        *b_m_y;   //!
   TBranch        *b_b_x;   //!
   TBranch        *b_b_y;   //!

   impactPoints(TTree *tree=0);
   virtual ~impactPoints();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef impactPoints_cxx
impactPoints::impactPoints(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
/*
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/dpg_hgcal/tb_hgcal/forAnalysis/DataNtuple/HGCal_TB18_October_ConfigurationI/v13/Electron/HGCTB18_DataNtuple_EleE30.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/dpg_hgcal/tb_hgcal/forAnalysis/DataNtuple/HGCal_TB18_October_ConfigurationI/v13/Electron/HGCTB18_DataNtuple_EleE30.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/eos/cms/store/group/dpg_hgcal/tb_hgcal/forAnalysis/DataNtuple/HGCal_TB18_October_ConfigurationI/v13/Electron/HGCTB18_DataNtuple_EleE30.root:/trackimpactntupler");
      dir->GetObject("impactPoints",tree);

   }
*/
   Init(tree);
}

impactPoints::~impactPoints()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t impactPoints::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t impactPoints::LoadTree(Long64_t entry)
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

void impactPoints::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("ntracks", &ntracks, &b_ntracks);
   fChain->SetBranchAddress("impactX_HGCal_layer_1", &impactX_HGCal_layer_1, &b_impactX_HGCal_layer_1);
   fChain->SetBranchAddress("impactY_HGCal_layer_1", &impactY_HGCal_layer_1, &b_impactY_HGCal_layer_1);
   fChain->SetBranchAddress("impactX_HGCal_layer_2", &impactX_HGCal_layer_2, &b_impactX_HGCal_layer_2);
   fChain->SetBranchAddress("impactY_HGCal_layer_2", &impactY_HGCal_layer_2, &b_impactY_HGCal_layer_2);
   fChain->SetBranchAddress("impactX_HGCal_layer_3", &impactX_HGCal_layer_3, &b_impactX_HGCal_layer_3);
   fChain->SetBranchAddress("impactY_HGCal_layer_3", &impactY_HGCal_layer_3, &b_impactY_HGCal_layer_3);
   fChain->SetBranchAddress("impactX_HGCal_layer_4", &impactX_HGCal_layer_4, &b_impactX_HGCal_layer_4);
   fChain->SetBranchAddress("impactY_HGCal_layer_4", &impactY_HGCal_layer_4, &b_impactY_HGCal_layer_4);
   fChain->SetBranchAddress("impactX_HGCal_layer_5", &impactX_HGCal_layer_5, &b_impactX_HGCal_layer_5);
   fChain->SetBranchAddress("impactY_HGCal_layer_5", &impactY_HGCal_layer_5, &b_impactY_HGCal_layer_5);
   fChain->SetBranchAddress("impactX_HGCal_layer_6", &impactX_HGCal_layer_6, &b_impactX_HGCal_layer_6);
   fChain->SetBranchAddress("impactY_HGCal_layer_6", &impactY_HGCal_layer_6, &b_impactY_HGCal_layer_6);
   fChain->SetBranchAddress("impactX_HGCal_layer_7", &impactX_HGCal_layer_7, &b_impactX_HGCal_layer_7);
   fChain->SetBranchAddress("impactY_HGCal_layer_7", &impactY_HGCal_layer_7, &b_impactY_HGCal_layer_7);
   fChain->SetBranchAddress("impactX_HGCal_layer_8", &impactX_HGCal_layer_8, &b_impactX_HGCal_layer_8);
   fChain->SetBranchAddress("impactY_HGCal_layer_8", &impactY_HGCal_layer_8, &b_impactY_HGCal_layer_8);
   fChain->SetBranchAddress("impactX_HGCal_layer_9", &impactX_HGCal_layer_9, &b_impactX_HGCal_layer_9);
   fChain->SetBranchAddress("impactY_HGCal_layer_9", &impactY_HGCal_layer_9, &b_impactY_HGCal_layer_9);
   fChain->SetBranchAddress("impactX_HGCal_layer_10", &impactX_HGCal_layer_10, &b_impactX_HGCal_layer_10);
   fChain->SetBranchAddress("impactY_HGCal_layer_10", &impactY_HGCal_layer_10, &b_impactY_HGCal_layer_10);
   fChain->SetBranchAddress("impactX_HGCal_layer_11", &impactX_HGCal_layer_11, &b_impactX_HGCal_layer_11);
   fChain->SetBranchAddress("impactY_HGCal_layer_11", &impactY_HGCal_layer_11, &b_impactY_HGCal_layer_11);
   fChain->SetBranchAddress("impactX_HGCal_layer_12", &impactX_HGCal_layer_12, &b_impactX_HGCal_layer_12);
   fChain->SetBranchAddress("impactY_HGCal_layer_12", &impactY_HGCal_layer_12, &b_impactY_HGCal_layer_12);
   fChain->SetBranchAddress("impactX_HGCal_layer_13", &impactX_HGCal_layer_13, &b_impactX_HGCal_layer_13);
   fChain->SetBranchAddress("impactY_HGCal_layer_13", &impactY_HGCal_layer_13, &b_impactY_HGCal_layer_13);
   fChain->SetBranchAddress("impactX_HGCal_layer_14", &impactX_HGCal_layer_14, &b_impactX_HGCal_layer_14);
   fChain->SetBranchAddress("impactY_HGCal_layer_14", &impactY_HGCal_layer_14, &b_impactY_HGCal_layer_14);
   fChain->SetBranchAddress("impactX_HGCal_layer_15", &impactX_HGCal_layer_15, &b_impactX_HGCal_layer_15);
   fChain->SetBranchAddress("impactY_HGCal_layer_15", &impactY_HGCal_layer_15, &b_impactY_HGCal_layer_15);
   fChain->SetBranchAddress("impactX_HGCal_layer_16", &impactX_HGCal_layer_16, &b_impactX_HGCal_layer_16);
   fChain->SetBranchAddress("impactY_HGCal_layer_16", &impactY_HGCal_layer_16, &b_impactY_HGCal_layer_16);
   fChain->SetBranchAddress("impactX_HGCal_layer_17", &impactX_HGCal_layer_17, &b_impactX_HGCal_layer_17);
   fChain->SetBranchAddress("impactY_HGCal_layer_17", &impactY_HGCal_layer_17, &b_impactY_HGCal_layer_17);
   fChain->SetBranchAddress("impactX_HGCal_layer_18", &impactX_HGCal_layer_18, &b_impactX_HGCal_layer_18);
   fChain->SetBranchAddress("impactY_HGCal_layer_18", &impactY_HGCal_layer_18, &b_impactY_HGCal_layer_18);
   fChain->SetBranchAddress("impactX_HGCal_layer_19", &impactX_HGCal_layer_19, &b_impactX_HGCal_layer_19);
   fChain->SetBranchAddress("impactY_HGCal_layer_19", &impactY_HGCal_layer_19, &b_impactY_HGCal_layer_19);
   fChain->SetBranchAddress("impactX_HGCal_layer_20", &impactX_HGCal_layer_20, &b_impactX_HGCal_layer_20);
   fChain->SetBranchAddress("impactY_HGCal_layer_20", &impactY_HGCal_layer_20, &b_impactY_HGCal_layer_20);
   fChain->SetBranchAddress("impactX_HGCal_layer_21", &impactX_HGCal_layer_21, &b_impactX_HGCal_layer_21);
   fChain->SetBranchAddress("impactY_HGCal_layer_21", &impactY_HGCal_layer_21, &b_impactY_HGCal_layer_21);
   fChain->SetBranchAddress("impactX_HGCal_layer_22", &impactX_HGCal_layer_22, &b_impactX_HGCal_layer_22);
   fChain->SetBranchAddress("impactY_HGCal_layer_22", &impactY_HGCal_layer_22, &b_impactY_HGCal_layer_22);
   fChain->SetBranchAddress("impactX_HGCal_layer_23", &impactX_HGCal_layer_23, &b_impactX_HGCal_layer_23);
   fChain->SetBranchAddress("impactY_HGCal_layer_23", &impactY_HGCal_layer_23, &b_impactY_HGCal_layer_23);
   fChain->SetBranchAddress("impactX_HGCal_layer_24", &impactX_HGCal_layer_24, &b_impactX_HGCal_layer_24);
   fChain->SetBranchAddress("impactY_HGCal_layer_24", &impactY_HGCal_layer_24, &b_impactY_HGCal_layer_24);
   fChain->SetBranchAddress("impactX_HGCal_layer_25", &impactX_HGCal_layer_25, &b_impactX_HGCal_layer_25);
   fChain->SetBranchAddress("impactY_HGCal_layer_25", &impactY_HGCal_layer_25, &b_impactY_HGCal_layer_25);
   fChain->SetBranchAddress("impactX_HGCal_layer_26", &impactX_HGCal_layer_26, &b_impactX_HGCal_layer_26);
   fChain->SetBranchAddress("impactY_HGCal_layer_26", &impactY_HGCal_layer_26, &b_impactY_HGCal_layer_26);
   fChain->SetBranchAddress("impactX_HGCal_layer_27", &impactX_HGCal_layer_27, &b_impactX_HGCal_layer_27);
   fChain->SetBranchAddress("impactY_HGCal_layer_27", &impactY_HGCal_layer_27, &b_impactY_HGCal_layer_27);
   fChain->SetBranchAddress("impactX_HGCal_layer_28", &impactX_HGCal_layer_28, &b_impactX_HGCal_layer_28);
   fChain->SetBranchAddress("impactY_HGCal_layer_28", &impactY_HGCal_layer_28, &b_impactY_HGCal_layer_28);
   fChain->SetBranchAddress("impactX_HGCal_layer_29", &impactX_HGCal_layer_29, &b_impactX_HGCal_layer_29);
   fChain->SetBranchAddress("impactY_HGCal_layer_29", &impactY_HGCal_layer_29, &b_impactY_HGCal_layer_29);
   fChain->SetBranchAddress("impactX_HGCal_layer_30", &impactX_HGCal_layer_30, &b_impactX_HGCal_layer_30);
   fChain->SetBranchAddress("impactY_HGCal_layer_30", &impactY_HGCal_layer_30, &b_impactY_HGCal_layer_30);
   fChain->SetBranchAddress("impactX_HGCal_layer_31", &impactX_HGCal_layer_31, &b_impactX_HGCal_layer_31);
   fChain->SetBranchAddress("impactY_HGCal_layer_31", &impactY_HGCal_layer_31, &b_impactY_HGCal_layer_31);
   fChain->SetBranchAddress("impactX_HGCal_layer_32", &impactX_HGCal_layer_32, &b_impactX_HGCal_layer_32);
   fChain->SetBranchAddress("impactY_HGCal_layer_32", &impactY_HGCal_layer_32, &b_impactY_HGCal_layer_32);
   fChain->SetBranchAddress("impactX_HGCal_layer_33", &impactX_HGCal_layer_33, &b_impactX_HGCal_layer_33);
   fChain->SetBranchAddress("impactY_HGCal_layer_33", &impactY_HGCal_layer_33, &b_impactY_HGCal_layer_33);
   fChain->SetBranchAddress("impactX_HGCal_layer_34", &impactX_HGCal_layer_34, &b_impactX_HGCal_layer_34);
   fChain->SetBranchAddress("impactY_HGCal_layer_34", &impactY_HGCal_layer_34, &b_impactY_HGCal_layer_34);
   fChain->SetBranchAddress("impactX_HGCal_layer_35", &impactX_HGCal_layer_35, &b_impactX_HGCal_layer_35);
   fChain->SetBranchAddress("impactY_HGCal_layer_35", &impactY_HGCal_layer_35, &b_impactY_HGCal_layer_35);
   fChain->SetBranchAddress("impactX_HGCal_layer_36", &impactX_HGCal_layer_36, &b_impactX_HGCal_layer_36);
   fChain->SetBranchAddress("impactY_HGCal_layer_36", &impactY_HGCal_layer_36, &b_impactY_HGCal_layer_36);
   fChain->SetBranchAddress("impactX_HGCal_layer_37", &impactX_HGCal_layer_37, &b_impactX_HGCal_layer_37);
   fChain->SetBranchAddress("impactY_HGCal_layer_37", &impactY_HGCal_layer_37, &b_impactY_HGCal_layer_37);
   fChain->SetBranchAddress("impactX_HGCal_layer_38", &impactX_HGCal_layer_38, &b_impactX_HGCal_layer_38);
   fChain->SetBranchAddress("impactY_HGCal_layer_38", &impactY_HGCal_layer_38, &b_impactY_HGCal_layer_38);
   fChain->SetBranchAddress("impactX_HGCal_layer_39", &impactX_HGCal_layer_39, &b_impactX_HGCal_layer_39);
   fChain->SetBranchAddress("impactY_HGCal_layer_39", &impactY_HGCal_layer_39, &b_impactY_HGCal_layer_39);
   fChain->SetBranchAddress("impactX_HGCal_layer_40", &impactX_HGCal_layer_40, &b_impactX_HGCal_layer_40);
   fChain->SetBranchAddress("impactY_HGCal_layer_40", &impactY_HGCal_layer_40, &b_impactY_HGCal_layer_40);
   fChain->SetBranchAddress("trackChi2_X", &trackChi2_X, &b_trackChi2_X);
   fChain->SetBranchAddress("trackChi2_Y", &trackChi2_Y, &b_trackChi2_Y);
   fChain->SetBranchAddress("dwcReferenceType", &dwcReferenceType, &b_dwcReferenceType);
   fChain->SetBranchAddress("m_x", &m_x, &b_m_x);
   fChain->SetBranchAddress("m_y", &m_y, &b_m_y);
   fChain->SetBranchAddress("b_x", &b_x, &b_b_x);
   fChain->SetBranchAddress("b_y", &b_y, &b_b_y);
   Notify();
}

Bool_t impactPoints::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void impactPoints::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t impactPoints::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef impactPoints_cxx
