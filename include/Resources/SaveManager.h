#ifndef __SAVE_MANAGER_H__
#define __SAVE_MANAGER_H__

#include <string>
#include "Scene.h"
#include "Player.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "LibMaths.h"

namespace Resources
{
    #pragma region Typedefs
    typedef Resources::Scene    Scene;
    typedef Game::Player        Player;
    typedef Game::LevelManager  LevelManager;
    typedef Game::GameObject    GameObject;
    typedef Core::Maths::Vec3   Vec3;
    #pragma endregion

    class SaveManager
    {
        public:
            #pragma region Functions
                static void save(std::string folderPath, Scene* scene) noexcept;
                static void load(std::string folderPath, Scene* scene, Player* player, 
                                 LevelManager* levelMgr) noexcept;
                
                static bool saveExists(std::string folderPath) noexcept;
            #pragma endregion
        private:
            #pragma region Constructors
            SaveManager() = default;
            ~SaveManager() = default;
            #pragma endregion
    
            #pragma region Functions
                static void loadLevel(std::string folderPath, Scene* scene, 
                    Player* player, LevelManager* levelMgr)             noexcept;

                static void loadInventory(std::string folderPath, Player* player) 
                                                                        noexcept;

                static void emptyScene(Scene* scene, Player* player, 
                    LevelManager* levelMgr)                             noexcept;

                static GameObject* createGameObject(Scene* scene, std::string name, 
                    std::string model, const Vec3& translation, const Vec3& rotation,
                    const Vec3& scale)                                  noexcept;

                static void setupGameObject(GameObject* go, std::string colliderType,
                    int isTrigger)                                      noexcept;

                static void createEnemy(Scene* scene, LevelManager* levelMgr, 
                    std::string name, std::string model, const Vec3& translation, 
                    const Vec3& rotation, const Vec3& scale, Player* player, 
                    float maxLife, float currentLife)                   noexcept;

                static void createPickableObject(Scene* scene, std::string name,
                    std::string model, const Vec3& translation, 
                    const Vec3 rotation, const Vec3& scale, uint itemType, 
                    int nbItems)                                        noexcept;

                static void updatePlayer(Player* player, const Vec3& translation, 
                    const Vec3& rotation, const Vec3& scale, float maxLife, 
                    float currentLife)                                  noexcept;
            #pragma endregion
    };

} // namespace Resources


#endif //__SAVE_MANAGER_H__