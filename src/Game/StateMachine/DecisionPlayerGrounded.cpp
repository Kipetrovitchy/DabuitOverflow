#include "DecisionPlayerGrounded.h"
#include "Player.h"

namespace Game::StateMachines
{
    #pragma region Constructor
    DecisionPlayerGrounded::DecisionPlayerGrounded() : 
        DecisionPlayer()
    {}

    DecisionPlayerGrounded::DecisionPlayerGrounded(const DecisionPlayerGrounded& decisonPlayer) :
        DecisionPlayer(decisonPlayer)
    {}

    DecisionPlayerGrounded::DecisionPlayerGrounded(Player* p, bool negate) :
        DecisionPlayer(p, negate)
    {}
    #pragma endregion

    #pragma region Operators
    DecisionPlayerGrounded& DecisionPlayerGrounded::operator=(const DecisionPlayerGrounded& decisionPlayer)
    {
        DecisionPlayer::operator=(decisionPlayer);
        _player = decisionPlayer._player;
        
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    DecisionPlayerGrounded* DecisionPlayerGrounded::copy() noexcept
    {
        return new DecisionPlayerGrounded(*this);
    }

    bool DecisionPlayerGrounded::isValidated() noexcept
    {
        return (_negate) ? !_player->isGrounded() : _player->isGrounded();
    }
    #pragma endregion
}