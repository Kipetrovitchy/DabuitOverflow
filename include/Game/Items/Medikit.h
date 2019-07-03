#ifndef __MEDIKIT_H__
#define __MEDIKIT_H__

#include "Consumable.h"

namespace Game::Items
{
    #pragma region Typedefs
    typedef Resources::ResourcesManager ResourcesManager;
    #pragma endregion

    class Medikit : public Consumable
    {
    private:
        #pragma region Attributes
        #pragma endregion
    public:
        #pragma region Constructors
        Medikit();
        Medikit(const ItemType& type, const string& name,
                      uint stackMax, Texture* texture, float power);
        Medikit(const Medikit& copy);
        ~Medikit() = default;
        #pragma endregion

        #pragma region Accessors

        #pragma endregion

        #pragma region Operators
        Medikit& operator=(const Medikit& copy) noexcept;
        #pragma endregion

        #pragma region Functions
        Item& update(Scene& scene, float deltaTime) noexcept override;

        Medikit& use(Entity* target) noexcept override;
        #pragma endregion
    };    
}

#endif//__MEDIKIT_H__