objects = main.o 
HGCTBAna.exe : $(objects)
	g++ -o HGCTBAna.exe $(objects) `root-config --libs`
main.o : main.C HGCTBAna.h HGCTBAna.C HGCTBAlgo.C impactPoints.h
	g++ -Wall -Wno-deprecated `root-config --cflags` main.C -c
clean :
	rm HGCTBAna.exe $(objects)

