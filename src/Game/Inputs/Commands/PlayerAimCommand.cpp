#include "PlayerAimCommand.h"

namespace Game::Inputs::Commands
{
    PlayerAimCommand::PlayerAimCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerAimCommand::PlayerAimCommand(const PlayerAimCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerAimCommand& PlayerAimCommand::operator=(const PlayerAimCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerAimCommand::execute() noexcept
    {
        if (_smp)
            _smp->aim();

        return *this;
    }
} // Game::Inputs::Commands