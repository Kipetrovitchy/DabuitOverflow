#include "DecisionEnemyCanAttack.h"
#include "Enemy.h"

namespace Game::StateMachines
{
    #pragma region Constructor
    DecisionEnemyCanAttack::DecisionEnemyCanAttack() : 
        DecisionEnemy()
    {}

    DecisionEnemyCanAttack::DecisionEnemyCanAttack(const DecisionEnemyCanAttack& de) :
        DecisionEnemy(de)
    {}

    DecisionEnemyCanAttack::DecisionEnemyCanAttack(Enemy* e, bool negate) :
        DecisionEnemy(e, negate)
    {}
    #pragma endregion

    #pragma region Operators
    DecisionEnemyCanAttack& DecisionEnemyCanAttack::operator=(const DecisionEnemyCanAttack& de)
    {
        DecisionEnemy::operator=(de);
        _enemy = de._enemy;
        
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    DecisionEnemyCanAttack* DecisionEnemyCanAttack::copy() noexcept
    {
        return new DecisionEnemyCanAttack(*this);
    }

    bool DecisionEnemyCanAttack::isValidated() noexcept
    {
        return (_negate) ? !_enemy->CanHitTarget() : _enemy->CanHitTarget();
    }
    #pragma endregion
}