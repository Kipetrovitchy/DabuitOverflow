#include "Inventory.h"

#include "ItemFactory.h"

namespace Game
{
    #pragma region Constructors
        Inventory::Inventory() :
            _items      {},
            _maxSize    { 0 },
            _mainItem   { nullptr },
            _manager    { nullptr }
        {}
        Inventory::Inventory(const Inventory& copy) :
            _items      {copy._items},
            _maxSize    {copy._maxSize},
            _mainItem   {copy._mainItem},
            _manager    { copy._manager }
        {}
        Inventory::~Inventory()
        {
            ItemsMap::iterator it = _items.begin();
            while (_items.size() > 0)
            {
                delete it->second;
                _items.erase(it);
                it = _items.begin();
            }
            _mainItem = nullptr;
        }
    #pragma endregion

    #pragma region Operators
        Inventory&  Inventory::operator=(const Inventory& copy)
        {
            _items    = copy._items;
            _maxSize  = copy._maxSize;
            _mainItem = copy._mainItem;
            _manager  = copy._manager;

            return *this;
        }
    #pragma endregion

    #pragma region Private Functions
        Item*  Inventory::addNewItem(ItemType newItemType, uint nb)
        {
            Item* newItem = createItem(newItemType, this, _manager);

            if (newItem)
            {
                uint addMax = (nb > newItem->stackMax() ? newItem->stackMax() : nb);
                newItem->currStack() = addMax;

                _items.emplace(newItemType, newItem);
            }
            
            return newItem;
        }
        Inventory&  Inventory::addExistentItem(Item* item, uint nb)
        {
            uint stackMax = item->stackMax();
            uint currStack = item->currStack();
            
            uint addMax = (nb > stackMax ? stackMax : nb);

            if ((currStack + addMax) <= stackMax)
                item->currStack() += addMax;
            else
                item->currStack() += (stackMax - currStack);

            return *this;
        }
    #pragma endregion

    #pragma region Functions
        Inventory&  Inventory::init(Player* owner, ResourcesManager* manager)
        {
            _maxSize = 10;
            _owner   = owner;
            _manager = manager;

            return *this;
        }

        Inventory&  Inventory::update(Scene& scene, float deltaTime) noexcept
        {
            ItemsMap::iterator it = _items.begin();
            for (; it != _items.end(); ++it)
                it->second->update(scene, deltaTime);

            return *this;
        }

        Item* Inventory::addItem(ItemType newItemType, uint nb) noexcept
        {
            ItemsMap::iterator it = _items.find(newItemType);
            
            if (it == _items.end())
                return addNewItem(newItemType, nb);
            else if (it->second->currStack() < it->second->stackMax())
                addExistentItem(it->second, nb);

            return it->second;
        }
        Inventory&  Inventory::removeItem(ItemType newItemType, uint nb) noexcept
        {
            ItemsMap::iterator it = _items.find(newItemType);
            if (it != _items.end())
            {
                if (it->second->currStack() <= nb)
                {
                    delete it->second;
                    _items.erase(it);
                }
                else
                    it->second->currStack() -= nb;
            }

            return *this;
        }

        Item*   Inventory::getItem(const ItemType& type) noexcept
        {
            ItemsMap::iterator it = _items.begin();
            for (; it != _items.end(); ++it)
            {
                if (it->second->type() == type)
                    return it->second;
            }
            return nullptr;
        }
        uint    Inventory::nbOfItem(const ItemType& type) noexcept
        {
            ItemsMap::iterator it = _items.begin();
            for (; it != _items.end(); ++it)
            {
                if (it->second->type() == type)
                    return it->second->currStack();
            }
            return 0;
        }

        Inventory&  Inventory::switchMain(int dir) noexcept
        {
            ItemType type { ItemType::NONE };
            //Change to the previous weapon
            if (dir < 0)
            {
                std::map<ItemType, Item*>::reverse_iterator itMain { _items.find(_mainItem->type()) };
                //First iteration, from the actual weapon to the first item
                for (auto it = itMain; it != _items.rend(); ++it)
                {
                    type = it->first;
                    if (type < ItemType::WEAPONS && type != ItemType::NONE)
                    {
                        _mainItem = it->second;
                        return *this;
                    }
                }

                //Loop the change if there is no weapon in the part checked above
                for (auto it = _items.rbegin(); it != itMain; ++it)
                {
                    type = it->first;
                    if (type < ItemType::WEAPONS && type != ItemType::NONE)
                    {
                        _mainItem = it->second;
                        return *this;
                    }
                }
            }
            //Change to the next weapon
            else if (dir > 0)
            {
                std::map<ItemType, Item*>::iterator itMain { _items.find(_mainItem->type()) };
                //First iteration, from the actual weapon to the last item
                for (auto it = std::next(itMain, 1); it != _items.end(); ++it)
                {
                    type = it->first;
                    if (type < ItemType::WEAPONS && type != ItemType::NONE)
                    {
                        _mainItem = it->second;
                        return *this;
                    }
                }

                //Loop the change if there is no weapon in the part checked above
                for (auto it = _items.begin(); it != itMain; ++it)
                {
                    type = it->first;
                    if (type < ItemType::WEAPONS && type != ItemType::NONE)
                    {
                        _mainItem = it->second;
                        return *this;
                    }
                }
            }
            
            return *this;
        }

        Inventory&  Inventory::setMain(Item* main) noexcept
        {
            Weapon* newMain = dynamic_cast<Weapon*>(main);

            if (newMain)
            {
                newMain->model()->active() = true;
                _mainItem = newMain;
            }

            return *this;
        }

        Inventory& Inventory::clear() noexcept
        {
            ItemsMap::iterator it = _items.begin();
            for (; it != _items.end(); ++it)
            {
                if (it->second)
                    delete it->second;
            }

            _items.clear();
            return *this; 
        }

        Inventory& Inventory::save(std::ofstream& fs) noexcept
        {
            ItemsMap::iterator it = _items.begin();
            for (; it != _items.end(); ++it)
            {
                fs << (uint)it->first << "," <<  it->second->currStack() << ",";
                if (_mainItem == it->second)
                    fs << 1 <<"\n";
                else
                    fs << 0 << "\n";
            }
            return *this; 
        }

    #pragma endregion
} // namespace Game