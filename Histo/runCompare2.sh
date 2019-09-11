BaseDir=$PWD
Tagf1=Data
Tagf1V=v13  # i.e. v13 or ...
Tagf2=MC
Tagf2V=BeamProf_v1  # i.e. BeamProf_v1 or v2_withMCP_EMN_Angle or ..
Par=Ele

#BeamE=( 20 30 50 80 100 120 200 250 300 )
BeamE=( 30 100 250 )
BESize=${#BeamE[@]}

HistoName=(SumE E1byE7 E1byE19 E7byE19 E7byEAll E19byEAll )
HNSize=${#HistoName[@]}

make clean
make

for (( iBE=0; iBE<${BESize}; iBE++ ))
do
    echo ======================== Beam Energy ${BeamE[$iBE]} GeV =======================
    File1=$BaseDir/Histograms/$Tagf1/$Tagf1V/$Par/HGCTBHisto_${Tagf1}_${Par}E${BeamE[$iBE]}_${Tagf1V}.root
    File2=$BaseDir/Histograms/$Tagf2/$Tagf2V/$Par/HGCTBHisto_${Tagf2}_${Par}E${BeamE[$iBE]}_${Tagf2V}.root
    
    for (( iHN=0; iHN<${HNSize}; iHN++ ))
    do
	
	echo "        ================== HistoName: ${HistoName[$iHN]} ================"
	
	echo "mkdir -p Plots/${Tagf1}_$Tagf1V-${Tagf2}_$Tagf2V/$Par/${BeamE[$iBE]}/${HistoName[$iHN]}"
	mkdir -p Plots/${Tagf1}_$Tagf1V-${Tagf2}_$Tagf2V/$Par/${BeamE[$iBE]}/${HistoName[$iHN]}/
	cp CompareHisto2.exe Plots/${Tagf1}_$Tagf1V-${Tagf2}_$Tagf2V/$Par/${BeamE[$iBE]}/${HistoName[$iHN]}/
	echo "cd Plots/${Tagf1}_$Tagf1V-${Tagf2}_$Tagf2V/$Par/${BeamE[$iBE]}/${HistoName[$iHN]}/"
	cd Plots/${Tagf1}_$Tagf1V-${Tagf2}_$Tagf2V/$Par/${BeamE[$iBE]}/${HistoName[$iHN]}/
	echo "mkdir -p PDF/ PNG/ ROOT/"
	mkdir -p PDF/ PNG/ ROOT/
	echo "Running... ./CompareHisto2.exe ${Tagf1}_$Tagf1V $File1 ${Tagf2}_$Tagf2V $File2 ${HistoName[$iHN]} $Par ${BeamE[$iBE]}"
	./CompareHisto2.exe ${Tagf1}_$Tagf1V $File1 ${Tagf2}_$Tagf2V $File2 ${HistoName[$iHN]} $Par ${BeamE[$iBE]}
	mv *pdf PDF/
	mv *png PNG/
	mv *root ROOT/
	cd $BaseDir
    done
done
