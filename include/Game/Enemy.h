#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Model.h"
#include "Shader.h"
#include "Transform.h"
#include "IController.h"
#include "LibMaths.h"
#include "StateMachine.h"

#define ENEMY_VIEW_RANGE 20
#define ENEMY_HIT_RANGE 2
#define ENEMY_ATTACKCOOLDOWN 1.0f
#define ENEMY_DAMAGE 25.0f
#define ENEMY_SPEED 2.5f
#define ENEMY_ACCELERATION 30.0f

namespace Game
{
    #pragma region Typedefs
        typedef ::Resources::Model            Model;
        typedef ::Resources::Shader           Shader;
        typedef ::Physics::Transform          Transform;
        typedef StateMachines::IController    IController;
        typedef StateMachines::StateMachine   StateMachine;
        typedef ::Core::Maths::Vec3           Vec3;
        typedef Inputs::InputMgr               InputMgr;
    #pragma endregion

    class Enemy : public Entity, public IController
    {
        private:
            #pragma region Attributes
            bool        _canSeeTarget;
            bool        _canHitTarget;
            Entity*     _target;
            Vec3        _lastKnownTargetPos;
            float       _viewRange;
            float       _hitRange;
            float       _attackCooldown;
            float       _attackCooldownMax;
            float       _damage;
            StateMachine  _stateMachine;
            #pragma endregion
    
        public:
            #pragma region Constructors
            Enemy();
            Enemy(const Enemy& e);
            Enemy(Model* m, Shader* s, const Transform& tr, Entity* target);
            Enemy(const std::string& name, Model* m, Shader* s, const Transform& tr, 
                    Entity* target, float maxLife, float currentLife, 
                    float viewRange = ENEMY_VIEW_RANGE, float hitRange = ENEMY_HIT_RANGE);
            ~Enemy() = default;
            #pragma endregion

            #pragma region Accessors
            inline Vec3     lastKownTargetPos() const { return _lastKnownTargetPos; };
            inline Vec3&    lastKownTargetPos() { return _lastKnownTargetPos; };
            inline bool     CanSeeTarget() const { return _canSeeTarget; };
            inline bool&    CanSeeTarget() { return _canSeeTarget; };
            inline bool     CanHitTarget() const { return _canHitTarget; };
            inline bool&    CanHitTarget() { return _canHitTarget; };
            #pragma endregion
    
            #pragma region Operators
            Enemy& operator=(const Enemy& e);
            #pragma endregion
    
            #pragma region Functions
            bool        checkTargetPos(Scene& scene) noexcept;
            GameObject& update(Scene& scene, float deltaTime)                         noexcept override;
            Enemy&      updateKnownTargetPos(Scene& scene) noexcept;
            Enemy&      updateCooldown(float deltaTime)                 noexcept;
            Enemy&      resetCooldown()                                 noexcept;
            Enemy&      moveTowardTarget(float deltaTime)               noexcept;
            Enemy&      attack()                                        noexcept;
            float       distanceToTarget()                              noexcept;

            Enemy&      createStateMachine()                             noexcept;
            GameObject& save(std::ofstream& fs, ResourcesManager& resourceManager, std::string folderPath) noexcept override;
            #pragma endregion
    };
} // namespace Game

#endif //__ENEMY_H__
