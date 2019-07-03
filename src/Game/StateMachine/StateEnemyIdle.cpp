#include "StateEnemyIdle.h"
#include "Transition.h"
#include "Enemy.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    StateEnemyIdle::StateEnemyIdle():
        StateEnemy()
    {}

    StateEnemyIdle::StateEnemyIdle(const StateEnemyIdle& se):
        StateEnemy(se)
    {
        for (Transition* t : se._transitions)
            if (t)
                _transitions.push_back(t->copy());
    }

    StateEnemyIdle::StateEnemyIdle(Enemy* e) :
        StateEnemy(e)
    {}

    StateEnemyIdle::StateEnemyIdle(Enemy* e, const std::vector<Transition*>& transitions) :
        StateEnemy(e)
    {
        for (Transition* t : transitions)
            if (t)
                _transitions.push_back(t->copy());
    }
    #pragma endregion

    #pragma region Operators
    StateEnemyIdle& StateEnemyIdle::operator=(const StateEnemyIdle& se) noexcept
    {
        _enemy = se._enemy;
        for (Transition* t : se._transitions)
            if (t)
                _transitions.push_back(t->copy());

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    State& StateEnemyIdle::update(Scene& scene, float deltaTime) noexcept
    {        
        _enemy->updateCooldown(deltaTime);
        _enemy->updateKnownTargetPos(scene);
        
        return *this;
    }
    #pragma endregion

    
} // namespace Gme::StateMachine
