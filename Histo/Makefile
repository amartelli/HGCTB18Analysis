all : HGCTBHisto.exe CompareHisto.exe

objects1 = main.o 
objects2 = CompareHisto.o

HGCTBHisto.exe : $(objects1)
	g++ -o HGCTBHisto.exe $(objects1) `root-config --libs`
main.o : main.C HGCTBHisto.h HGCTBHisto.C
	g++ -Wall -Wno-deprecated `root-config --cflags` main.C -c

CompareHisto.exe : $(objects2)
	g++ -o CompareHisto.exe $(objects2) `root-config --libs`

CompareHisto.o : CompareHisto.C
	g++ -Wall -Wno-deprecated `root-config --cflags` CompareHisto.C -c

clean :
	rm HGCTBHisto.exe CompareHisto.exe $(objects1) $(objects2)
