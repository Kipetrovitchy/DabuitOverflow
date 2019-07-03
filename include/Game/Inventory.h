#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <map>
#include <iostream>

#include "Weapon.h"
#include "Ammo.h"
#include "ResourcesManager.h"

namespace Game
{
    #pragma region Typedefs
        typedef Resources::Scene            Scene;
        typedef Resources::ResourcesManager ResourcesManager;
        typedef Items::Item                 Item;
        typedef Items::Weapon               Weapon;
        typedef Items::Ammo                 Ammo;
        typedef Items::ItemType             ItemType;
        typedef std::map<ItemType, Item*>   ItemsMap;
    #pragma endregion

    class Inventory
    {
        private:
            #pragma region Attributes
                Player*             _owner;
                ItemsMap            _items;
                uint                _maxSize;
                Item*               _mainItem;
                ResourcesManager*   _manager;
            #pragma endregion

            #pragma region Private Functions
                Item*  addNewItem(ItemType newItemType, uint nb);
                Inventory&  addExistentItem(Item* item, uint nb);
            #pragma endregion

        public:
            #pragma region Constructors
                Inventory();
                Inventory(const Inventory& copy);
                ~Inventory();
            #pragma endregion

            #pragma region Accessors
                inline Player*   owner()          { return _owner; }
                inline ItemsMap  items()    const { return _items; }
                inline ItemsMap& items()          { return _items; }
                inline uint      maxSize()  const { return _maxSize; }
                inline uint&     maxSize()        { return _maxSize; }
                inline Item*     mainItem() const { return _mainItem; }
            #pragma endregion

            #pragma region Operators
                Inventory&  operator=(const Inventory& copy);
            #pragma endregion

            #pragma region Functions
                Inventory&  init(Player* owner, ResourcesManager* manager);

                Inventory&  update(Scene& scene, float deltaTime) noexcept ;

                Item*       addItem(ItemType, uint nb = 1) noexcept ;
                Inventory&  removeItem(ItemType, uint nb = 1) noexcept ;

                Item*       getItem(const ItemType& type) noexcept ;
                uint        nbOfItem(const ItemType& type) noexcept ;

                Inventory&  switchMain(int dir) noexcept ;
                Inventory&  setMain(Item* main) noexcept ;

                Inventory&  clear()             noexcept;
                Inventory&  save(std::ofstream& fs) noexcept;
            #pragma endregion
    };
} // namespace Game

#endif //__INVENTORY_H__