#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "LibMaths.h"
#include "Entity.h"
#include "Model.h"
#include "Shader.h"
#include "Transform.h"
#include "IController.h"
#include "StateMachinePlayer.h"
#include "Inventory.h"
#include "Scene.h"

#include <functional>

#define PLAYER_BASE_ACCELERATION 40.0f
#define PLAYER_BASE_MAXSPEED 10.0f
#define PLAYER_BASE_JUMPSTRENGHT 10.0f 
#define PLAYER_BASE_DECELERATION 30.0f
#define PLAYER_BASE_HEALTH 100.f

#define ZOOM_MIN 1.0f
#define ZOOM_MAX 2.0f

namespace LowRenderer
{
    class Camera3D;
}

namespace Game
{
    #pragma region Typedefs
        typedef Core::Maths::Vec3                   Vec3;
        typedef Resources::Scene                    Scene;
        typedef Resources::Model                    Model;
        typedef Resources::Shader                   Shader;
        typedef Physics::Transform                  Transform;
        typedef StateMachines::IController          IController;
        typedef StateMachines::StateMachinePlayer   StateMachinePlayer;
        typedef Game::Items::Item                   Item;
        typedef Inputs::InputMgr                    InputMgr;
        typedef LowRenderer::Camera3D               Camera3D;
    #pragma endregion

    class Player : public Entity, public IController
    {
        private:
            #pragma region Attributes
            bool            _hasToJump;
            bool            _hasToShoot;
            bool            _hasToReload;
            bool            _hasToHeal;
            bool            _hasToAim;
            bool            _isGrounded;
            
            Camera3D*       _camera;
            GameObject*     _gunAnchorObject;
            float           _acceleration;
            float           _deceleration;
            float           _maxSpeed;
            float           _jumpStrenght;
            Vec3            _direction;
            float           _zoom;

            StateMachinePlayer _stateMachine;

            Inventory       _inventory;

            std::function<void(int, int)> _updateHP;
            std::function<void(Weapon*)>  _updateWeapon;
            std::function<void(int, int)> _updateAmmo;
            std::function<void(bool)>     _updateMedkit;
            #pragma endregion

        public:
            #pragma region Constructors
            Player();
            Player(const std::string& name, Model* m, Shader* s, const Transform& tr, 
                    Camera3D* camera, float maxLife = PLAYER_BASE_HEALTH,
                    float maxSpeed = PLAYER_BASE_MAXSPEED);
            Player(const Player& type);
            ~Player() = default;
            #pragma endregion

            #pragma region Accessors
            inline bool         isGrounded()        { return _isGrounded; }
            inline Inventory&   inventory()         { return _inventory; }
            inline GameObject*  gunAnchorObject()   { return _gunAnchorObject; }
            #pragma endregion

            #pragma region Operators
            Player& operator=(const Player& p);
            #pragma endregion

            #pragma region Functions
            Vec3    getForward()            noexcept;
            Vec3    getRight()              noexcept;

            Player& moveForward()           noexcept;
            Player& moveBackward()          noexcept;
            Player& moveRight()             noexcept;
            Player& moveLeft()              noexcept;
            
            Player& jump()                  noexcept;
            Player& shoot()                 noexcept;
            Player& reload()                noexcept;
            Player& changeWeapon(int dir)   noexcept;
            Player& heal()                  noexcept;
            Player& aim()                   noexcept;
            
            GameObject& update(Scene& scene, float deltaTime) noexcept override;

            Player& updateHpHUD()           noexcept;
            Player& updateWeaponHUD()       noexcept;
            Player& updateAmmoHUD()         noexcept;
            Player& updateMedkitHUD()       noexcept;
            Player& move(float deltaTime)   noexcept;

            Player& tryJump()               noexcept;
            Player& tryShoot(Scene& scene)  noexcept;
            Player& tryReload()             noexcept;
            Player& tryHeal()               noexcept;
            Player& tryAim(float deltaTime) noexcept;

            Player& createStateMachine() noexcept;

            Player& updateIsGroundedValue(Scene& scene) noexcept;
            Player& loadGunModel() noexcept;
            Entity& takeDamage(float f) noexcept override;

            bool    struckByBullet(Scene& scene,
                                   const Core::Maths::Vec3& collPoint,
                                   float damage) noexcept override;

            bool pickUpItem(ItemType type, uint numberOfItem) noexcept override;
            #pragma endregion

            #pragma region Accessors
            inline StateMachinePlayer& stateMachine() { return _stateMachine; };

            Player& setUpdateHP(std::function<void(int, int)> func) noexcept;
            Player& setUpdateWeapon(std::function<void(Weapon*)> func) noexcept;
            Player& setUpdateAmmo(std::function<void(int, int)> func) noexcept;
            Player& setUpdateMedkit(std::function<void(bool)> func) noexcept;

            GameObject& save(std::ofstream& fs, ResourcesManager& resourceManager, std::string folderPath) noexcept override;
            #pragma endregion
    };
} // namespace Game

#endif //__PLAYER_H__