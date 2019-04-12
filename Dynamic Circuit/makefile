all: DynamicCircuit

DynamicCircuit: main.cpp BitField.o Bit.o Component.o
	g++ main.cpp BitField.o Bit.o Component.o -o DynamicCircuit

BitFieled.o: BitField.cpp
	g++ -c BitField.cpp

Bit.o: Bit.cpp
	g++ -c Bit.cpp

Component.o: Component.cpp
	g++ -c Component.cpp

clean:
	rm -f *.o DynamicCircuit
