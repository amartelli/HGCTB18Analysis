#define HGCTBHisto_cxx
#include "HGCTBHisto.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TStopwatch.h"

// C++ Headers
#include <iostream>

using namespace std;
void HGCTBHisto::Loop(string outputfile, int nMaxEvt, int nPrintEvent, float beamE )
{
   TStopwatch sw;
   sw.Start();

   if (fChain == 0) return;

   cout << "Output file : " << outputfile << endl;
   char *outfilename = const_cast<char*>(outputfile.c_str());
   TFile *ofile = new TFile(outfilename,"RECREATE");
   //TTree *t1 = new TTree("HistoTree","HGCalTB Histograms");

   Long64_t nentries = fChain->GetEntriesFast();
   if (nMaxEvt >=0 && nMaxEvt <= nentries ) nentries=nMaxEvt;
   cout << "Running over " << nentries << " entries..."  << endl;

   //beamE = 100.;
   unsigned int maxLayerEE=28;

   int nBin=100;
   float minBin1=0., maxBin1=120*beamE;
   float minBin2=0., maxBin2=20*beamE;
   TH1F *h_SumEAll;
   TH1F *h_SumELayer[maxLayerEE];
   TH1F *h_E1Layer[maxLayerEE];
   TH1F *h_E7Layer[maxLayerEE];
   TH1F *h_E19Layer[maxLayerEE];
   TH1F *h_E1byE7Layer[maxLayerEE];
   TH1F *h_E1byE19Layer[maxLayerEE];
   TH1F *h_E7byE19Layer[maxLayerEE];
   TH1F *h_E7byEAllLayer[maxLayerEE];
   TH1F *h_E19byEAllLayer[maxLayerEE];

   h_SumEAll  = new TH1F("h_SumEAll","Sum Rechits of All Layers",
			   nBin,minBin1,maxBin1);

   for (unsigned int ilayer=0; ilayer<maxLayerEE; ilayer++){
     h_SumELayer[ilayer]      = new TH1F(Form("h_SumELayer%d",ilayer+1),Form("Sum Rechits of Layer%d",ilayer+1),
				    nBin,minBin2,maxBin2);
     h_E1Layer[ilayer]        = new TH1F(Form("h_E1Layer%d",ilayer+1),Form("E1 of Layer%d",ilayer+1),
				    nBin,minBin2,maxBin2);
     h_E7Layer[ilayer]        = new TH1F(Form("h_E7Layer%d",ilayer+1),Form("E7 of Layer%d",ilayer+1),
				    nBin,minBin2,maxBin2);
     h_E19Layer[ilayer]       = new TH1F(Form("h_E19Layer%d",ilayer+1),Form("E19 of Layer%d",ilayer+1),
				    nBin,minBin2,maxBin2);
     h_E1byE7Layer[ilayer]    = new TH1F(Form("h_E1byE7Layer%d",ilayer+1),Form("E1byE7 of Layer%d",ilayer+1),
				    nBin,0.,1.0);
     h_E1byE19Layer[ilayer]   = new TH1F(Form("h_E1byE19Layer%d",ilayer+1),Form("E1byE19 of Layer%d",ilayer+1),
				    nBin,0.,1.0);
     h_E7byE19Layer[ilayer]   = new TH1F(Form("h_E7byE19Layer%d",ilayer+1),Form("E7byE19 of Layer%d",ilayer+1),
				    nBin,0.,1.0);
     h_E7byEAllLayer[ilayer]  = new TH1F(Form("h_E7byEAllLayer%d",ilayer+1),Form("E7byEAll of Layer%d",ilayer+1),
				    nBin,0.,1.0);
     h_E19byEAllLayer[ilayer] = new TH1F(Form("h_E19byEAllLayer%d",ilayer+1),Form("E19byEAll of Layer%d",ilayer+1),
				    nBin,0.,1.0);
       }

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      if (jentry % 1000 == 0) std::cout << "  " << jentry  << "  Events Processed... " << std::endl;

      //if (jentry % 1000 == 0) cout << "sumEAll: " << sumEAll << endl;
      h_SumEAll->Fill(sumEAll);

      if (nLayer<maxLayerEE) maxLayerEE=nLayer;
      for (unsigned int ilayer=0; ilayer<maxLayerEE; ilayer++){
	h_SumELayer[ilayer]->Fill( sumELayer->at(ilayer) );
	h_E1Layer[ilayer]->Fill( E1Layer->at(ilayer) );
	h_E7Layer[ilayer]->Fill( E7Layer->at(ilayer) );
	h_E19Layer[ilayer]->Fill( E19Layer->at(ilayer) );
	h_E1byE7Layer[ilayer]->Fill( E1Layer->at(ilayer)/E7Layer->at(ilayer) );
	h_E1byE19Layer[ilayer]->Fill( E1Layer->at(ilayer)/E19Layer->at(ilayer) );
	h_E7byE19Layer[ilayer]->Fill( E7Layer->at(ilayer)/E19Layer->at(ilayer) );
	h_E7byEAllLayer[ilayer]->Fill( E7Layer->at(ilayer)/sumELayer->at(ilayer) );
	h_E19byEAllLayer[ilayer]->Fill( E19Layer->at(ilayer)/sumELayer->at(ilayer) );
      } // Layer Loop

   } // Event Loop 

   //t1->Write();
   ofile->Write();
   ofile->Close();

   sw.Stop();
   std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
   std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
