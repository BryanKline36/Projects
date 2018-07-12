all: project11

project11: project11.cpp list2.o
	g++ project11.cpp list2.o -o project11

list2.o: list2.cpp
	g++ -c list2.cpp

clean:
	rm -f *.o project11
