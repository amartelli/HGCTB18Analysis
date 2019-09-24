
objects2 = mainFastTime.o
HGCTBAnaFastTime.exe : $(objects2)
	g++ -o HGCTBAnaFastTime.exe $(objects2) `root-config --libs`
mainFastTime.o : mainFastTime.C HGCTBAnaFastTime.h HGCTBAnaFastTime.C HGCTBAlgoFastTime.C
	g++ -Wall -Wno-deprecated `root-config --cflags` mainFastTime.C -c

clean :
	rm HGCTBAnaFastTime.exe $(objects2) HGCTBAna.exe  $(objects1)


objects1 = main.o 
HGCTBAna.exe : $(objects1)
	g++ -o HGCTBAna.exe $(objects1) `root-config --libs`
main.o : main.C HGCTBAna.h HGCTBAna.C HGCTBAlgo.C
	g++ -Wall -Wno-deprecated `root-config --cflags` main.C -c


#g++ -o HGCTBAnaFastTime.exe mainFastTime.o `root-config --libs` 
#g++ -Wall -Wno-deprecated  `root-config --cflags` HGCTBAnaFastTime.h HGCTBAnaFastTime.C HGCTBAlgoFastTime.C mainFastTime.C -c
