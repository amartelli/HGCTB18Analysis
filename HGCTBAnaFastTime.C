#define HGCTBAnaFastTime_cxx
#include "HGCTBAnaFastTime.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TStopwatch.h"

// User defined Class
#include "HGCTBAlgoFastTime.C"

void HGCTBAnaFastTime::Loop(string finName, string outputfile, int nTotEvt, int nPrintEvent, float mipCut)
{

  
   TStopwatch sw;
   sw.Start();

   //bool debug = true;
   bool debug = false;
   
   TFile *fin = TFile::Open(finName.c_str());
   
   TDirectory * dir = (TDirectory*)fin->Get(Form("%s:/rechitntupler",finName.c_str()));
   TTree *tin = new TTree();
   dir->GetObject("hits",tin);
   
   Init(tin);

   //unsigned int   nLayer=41;  
   unsigned int   nLayer=30;  


   cout << "Output file : " << outputfile << endl;
   char *outfilename = const_cast<char*>(outputfile.c_str());
   TFile *ofile = new TFile( outfilename,"RECREATE");

   map<string, TH1F*> hmap;  
   for(unsigned int il=1; il<=nLayer; il++){
     for(int iR=1; iR<=2; iR++){
       
       if(il == 1){
	 //all layers together
	 hmap[Form("avgTime_layerAll_nR%d", iR)] = new TH1F( Form("avgTime_layerAll_nR%d", iR), "", 1000, -5., 10.);     
	 hmap[Form("avgTimeSmeared_layerAll_nR%d", iR)] = new TH1F( Form("avgTimeSmeared_layerAll_nR%d", iR), "", 1000, -5., 10.);     
       }       
       hmap[Form("avgTime_layer%d_nR%d",il, iR)] = new TH1F( Form("avgTime_layer%d_nR%d",il, iR), "", 1000, -5., 10.);       
       hmap[Form("avgTimeSmeared_layer%d_nR%d",il, iR)] = new TH1F( Form("avgTimeSmeared_layer%d_nR%d",il, iR), "", 1000, -5., 10.);       
     }
   }
   
   
   TTree *t1 = new TTree("AnaTree","HGCalTB Analysed Tree");

   Long64_t nentries = fChain->GetEntriesFast();
   if (nTotEvt >=0 && nTotEvt <= nentries ) nentries=nTotEvt;
   cout << "Running over " << nentries << " entries..."  << endl;


   // Creating HGCTBAlgo Class //
   HGCTBAlgoFastTime h1;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (jentry % nPrintEvent == 0) std::cout << "  " << jentry  << "  Events Processed... " << std::endl;

      // Initializing HGCTBAlgo Class //
      h1.Init(*rechit_energy, *rechit_layer, *rechit_iu, *rechit_iv,
              *rechit_x,  *rechit_y, *rechit_time_mc, *rechit_time_mc_firstHit, 
	      *rechit_time_mc_lastHit, *rechit_z, mipCut, nLayer, *rechit_module);

      if(debug) std::cout << " before getting time "<< std::endl;
      for (unsigned int iLayer=1; iLayer <= nLayer; iLayer++){

	for(int iR=1; iR<=2; iR++){
	  if(debug) std::cout << " now time final " << std::endl;
	  if(iLayer == 1){
	    float averageTimeAll = h1.GetTime(-1, iR);
	    if(debug) std::cout << " averageTimeAll = " << averageTimeAll << std::endl;
	    hmap[Form("avgTime_layerAll_nR%d", iR)]->Fill(averageTimeAll);

	    float averageTimeSAll = h1.GetTimeSmeared(-1, iR);
	    if(debug) std::cout << " averageTimeSAll = " << averageTimeSAll << std::endl;
	    hmap[Form("avgTimeSmeared_layerAll_nR%d", iR)]->Fill(averageTimeSAll);
	  }
	  float averageTime = h1.GetTime(iLayer, iR);
	  if(debug) std::cout << " averageTime = " << averageTime << std::endl;
	  hmap[Form("avgTime_layer%d_nR%d", iLayer, iR)]->Fill(averageTime);

	  float averageTimeS = h1.GetTimeSmeared(iLayer, iR);
	  if(debug) std::cout << " averageTimeS = " << averageTimeS << std::endl;
	  hmap[Form("avgTimeSmeared_layer%d_nR%d", iLayer, iR)]->Fill(averageTimeS);

	}//for(int iR=1; iR<=2; iR++)
      }//for (unsigned int iLayer=1; iLayer <= rechit_layer->back(); iLayer++)
      
      t1->Fill();

   } // Event Loop


   ///Write the histogram
   ofile->cd();
   for(map<string,TH1F*>::iterator it = hmap.begin(); it != hmap.end(); ++it) {
     if(debug) std::cout << " writing histo = " << it->first << std::endl;
     hmap[it->first]->Write();
   }


   ofile->Write();
   ofile->Close();

   sw.Stop();
   std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
   std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
