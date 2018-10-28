all: MapMakerMain

MapMakerMain: mapMakerDriver.cpp MapMaker.o
	g++-7 mapMakerDriver.cpp MapMaker.o -o MapMakerMain

MapMaker.o: MapMaker.cpp
	g++-7 -c MapMaker.cpp

clean:
	rm -f *.o MapMakerMain


