BaseDir=/afs/cern.ch/work/a/asroy/public/HGCalTB2018/Analysis/CMSSW_11_0_0_pre5/src/
BeamE=100
Par=Ele
DataType=MC  # Data/MC
Tag=BeamProf_v1 # i.e. v13/BeamProf_v1

MaxEvent=-1
ReportEvery=1000

InputFilePath=${BaseDir}/${DataType}/${Tag}/
InputFileName=HGCTBAnaOutput_${DataType}_${Par}E${BeamE}_${Tag}.root

OutputFile=HGCTBHisto_${DataType}_${Par}E${BeamE}_${Tag}.root

echo "Running... ./HGCTBHisto.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $BeamE"
./HGCTBHisto.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery $BeamE
