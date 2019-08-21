# HGCTB18Analysis

Requiremnt: ROOT

Instruction:

Since it is not depend on the CMSSW, any CMSSW release can be used to import ROOT.

cmsrel CMSSW_11_0_0_pre5

cd CMSSW_11_0_0_pre5/src

cmsenv

git clone https://github.com/ashimroy/HGCTB18Analysis.git

make


That's it. Ready to run.

How to run?
./HGCTBAna.exe InputFie OutputFile TotalEvent ReportEvery MIPCut

Example:
./HGCTBAna.exe /afs/cern.ch/work/a/asroy/public/HGCalTB2018/SIMtoDataFormat/CMSSW_9_3_0/src/HGCal/ntupleNewBeamProfEleE100.root HGCTBAnaOutput.root 10000 1000 1.0

Or,
./run.sh  


Please change the input parameters in the run.sh according to your requirement and then run.  

