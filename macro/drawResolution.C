#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TRandom3.h"


void drawResolution(){

  gROOT->Macro("/afs/cern.ch/user/a/amartell/public/setStyle.C");

  int iColors[3] = {kBlack, kRed+2, kBlue+2};
  //  int iColorsHG[3] = {kGray+3, kRed+2, kAzure-2};
  int iColorsHG[3] = {kGreen+2, kRed+2, kAzure+2};
  int iColorsHG2[3] = {kBlack, kRed+2, kBlack};

  //from TB
  float paramA[3];
  float parErrA[3];
  float paramC[3];
  float parErrC[3];
  //100um
  paramA[0] = 4.; //10.24;
  parErrA[0] = 0.001;
  paramC[0] = 0.05;
  parErrC[0] = 0.001;
  //200um  
  paramA[1] = 4; //10.24;
  parErrA[1] = 0.001;
  paramC[1] = 0.05;
  parErrC[1] = 0.001;
  //300um 
  paramA[2] = 4; //15.5;
  parErrA[2] = 0.001;
  paramC[2] = 0.05;
  parErrC[2] = 0.001;

  float GeVToMip_300 = 1. / (85.5e-6);  //MIP/GeV
  float GeVToMip_200 = 1. / (57e-6);

  // float GeVToMip_300 = 1. / (85.5);  //MIP/GeV
  // float GeVToMip_200 = 1. / (57);

  float MipToGeV_300 = 1. * 85.5e-6;   // GeV/MIP
  float MipToGeV_200 = 1. * 57e-6;


  float MipTofC_300 = 3.84;
  float MipTofC_200 = 2.56;

  float fC2MIP_300 = 1./3.84;
  float fC2MIP_200 = 1./2.56;


  TF1* TB_MIP_100 = new TF1("TB_MIP_100", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1., 1000.);
  TF1* TB_MIP_200 = new TF1("TB_MIP_200", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1., 1000.);
  TF1* TB_MIP_300 = new TF1("TB_MIP_300", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1., 1000.);

  TB_MIP_100->SetParameters(paramA[0] * fC2MIP_300, paramC[0]);
  TB_MIP_200->SetParameters(paramA[1] * fC2MIP_200, paramC[1]);
  TB_MIP_300->SetParameters(paramA[2] * fC2MIP_300, paramC[2]);
  TB_MIP_100->SetLineColor(iColors[0]);
  TB_MIP_200->SetLineColor(iColors[1]);
  TB_MIP_300->SetLineColor(iColors[2]);
  TB_MIP_100->SetLineWidth(2);
  TB_MIP_200->SetLineWidth(2);
  TB_MIP_300->SetLineWidth(2);


  TF1* TB_GEV_100 = new TF1("TB_GEV_100", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1.e-3, 1000.);
  TF1* TB_GEV_200 = new TF1("TB_GEV_200", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1.e-3, 1000.);
  TF1* TB_GEV_300 = new TF1("TB_GEV_300", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1.e-3, 1000.);

  TB_GEV_100->SetParameters(paramA[0] * fC2MIP_300 * MipToGeV_300, paramC[0]);
  TB_GEV_200->SetParameters(paramA[1] * fC2MIP_200 * MipToGeV_200, paramC[1]);
  TB_GEV_300->SetParameters(paramA[2] * fC2MIP_300 * MipToGeV_300,  paramC[2]);
  TB_GEV_100->SetLineColor(iColors[0]);
  TB_GEV_200->SetLineColor(iColors[1]);
  TB_GEV_300->SetLineColor(iColors[2]);
  TB_GEV_100->SetLineWidth(2);
  TB_GEV_200->SetLineWidth(2);
  TB_GEV_300->SetLineWidth(2);


  TF1* TB_Q_100 = new TF1("TB_Q_100", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1., 1000.);
  TF1* TB_Q_200 = new TF1("TB_Q_200", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1., 1000.);
  TF1* TB_Q_300 = new TF1("TB_Q_300", "sqrt(pow([0]/x, 2) + pow([1], 2) )", 1., 1000.);

  TB_Q_100->SetParameters(paramA[0] , paramC[0]);
  TB_Q_200->SetParameters(paramA[1] , paramC[1]);
  TB_Q_300->SetParameters(paramA[2] ,  paramC[2]);
  TB_Q_100->SetLineColor(iColors[0]);
  TB_Q_200->SetLineColor(iColors[1]);
  TB_Q_300->SetLineColor(iColors[2]);
  TB_Q_100->SetLineWidth(2);
  TB_Q_200->SetLineWidth(2);
  TB_Q_300->SetLineWidth(2);


  gStyle->SetOptTitle(0);

  TLatex tBX;
  tBX.SetNDC();
  tBX.SetTextSize(0.05);
  tBX.SetTextFont(132);



  TLatex tBX200;
  tBX200.SetNDC();
  tBX200.SetTextSize(0.03);
  tBX200.SetTextFont(132);
  tBX200.SetTextColor(iColors[1]);

  TLatex tBX300;
  tBX300.SetNDC();
  tBX300.SetTextSize(0.03);
  tBX300.SetTextFont(132);
  tBX300.SetTextColor(iColors[2]);

  TLatex tB200;
  tB200.SetNDC();
  tB200.SetTextSize(0.035);
  tB200.SetTextFont(132);
  tB200.SetTextColor(iColors[1]);

  TLatex tB300;
  tB300.SetNDC();
  tB300.SetTextSize(0.035);
  tB300.SetTextFont(132);
  tB300.SetTextColor(iColors[2]);



  TCanvas* cMIP = new TCanvas(); 
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetGrid();
  cMIP->cd();
  TB_MIP_200->SetRange(1, 1000);
  TB_MIP_200->GetXaxis()->SetTitle("MIP");
  TB_MIP_200->GetYaxis()->SetRangeUser(0.01, 100.);
  TB_MIP_200->GetYaxis()->SetTitle("#sigma_{t} (ns)");

  TB_MIP_200->Draw();
  TB_MIP_300->Draw("same");

  tBX.DrawLatex(0.50,0.85, "#sigma(t) (ns) = A/x #oplus C");


  tBX200.DrawLatex(0.2,0.80, "fC2MIP = 1./2.56 MIP/fC");
  tBX300.DrawLatex(0.2,0.75, "fC2MIP = 1./3.84 MIP/fC");
  tB200.DrawLatex(0.5,0.80, Form("TB 200um A = %.2fns  C = %.2fns", TB_MIP_200->GetParameter(0), TB_MIP_200->GetParameter(1)));
  tB300.DrawLatex(0.5,0.75, Form("TB 300um A = %.2fns  C = %.2fns", TB_MIP_300->GetParameter(0), TB_MIP_300->GetParameter(1)));

  cMIP->Print("timeResolution_singleSensor_MIP.png", "png");
  cMIP->Print("timeResolution_singleSensor_MIP.pdf", "pdf");
  cMIP->Print("timeResolution_singleSensor_MIP.root", "root");



  TCanvas* cGEV = new TCanvas(); 
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetGrid();
  cGEV->cd();
  //  TB_GEV_200->SetRange(1, 1000);
  TB_GEV_200->GetXaxis()->SetTitle("energy (keV)");
  TB_GEV_200->GetYaxis()->SetRangeUser(0.01, 20.);
  TB_GEV_200->GetYaxis()->SetTitle("#sigma_{t} (ns)");

  TB_GEV_200->Draw();
  TB_GEV_300->Draw("same");

  tBX.DrawLatex(0.50,0.85, "#sigma(t) (ns) = A/x #oplus C");


  tBX200.DrawLatex(0.2,0.80, "MIP2GeV = 57e-6 GeV/MIP");
  tBX300.DrawLatex(0.2,0.75, "MIP2GeV = 85.5e-6 GeV/MIP");
  tB200.DrawLatex(0.5,0.80, Form("TB 200um A = %.2ens  C = %.2fns", TB_GEV_200->GetParameter(0), TB_GEV_200->GetParameter(1)));
  tB300.DrawLatex(0.5,0.75, Form("TB 300um A = %.2ens  C = %.2fns", TB_GEV_300->GetParameter(0), TB_GEV_300->GetParameter(1)));

  cGEV->Print("timeResolution_singleSensor_GEV.png", "png");
  cGEV->Print("timeResolution_singleSensor_GEV.pdf", "pdf");
  cGEV->Print("timeResolution_singleSensor_GEV.root", "root");

  TCanvas* cQ = new TCanvas(); 
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->SetGrid();
  cQ->cd();
  //  TB_Q_200->SetRange(1, 1000);
  TB_Q_200->GetXaxis()->SetTitle("Q (fC)");
  TB_Q_200->GetYaxis()->SetRangeUser(0.01, 50.);
  TB_Q_200->GetYaxis()->SetTitle("#sigma_{t} (ns)");

  TB_Q_200->Draw();
  TB_Q_300->Draw("same");

  tBX.DrawLatex(0.50,0.85, "#sigma(t) (ns) = A/x #oplus C");

  tB200.DrawLatex(0.5,0.80, Form("TB 200um A = %.2fns  C = %.2fns", TB_Q_200->GetParameter(0), TB_Q_200->GetParameter(1)));
  tB300.DrawLatex(0.5,0.75, Form("TB 300um A = %.2fns  C = %.2fns", TB_Q_300->GetParameter(0), TB_Q_300->GetParameter(1)));

  cQ->Print("timeResolution_singleSensor_Q.png", "png");
  cQ->Print("timeResolution_singleSensor_Q.pdf", "pdf");
  cQ->Print("timeResolution_singleSensor_Q.root", "root");






}
