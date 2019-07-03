#include "Consumable.h"

namespace Game::Items
{
    #pragma region Constructors
    Consumable::Consumable() :
        Item(),
        _power {0.0f}
    {}
    Consumable::Consumable(const ItemType& type, const string& name,
                           uint stackMax, Texture* texture, float power) :
        Item(type, name, stackMax, 0, 0, texture),
        _power  {power}
    {}
    Consumable::Consumable(const Consumable& copy) :
        Item(copy),
        _power  {copy._power}
    {}
    #pragma endregion

    #pragma region Operators
    Consumable& Consumable::operator=(const Consumable& copy) noexcept
    {
        Item::operator=(copy);
        _power = copy._power;

        return *this;            
    }
    #pragma endregion

    #pragma region Functions
    #pragma endregion 
}