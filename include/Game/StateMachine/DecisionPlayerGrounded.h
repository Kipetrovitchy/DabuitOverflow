#ifndef __DECISION_PLAYER_GROUNDED_H__
#define __DECISION_PLAYER_GROUNDED_H__

#include "DecisionPlayer.h"

namespace Game::StateMachines
{    
    class DecisionPlayerGrounded : public DecisionPlayer
    {
        public:
            #pragma region Constructors
            DecisionPlayerGrounded();
            DecisionPlayerGrounded(const DecisionPlayerGrounded& decisonPlayer);
            DecisionPlayerGrounded(::Game::Player* p, bool negate);
            virtual ~DecisionPlayerGrounded() = default;
            #pragma endregion
    
            #pragma region Operators
            DecisionPlayerGrounded& operator=(const DecisionPlayerGrounded& pdg);
            #pragma endregion
    
            #pragma region Functions
            DecisionPlayerGrounded* copy() noexcept override;
            bool                    isValidated() noexcept override;
            #pragma endregion
    };

} // namespace Game::StateMachine


#endif //__PLAYER_DECISION_GROUNDED_H__