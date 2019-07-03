#include "DecisionEnemy.h"
#include "Enemy.h"

namespace Game::StateMachines
{
    #pragma region Constructor
    DecisionEnemy::DecisionEnemy() :
        Decision(), 
        _enemy {nullptr}
    {}

    DecisionEnemy::DecisionEnemy(const DecisionEnemy& decisonPlayer) :
        Decision(decisonPlayer),
        _enemy {decisonPlayer._enemy}
    {}
    

    DecisionEnemy::DecisionEnemy(Enemy* e, bool negate) :
        Decision(negate),
        _enemy {e}
    {}
    #pragma endregion

    #pragma region OperatorsOperators
    DecisionEnemy& DecisionEnemy::operator=(const DecisionEnemy& decisionEnemy)
    {
        Decision::operator=(decisionEnemy);
        _enemy = decisionEnemy._enemy;
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    DecisionEnemy& DecisionEnemy::init(IController* c) noexcept
    {
        _enemy = dynamic_cast<Enemy*>(c);

        return *this;
    }
    #pragma endregion
}