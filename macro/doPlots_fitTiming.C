//example to run 
//photon (PDG 22) - kaon 0 long (PDG 130)
//optionType is th einput folder with the produced .root
//
//root -l doPlots_fitTiming.C'("22", "TDRset_0PU_allEta")

#include "TLegend.h"
#include "TLatex.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include "TTree.h"
#include "TChain.h"
#include <vector>
#include <fstream>
#include <string>
#include "TROOT.h"
#include "TSystem.h"
#include <iostream>
#include <fstream>

float getXmax(TH1F* histo, float& YMax){

  float yVal = 0.;
  int xBin = 1;
  for(int iB=1; iB<histo->GetNbinsX(); ++iB){
    if(histo->GetBinContent(iB) > yVal){
      xBin = iB;
      yVal = histo->GetBinContent(iB);
      YMax = yVal;
      if(yVal > 0 && histo->GetBinContent(iB) < yVal) break;
    }
  }

  std::cout << histo->GetName() << " " << histo->GetBinCenter(xBin) << std::endl; 
  return histo->GetBinCenter(xBin);
}

//fit the histos of average time of the shower over several events
void getParameters(TH1F* histo, float& mean, float& meanE, float& sigma, float& sigmaE ){

  TF1* hfithisto = new TF1("hfithisto", "gaus", -0.5, 1.);
  TF1* hfithisto2 = new TF1("hfithisto2", "gaus", -0.5, 1.);
  hfithisto2->SetLineColor(kBlue);


  hfithisto->SetRange(histo->GetMean() - 2.*histo->GetRMS(),
		      histo->GetMean() + 2.*histo->GetRMS());
  hfithisto->SetParameter(1, histo->GetMean());
  hfithisto->SetParameter(2, histo->GetRMS());
  histo->Fit("hfithisto", "RQ");

  hfithisto2->SetRange(hfithisto->GetParameter(1) - 2.*hfithisto->GetParameter(2), hfithisto->GetParameter(1) + 2.*hfithisto->GetParameter(2));
  hfithisto2->SetParameters(hfithisto->GetParameter(0), hfithisto->GetParameter(1), hfithisto->GetParameter(2));
  histo->Fit("hfithisto2", "RQ");
 
  mean = hfithisto2->GetParameter(1);
  meanE = hfithisto2->GetParError(1);
  sigma = hfithisto2->GetParameter(2);
  sigmaE = hfithisto2->GetParError(2);
  return;
}



void doPlots_fitTiming(){
  gROOT->Macro("/afs/cern.ch/user/a/amartell/public/setStyle.C");

  gStyle->SetOptTitle(0);
  
  gROOT->Reset();
  gROOT->Macro("~/public/setStyle.C");
  gStyle->SetOptStat(1);
  gStyle->SetOptFit(1);

  std::cout << " begin heer " << std::endl; 
  std::string fileBase = "/eos/cms/store/group/upgrade/HGCAL/simulation/2018/Oct/V2/timingStudies/amartellTests/";
  std::string fileName = "histo_20.root";

  int nFiles = 9;
  std::vector<int> energyVal;
  energyVal.push_back(20);
  energyVal.push_back(30);
  energyVal.push_back(50);
  energyVal.push_back(80);
  energyVal.push_back(100);
  energyVal.push_back(150);
  energyVal.push_back(200);
  energyVal.push_back(250);
  energyVal.push_back(300);

  TFile* inF[9];
  for(int ij=0; ij<nFiles; ++ij){
    inF[ij] = TFile::Open((fileBase+Form("/histo_%d.root", energyVal[ij])).c_str());
    //    inF[ij] = TFile::Open((fileBase+Form("/noTime_histo_%d.root", energyVal[ij])).c_str());
    //inF[ij] = TFile::Open((fileBase+Form("/histoSmearingOK_%d.root", energyVal[ij])).c_str());
  }
  std::cout << " >>> files loaded " << std::endl;


  //  int iColors[16] = {kRed, kOrange+4, kOrange-3, kOrange-2, kBlue, kBlue-9, kAzure-9, kAzure+10, kCyan, kGreen+1, kCyan-2, kYellow+2}; //kGray+1};
  int iColors[9] = {kRed+1, kMagenta, kBlue, kCyan+2, kGreen+1, kGray+2, kViolet, kYellow+2, kOrange-3};
  int iStyle[4] = {20, 21, 22, 23};
  //  int iColors[6] = {kGreen+1, kBlue, kRed};
  
  int nBinsRad = 2;
  int nLayers = 30;

  TGraphErrors* tg[9][2];
  TGraphErrors* tgM[9][2];
  TGraphErrors* tgFrEvt[9][2];
  TGraphErrors* tgS[9][2];
  TGraphErrors* tgMS[9][2];
  TGraphErrors* tgFrEvtS[9][2];
  ///
  TGraphErrors* tgMAll[2];
  TGraphErrors* tgAll[2];
  TGraphErrors* tgMAllS[2];
  TGraphErrors* tgAllS[2];


  for(int iR=0; iR<nBinsRad; ++iR){
  
    tgMAll[iR] = new TGraphErrors();
    tgMAll[iR]->SetName(Form("meanAll_rad%d", iR));
    tgMAll[iR]->SetPoint(0, -1, -1);

    tgMAll[iR]->SetLineColor(iColors[iR]);
    tgMAll[iR]->SetMarkerColor(iColors[iR]);
    tgMAll[iR]->SetMarkerSize(1.2);
    tgMAll[iR]->SetLineWidth(2);
    tgMAll[iR]->SetMarkerStyle(iStyle[iR]);  
    //
    tgAll[iR] = new TGraphErrors();
    tgAll[iR]->SetName(Form("resolutionAll_rad%d", iR));
    tgAll[iR]->SetPoint(0, -1, -1);

    tgAll[iR]->SetLineColor(iColors[iR]);
    tgAll[iR]->SetMarkerColor(iColors[iR]);
    tgAll[iR]->SetMarkerSize(1.2);
    tgAll[iR]->SetLineWidth(2);
    tgAll[iR]->SetMarkerStyle(iStyle[iR]);  
    //
    tgMAllS[iR] = new TGraphErrors();
    tgMAllS[iR]->SetName(Form("meanAllS_rad%d", iR));
    tgMAllS[iR]->SetPoint(0, -1, -1);

    tgMAllS[iR]->SetLineColor(iColors[iR]);
    tgMAllS[iR]->SetMarkerColor(iColors[iR]);
    tgMAllS[iR]->SetMarkerSize(1.2);
    tgMAllS[iR]->SetLineWidth(2);
    tgMAllS[iR]->SetMarkerStyle(iStyle[iR]);  
    //
    tgAllS[iR] = new TGraphErrors();
    tgAllS[iR]->SetName(Form("resolutionAllS_rad%d", iR));
    tgAllS[iR]->SetPoint(0, -1, -1);

    tgAllS[iR]->SetLineColor(iColors[iR]);
    tgAllS[iR]->SetMarkerColor(iColors[iR]);
    tgAllS[iR]->SetMarkerSize(1.2);
    tgAllS[iR]->SetLineWidth(2);
    tgAllS[iR]->SetMarkerStyle(iStyle[iR]);  

    for(int iF=0; iF<nFiles; ++iF){

    tg[iF][iR] = new TGraphErrors();
    tg[iF][iR]->SetName(Form("resolution_rad%d", iR));
    tg[iF][iR]->SetPoint(0, -1, -1);
    
    tg[iF][iR]->SetLineColor(iColors[iF]);   
    tg[iF][iR]->SetMarkerColor(iColors[iF]); 
    tg[iF][iR]->SetMarkerSize(1.2); 
    tg[iF][iR]->SetLineWidth(2);
    tg[iF][iR]->SetMarkerStyle(iStyle[iR]);
    ////////      
    tgM[iF][iR] = new TGraphErrors();
    tgM[iF][iR]->SetName(Form("mean_rad%d", iR));
    tgM[iF][iR]->SetPoint(0, -1, -1);
      
    tgM[iF][iR]->SetLineColor(iColors[iF]);
    tgM[iF][iR]->SetLineWidth(2);
    tgM[iF][iR]->SetMarkerSize(1.2); 
    tgM[iF][iR]->SetMarkerColor(iColors[iF]);
    tgM[iF][iR]->SetMarkerStyle(iStyle[iR]);
    //////////           
    tgFrEvt[iF][iR] = new TGraphErrors();
    tgFrEvt[iF][iR]->SetName(Form("fractionEvt_rad%d", iR));
    tgFrEvt[iF][iR]->SetPoint(0, -1, -1);
      
    tgFrEvt[iF][iR]->SetLineColor(iColors[iF]);
    tgFrEvt[iF][iR]->SetLineWidth(2);
    tgFrEvt[iF][iR]->SetMarkerSize(1.2); 
    tgFrEvt[iF][iR]->SetMarkerColor(iColors[iF]);
    tgFrEvt[iF][iR]->SetMarkerStyle(iStyle[iR]);


    /////smeared
    tgS[iF][iR] = new TGraphErrors();
    tgS[iF][iR]->SetName(Form("resolutionS_rad%d", iR));
    tgS[iF][iR]->SetPoint(0, -1, -1);
    
    tgS[iF][iR]->SetLineColor(iColors[iF]);   
    tgS[iF][iR]->SetMarkerColor(iColors[iF]); 
    tgS[iF][iR]->SetMarkerSize(1.2); 
    tgS[iF][iR]->SetLineWidth(2);
    tgS[iF][iR]->SetMarkerStyle(iStyle[iR]);
    ////////      
    tgMS[iF][iR] = new TGraphErrors();
    tgMS[iF][iR]->SetName(Form("meanS_rad%d", iR));
    tgMS[iF][iR]->SetPoint(0, -1, -1);
      
    tgMS[iF][iR]->SetLineColor(iColors[iF]);
    tgMS[iF][iR]->SetLineWidth(2);
    tgMS[iF][iR]->SetMarkerSize(1.2); 
    tgMS[iF][iR]->SetMarkerColor(iColors[iF]);
    tgMS[iF][iR]->SetMarkerStyle(iStyle[iR]);
    //////////           
    tgFrEvtS[iF][iR] = new TGraphErrors();
    tgFrEvtS[iF][iR]->SetName(Form("fractionEvtS_rad%d", iR));
    tgFrEvtS[iF][iR]->SetPoint(0, -1, -1);
      
    tgFrEvtS[iF][iR]->SetLineColor(iColors[iF]);
    tgFrEvtS[iF][iR]->SetLineWidth(2);
    tgFrEvtS[iF][iR]->SetMarkerSize(1.2); 
    tgFrEvtS[iF][iR]->SetMarkerColor(iColors[iF]);
    tgFrEvtS[iF][iR]->SetMarkerStyle(iStyle[iR]);
    }
  }

  std::string plotFolder = "plotsTime";       


  TH1F* timeHisto_layer[9][30][2];
  TH1F* timeHistoSmeared_layer[9][30][2];
  
  TH1F* avgTimeSmeared;
  TH1F* avgTime;
  TH1F* avgTimeAllSmeared;
  TH1F* avgTimeAll;

  TF1* hfithisto = new TF1("hfithisto", "gaus", -0.5, 1.);
  TF1* hfithisto2 = new TF1("hfithisto2", "gaus", -0.5, 1.);
  hfithisto2->SetLineColor(kBlue);
  TCanvas* c1;

  for(int iF=0; iF<nFiles; ++iF){

    for(int iRad=0; iRad<nBinsRad; ++iRad){
      avgTimeAllSmeared = (TH1F*)(inF[iF]->Get(Form("avgTimeSmeared_layerAll_nR%d", iRad+1)));
      avgTimeAll = (TH1F*)(inF[iF]->Get(Form("avgTime_layerAll_nR%d", iRad+1)));
      avgTimeAllSmeared->GetXaxis()->SetRangeUser(-1., 3.);

      float mean = -1;
      float meanE = -1;
      float sigma = -1;
      float sigmaE = -1;
      /*
      getParameters(avgTimeAll, mean, meanE, sigma, sigmaE);
      tgMAll[iRad]->SetPoint(iF, energyVal[iF],  mean);
      tgMAll[iRad]->SetPointError(iF, 0,  meanE);
      tgAll[iRad]->SetPoint(iF, energyVal[iF],  sigma);
      tgAll[iRad]->SetPointError(iF, 0,  sigmaE);

      mean = -1;
      meanE = -1;
      sigma = -1;
      sigmaE = -1;
      */

      if(avgTimeAllSmeared->GetEntries() < 100){
	tgMAllS[iRad]->SetPoint(iF, energyVal[iF],  -1);
	tgMAllS[iRad]->SetPointError(iF, 0,  0);
	tgAllS[iRad]->SetPoint(iF, energyVal[iF],  -1);
	tgAllS[iRad]->SetPointError(iF, 0,  0);
      }
      else{
	getParameters(avgTimeAllSmeared, mean, meanE, sigma, sigmaE);
	tgMAllS[iRad]->SetPoint(iF, energyVal[iF],  mean);
	tgMAllS[iRad]->SetPointError(iF, 0,  meanE);
	tgAllS[iRad]->SetPoint(iF, energyVal[iF],  sigma);
	tgAllS[iRad]->SetPointError(iF, 0,  sigmaE);
      }

      if(avgTimeAll->GetEntries() > 100){      
	tgMAll[iRad]->SetPoint(iF, energyVal[iF], avgTimeAll->GetMean());
	tgMAll[iRad]->SetPointError(iF, 0, avgTimeAll->GetMeanError());
	tgAll[iRad]->SetPoint(iF, energyVal[iF], avgTimeAll->GetRMS());
	tgAll[iRad]->SetPointError(iF, 0, avgTimeAll->GetRMSError());
      }


      for(int iL=0; iL<nLayers; ++iL){
	//std::cout << " iF = " << iF  << " irad = " << iRad << " iL = " << iL << std::endl;

	avgTimeSmeared = (TH1F*)(inF[iF]->Get(Form("avgTimeSmeared_layer%d_nR%d", iL+1, iRad+1)));
	avgTime = (TH1F*)(inF[iF]->Get(Form("avgTime_layer%d_nR%d", iL+1, iRad+1)));
	avgTimeSmeared->GetXaxis()->SetRangeUser(-1, 3.);

	
	if(iF == 1 && iRad == 0){
	  c1 = new TCanvas();
	  c1->cd();
	  avgTimeSmeared->Draw();
	  c1->Print(Form("allPlots/avgTimeSmeared_layer_%d_rad%d_energy%d.png", iL, iRad, iF), ".png");
	}
	

	mean = -1;
	meanE = -1;
	sigma = -1;
	sigmaE = -1;
	if(avgTimeSmeared->GetEntries() < 100){
	  tgMS[iF][iRad]->SetPoint(iL, iL,  -1);
	  tgMS[iF][iRad]->SetPointError(iL, 0,  0);
	  tgS[iF][iRad]->SetPoint(iL, iL,  -1);
	  tgS[iF][iRad]->SetPointError(iL, 0,  0);
	}
	else{
	  getParameters(avgTimeSmeared, mean, meanE, sigma, sigmaE);
	  tgMS[iF][iRad]->SetPoint(iL, iL,  mean);
	  tgMS[iF][iRad]->SetPointError(iL, 0,  meanE);
	  tgS[iF][iRad]->SetPoint(iL, iL,  sigma);
	  tgS[iF][iRad]->SetPointError(iL, 0,  sigmaE);
	}

	if(avgTime->GetEntries() < 100){
	  tgM[iF][iRad]->SetPoint(iL, iL,  -1);
	  tgM[iF][iRad]->SetPointError(iL, 0, 0);
	  tg[iF][iRad]->SetPoint(iL, iL,  -1);
	  tg[iF][iRad]->SetPointError(iL, 0, 0);
	}
	else{
	  tgM[iF][iRad]->SetPoint(iL, iL,  avgTime->GetMean());
	  tgM[iF][iRad]->SetPointError(iL, 0, avgTime->GetMeanError());
	  tg[iF][iRad]->SetPoint(iL, iL,  avgTime->GetRMS());
	  tg[iF][iRad]->SetPointError(iL, 0, avgTime->GetRMSError());
	}

	delete avgTimeSmeared;
	delete avgTime;

	timeHisto_layer[iF][iL][iRad] = (TH1F*)(inF[iF]->Get(Form("timeHisto_layer%d_nR%d", iL+1, iRad+1)));
	timeHistoSmeared_layer[iF][iL][iRad] = (TH1F*)(inF[iF]->Get(Form("timeHistoSmeared_layer%d_nR%d", iL+1, iRad+1)));


      }//layer
      delete avgTimeAllSmeared;
      delete avgTimeAll;
    }//rad
  }//files

  std::cout << " all done now print results " << std::endl;


  TLegend *legTGM100 = new TLegend(0.25,0.80,0.45,0.9,NULL,"brNDC");
  legTGM100->SetTextFont(42);
  legTGM100->SetTextSize(0.05);
  legTGM100->SetFillColor(kWhite);
  legTGM100->SetLineColor(kWhite);
  legTGM100->SetShadowColor(kWhite);
  legTGM100->AddEntry(tgM[4][0], Form("%.1d GeV", energyVal.at(4)), "l");

  TLegend *legTGM = new TLegend(0.25,0.55,0.45,0.9,NULL,"brNDC");
  legTGM->SetTextFont(42);
  legTGM->SetTextSize(0.05);
  legTGM->SetFillColor(kWhite);
  legTGM->SetLineColor(kWhite);
  legTGM->SetShadowColor(kWhite);
  for(int iF=0; iF<nFiles; ++iF){
    legTGM->AddEntry(tgM[iF][0], Form("%.1d GeV", energyVal.at(iF)), "l");
  }

  TLegend *legTGMa = new TLegend(0.25,0.75,0.45,0.9,NULL,"brNDC");
  legTGMa->SetTextFont(42);
  legTGMa->SetTextSize(0.05);
  legTGMa->SetFillColor(kWhite);
  legTGMa->SetLineColor(kWhite);
  legTGMa->SetShadowColor(kWhite);
  for(int iR=0; iR<nBinsRad; ++iR){
    legTGMa->AddEntry(tgMAll[iR], Form("rad = %d", iR+1), "p");
  }

  std::cout << " legends ok  " << std::endl;

  //////
  TCanvas* ch_R100 = new TCanvas();
  ch_R100->cd();
  tg[4][0]->GetXaxis()->SetTitle("layer");
  tg[4][0]->GetYaxis()->SetTitle("RMS (ns)");
  tg[4][0]->GetYaxis()->SetRangeUser(0., 0.05);
  tg[4][0]->Draw("ap");
  tg[4][1]->Draw("p,same");
  legTGM100->Draw("same");
  ch_R100->Print((plotFolder+"/h_timeResoVsLayer_E100.png").c_str(), "png");
  ch_R100->Print((plotFolder+"/h_timeResoVsLayer_E100.pdf").c_str(), "pdf");  
  ch_R100->Print((plotFolder+"/h_timeResoVsLayer_E100.root").c_str(), "root");
  //
  TCanvas* ch_M100 = new TCanvas();
  ch_M100->cd();
  tgM[4][0]->GetXaxis()->SetTitle("layer");
  tgM[4][0]->GetYaxis()->SetTitle("mean (ns)");
  tgM[4][0]->GetYaxis()->SetRangeUser(1., 1.2);
  tgM[4][0]->Draw("ap");
  tgM[4][1]->Draw("p,same");
  legTGM100->Draw("same");
  ch_M100->Print((plotFolder+"/h_timeMeanVsLayer_E100.png").c_str(), "png");
  ch_M100->Print((plotFolder+"/h_timeMeanVsLayer_E100.pdf").c_str(), "pdf");  
  ch_M100->Print((plotFolder+"/h_timeMeanVsLayer_E100.root").c_str(), "root");

  
  TCanvas* ch_R = new TCanvas();
  ch_R->cd();
  tg[0][0]->GetXaxis()->SetTitle("layer");
  tg[0][0]->GetYaxis()->SetTitle("RMS (ns)");
  tg[0][0]->GetYaxis()->SetRangeUser(0., 0.05);
  tg[0][0]->Draw("ap");
  tg[0][1]->Draw("p,same");
  for(int iF=1; iF<nFiles; ++iF){
    tg[iF][0]->Draw("p,same");
    tg[iF][1]->Draw("p,same");    
  }
  legTGM->Draw("same");
  ch_R->Print((plotFolder+"/h_timeResoVsLayer.png").c_str(), "png");
  ch_R->Print((plotFolder+"/h_timeResoVsLayer.pdf").c_str(), "pdf");  
  ch_R->Print((plotFolder+"/h_timeResoVsLayer.root").c_str(), "root");
  //
  TCanvas* ch_M = new TCanvas();
  ch_M->cd();
  tgM[0][0]->GetXaxis()->SetTitle("layer");
  tgM[0][0]->GetYaxis()->SetTitle("mean (ns)");
  tgM[0][0]->GetYaxis()->SetRangeUser(1., 1.2);
  tgM[0][0]->Draw("ap");
  tgM[0][1]->Draw("p,same");
  for(int iF=1; iF<nFiles; ++iF){
    tgM[iF][0]->Draw("p,same");
    tgM[iF][1]->Draw("p,same");    
  }
  legTGM->Draw("same");
  ch_M->Print((plotFolder+"/h_timeMeanVsLayer.png").c_str(), "png");
  ch_M->Print((plotFolder+"/h_timeMeanVsLayer.pdf").c_str(), "pdf");  
  ch_M->Print((plotFolder+"/h_timeMeanVsLayer.root").c_str(), "root");

  //smeared
  TCanvas* ch_RS = new TCanvas();
  ch_RS->cd();
  tgS[0][0]->GetXaxis()->SetTitle("layer");
  tgS[0][0]->GetYaxis()->SetTitle("sigma (ns) - smeared");
  tgS[0][0]->GetYaxis()->SetRangeUser(0., 1.);
  tgS[0][0]->Draw("ap");
  tgS[0][1]->Draw("p,same");
  for(int iF=1; iF<nFiles; ++iF){
    tgS[iF][0]->Draw("p,same");
    tgS[iF][1]->Draw("p,same");    
  }
  legTGM->Draw("same");
  ch_RS->Print((plotFolder+"/h_timeResoVsLayer_smeared.png").c_str(), "png");
  ch_RS->Print((plotFolder+"/h_timeResoVsLayer_smeared.pdf").c_str(), "pdf");  
  ch_RS->Print((plotFolder+"/h_timeResoVsLayer_smeared.root").c_str(), "root");
  //
  TCanvas* ch_MS = new TCanvas();
  ch_MS->cd();
  tgMS[0][0]->GetXaxis()->SetTitle("layer");
  tgMS[0][0]->GetYaxis()->SetTitle("mean (ns) - smeared");
  tgMS[0][0]->GetYaxis()->SetRangeUser(1., 1.2);
  tgMS[0][0]->Draw("ap");
  tgMS[0][1]->Draw("p,same");
  for(int iF=1; iF<nFiles; ++iF){
    tgMS[iF][0]->Draw("p,same");
    tgMS[iF][1]->Draw("p,same");    
  }
  legTGM->Draw("same");
  ch_MS->Print((plotFolder+"/h_timeMeanVsLayer_smeared.png").c_str(), "png");
  ch_MS->Print((plotFolder+"/h_timeMeanVsLayer_smeared.pdf").c_str(), "pdf");  
  ch_MS->Print((plotFolder+"/h_timeMeanVsLayer_smeared.root").c_str(), "root");


  ////////all
  TCanvas* ch_Ra = new TCanvas();
  ch_Ra->cd();
  tgAll[0]->GetXaxis()->SetTitle("energy (GeV)");
  tgAll[0]->GetYaxis()->SetTitle("RMS (ns)");
  tgAll[0]->GetYaxis()->SetRangeUser(0., 0.05);
  tgAll[0]->Draw("ap");
  for(int iR=1; iR<nBinsRad; ++iR){
    tgAll[iR]->Draw("p,same");
  }
  legTGMa->Draw("same");
  ch_Ra->Print((plotFolder+"/h_timeResoVsLayer_All.png").c_str(), "png");
  ch_Ra->Print((plotFolder+"/h_timeResoVsLayer_All.pdf").c_str(), "pdf");  
  ch_Ra->Print((plotFolder+"/h_timeResoVsLayer_All.root").c_str(), "root");
  //
  TCanvas* ch_Ma = new TCanvas();
  ch_Ma->cd();
  tgMAll[0]->GetXaxis()->SetTitle("energy (GeV)");
  tgMAll[0]->GetYaxis()->SetTitle("mean (ns)");
  tgMAll[0]->GetYaxis()->SetRangeUser(1.0, 1.2);
  tgMAll[0]->Draw("ap");
  for(int iR=1; iR<nBinsRad; ++iR){
    tgMAll[iR]->Draw("p,same");
  }
  legTGMa->Draw("same");
  ch_Ma->Print((plotFolder+"/h_timeMeanVsLayer_All.png").c_str(), "png");
  ch_Ma->Print((plotFolder+"/h_timeMeanVsLayer_All.pdf").c_str(), "pdf");  
  ch_Ma->Print((plotFolder+"/h_timeMeanVsLayer_All.root").c_str(), "root");

  //smeared
  TCanvas* ch_RSa = new TCanvas();
  ch_RSa->cd();
  tgAllS[0]->GetXaxis()->SetTitle("energy (GeV)");
  tgAllS[0]->GetYaxis()->SetTitle("sigma (ns) - smeared");
  tgAllS[0]->GetYaxis()->SetRangeUser(0., 0.2);
  tgAllS[0]->Draw("ap");
  for(int iR=1; iR<nBinsRad; ++iR){
    tgAllS[iR]->Draw("p,same");
  }
  legTGMa->Draw("same");
  ch_RSa->Print((plotFolder+"/h_timeResoVsLayer_smeared_All.png").c_str(), "png");
  ch_RSa->Print((plotFolder+"/h_timeResoVsLayer_smeared_All.pdf").c_str(), "pdf");  
  ch_RSa->Print((plotFolder+"/h_timeResoVsLayer_smeared_All.root").c_str(), "root");
  //
  TCanvas* ch_MSa = new TCanvas();
  ch_MSa->cd();
  tgMAllS[0]->GetXaxis()->SetTitle("energy (GeV)");
  tgMAllS[0]->GetYaxis()->SetTitle("mean (ns) - smeared");
  tgMAllS[0]->GetYaxis()->SetRangeUser(1.0, 1.1);
  tgMAllS[0]->Draw("ap");
  for(int iR=1; iR<nBinsRad; ++iR){
    tgMAllS[iR]->Draw("p,same");    
  }
  legTGMa->Draw("same");
  ch_MSa->Print((plotFolder+"/h_timeMeanVsLayer_smeared_All.png").c_str(), "png");
  ch_MSa->Print((plotFolder+"/h_timeMeanVsLayer_smeared_All.pdf").c_str(), "pdf");  
  ch_MSa->Print((plotFolder+"/h_timeMeanVsLayer_smeared_All.root").c_str(), "root");


  nFiles = 0;
  //here below produce the distrib with time over layers/cluster/all....
  //disabled for the moment
  TCanvas* times[9][30][2];
  for(int iF=0; iF<nFiles; ++iF){
    for(int iL=0; iL<nLayers; ++iL){
      for(int iR=0; iR<nBinsRad; ++iR){
	times[iF][iL][iR] = new TCanvas();
	times[iF][iL][iR]->cd();
	timeHisto_layer[iF][iL][iR]->Draw();
	gPad->SetLogy();
	if(iL < 10)
	  times[iF][iL][iR]->Print(Form("timesPlots/times_E%d_L0%d_R%d.png", iF, iL, iR), "png");
	else
	  times[iF][iL][iR]->Print(Form("timesPlots/times_E%d_L%d_R%d.png", iF, iL, iR), "png");
      }
    }
  }

  TCanvas* timesSmeared[9][30][2];
  for(int iF=0; iF<nFiles; ++iF){
    for(int iL=0; iL<nLayers; ++iL){
      for(int iR=0; iR<nBinsRad; ++iR){
	timesSmeared[iF][iL][iR] = new TCanvas();
	timesSmeared[iF][iL][iR]->cd();
	timeHistoSmeared_layer[iF][iL][iR]->Draw();
	gPad->SetLogy();
	if(iL < 10)
	timesSmeared[iF][iL][iR]->Print(Form("timesPlots/timesSmeared_E%d_L0%d_R%d.png", iF, iL, iR), "png");
	else
	timesSmeared[iF][iL][iR]->Print(Form("timesPlots/timesSmeared_E%d_L%d_R%d.png", iF, iL, iR), "png");
      }
    }
  }

  std::cout << " all done - ciao " << std::endl;

  return;



}
