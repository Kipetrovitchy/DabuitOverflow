#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>

#include "Scene.h"
#include "Texture.h"

namespace Game::Items
{
    enum class ItemType : uint
    {
        NONE = 0,

        M4,
        EAGLE,

        WEAPONS,

        RIFLE_AMMO,
        PISTOL_AMMO,

        AMMO,

        MEDIKIT,

        CONSUMABLE,

        COUNT
    };

    #pragma region Typedefs
        typedef std::string         string;
        typedef Resources::Scene    Scene;
        typedef Resources::Texture  Texture;
    #pragma endregion

    class Item
    {
        protected:
            #pragma region Attributes
                ItemType    _type;
                string      _name;
                Texture*    _texture;
                uint        _stackMax;
                uint        _currStack;
                float       _weight;
            #pragma endregion

        public:
            #pragma region Constructors
                Item();
                Item(const ItemType& type, const string& name,
                     uint stackMax, uint currStack, float weight, Texture* texture);
                Item(const Item& copy);
                virtual ~Item() = default;
            #pragma endregion

            #pragma region Accessors
                inline ItemType     type()      const { return _type; }
                inline ItemType&    type()            { return _type; }
                inline string       name()      const { return _name; }
                inline string&      name()            { return _name; }
                inline uint         stackMax()  const { return _stackMax; }
                inline uint&        stackMax()        { return _stackMax; }
                inline uint         currStack() const { return _currStack; }
                inline uint&        currStack()       { return _currStack; }
                inline float        weight()    const { return _weight; }
                inline float&       weight()          { return _weight; }
            #pragma endregion

            #pragma region Operators
                Item&   operator=(const Item& copy);
                bool    operator==(const Item& i);
            #pragma endregion 

            #pragma region Functions
                virtual Item& update(Scene& scene, float deltaTime) noexcept = 0;
            #pragma endregion
    };
} // namespace Game::Items

#endif //__ITEM_H__