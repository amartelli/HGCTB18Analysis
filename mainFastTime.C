#include "HGCTBAnaFastTime.C"
#include "TROOT.h"
#include <algorithm>

int main(){

  std::cout << " >>> in mainFastTime timing analysis " << std::endl;
  const int nfiles = 9;
  int energyNames[nfiles] = {20, 30, 50, 80, 100, 150, 200, 250, 300};

  //better to stick to realistic sim with Angle
  string path = "/eos/cms/store/group/dpg_hgcal/tb_hgcal/2018/cern_h2_october/offline_analysis/sim_ntuples/v2/withMCP/EMN/Angle/";
  //  string path = "/eos/cms/store/group/dpg_hgcal/tb_hgcal/2018/cern_h2_october/offline_analysis/sim_ntuples/v2/withMCP/EMN/noAngle/";

  //int StopAtEvent=10000;
  int StopAtEvent=-1;
  //  int StopAtEvent=10;
  int ReportEvery=1000;
  double mipCut = 15.0;
  
  
  for(int i=0; i<nfiles; i++){
    //ntuple_sim_config22_pdgID11_beamMomentum20_listFTFP_BERT_EMN.root
    string fname = Form("%sntuple_sim_config22_pdgID11_beamMomentum%d_listFTFP_BERT_EMN.root",path.c_str(),energyNames[i]);

    //your output path
    string outFname = Form("/eos/cms/store/group/upgrade/HGCAL/simulation/2018/Oct/V2/timingStudies/histo_%d.root",energyNames[i]);    
    //string outFname = Form("/eos/cms/store/group/upgrade/HGCAL/simulation/2018/Oct/V2/timingStudies/amartellTests/histoTest_%d.root",energyNames[i]);

    //string outFname = Form("/eos/cms/store/group/upgrade/HGCAL/simulation/2018/Oct/V2/timingStudies/amartellTests/histoSmearingOK_%d.root",energyNames[i]);
    //  string outFname = Form("/eos/cms/store/group/upgrade/HGCAL/simulation/2018/Oct/V2/timingStudies/amartellTests/noTime_histo_%d.root",energyNames[i]);

    cout<<"======Looping over "<<fname<<endl;

    HGCTBAnaFastTime m;
    m.Loop(fname, outFname, StopAtEvent, ReportEvery, mipCut);
    
    //gROOT->ProcessLine( Form("./HGCTBAna.exe %s %s %d %d %f", fname.c_str(), outFname.c_str(), StopAtEvent, ReportEvery, mipCut));

    
  }//for(int i=0; i<nfiiles; i++)
  
  return 0;  
}
