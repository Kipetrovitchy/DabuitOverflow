#ifndef __DECISION_ENEMY_REACHED_TARGET_POS_H__
#define __DECISION_ENEMY_REACHED_TARGET_POS_H__

#include "DecisionEnemy.h"

namespace Game::StateMachines
{    
    class DecisionEnemyReachedTargetPos : public DecisionEnemy
    {
        public:
            #pragma region Constructors
            DecisionEnemyReachedTargetPos();
            DecisionEnemyReachedTargetPos(const DecisionEnemyReachedTargetPos& de);
            DecisionEnemyReachedTargetPos(::Game::Enemy* p, bool negate);
            virtual ~DecisionEnemyReachedTargetPos() = default;
            #pragma endregion
    
            #pragma region Operators
            DecisionEnemyReachedTargetPos& operator=(const DecisionEnemyReachedTargetPos& de);
            #pragma endregion
    
            #pragma region Functions
            DecisionEnemyReachedTargetPos* copy() noexcept override;
            bool                    isValidated() noexcept override;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__DECISION_ENEMY_REACHED_TARGET_POS_H__