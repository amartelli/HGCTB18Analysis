#define HGCTBAna_cxx
#include "HGCTBAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TStopwatch.h"

// User defined Class
#include "HGCTBAlgo.C"

void HGCTBAna::Loop(string outputfile, int nTotEvt, int nPrintEvent, float mipCut)
{
   TStopwatch sw;
   sw.Start();

   if (fChain == 0) return;

   cout << "Output file : " << outputfile << endl;
   char *outfilename = const_cast<char*>(outputfile.c_str());
   TFile *ofile = new TFile(outfilename,"RECREATE");
   TTree *t1 = new TTree("AnaTree","HGCalTB Analysed Tree");

   Long64_t nentries = fChain->GetEntriesFast();
   if (nTotEvt >=0 && nTotEvt <= nentries ) nentries=nTotEvt;
   cout << "Running over " << nentries << " entries..."  << endl;

   unsigned int   nLayer=41;
   float         sumEAll=0;
   vector<float> sumELayer;   sumELayer.clear();
   vector<float> maxELayer;   maxELayer.clear();
   vector<float> E1Layer;     E1Layer.clear();
   vector<float> E7Layer;     E7Layer.clear();
   vector<float> E19Layer;    E19Layer.clear();
   //vector<float> E37Layer;  E37Layer.clear();

   t1->Branch("nLayer",&nLayer);
   t1->Branch("sumEAll",&sumEAll);
   t1->Branch("sumELayer",&sumELayer);
   t1->Branch("maxELayer",&maxELayer);
   t1->Branch("E1Layer",&E1Layer);
   t1->Branch("E7Layer",&E7Layer);
   t1->Branch("E19Layer",&E19Layer);
   //t1->Branch("E37Layer",&E37Layer);

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
	float sumE = h1.SumELayer(iLayer);
	float maxE = h1.MaxHitELayer(iLayer);
	float E1  = h1.Cluster(iLayer,0,mipCut);
	float E7  = h1.Cluster(iLayer,1,mipCut);
	float E19 = h1.Cluster(iLayer,2,mipCut);	
	//float E37 = h1.Cluster(iLayer,3,mipCut);

	sumELayer.push_back(sumE);
	maxELayer.push_back(maxE);
	E1Layer.push_back(E1);
	E7Layer.push_back(E7);
	E19Layer.push_back(E19);
	//E37Layer.push_back(E37);
	/*
	cout << "Layer : Sum RecHit Energy   " << iLayer << " : " << h1.SumELayer(iLayer) << endl;
	cout << "Layer : MaxHit Energy   " << iLayer << " : " << h1.MaxHitELayer(iLayer) << endl;
	cout << "E1 : "  << E1  << endl;
	cout << "E7 : "  << E7  << endl;
	cout << "E19 : " << E19 << endl;
	//cout << "E37 : " << E37 << endl;
	*/
      }
      t1->Fill();

      sumELayer.clear();
      maxELayer.clear();
      E1Layer.clear();
      E7Layer.clear();
      E19Layer.clear();
      // E37Layer.clear();
   } // Event Loop

   ofile->Write();
   ofile->Close();

   sw.Stop();
   std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
   std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
