#include <iostream>
#include "Bit.h"

Bit::Bit()
{
    state = 0x00;
    borders = 0x00;
}

Bit::~Bit()
{
    // default
}

void Bit::setBitValue(char bitValue)
{
    state |= bitValue & bitMask;
}

void Bit::setNeighborConnections(char neighborConnections)
{
    state |= neighborConnections & neighborMask;
}

void Bit::setBorders(char bitBorders)
{
    borders = borderMask | bitBorders;
}

void Bit::setState(char state)
{
    state = state;
}

char Bit::getBitValue()
{
    return state & bitMask;
}

bool Bit::getBit()
{
    return state & bitMask;   
}

char Bit::getNeighborConnections()
{
    return (state & neighborMask) & borders;
}

char Bit::getBorders()
{
    return borders;
}

char Bit::getState()
{
    return state;
}

void Bit::diagnosticPrint(bool verbose)
{
    if(verbose)
    {
        std::cout << std::hex << "bitMask: " << (int)bitMask << std::endl;
        std::cout << "neighborMask: " << (int)neighborMask << std::endl;
    }

    std::cout << "state: " << (int)state << std::endl;
    std::cout << "borders: " << (int)borders << std::dec << std::endl;
}

