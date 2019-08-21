InputFilePath=/afs/cern.ch/work/a/asroy/public/HGCalTB2018/SIMtoDataFormat/CMSSW_9_3_0/src/HGCal/
InputFileName=ntupleNewBeamProfEleE100.root
OutputFile=test_output.root
StopAtEvent=10000
ReportEvery=1000
MIPCut=1.0

echo "Running... ./HGCTBAna.exe $InputFilePath$InputFileName $OutputFile $StopAtEvent $ReportEvery $MIPCut"
./HGCTBAna.exe $InputFilePath$InputFileName $OutputFile $StopAtEvent $ReportEvery $MIPCut
