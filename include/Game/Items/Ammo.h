#ifndef __AMMO_H__
#define __AMMO_H__
 
#include <string>
 
#include "Item.h"
 
namespace Game::Items
{
    #pragma region Typedefs

    #pragma endregion
 
    class Ammo : public Item
    {
        protected:
            #pragma region Attributes

            #pragma endregion
 
        public:
            #pragma region Constructors
                Ammo();
                Ammo(const ItemType& type, const std::string& name, uint stackMax,
                     Texture* texture);
                Ammo(const Ammo& copy);
                ~Ammo() = default;
            #pragma endregion
 
            #pragma region Accessors

            #pragma endregion
 
            #pragma region Operators
                Ammo&     operator=(const Ammo& copy);
            #pragma endregion
 
            #pragma region Functions
                Item&       update(Scene& scene, float deltaTime) noexcept override;
            #pragma endregion
    };
} // namespace Game::Items
 
#endif //__AMMO_H__