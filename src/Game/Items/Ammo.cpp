#include "Ammo.h"
 
namespace Game::Items
{
    #pragma region Constructors
        Ammo::Ammo() : Item()
        {}
        Ammo::Ammo(const ItemType& type, const std::string& name, uint stackMax,
                   Texture* texture) : 
            Item(type, name, stackMax, 0, 0, texture)
        {}
        Ammo::Ammo(const Ammo& copy) : Item(copy)
        {}
    #pragma endregion
    #pragma region Operators
        Ammo&     Ammo::operator=(const Ammo& copy)
        {
            Item::operator=(copy);
 
            return *this;
        }
    #pragma endregion
 
    #pragma region Functions
        Item&   Ammo::update(Scene& scene, float deltaTime) noexcept
        {
            (void) scene;
            (void) deltaTime;

            return *this;
        }
    #pragma endregion
}