#ifndef __PLAYER_DECISION_H__
#define __PLAYER_DECISION_H__

#include "Decision.h"

namespace Game 
{
    class Player;
}
namespace Game::StateMachines
{    
    class DecisionPlayer : public Decision
    {
        protected:
            #pragma region Attributes
            Player* _player;
            #pragma endregion
    
        public:
            #pragma region Constructors
            DecisionPlayer();
            DecisionPlayer(const DecisionPlayer& decisonPlayer);
            DecisionPlayer(Player* p, bool negate);
            virtual ~DecisionPlayer() = default;
            #pragma endregion
    
            #pragma region Operators
            DecisionPlayer& operator=(const DecisionPlayer& pdg);
            #pragma endregion
    
            #pragma region Functions
            DecisionPlayer&     init(IController* c) noexcept override final;
            virtual DecisionPlayer* copy() noexcept = 0;
            virtual bool            isValidated() noexcept = 0;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__PLAYER_DECISION_H__