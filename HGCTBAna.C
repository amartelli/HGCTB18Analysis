#define HGCTBAna_cxx
#include "HGCTBAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TStopwatch.h"

// User defined Class
#include "HGCTBAlgo.C"

void HGCTBAna::Loop(string finName, string outputfile, int nTotEvt, int nPrintEvent, float mipCut)
{

  
   TStopwatch sw;
   sw.Start();

   //bool debug = true;
   bool debug = false;
   
   bool applyTOFCorr = true; ///for timing
   //bool applyTOFCorr = false; ///for timing
   TFile *fin = TFile::Open(finName.c_str());
   
   TDirectory * dir = (TDirectory*)fin->Get(Form("%s:/rechitntupler",finName.c_str()));
   TTree *tin = new TTree();
   dir->GetObject("hits",tin);
   
   Init(tin);

   unsigned int   nLayer=41;  
   //unsigned int   nLayer=28;  


   cout << "Output file : " << outputfile << endl;
   char *outfilename = const_cast<char*>(outputfile.c_str());
   TFile *ofile = new TFile( outfilename,"RECREATE");

   map<string, TH1F*> hmap;
   /*
   int nbins = 200;
   float xmin = 110;
   float xmax = 120;
   */
   int nbins = 400;
   float xmin = 110.5;
   float xmax = 112;
   
   for(int il=1; il<=nLayer; il++){

     hmap[Form("time_layer%d_nR0",il)] = new TH1F( Form("time_layer%d_nR0",il), Form("time_layer%d_nR0",il), nbins, xmin, xmax);

       for(int iR=1; iR<=2; iR++){
	 
	 hmap[Form("time_layer%d_nR%d",il,iR)] = new TH1F( Form("time_layer%d_nR%d",il,iR), Form("time_layer%d_nR%d",il,iR), nbins, xmin, xmax);
	 

	 //hmap[Form("timeDiff_layer%d_nR%d",il,iR)] = new TH1F( Form("timeDiff_layer%d_nR%d",il,iR), Form("timeDiff_layer%d_nR%d",il,iR), 1000, -10, 10);
	 hmap[Form("timeDiff_layer%d_nR%d",il,iR)] = new TH1F( Form("timeDiff_layer%d_nR%d",il,iR), Form("timeDiff_layer%d_nR%d",il,iR), 1000, -0.3, 0.3);

	 if(il ==1){
	   //all layers together
	   hmap[Form("avgTime_layer-1_nR%d", iR)] = new TH1F( Form("avgTime_layer-1_nR%d", iR), "", 1000, -5., 10.);     
	 }

	 hmap[Form("avgTime_layer%d_nR%d",il, iR)] = new TH1F( Form("avgTime_layer%d_nR%d",il, iR), "", 1000, -5., 10.);

       }//
   }//For(ing il=0; il<nLayer; il++)
   

   for(int iR=0; iR<=2; iR++){
     hmap[Form("time_EachLayerTime_allinOne_nR%d",iR)] = new TH1F( Form("time_EachLayerTime_allinOne_nR%d",iR), Form("time_EachLayerTime_allinOne_nR%d",iR), nbins, xmin, xmax);
     hmap[Form("time_OneTimeFromAllLayer_allinOne_nR%d",iR)] = new TH1F( Form("time_OneTimeFromAllLayer_allinOne_nR%d",iR), Form("time_OneTimeFromAllLayer_allinOne_nR%d",iR), 2000, xmin, xmax);
   }

   //if (fChain == 0) return;

   TTree *t1 = new TTree("AnaTree","HGCalTB Analysed Tree");

   Long64_t nentries = fChain->GetEntriesFast();
   if (nTotEvt >=0 && nTotEvt <= nentries ) nentries=nTotEvt;
   cout << "Running over " << nentries << " entries..."  << endl;


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
              *rechit_x,  *rechit_y, *rechit_time_mc, *rechit_time_mc_firstHit, 
	      *rechit_time_mc_lastHit, *rechit_z, mipCut);

      sumEAll = h1.SumE();
      //cout << "Sum Rechit Energy All:  " <<  sumEAll << endl;
      nLayer=rechit_layer->back();

      float sumEAllLayers[10]; ///each index is for ring
      float EiWeiTimeAllLayers[10]; ///each index is for ring
      
      for(int iR=0; iR<10; iR++){
	sumEAllLayers[iR] = 0;
	EiWeiTimeAllLayers[iR] = 0;
      }

      for (unsigned int iLayer=1; iLayer <= rechit_layer->back(); iLayer++){
	float sumE = h1.SumELayer(iLayer);
	float maxE = h1.MaxHitELayer(iLayer);
	float E1  = h1.Cluster(iLayer,0,mipCut);
	float E7  = h1.Cluster(iLayer,1,mipCut);
	float E19 = h1.Cluster(iLayer,2,mipCut);	
	//float E37 = h1.Cluster(iLayer,3,mipCut);

	//std::cout << " >>> fine Cluster in Ana " << std::endl;

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


	///SJ - timing analysis

	///timing of the layer with just central cell

	if(debug){
	  cout<<"calling EnWeiLayerTime for layer "<<iLayer-1<<endl;
	}

	float tmpsumE_layer = 0;
	float layertime_centralCell = h1.EnWeiLayerTime(iLayer, 0, tmpsumE_layer, applyTOFCorr);
	EiWeiTimeAllLayers[0] += layertime_centralCell * tmpsumE_layer;  ///because layertime_centralCell is / by tmpsumE_layer
	sumEAllLayers[0] += tmpsumE_layer;
	
	hmap[Form("time_layer%d_nR0",iLayer)]->Fill(layertime_centralCell);
	
	hmap[Form("time_EachLayerTime_allinOne_nR0")]->Fill(layertime_centralCell);

	for(int iR=1; iR<=2; iR++){
	  
	  vector<float> timeDiff = h1.LayerTimeDiff(iLayer, iR);
	  for(int ihit=0; ihit<timeDiff.size(); ihit++){
	    
	    hmap[Form("timeDiff_layer%d_nR%d", iLayer, iR)]->Fill(timeDiff[ihit]);
	    
	  }//for(int ihit=0; ihit<timeDiff.size(); ihit++)
	  

	if(debug){
	  cout<<"Again calling EnWeiLayerTime for layer "<<iLayer-1<<" and ring "<<iR<<endl;
	}
	
	  float tmpsumE_layer = 0;
	  float layertime = h1.EnWeiLayerTime(iLayer, iR, tmpsumE_layer, applyTOFCorr);
	  EiWeiTimeAllLayers[iR] += layertime * tmpsumE_layer;  ///because layertime_centralCell is / by tmpsumE_layer
	  sumEAllLayers[iR] += tmpsumE_layer;
	
	  hmap[Form("time_layer%d_nR%d",iLayer, iR)]->Fill(layertime);
	  
	  hmap[Form("time_EachLayerTime_allinOne_nR%d",iR)]->Fill(layertime);

	  ////
	  //std::cout << " now time final " << std::endl;
	  if(iLayer == 1){
	    float averageTimeAll = h1.GetTime(-1, iR);
	    //std::cout << " averageTimeAll = " << averageTimeAll << std::endl;
	    hmap[Form("avgTime_layer-1_nR%d", iR)]->Fill(averageTimeAll);
	  }
	  float averageTime = h1.GetTime(iLayer, iR);
	  //std::cout << " averageTime = " << averageTime << std::endl;
	  hmap[Form("avgTime_layer%d_nR%d", iLayer, iR)]->Fill(averageTime);

	}//for(int iR=1; iR<=2; iR++)

      

      }//for (unsigned int iLayer=1; iLayer <= rechit_layer->back(); iLayer++)

      for(int iR=0; iR<=2; iR++){
	
	EiWeiTimeAllLayers[iR] = EiWeiTimeAllLayers[iR]/sumEAllLayers[iR];
	
	
	hmap[Form("time_OneTimeFromAllLayer_allinOne_nR%d",iR)]->Fill(EiWeiTimeAllLayers[iR]);
      }
      
      t1->Fill();

      sumELayer.clear();
      maxELayer.clear();
      E1Layer.clear();
      E7Layer.clear();
      E19Layer.clear();
      // E37Layer.clear();
   } // Event Loop


   ///Write the histogram
   ofile->cd();
   for(map<string,TH1F*>::iterator it = hmap.begin(); it != hmap.end(); ++it) {
     // std::cout << " writing histo = " << it->first << std::endl;
     hmap[it->first]->Write();
   }


   ofile->Write();
   ofile->Close();

   sw.Stop();
   std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
   std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
