#include "PlayerJumpCommand.h"

namespace Game::Inputs::Commands
{
    PlayerJumpCommand::PlayerJumpCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerJumpCommand::PlayerJumpCommand(const PlayerJumpCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerJumpCommand& PlayerJumpCommand::operator=(const PlayerJumpCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerJumpCommand::execute() noexcept
    {
        if (_smp)
            _smp->jump();

        return *this;
    }
} // Game::Inputs::Commands