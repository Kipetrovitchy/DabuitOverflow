#include "DecisionPlayer.h"
#include "Player.h"

namespace Game::StateMachines
{
    #pragma region Constructor
    DecisionPlayer::DecisionPlayer() :
        Decision(), 
        _player {nullptr}
    {}

    DecisionPlayer::DecisionPlayer(const DecisionPlayer& decisonPlayer) :
        Decision(decisonPlayer),
        _player {decisonPlayer._player}
    {}
    

    DecisionPlayer::DecisionPlayer(Player* p, bool negate) :
        Decision(negate),
        _player {p}
    {}
    #pragma endregion

    #pragma region OperatorsOperators
    DecisionPlayer& DecisionPlayer::operator=(const DecisionPlayer& decisionPlayer)
    {
        Decision::operator=(decisionPlayer);
        _player = decisionPlayer._player;
        return *this;
    }
    #pragma endregion

    #pragma region Functions
    DecisionPlayer& DecisionPlayer::init(IController* c) noexcept
    {
        _player = dynamic_cast<Player*>(c);

        return *this;
    }
    #pragma endregion
}