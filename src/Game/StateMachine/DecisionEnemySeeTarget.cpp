#include "DecisionEnemySeeTarget.h"
#include "Enemy.h"

namespace Game::StateMachines
{
    #pragma region Constructor
    DecisionEnemySeeTarget::DecisionEnemySeeTarget() : 
        DecisionEnemy()
    {}

    DecisionEnemySeeTarget::DecisionEnemySeeTarget(const DecisionEnemySeeTarget& de) :
        DecisionEnemy(de)
    {}

    DecisionEnemySeeTarget::DecisionEnemySeeTarget(Enemy* e, bool negate) :
        DecisionEnemy(e, negate)
    {}
    #pragma endregion

    #pragma region Operators
    DecisionEnemySeeTarget& DecisionEnemySeeTarget::operator=(const DecisionEnemySeeTarget& de)
    {
        DecisionEnemy::operator=(de);
        _enemy = de._enemy;
        
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    DecisionEnemySeeTarget* DecisionEnemySeeTarget::copy() noexcept
    {
        return new DecisionEnemySeeTarget(*this);
    }

    bool DecisionEnemySeeTarget::isValidated() noexcept
    {
        return (_negate) ? !_enemy->CanSeeTarget() : _enemy->CanSeeTarget();
    }
    #pragma endregion
}