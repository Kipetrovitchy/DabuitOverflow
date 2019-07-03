#include "PlayerBackwardCommand.h"

namespace Game::Inputs::Commands
{
    PlayerBackwardCommand::PlayerBackwardCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerBackwardCommand::PlayerBackwardCommand(const PlayerBackwardCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerBackwardCommand& PlayerBackwardCommand::operator=(const PlayerBackwardCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerBackwardCommand::execute() noexcept
    {
        if (_smp)
            _smp->moveBackward();

        return *this;
    }
} // Game::Inputs::Commands