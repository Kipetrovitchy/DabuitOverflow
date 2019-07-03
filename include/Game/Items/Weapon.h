#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <string>

#include "Item.h"
#include "BulletFactory.h"

namespace Game
{
    class Inventory;
}

namespace Game::Items
{
    #pragma region Typedefs
        typedef std::string         string;
        typedef Core::Maths::Vec3   Vec3;
        typedef Resources::Scene    Scene;
    #pragma endregion

    class Weapon : public Item
    {
        private:
            #pragma region Attributes
                //The inventory in wich the weapon is stocked
                Inventory*              _inventory;
                //The 3d model of the weapon
                GameObject*             _model;
                //Shoot variables
                bool                    _canShoot;
                float                   _shootCd;
                float                   _reloadCd;
                //Bullet fired
                ItemType                _bulletType;
                std::vector<Bullet*>    _firedBullets;
                //Main stats
                uint                    _actualClip;
                uint                    _clipSize;
                float                   _rate;
                float                   _range;
                float                   _reload;
                float                   _damage;
            #pragma endregion

        public:
            #pragma region Constructors
                Weapon();
                Weapon(Inventory* inventory, const ItemType& type,
                       const string& name, float weight, const ItemType& bType,
                       uint clipS, float rate, float range, float reload,
                       float damage, Texture* texture, GameObject* model);
                Weapon(const Weapon& copy);
                ~Weapon();
            #pragma endregion

            #pragma region Accessors
                inline GameObject*  model()            { return _model; }
                inline bool         canShoot()   const { return _canShoot; }
                inline bool&        canShoot()         { return _canShoot; }
                inline ItemType     bulletType() const { return _bulletType; }
                inline ItemType&    bulletType()       { return _bulletType; }
                inline uint         clipSize()   const { return _clipSize; }
                inline uint&        clipSize()         { return _clipSize; }
                inline float        rate()       const { return _rate; }
                inline float&       rate()             { return _rate; }
                inline float        range()      const { return _range; }
                inline float&       range()            { return _range; }
                inline float        reload()     const { return _reload; }
                inline float&       reload()           { return _reload; }
                inline float        damage()     const { return _damage; }
                inline float&       damage()           { return _damage; }
                inline uint         actualClip() const { return _actualClip; }
                inline uint&        actualClip()       { return _actualClip; }
                inline Texture*     texture()          { return _texture; }
            #pragma endregion

            #pragma region Operators
                Weapon& operator=(const Weapon& copy);
            #pragma endregion

            #pragma region Functions
                Item&       update(Scene& scene, float deltaTime) noexcept override;

                Weapon&     shoot(Scene& scene, const Vec3& front) noexcept;
                Weapon&     updateCanShootValue(float deltaTime) noexcept;
                Weapon&     startReload() noexcept;
                Weapon&     reloadClip() noexcept;

                Weapon&     setActive(bool flag) noexcept;
            #pragma endregion
    };
} // namespace Game::Items

#endif //__WEAPON_H__