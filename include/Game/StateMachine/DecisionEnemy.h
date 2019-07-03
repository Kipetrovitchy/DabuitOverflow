#ifndef __DECISION_ENEMY_H__
#define __DECISION_ENEMY_H__

#include "Decision.h"

namespace Game 
{
    class Enemy;
}
namespace Game::StateMachines
{    
    class DecisionEnemy : public Decision
    {
        protected:
            #pragma region Attributes
            Enemy* _enemy;
            #pragma endregion
    
        public:
            #pragma region Constructors
            DecisionEnemy();
            DecisionEnemy(const DecisionEnemy& de);
            DecisionEnemy(Enemy* e, bool negate);
            virtual ~DecisionEnemy() = default;
            #pragma endregion
    
            #pragma region Operators
            DecisionEnemy& operator=(const DecisionEnemy& de);
            #pragma endregion
    
            #pragma region Functions
            DecisionEnemy&          init(IController* c) noexcept override final;
            virtual DecisionEnemy*  copy() noexcept = 0;
            virtual bool            isValidated() noexcept = 0;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__DECISION_ENEMY_H__