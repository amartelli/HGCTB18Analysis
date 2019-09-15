void getMeanReso(){

  const int nfiles = 9;
  double energyNames[nfiles] = {20, 30, 50, 80, 100, 150, 200, 250, 300};
  
  double mean[nfiles];
  double rms[nfiles];
  
  string histName="time_EachLayerTime_allinOne_nR2";
  
  for(int i=0; i<nfiles; i++){

    string fname = Form("histo_%d.root",(int)energyNames[i]);
    TFile *infile = TFile::Open(fname.c_str());
    TH1F *h = (TH1F*)infile->Get(histName.c_str());
    h->GetXaxis()->SetRangeUser(110.5, 111);
    mean[i] = h->GetMean();
    rms[i] = h->GetRMS();
  }


  TGraph *g = new TGraph(nfiles, energyNames, rms );
  g->SetMarkerStyle(20);
  g->Draw("AC");
}
