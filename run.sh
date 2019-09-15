#!/bin/bash


#InputFilePath=/afs/cern.ch/work/a/asroy/public/HGCalTB2018/SIMtoDataFormat/CMSSW_9_3_0/src/HGCal/
#InputFileName=ntupleNewBeamProfEleE100.root

InputFilePath=/eos/cms/store/group/dpg_hgcal/tb_hgcal/2018/cern_h2_october/offline_analysis/sim_ntuples/v2/withMCP/EMN/Angle/
InputFileName=ntuple_sim_config22_pdgID11_beamMomentum100_listFTFP_BERT_EMN.root
OutputFile=test_output.root
#StopAtEvent=10000
#StopAtEvent=-1
StopAtEvent=10000
ReportEvery=1000
MIPCut=1.0

echo "Running... ./HGCTBAna.exe $InputFilePath$InputFileName $OutputFile $StopAtEvent $ReportEvery $MIPCut"
./HGCTBAna.exe $InputFilePath$InputFileName $OutputFile $StopAtEvent $ReportEvery $MIPCut
