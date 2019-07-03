#ifndef __ITEM_FACTORY_H__
#define __ITEM_FACTORY_H__

#include "Weapon.h"
#include "Ammo.h"
#include "ResourcesManager.h"

namespace Game::Items
{
    class Consumable;

    #pragma region Typedefs
    typedef Resources::ResourcesManager ResourcesManager;
    #pragma endregion

    Item*   createItem(const ItemType& type, Inventory* inv,
                       ResourcesManager* manager) noexcept;

    Weapon* createWeapon(const ItemType& type, Inventory* inv,
                         ResourcesManager* manager) noexcept;

    Ammo*   createAmmo(const ItemType& type, ResourcesManager* manager) noexcept;

    Consumable* createConsumable(const ItemType& type, ResourcesManager* manager) noexcept;
}

#endif//__ITEM_TYPE_H__