#include "Enemy.h"

#include "SegmentHit.h"
#include "Segment.h"
#include "3DCollisions.h"
#include "DecisionEnemyCanAttack.h"
#include "DecisionEnemySeeTarget.h"
#include "DecisionEnemyReachedTargetPos.h"
#include "StateEnemyAttack.h"
#include "StateEnemyChase.h"
#include "StateEnemyIdle.h"
#include "Transition.h"

namespace Game
{
    #pragma region Typedefs
        typedef ::Physics::Collisions::Segment    Segment;
        typedef ::Physics::Collisions::SegmentHit SegmentHit;
    #pragma endregion

    #pragma region Constructors

    Enemy::Enemy() :
        Entity(),
        IController(),
        _target { nullptr },
        _lastKnownTargetPos { Vec3::infinity },
        _viewRange { ENEMY_VIEW_RANGE },
        _hitRange { ENEMY_HIT_RANGE },
        _attackCooldown { ENEMY_ATTACKCOOLDOWN },
        _attackCooldownMax { ENEMY_ATTACKCOOLDOWN },
        _damage { ENEMY_DAMAGE }
    {
        addRigidBody(true, 3.0f);
        addCollider(Physics::Collisions::EColliderType::SPHERE);
        createStateMachine();
    }

    Enemy::Enemy(const Enemy& e) :
        Entity(e),
        _target { e._target},
        _lastKnownTargetPos { e._lastKnownTargetPos },
        _viewRange { e._viewRange },
        _hitRange { e._hitRange },
        _attackCooldown { e._attackCooldown },
        _attackCooldownMax { e._attackCooldownMax },
        _damage { e._damage }
    {
        addRigidBody(true, 3.0f);
        addCollider(Physics::Collisions::EColliderType::SPHERE);
        createStateMachine();
    }

    Enemy::Enemy(Model* m, Shader* s, const Transform& tr, Entity* target) :
        Entity("", m, s, tr),
        IController(),
        _target { target },
        _lastKnownTargetPos { Vec3::infinity },
        _viewRange { ENEMY_VIEW_RANGE },
        _hitRange { ENEMY_HIT_RANGE },
        _attackCooldown { ENEMY_ATTACKCOOLDOWN },
        _attackCooldownMax { ENEMY_ATTACKCOOLDOWN },
        _damage { ENEMY_DAMAGE }
    {
        addRigidBody(true, 3.0f);
        addCollider(Physics::Collisions::EColliderType::SPHERE);
        createStateMachine();
    }

    Enemy::Enemy(const std::string& name, Model* m, Shader* s, const Transform& tr, 
                    Entity* target, float maxLife, float currentLife, 
                    float viewRange, float hitRange) :
        Entity(name, m, s, tr, maxLife, currentLife),
        IController(),
        _target { target },
        _lastKnownTargetPos { Vec3::infinity },
        _viewRange { viewRange },
        _hitRange { hitRange },
        _attackCooldown { ENEMY_ATTACKCOOLDOWN },
        _attackCooldownMax { ENEMY_ATTACKCOOLDOWN },
        _damage { ENEMY_DAMAGE }
    {
        addRigidBody(true, 3.0f);
        addCollider(Physics::Collisions::EColliderType::SPHERE);
        createStateMachine();
    }
    #pragma endregion

    #pragma region Operators
        Enemy& Enemy::operator=(const Enemy& e)
        {
            Entity::operator=(e);
            _target = e._target;
            _viewRange = e._viewRange;
            _hitRange = e._hitRange;

            return *this;
        }
    #pragma endregion

    #pragma region Functions
    bool Enemy::checkTargetPos(Scene& scene) noexcept
    {
        _canSeeTarget = false;
        _canHitTarget = false;
        SegmentHit* hit {nullptr};

        //Segment enemy - player
        Segment s {_transform.position(), _target->transform().position()};

        //Target is too far for the enemy to see it
        if (s.sqLength() > _viewRange * _viewRange)
            return false;

        std::list<GameObject*>& gameObjects { scene.objects() };
        //We test if the segment collide with something else than the player
        for (GameObject* go : gameObjects)
        {
            if (go && go != this && go != _target)
            {
                if (go->isActive() && go->hasCollider() && !go->collider()->isTrigger() 
                    && go->collideWithSegment(s, hit))
                {
                    delete hit;
                    return false;
                }
            }
        }

        //Target is near enough to be attacked
        if (s.sqLength() <= _hitRange * _hitRange)
            _canHitTarget = true;

        _canSeeTarget = true;
        return true;
    }

    GameObject& Enemy::update(Scene& scene, float deltaTime) noexcept
    {
        if (!_active)
            return *this;

        _stateMachine.update(scene, deltaTime);
        return *this;
    }

    Enemy& Enemy::updateKnownTargetPos(Scene& scene) noexcept
    {
        if (_target && checkTargetPos(scene))
            _lastKnownTargetPos = _target->transform().position();

        return *this;
    }

    Enemy& Enemy::updateCooldown(float deltaTime) noexcept
    {
        if (_attackCooldown == 0)
            return *this;

        _attackCooldown -= deltaTime;

        if (_attackCooldown < 0)
            _attackCooldown = 0;
        
        return *this;
    }

    Enemy& Enemy::resetCooldown() noexcept
    {
        _attackCooldown = _attackCooldownMax;

        return *this;
    }

    Enemy& Enemy::moveTowardTarget(float deltaTime) noexcept
    {
        if (!_target)
            return *this;

        Vec3 impulseDir { _transform.position(), _lastKnownTargetPos};
        impulseDir.y = 0.0f;
        impulseDir.unit();
        Vec3    impulse = ((impulseDir * ENEMY_SPEED) - _rigidBody->velocity()) * 
                            (ENEMY_ACCELERATION * deltaTime);
        impulse.y = 0;
        _rigidBody->addForce(impulse);

        return *this;
    }

    Enemy& Enemy::attack() noexcept
    {
        if (_target && _attackCooldown == 0)
        {
            _target->takeDamage(_damage);
            resetCooldown();
        }

        return *this;
    }

    float Enemy::distanceToTarget() noexcept
    {
        Vec3 dir { _transform.position(), _lastKnownTargetPos};
        dir.y = 0;
        return dir.length();
    }


    Enemy& Enemy::createStateMachine() noexcept
    {
        using namespace StateMachines;

        DecisionEnemyCanAttack* canAttack = new DecisionEnemyCanAttack(this, false);
        DecisionEnemyCanAttack* cannotAttack = new DecisionEnemyCanAttack(this, true);
        DecisionEnemyReachedTargetPos* reachedPos = new DecisionEnemyReachedTargetPos(this, false);
        DecisionEnemySeeTarget* seeTarget = new DecisionEnemySeeTarget(this, false);

        StateEnemyAttack* attack = new StateEnemyAttack(this);
        StateEnemyChase* chase = new StateEnemyChase(this);
        StateEnemyIdle* idle = new StateEnemyIdle(this);

        Transition* chaseAttack = new Transition(attack);
        Transition* chaseIdle = new Transition(idle);
        Transition* idleChase = new Transition(chase);
        Transition* attackChase = new Transition(chase);

        idleChase->addDecision(seeTarget);
        chaseIdle->addDecision(reachedPos);
        chaseAttack->addDecision(canAttack);
        attackChase->addDecision(cannotAttack);

        idle->addTransition(idleChase);
        chase->addTransition(chaseAttack);
        chase->addTransition(chaseIdle);
        attack->addTransition(attackChase);

        _stateMachine.changeState(idle);

        _stateMachine.addReferences(11, canAttack, cannotAttack, reachedPos, seeTarget, 
            attack, chase, idle, chaseAttack, chaseIdle, idleChase, attackChase);

        return *this;
    }

    GameObject& Enemy::save(std::ofstream& fs, ResourcesManager& resourceManager, std::string folderPath) noexcept
    {
        Entity::save(fs, resourceManager, folderPath);

        return *this;
    }

    #pragma endregion

} // namespace Game
