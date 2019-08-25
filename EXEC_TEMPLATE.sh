#!/bin/bash                                                                                                              
DataType="#DataType#"

if [ "$DataType" == "Data" ]
then 
    InputFilePath=/eos/cms/store/group/dpg_hgcal/tb_hgcal/forAnalysis/DataNtuple/HGCal_TB18_October_ConfigurationI/v13/Electron/ 
    InputFileName=HGCTB18_DataNtuple_#Par#E#Energy#.root  ## Data
    OutputFile=HGCTBAnaOutput_#DataType#_#Par#E#Energy#_#TagData#.root
else
    InputFilePath=/eos/cms/store/group/dpg_hgcal/tb_hgcal/simulation2018/HGCal_TB18_October_ConfigurationI/BeamMomProfileGun_VtxGaus/ntuples/
    InputFileName=ntuple_sim_config22_pdgID11_beamMomentum#Energy#.root  ##MC
    OutputFile=HGCTBAnaOutput_#DataType#_#Par#E#Energy#_#TagMC#.root
fi

MaxEvent=-1
ReportEvery=1000
MIPCut=1.0
                                                  
echo "inside jobsubmit"
pwd
cd /afs/cern.ch/work/a/asroy/public/HGCalTB2018/Analysis/CMSSW_11_0_0_pre5/src
pwd
source /cvmfs/cms.cern.ch/cmsset_default.sh
echo "sourced"
cmsenv
cd ${_CONDOR_SCRATCH_DIR}
pwd
hostname
make
echo "Running... ./HGCTBAna.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $MIPCut"
./HGCTBAna.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $MIPCut
