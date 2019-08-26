InputFilePath=/eos/cms/store/group/dpg_hgcal/tb_hgcal/forAnalysis/DataNtuple/HGCal_TB18_October_ConfigurationI/v13/Electron/ 
#InputFilePath=/eos/cms/store/group/dpg_hgcal/tb_hgcal/simulation2018/HGCal_TB18_October_ConfigurationI/BeamMomProfileGun_VtxGaus/ntuples/

InputFileName=HGCTB18_DataNtuple_EleE30.root
#InputFileName=ntuple_sim_config22_pdgID11_beamMomentum100.root

OutputFile=HGCTBAnaOutput_Data_EleE30_v13.root
#OutputFile=HGCTBAnaOutput_MC_EleE100_BeamProf1.root

MaxEvent=-1
ReportEvery=1000
MIPCut=1.0

echo "Running... ./HGCTBAna.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $MIPCut"
./HGCTBAna.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $MIPCut
