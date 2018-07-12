all: project10

project10: project10.cpp queue3.o
	g++ project10.cpp queue3.o -o project10

queue3.o: queue3.cpp
	g++ -c queue3.cpp

clean:
	rm -f *.o project10
