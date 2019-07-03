#include "ItemFactory.h"

#include "Medikit.h"

namespace Game::Items
{
    Item*   createItem(const ItemType& type, Inventory* inv,
                       ResourcesManager* manager) noexcept
    {
        if (type < ItemType::WEAPONS)
            return createWeapon(type, inv, manager);
        else if (type < ItemType::AMMO && type > ItemType::WEAPONS)
            return createAmmo(type, manager);
        else
            return createConsumable(type, manager);
    }

    Weapon* createWeapon(const ItemType& type, Inventory* inv,
                         ResourcesManager* manager) noexcept
    {
        switch (type)
        {
        {
        case ItemType::EAGLE:
            return new Weapon(
                inv, type, "Aigle du Désert", 1.f,
                ItemType::PISTOL_AMMO, 8, 120.f, 20.f, 0.75f, 45.f,
                manager->getTexture("./resources/Items/Handgun/Aigle_du_Desert.png"),
                new GameObject("Aigle du Désert",
                    manager->getModel("resources/Items/Handgun/pist_deagle.obj"),
			        manager->getShader (PATH_VERTEX, PATH_FRAGMENT),
			        {{0.0f, 0.0f, 0.0f}, Vec3::zero, Vec3::one * 0.1}));
        }
        case ItemType::M4:
        {
            return new Weapon(
                inv, type, "M4A1", 3.f,
                ItemType::RIFLE_AMMO, 24, 666.f, 10.f, 1.25f, 24.f,
                manager->getTexture("./resources/Items/M4/M4a1.png"),
                new GameObject("M4A1", 
                    manager->getModel("resources/Items/M4/M4a1.obj"),
			        manager->getShader (PATH_VERTEX, PATH_FRAGMENT),
			        {{0.0f, 0.0f, 0.0f}, Vec3::zero, Vec3::one * 0.1}));
        }
        default: return nullptr;
        }
    }

    Ammo* createAmmo(const ItemType& type, ResourcesManager* manager) noexcept
    {
        switch (type)
        {
            case ItemType::RIFLE_AMMO:
            {
                return new Ammo(type, "RIFLE ammo", 192,
                    manager->getTexture("./resources/Items/RIFLE ammo.png"));
            }
            case ItemType::PISTOL_AMMO:
            {
                return new Ammo(type, "PISTOL ammo", 64,
                    manager->getTexture("./resources/Items/PISTOL ammo.png"));
            }
            default:    return nullptr;
        }
    }

    Consumable* createConsumable(const ItemType& type, ResourcesManager* manager) noexcept
    {
        switch (type)
        {
            case ItemType::MEDIKIT:
            {
                return new Medikit(type, "Medikit", 1,
                    manager->getTexture("./resources/Items/medkit.png"), 50);
            }
            default:    return nullptr;
        }
    }
} // Game::Items
