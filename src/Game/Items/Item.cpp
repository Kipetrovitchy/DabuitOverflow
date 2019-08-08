#include "Item.h"
#include <limits.h>

namespace Game::Items
{
    #pragma region Constructors
        Item::Item() :
            _type       {ItemType::NONE},
            _name       {"Item"},
            _texture    { nullptr },
            _stackMax   {UINT8_MAX},
            _currStack  {0},
            _weight     {0}
        {}
        Item::Item(const ItemType& type, const string& name,
                   uint stackMax, uint currStack, float weight, Texture* texture) :
            _type       {type},
            _name       {name},
            _texture    {texture},
            _stackMax   {stackMax},
            _currStack  {currStack},
            _weight     {weight}
        {}
        Item::Item(const Item& copy) :
            _type       {copy._type},
            _name       {copy._name},
            _texture    {copy._texture},
            _stackMax   {copy._stackMax},
            _currStack  {copy._currStack},
            _weight     {copy._weight}
        {}
    #pragma endregion

    #pragma region Operators
        Item&   Item::operator=(const Item& copy)
        {
            _type       = copy._type;
            _name       = copy._name;
            _texture    = copy._texture;
            _stackMax   = copy._stackMax;
            _currStack  = copy._currStack;
            _weight     = copy._weight;

            return *this;
        }
        bool    Item::operator==(const Item& i)
        {
            if (_type == i._type)
                return true;
            else
                return false;
        }
    #pragma endregion

    #pragma region Functions

    #pragma endregion
} // namespace Game::Items
