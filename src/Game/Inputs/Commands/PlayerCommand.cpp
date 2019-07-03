#include "PlayerCommand.h"

namespace Game::Inputs::Commands
{
    PlayerCommand::PlayerCommand():
        _smp { nullptr }
    {} 

    PlayerCommand::PlayerCommand(StateMachinePlayer* smp):
        _smp { smp }
    {}

    PlayerCommand::PlayerCommand(const PlayerCommand& pc):
        _smp { pc._smp }
    {
        _enabled = pc._enabled;
    }

    PlayerCommand& PlayerCommand::operator=(const PlayerCommand& pc)
    {
        _enabled = pc._enabled;
        _smp = pc._smp;

        return *this;
    }
} // Game::Inputs::Commands
