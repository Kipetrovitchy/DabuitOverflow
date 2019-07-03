#include "StateEnemyAttack.h"
#include "Transition.h"
#include "Enemy.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    StateEnemyAttack::StateEnemyAttack():
        StateEnemy()
    {}

    StateEnemyAttack::StateEnemyAttack(const StateEnemyAttack& se):
        StateEnemy(se)
    {
        for (Transition* t : se._transitions)
            if (t)
                _transitions.push_back(t->copy());
    }

    StateEnemyAttack::StateEnemyAttack(Enemy* e) :
        StateEnemy(e)
    {}

    StateEnemyAttack::StateEnemyAttack(Enemy* e, const std::vector<Transition*>& transitions) :
        StateEnemy(e)
    {
        for (Transition* t : transitions)
            if (t)
                _transitions.push_back(t->copy());
    }
    #pragma endregion

    #pragma region Operators
    StateEnemyAttack& StateEnemyAttack::operator=(const StateEnemyAttack& se) noexcept
    {
        _enemy = se._enemy;
        for (Transition* t : se._transitions)
            if (t)
                _transitions.push_back(t->copy());

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    State& StateEnemyAttack::update(Scene& scene, float deltaTime) noexcept
    {
        _enemy->updateCooldown(deltaTime);
        _enemy->updateKnownTargetPos(scene);

        //Hit the target
        _enemy->attack();

        return *this;
    }
    #pragma endregion

    
} // namespace Gme::StateMachine
