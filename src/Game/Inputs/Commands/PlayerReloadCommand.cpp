#include "PlayerReloadCommand.h"

namespace Game::Inputs::Commands
{
    PlayerReloadCommand::PlayerReloadCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerReloadCommand::PlayerReloadCommand(const PlayerReloadCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerReloadCommand& PlayerReloadCommand::operator=(const PlayerReloadCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerReloadCommand::execute() noexcept
    {
        if (_smp)
            _smp->reload();

        return *this;
    }
} // Game::Inputs::Commands