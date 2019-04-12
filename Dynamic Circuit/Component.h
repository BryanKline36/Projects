#include "BitField.h"

class Component
{
    enum Type
    {
        Switch,
        LED
    };


    public:

        Component();
        Component(Type componentType);

        Component& operator = (const Component& component);

        void activate(BitField::FieldPosition fieldPosition);
        void activate(BitField::FieldPosition fieldPosition, const Bit &bit);

        void deactivate(BitField::FieldPosition fieldPosition);
        void deactivate(FieldPosition fieldPosition, const Bit &bit);


    private:

        bool state;
        Type type;



};