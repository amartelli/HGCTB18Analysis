BeamE=250
Par=Ele
#DataType=MC  # Data/MC                                                                                   
#Tag=BeamProf_v1 # i.e. v13/BeamProf_v1
 
File1=HGCTBHisto_Data_EleE${BeamE}_v13.root
File2=HGCTBHisto_MC_EleE${BeamE}_BeamProf_v1.root
HistoName1=SumELayer
HistoName2=E1byE7
HistoName3=E1byE19
HistoName4=E7byE19
HistoName5=E19byEAll
#XTitle="SumRechits"
#YTitle="Events Normalized to Data"

echo "mkdir -p Plots/$Par/$BeamE/$HistoName1"
mkdir -p Plots/$Par/$BeamE/$HistoName1
echo "Running... ./CompareHisto.exe $File1 $File2 $HistoName1 $Par $BeamE"
./CompareHisto.exe $File1 $File2 $HistoName1 $Par $BeamE

echo "mkdir -p Plots/$Par/$BeamE/$HistoName2"
mkdir -p Plots/$Par/$BeamE/$HistoName2
echo "Running... ./CompareHisto.exe $File1 $File2 $HistoName2 $Par $BeamE"
./CompareHisto.exe $File1 $File2 $HistoName2 $Par $BeamE

echo "mkdir -p Plots/$Par/$BeamE/$HistoName3"
mkdir -p Plots/$Par/$BeamE/$HistoName3
echo "Running... ./CompareHisto.exe $File1 $File2 $HistoName3 $Par $BeamE"
./CompareHisto.exe $File1 $File2 $HistoName3 $Par $BeamE

echo "mkdir -p Plots/$Par/$BeamE/$HistoName4"
mkdir -p Plots/$Par/$BeamE/$HistoName4
echo "Running... ./CompareHisto.exe $File1 $File2 $HistoName4 $Par $BeamE"
./CompareHisto.exe $File1 $File2 $HistoName4 $Par $BeamE

echo "mkdir -p Plots/$Par/$BeamE/$HistoName5"
mkdir -p Plots/$Par/$BeamE/$HistoName5
echo "Running... ./CompareHisto.exe $File1 $File2 $HistoName5 $Par $BeamE"
./CompareHisto.exe $File1 $File2 $HistoName5 $Par $BeamE
