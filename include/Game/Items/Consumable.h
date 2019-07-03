#ifndef __CONSUMABLE_H__
#define __CONSUMABLE_H__

#include "Item.h"
#include "Entity.h"

namespace Game::Items
{
    #pragma region Typedefs
    typedef Game::Entity    Entity;
    #pragma endregion

    class Consumable : public Item
    {
    protected:
        #pragma region Attributes
        float   _power;
        #pragma endregion
    public:
        #pragma region Constructors
        Consumable();
        Consumable(const ItemType& type, const string& name,
                   uint stackMax, Texture* texture, float power);
        Consumable(const Consumable& copy);
        ~Consumable() = default;
        #pragma endregion

        #pragma region Accessors
        inline float   power() const { return _power; }
        inline float&  power()       { return _power; }
        #pragma endregion

        #pragma region Operators
        Consumable& operator=(const Consumable& copy) noexcept;
        #pragma endregion

        #pragma region Functions
            virtual Item& update(Scene& scene, float deltaTime) noexcept = 0;
            virtual Consumable& use(Entity* target) noexcept = 0;
        #pragma endregion
    };    
}

#endif//__CONSUMABLE_H__