#include "PlayerForwardCommand.h"

namespace Game::Inputs::Commands
{
    PlayerForwardCommand::PlayerForwardCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerForwardCommand::PlayerForwardCommand(const PlayerForwardCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerForwardCommand& PlayerForwardCommand::operator=(const PlayerForwardCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerForwardCommand::execute() noexcept
    {
        if (_smp)
            _smp->moveForward();

        return *this;
    }
} // Game::Inputs::Commands