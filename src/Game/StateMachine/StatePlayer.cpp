#include "StatePlayer.h"
#include "Transition.h"
#include "Player.h"

namespace Game::StateMachines
{
    #pragma region Constructors
    StatePlayer::StatePlayer():
        _player {nullptr}
    {}

    StatePlayer::StatePlayer(const StatePlayer& sp):
        _player {sp._player}
    {
        for (Transition* t : sp._transitions)
            if (t)
                _transitions.push_back(t->copy());
    }

    StatePlayer::StatePlayer(Player* p) :
        _player {p}
    {}

    StatePlayer::StatePlayer(Player* p, const std::vector<Transition*>& transitions) :
        _player {p}
    {
        for (Transition* t : transitions)
            if (t)
                _transitions.push_back(t->copy());
    }
    #pragma endregion

    #pragma region Operators
    StatePlayer& StatePlayer::operator=(const StatePlayer& sp) noexcept
    {
        _player = sp._player;
        for (Transition* t : sp._transitions)
            if (t)
                _transitions.push_back(t->copy());

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    State& StatePlayer::init(IController* c) noexcept
    {
        if (c)
        {
            _player = dynamic_cast<Player*>(c);
            for (Transition* t : _transitions)
            {
                if (t)
                t->init(c);
            }
        }
        return *this;
    }
    #pragma endregion

    
} // namespace Gme::StateMachine
