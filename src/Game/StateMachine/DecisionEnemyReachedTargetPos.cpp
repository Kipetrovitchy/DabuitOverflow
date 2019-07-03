#include "DecisionEnemyReachedTargetPos.h"
#include "Enemy.h"
#include <limits>

namespace Game::StateMachines
{
    #pragma region Constructor
    DecisionEnemyReachedTargetPos::DecisionEnemyReachedTargetPos() : 
        DecisionEnemy()
    {}

    DecisionEnemyReachedTargetPos::DecisionEnemyReachedTargetPos(const DecisionEnemyReachedTargetPos& de) :
        DecisionEnemy(de)
    {}

    DecisionEnemyReachedTargetPos::DecisionEnemyReachedTargetPos(Enemy* e, bool negate) :
        DecisionEnemy(e, negate)
    {}
    #pragma endregion

    #pragma region Operators
    DecisionEnemyReachedTargetPos& DecisionEnemyReachedTargetPos::operator=(const DecisionEnemyReachedTargetPos& de)
    {
        DecisionEnemy::operator=(de);
        _enemy = de._enemy;
        
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    DecisionEnemyReachedTargetPos* DecisionEnemyReachedTargetPos::copy() noexcept
    {
        return new DecisionEnemyReachedTargetPos(*this);
    }

    bool DecisionEnemyReachedTargetPos::isValidated() noexcept
    {
        return (_negate) ? 
            (_enemy->distanceToTarget() > 0.1) : 
            (_enemy->distanceToTarget() <= 0.1);
    }
    #pragma endregion
}