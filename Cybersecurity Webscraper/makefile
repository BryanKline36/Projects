all: updateDictionary

updateDictionary: main.cpp Dictionary.o Accumulator.o
	g++ main.cpp Dictionary.o Accumulator.o -o updateDictionary

Dictionary.o: Dictionary.cpp Dictionary.h
	g++ -c Dictionary.cpp

Accumulator.o: Accumulator.cpp Accumulator.h
	g++ -c Accumulator.cpp

clean:
	rm -f *.o main
