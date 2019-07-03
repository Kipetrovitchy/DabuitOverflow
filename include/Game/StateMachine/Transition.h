#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include <vector>
#include "StateMachineObject.h"
#include "Decision.h"

namespace Game::StateMachines
{
    class State;
    class Transition : public StateMachineObject
    {
        private:
            #pragma region Attributes
            State*  _state;
            std::vector<Decision*>   _decisons;
            #pragma endregion
    
        public:
            #pragma region Constructors
            Transition() = default;
            Transition(const Transition& t);
            Transition(State* s);
            Transition(State* s, const std::vector<Decision*>& decisions);
            ~Transition() = default;
            #pragma endregion
    
            #pragma region Operators
            Transition& operator=(const Transition& t) noexcept;
            #pragma endregion
    
            #pragma region Functions
            Transition* copy() noexcept;
            bool  transition() noexcept;
            Transition& init(IController*) noexcept;
            Transition& addDecision(Decision* d) noexcept;
            #pragma endregion

            #pragma region Accessors
            inline State* state() { return _state; };
            #pragma endregion
    };
} // namespace Game::StateMachine


#endif //__TRANSITION_H__