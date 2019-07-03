#include "Decision.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    Decision::Decision() :
        _negate {false} 
    {}

    Decision::Decision(const Decision& d) :
        _negate {d._negate}
    {}

    Decision::Decision(const bool& negate) :
        _negate {negate}
    {}
    #pragma endregion
    
    #pragma region Operators
    Decision& Decision::operator=(const Decision& d) 
    {
        _negate = d._negate;

        return *this;
    }
    #pragma endregion
} // namespace Game::StateMachine
