#include "HGCTBHisto.C"
#include "TROOT.h"
#include <algorithm>


int main(int argc, const char *argv[]){
  gROOT->ProcessLine("#include <vector>");
  //gROOT->ProcessLine("#include <map>");

  string outfile    = argv[2];
  int    nMaxEvt    = atof(argv[3]);
  int    nPrintEvt  = atof(argv[4]);
  float  beamE      = atof(argv[5]);

  HGCTBHisto m(argv[1]);
  m.Loop(outfile,nMaxEvt,nPrintEvt,beamE);
}
