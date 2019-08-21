#define HGCTBAna_cxx
#include "HGCTBAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

// User defined Class
#include "HGCTBAlgo.C"

void HGCTBAna::Loop(string outputfile, int nTotEvt, int nPrintEvent, float mipCut)
{
   if (fChain == 0) return;

   cout << "Output file : " << outputfile << endl;
   char *outfilename = const_cast<char*>(outputfile.c_str());
   TFile *ofile = new TFile(outfilename,"RECREATE");
   TTree *t1 = new TTree("AnaTree","HGCalTB Analysed Tree");

   Long64_t nentries = fChain->GetEntriesFast();
   if (nTotEvt >=0 && nTotEvt <= nentries ) nentries=nTotEvt;
   cout << "Running over " << nTotEvt << " entries..."  << endl;

   int   nLayer=41;
   float sumEAll=0;
   vector<float> sumELayer;  sumELayer.clear();
   vector<float> r1Layer;  r1Layer.clear();
   vector<float> r7Layer;  r7Layer.clear();
   vector<float> r19Layer;  r19Layer.clear();

   t1->Branch("nLayer",&nLayer);
   t1->Branch("sumEAll",&sumEAll);
   t1->Branch("sumELayer",&sumELayer);
   t1->Branch("r1Layer",&r1Layer);
   t1->Branch("r7Layer",&r7Layer);
   t1->Branch("r19Layer",&r19Layer);

   // Creating HGCTBAlgo Class //
   HGCTBAlgo h1;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if (jentry % nPrintEvent == 0) std::cout << "  " << jentry  << "  Events Processed... " << std::endl;

      // Initializing HGCTBAlgo Class //
      h1.Init(*rechit_energy, *rechit_layer, *rechit_iu, *rechit_iv,
              *rechit_x,  *rechit_y,  mipCut);

      sumEAll = h1.SumE();
      //cout << "Sum Rechit Energy All:  " <<  sumEAll << endl;
      nLayer=rechit_layer->back();
      for (unsigned int iLayer=1; iLayer <= rechit_layer->back(); iLayer++){
	sumELayer.push_back( h1.SumELayer(iLayer) );
	float r1  = h1.Cluster(iLayer,0,mipCut);
	float r7  = h1.Cluster(iLayer,1,mipCut);
	float r19 = h1.Cluster(iLayer,2,mipCut);
	r1Layer.push_back(r1);
	r7Layer.push_back(r7);
	r19Layer.push_back(r19);
	/*
	cout << "Layer : Sum RecHit Energy   " << iLayer << " : " << h1.SumELayer(iLayer) << endl;
	cout << "Layer : MaxHit Energy   " << iLayer << " : " << h1.MaxHitELayer(iLayer) << endl;
	cout << "R1 : "  << r1  << endl;
	cout << "R7 : "  << r7  << endl;
	cout << "R19 : " << r19 << endl;
	*/
      }
      t1->Fill();
      sumELayer.clear();
      r1Layer.clear();
      r7Layer.clear();
      r19Layer.clear();
   } // Event Loop

   t1->Write();
   ofile->Write();
   ofile->Close();
}
