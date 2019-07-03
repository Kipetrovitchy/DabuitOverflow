#include "StateEnemyChase.h"
#include "Transition.h"
#include "Enemy.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    StateEnemyChase::StateEnemyChase():
        StateEnemy()
    {}

    StateEnemyChase::StateEnemyChase(const StateEnemyChase& se):
        StateEnemy(se)
    {
        for (Transition* t : se._transitions)
            if (t)
                _transitions.push_back(t->copy());
    }

    StateEnemyChase::StateEnemyChase(Enemy* e) :
        StateEnemy(e)
    {}

    StateEnemyChase::StateEnemyChase(Enemy* e, const std::vector<Transition*>& transitions) :
        StateEnemy(e)
    {
        for (Transition* t : transitions)
            if (t)
                _transitions.push_back(t->copy());
    }
    #pragma endregion

    #pragma region Operators
    StateEnemyChase& StateEnemyChase::operator=(const StateEnemyChase& se) noexcept
    {
        _enemy = se._enemy;
        for (Transition* t : se._transitions)
            if (t)
                _transitions.push_back(t->copy());

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    State& StateEnemyChase::update(Scene& scene, float deltaTime) noexcept
    {
        _enemy->updateCooldown(deltaTime);

        //Follow the target or move to its last known position
        _enemy->updateKnownTargetPos(scene);
        if (_enemy->lastKownTargetPos() != Vec3::infinity)
            _enemy->moveTowardTarget(deltaTime);

        return *this;
    }
    #pragma endregion

    
} // namespace Gme::StateMachine
