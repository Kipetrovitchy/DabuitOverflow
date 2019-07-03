#include "StateEnemy.h"
#include "Transition.h"
#include "Enemy.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    StateEnemy::StateEnemy():
        _enemy {nullptr}
    {}

    StateEnemy::StateEnemy(const StateEnemy& se):
        _enemy {se._enemy}
    {
        for (Transition* t : se._transitions)
            if (t)
                _transitions.push_back(t->copy());
    }

    StateEnemy::StateEnemy(Enemy* e) :
        _enemy {e}
    {}

    StateEnemy::StateEnemy(Enemy* e, const std::vector<Transition*>& transitions) :
        _enemy {e}
    {
        for (Transition* t : transitions)
            if (t)
                _transitions.push_back(t->copy());
    }
    #pragma endregion

    #pragma region Operators
    StateEnemy& StateEnemy::operator=(const StateEnemy& se) noexcept
    {
        _enemy = se._enemy;
        for (Transition* t : se._transitions)
            if (t)
                _transitions.push_back(t->copy());

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    State& StateEnemy::init(IController* c) noexcept
    {
        if (c)
        {
            _enemy = dynamic_cast<Enemy*>(c);
            for (Transition* t : _transitions)
            {
                if (t)
                t->init(c);
            }
        }
        return *this;
    }
    #pragma endregion

    
} // namespace Gme::StateMachine
