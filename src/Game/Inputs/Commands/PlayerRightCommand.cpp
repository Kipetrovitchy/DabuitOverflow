#include "PlayerRightCommand.h"

namespace Game::Inputs::Commands
{
    PlayerRightCommand::PlayerRightCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerRightCommand::PlayerRightCommand(const PlayerRightCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerRightCommand& PlayerRightCommand::operator=(const PlayerRightCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerRightCommand::execute() noexcept
    {
        if (_smp)
            _smp->moveRight();

        return *this;
    }
} // Game::Inputs::Commands