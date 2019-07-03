#ifndef __DECISION_ENEMY_CAN_ATTACK_H__
#define __DECISION_ENEMY_CAN_ATTACK_H__

#include "DecisionEnemy.h"

namespace Game::StateMachines
{    
    class DecisionEnemyCanAttack : public DecisionEnemy
    {
        public:
            #pragma region Constructors
            DecisionEnemyCanAttack();
            DecisionEnemyCanAttack(const DecisionEnemyCanAttack& de);
            DecisionEnemyCanAttack(::Game::Enemy* p, bool negate);
            virtual ~DecisionEnemyCanAttack() = default;
            #pragma endregion
    
            #pragma region Operators
            DecisionEnemyCanAttack& operator=(const DecisionEnemyCanAttack& de);
            #pragma endregion
    
            #pragma region Functions
            DecisionEnemyCanAttack* copy() noexcept override;
            bool                    isValidated() noexcept override;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__DECISION_ENEMY_CAN_ATTACK_H__