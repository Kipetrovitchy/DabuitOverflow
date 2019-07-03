#include "PlayerShootCommand.h"

namespace Game::Inputs::Commands
{
    PlayerShootCommand::PlayerShootCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerShootCommand::PlayerShootCommand(const PlayerShootCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerShootCommand& PlayerShootCommand::operator=(const PlayerShootCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerShootCommand::execute() noexcept
    {
        if (_smp)
            _smp->shoot();

        return *this;
    }
} // Game::Inputs::Commands