#include "Medikit.h"

namespace Game::Items
{
    #pragma region Constructors
    Medikit::Medikit() :
        Consumable()
    {}
    Medikit::Medikit(const ItemType& type, const string& name,
                           uint stackMax, Texture* texture, float power) :
        Consumable(type, name, stackMax, texture, power)
    {}
    Medikit::Medikit(const Medikit& copy) :
        Consumable(copy)
    {}
    #pragma endregion

    #pragma region Operators
    Medikit& Medikit::operator=(const Medikit& copy) noexcept
    {
        Consumable::operator=(copy);

        return *this;            
    }
    #pragma endregion

    #pragma region Functions
    Item& Medikit::update(Scene& scene, float deltaTime) noexcept
    {
        (void) scene;
        (void) deltaTime;
        return *this;
    }

    Medikit& Medikit::use(Entity* target) noexcept
    {
        target->regainHealth(_power);

        return *this;
    }
    #pragma endregion
}