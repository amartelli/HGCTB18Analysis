BaseDir=/afs/cern.ch/work/a/asroy/public/HGCalTB2018/Analysis/CMSSW_11_0_0_pre5/src/
Par=Ele
#DataType=Data  # Data/MC
DataType=MC  # Data/MC
#Tag=v13 # i.e. v13/BeamProf_v1
Tag=BeamProf_v1 # i.e. v13/BeamProf_v1
#Tag=v2_withMCP_EMN_Angle # i.e. v13/BeamProf_v1/ 

MaxEvent=-1
ReportEvery=1000

InputFilePath=${BaseDir}/${DataType}/${Tag}/

#BeamE=100
#BeamE=( 20 30 50 80 100 120 200 250 300 )
BeamE=( 30 100 250 )
BESize=${#BeamE[@]}

echo "mkdir -p Histograms/$DataType/$Tag/$Par"
mkdir -p Histograms/$DataType/$Tag/$Par
echo "cp HGCTBHisto.exe Histograms/$DataType/$Tag/$Par/"
cp HGCTBHisto.exe Histograms/$DataType/$Tag/$Par/
echo "cd Histograms/$DataType/$Tag/$Par"
cd Histograms/$DataType/$Tag/$Par

for (( iBE=0; iBE<${BESize}; iBE++ ))
do
    echo ======================== Beam BEergy ${BeamE[$iBE]} GeV ====================

    InputFileName=HGCTBAnaOutput_${DataType}_${Par}E${BeamE[$iBE]}_${Tag}.root
    OutputFile=HGCTBHisto_${DataType}_${Par}E${BeamE[$iBE]}_${Tag}.root
    
    echo "Running... ./HGCTBHisto.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery ${BeamE[$iBE]}"
    ./HGCTBHisto.exe $InputFilePath$InputFileName $OutputFile $MaxEvent $ReportEvery ${BeamE[$iBE]}
done
