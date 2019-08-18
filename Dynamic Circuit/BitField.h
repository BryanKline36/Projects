
#include "Bit.h"
#include "Components.h"

struct FieldPosition
{
    int x;
    int y;
    int z;
};

class BitField
{

    public:

        BitField();
        BitField(FieldPosition fieldPosition, const Components* circuitComponents);
        ~BitField();

        void runCircuit();

        char getBorderValue(FieldPosition fieldPosition);

        char getBorders(FieldPosition fieldPosition);
        char getNeighborStates(FieldPosition fieldPosition);
        char getNeighborConnections(FieldPosition fieldPosition);
        char getNeighborBitValues(FieldPosition fieldPosition);

    private:

        void updateField();

        void setBorders(FieldPosition fieldPosition, char borders);
        void setNeighborStates(FieldPosition fieldPosition, char* states);
        void setNeighborConnections(FieldPosition fieldPosition, char neighborConnections);
        void setNeighborBitValues(FieldPosition fieldPosition, char neighborBitValues);
        bool positionValid(FieldPosition fieldPosition);

        void destructorHelper(int index);

        char**** fields;

        int xDimension;
        int yDimension;
        int zDimension;

        Component* components;
};