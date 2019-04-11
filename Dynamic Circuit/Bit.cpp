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

void Bit::setBitNeighborConnections(char neighborConnections)
{
    state |= neighborConnections & neighborMask
}

void Bit::setBitBorders(char bitBorders)
{

    borders = borderValues;
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

char Bit::getBitNeighborConnections()
{
    return state & neighborMask;
}

char Bit::getBitBorders()
{
    return borders;
}

char Bit::getState()
{
    return state;
}

void Bit::DiagnosticPrint(bool verbose = false)
{
    if(verbose)
    {
        std::cout << std::hex << "bitMask: " << << std::endl;
        std::cout << "neighborMask: " << neighborMask << std::endl;
    }

    std::cout << "state: " << state << std::endl;
    std::cout << "borders " << borders << std::dec << std::endl;
}

