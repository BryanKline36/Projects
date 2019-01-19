all: HW1

HW1: main.cpp NetworkTopology.o Router.o
	g++ main.cpp NetworkTopology.o Router.o -o HW1

NetworkTopology.o: NetworkTopology.cpp NetworkTopology.h
	g++ -c NetworkTopology.cpp

Router.o: Router.cpp Router.h
	g++ -c Router.cpp

clean:
	rm -f *.o main
