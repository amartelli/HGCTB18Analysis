all : HGCTBHisto.exe CompareHisto2.exe CompareHisto3.exe

objects1 = main.o 
objects2 = CompareHisto2.o
objects3 = CompareHisto3.o

HGCTBHisto.exe : $(objects1)
	g++ -o HGCTBHisto.exe $(objects1) `root-config --libs`
main.o : main.C HGCTBHisto.h HGCTBHisto.C
	g++ -Wall -Wno-deprecated `root-config --cflags` main.C -c

CompareHisto2.exe : $(objects2)
	g++ -o CompareHisto2.exe $(objects2) `root-config --libs`

CompareHisto2.o : CompareHisto2.C
	g++ -Wall -Wno-deprecated `root-config --cflags` CompareHisto2.C -c

CompareHisto3.exe : $(objects3)
	g++ -o CompareHisto3.exe $(objects3) `root-config --libs`

CompareHisto3.o : CompareHisto3.C
	g++ -Wall -Wno-deprecated `root-config --cflags` CompareHisto3.C -c

clean :
	rm HGCTBHisto.exe CompareHisto.exe $(objects1) $(objects2) $(objects3)
