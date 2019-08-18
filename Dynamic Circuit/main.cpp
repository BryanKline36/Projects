#include <iostream>
#include "Bit.h"

char testBit = 0xFF;
char testNeighbors = 0x7C;
char testBorders = 0x38;

int main()
{
    Bit bit;

    bit.setBitValue(testBit);
    bit.setNeighborConnections(testNeighbors);
    bit.setBorders(testBorders);

    std::cout << std::hex << "state: " << (int)bit.getState() << std::endl;
    std::cout << "bit: " << (int)bit.getBitValue() << std::endl;
    std::cout << "neighbors: " << (int)bit.getNeighborConnections() << std::endl;
    std::cout << "borders: " << (int)bit.getBorders() << std::dec << std::endl;

    bit.diagnosticPrint(true);
    
    return 0;
}