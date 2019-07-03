#ifndef __DECISION_ENEMY_SEE_TARGET_H__
#define __DECISION_ENEMY_SEE_TARGET_H__

#include "DecisionEnemy.h"

namespace Game::StateMachines
{    
    class DecisionEnemySeeTarget : public DecisionEnemy
    {
        public:
            #pragma region Constructors
            DecisionEnemySeeTarget();
            DecisionEnemySeeTarget(const DecisionEnemySeeTarget& de);
            DecisionEnemySeeTarget(::Game::Enemy* p, bool negate);
            virtual ~DecisionEnemySeeTarget() = default;
            #pragma endregion
    
            #pragma region Operators
            DecisionEnemySeeTarget& operator=(const DecisionEnemySeeTarget& de);
            #pragma endregion
    
            #pragma region Functions
            DecisionEnemySeeTarget* copy() noexcept override;
            bool                    isValidated() noexcept override;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__DECISION_ENEMY_SEE_TARGET_H__