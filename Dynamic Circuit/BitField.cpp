#include "BitField.h"

#DEFINE TOTAL_FIELDS
#DEFINE FIELD_ZERO
#DEFINE FIELD_ONE

Bifield::BitField()
{
    fields = NULL;
    components = NULL;

    xDimension = 0;
    yDimension = 0;
    zDimension = 0;
}

Bifield::BitField(FieldPosition fieldPosition, Components* circuitComponents)
{
    int index, componentsSize = sizeof(circuitComponents) / sizeof(Components);
    int xAxis, yAxis, zAxis;

    components = new Components[componentsSize];

    for(index = 0; index < componentsSize; ++index)
    {   
        components[index] = circuitComponents[index];
    }

    xDimension = fieldPosition.x;
    yDimension = fieldPosition.y;
    zDimension = fieldPosition.z;

    fields = new Bit***[TOTAL_FIELDS];

    fields[FIELD_ZERO] = new Bit**[xDimension];
    fields[FIELD_ONE] = new Bit**[xDimension];

    for(xAxis = 0; xAxis < xDimension; ++xAxis)
    {
        fields[FIELD_ZERO][xAxis] = new Bit*[yAxis];
        fields[FIELD_ONE][xAxis] = new Bit*[yAxis];

        for(yAxis = 0; yAxis < yDimension; ++yAxis)
        {
            fields[FIELD_ZERO][xAxis][yAxis] = new Bit[zAxis];
            fields[FIELD_ONE][xAxis][yAxis] = new Bit[zAxis];
        }
    }
}


Bifield::~BitField()
{
    int xAxis, yAxis, zAxis;

    if(components != NULL)
    {
        delete[] components;
    }

    if(fields != NULL)
    {
        for(xAxis = 0; xAxis < xDimension; ++xAxis)
        {
            fields[FIELD_ZERO][xAxis] = new Bit*[yAxis];
            fields[FIELD_ONE][xAxis] = new Bit*[yAxis];

            for(yAxis = 0; yAxis < yDimension; ++yAxis)
            {
                fields[FIELD_ZERO][xAxis][yAxis] = new Bit[zAxis];
                fields[FIELD_ONE][xAxis][yAxis] = new Bit[zAxis];
            }
        }


    }
}

void Bifield::runCircuit()
{

}

char Bifield::getBorderValue(FieldPosition fieldPosition)
{

}

char Bifield::getBorders(FieldPosition fieldPosition)
{

}

char Bifield::getNeighborStates(FieldPosition fieldPosition)
{

}

char Bifield::getNeighborConnections(FieldPosition fieldPosition)
{

}

char Bifield::getNeighborBitValues(FieldPosition fieldPosition)
{

}

void Bifield::updateField()
{

}

void Bifield::setBorders(FieldPosition fieldPosition, char borders)
{

}

void Bifield::setNeighborStates(FieldPosition fieldPosition, char* states)
{

}

void Bifield::setNeighborConnections(FieldPosition fieldPosition, char neighborConnections)
{

}

void Bifield::setNeighborBitValues(FieldPosition fieldPosition, char neighborBitValues)
{

}

