#include "SaveManager.h"
#include "Enemy.h"
#include "csv.h"
#include "Item.h"
#include "PickableItem.h"
#include "Weapon.h"
#include <fstream>

namespace Resources
{
    typedef Game::Items::Item           Item;
    typedef Game::Items::ItemType       ItemType;
    typedef std::map<ItemType, Item*>   ItemsMap;
    typedef Game::Items::PickableItem   PickableItem;
    typedef Game::Items::Weapon         Weapon;
    #pragma region Functions
    bool SaveManager::saveExists(std::string folderPath) noexcept
    {
        std::ifstream level(folderPath + "level.csv");
        std::ifstream inventory(folderPath + "inventory.csv");

        return level.good() && inventory.good();
    }
        void SaveManager::load(std::string folderPath, Scene* scene, Player* player,
                               LevelManager* levelMgr) noexcept
    {
        loadLevel(folderPath, scene, player, levelMgr);
        loadInventory(folderPath, player);
    }

    void SaveManager::loadLevel(std::string folderPath, Scene* scene, Player* player,
                                LevelManager* levelMgr) noexcept
    {
        emptyScene(scene, player, levelMgr);

        std::string fileName = folderPath + "level.csv";
        io::CSVReader<18> in(fileName);

        in.read_header(io::ignore_extra_column, "Name", "Model", 
            "TranslationX", "TranslationY", "TranslationZ", 
            "RotationX", "RotationY", "RotationZ", 
            "ScaleX", "ScaleY", "ScaleZ", 
            "Collider", "IsTrigger", "GameObjectType", "MaxLife", "CurrentLife",
            "ItemPicked", "NbItemPicked");
        
        std::string name {""};
        std::string model {""};
        float trsltX {0.0f};
        float trsltY {0.0f};
        float trsltZ {0.0f};
        float rotateX {0.0f};
        float rotateY {0.0f};
        float rotateZ {0.0f};
        float scaleY {0.0f};
        float scaleX {0.0f};
        float scaleZ {0.0f};
        std::string colliderType {""};
        int isTrigger {0};
        int gameObjectType {0};
        float maxLife {0.0f};
        float currentLife {0.0f};
        float itemPicked {0.0f};
        float nbItemPicked {0.0f};

        while(in.read_row(name, model, trsltX, trsltY, trsltZ, rotateX, rotateY, rotateZ, 
            scaleX, scaleY, scaleZ, colliderType, isTrigger, gameObjectType, maxLife, currentLife, itemPicked, nbItemPicked))
        {
            Vec3 translation {trsltX, trsltY, trsltZ};
            Vec3 rotation {rotateX, rotateY, rotateZ};
            Vec3 scale {scaleX, scaleY, scaleZ};
            
            if (gameObjectType == 0)
            {
                GameObject* go;
                go = createGameObject(scene, name, model, translation, rotation, scale);
                setupGameObject(go, colliderType, isTrigger);
            }
            else if (gameObjectType == 1)
            {
                createEnemy(scene, levelMgr, name, model, translation, rotation, scale, player,
                    maxLife, currentLife);
            }
            else if (gameObjectType == 2)
            {
                updatePlayer(player, translation, rotation, scale,
                    maxLife, currentLife);
            }
            else if (gameObjectType == 3)
            {
                createPickableObject(scene, name, model, translation, rotation, scale, itemPicked, nbItemPicked);
            }
        }
    }

    void SaveManager::loadInventory(std::string folderPath, Player* player) noexcept
    {
        //Clear the current inventory
        player->inventory().clear();

        std::string fileName = folderPath + "inventory.csv";
        io::CSVReader<3> in(fileName);

        in.read_header(io::ignore_extra_column, "ItemType", "Nb", "IsMainItem");
        uint itemType {0};
        uint nb {0};
        uint isMainItem {0};

        while(in.read_row(itemType, nb, isMainItem))
        {
            if (isMainItem)
            {
                Item* mainItem = player->inventory().addItem((ItemType)itemType, nb);
                player->inventory().setMain(mainItem);
            }
            else
            {
                player->inventory().addItem((ItemType)itemType, nb);
            }
        }
        
        ItemsMap inv = player->inventory().items();
        ItemsMap::iterator it = inv.begin();
        for (; it != inv.end(); ++it)
        {
            Weapon* gun = dynamic_cast<Weapon*>(it->second);
            if (gun)
                gun->reloadClip();
        }        

        player->updateAmmoHUD();
        player->updateWeaponHUD();
        player->updateMedkitHUD();
    }

    void SaveManager::emptyScene(Scene* scene, Player* player, LevelManager* lvlMgr) noexcept
    {
        //std::cout << "Emptying scene" << std::endl;
        
        // Remove each children's scene
        std::list<GameObject*>::iterator itChildren = scene->objects().begin();
        while (itChildren != scene->objects().end())
        {
            if ((*itChildren) != player)
            {
                if (*itChildren)
                    delete *itChildren;
                itChildren = scene->objects().erase(itChildren);
            }
            else
                itChildren++;
        }

        // Remove each children's scene
        std::vector<GameObject*>::iterator itAdd = scene->objectsToAdd().begin();
        while (itAdd != scene->objectsToAdd().end())
        {
            if ((*itAdd) != player)
            {
                if (*itAdd)
                    delete *itAdd;
                itAdd = scene->objectsToAdd().erase(itAdd);
            }
            else
                itAdd++;
            
        }
        
        // As we are only stocking references there's no use to destroy the objects
        scene->objectsToRemove().clear();

        lvlMgr->enemies().clear();

        return;
    }

    GameObject* SaveManager::createGameObject(Scene* scene, std::string name, std::string model,
        const Vec3& translation, const Vec3& rotation, const Vec3& scale) noexcept
    {
        GameObject* go;
        size_t objPos = model.find(".obj");

        if (objPos != std::string::npos)
        {
            go = scene->addChild(new GameObject(
                name,
		        scene->resourcesManager()->getModel  (model),
		        scene->resourcesManager()->getShader (PATH_VERTEX, PATH_FRAGMENT),
		        {translation, rotation, scale}
		    ));
        }
        else
        {
            go = scene->addChild(new GameObject(
                name,
		        Model::createCube(scene->resourcesManager(), model),
		        scene->resourcesManager()->getShader (PATH_VERTEX, PATH_FRAGMENT),
		        {translation, rotation, scale}
		    )); 
        }
        return go;
    }

    void SaveManager::setupGameObject(GameObject* go, std::string colliderType,
        int isTrigger) noexcept
    {
        if (go && colliderType != "")
        {
            if (colliderType == "Box")
                go->addCollider(Physics::Collisions::EColliderType::BOX);
            else
                go->addCollider(Physics::Collisions::EColliderType::SPHERE);
            go->collider()->isTrigger() = isTrigger;
        }
    }

    void SaveManager::createEnemy(Scene* scene, LevelManager* levelMgr,
                    std::string name, std::string model, const Vec3& translation,
                    const Vec3& rotation, const Vec3& scale, Player* player, 
                    float maxLife, float currentLife) noexcept
    {
        Game::Enemy* newEnemy = new Game::Enemy(
            name,
		    scene->resourcesManager()->getModel  (model),
		 	scene->resourcesManager()->getShader (PATH_VERTEX, PATH_FRAGMENT),
		 	{translation, rotation, scale},
		    player,
            maxLife, currentLife);

        scene->addChild(newEnemy);
        levelMgr->addEnemy(newEnemy);
    }

    void SaveManager::updatePlayer(Player* player, const Vec3& translation, const Vec3& rotation, const Vec3& scale,
                    float maxLife, float currentLife) noexcept
    {
        player->transform().updateTransform(translation, rotation, scale);
        player->maxLife() = maxLife;
        player->life() = currentLife;
        player->updateHpHUD();
    }

    void SaveManager::createPickableObject(Scene* scene, std::string name, 
        std::string model, const Vec3& translation, const Vec3 rotation, 
        const Vec3& scale, uint itemType, int nbItems) noexcept
    {
        size_t objPos = model.find(".obj");

        if (objPos != std::string::npos)
        {
            PickableItem* pItem = new PickableItem(
                name,
                scene->resourcesManager()->getModel  (model),
                scene->resourcesManager()->getShader (PATH_VERTEX, PATH_FRAGMENT),
                {translation, rotation, scale}, (ItemType)itemType, nbItems);

            scene->addChild(pItem);
        }
        else
        {
            PickableItem* pItem = new PickableItem(
                name,
                Model::createCube(scene->resourcesManager(), model),
                scene->resourcesManager()->getShader (PATH_VERTEX, PATH_FRAGMENT),
                {translation, rotation, scale}, (ItemType)itemType, nbItems);

            scene->addChild(pItem);
        }
    }

    void SaveManager::save(std::string folderPath, Scene* scene) noexcept
    {
        std::ofstream fs;
        std::string fileName = folderPath + "level.csv";
        fs.open (fileName, std::ofstream::trunc);

        fs << "Name,Model,TranslationX,TranslationY,TranslationZ," << 
        "RotationX,RotationY,RotationZ,ScaleX,ScaleY,ScaleZ," <<
        "Collider,IsTrigger,GameObjectType,MaxLife,CurrentLife,ItemPicked," <<
        "NbItemPicked\n";

        scene->save(fs, folderPath);

        fs.close();
    }
    #pragma endregion
    
} // namespace Resources
