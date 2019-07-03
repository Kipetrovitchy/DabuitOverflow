#include "Transition.h"
#include "Decision.h"
#include "State.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    Transition::Transition(State* s) :
        _state {s}
    {}

    Transition::Transition(State* s, const std::vector<Decision*>& decisions) :
        _state {s}
    {
        for (Decision* d : decisions)
            if (d)
                _decisons.push_back(d->copy());
    }

    Transition::Transition(const Transition& t) :
        _state {t._state}
    {
        for (Decision* d : t._decisons)
            if (d)
                _decisons.push_back(d->copy());
    }
    #pragma endregion
    
    #pragma region Operators
    Transition& Transition::operator=(const Transition& t) noexcept
    {
        _state = t._state;
        for (Decision* d : t._decisons)
            if (d)
                _decisons.push_back(d->copy());
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    Transition* Transition::copy() noexcept
    {
        return new Transition(*this);
    }

    //If all decision are true then the transition happens
    bool Transition::transition() noexcept
    {
        for (Decision* d : _decisons)
            if (d && !d->isValidated())
                return false;
        return true;
    }

    Transition& Transition::init(IController* c) noexcept
    {
        if (c)
        {
            for (Decision* d : _decisons)
            {
                if (d)
                d->init(c);
            }
        }
        return *this;
    }

    Transition& Transition::addDecision(Decision* d) noexcept
    {
        _decisons.push_back(d);

        return *this;
    }
    #pragma endregion

} // namespace Game::StateMachine
