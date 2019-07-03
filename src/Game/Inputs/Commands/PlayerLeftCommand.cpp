#include "PlayerLeftCommand.h"

namespace Game::Inputs::Commands
{
    PlayerLeftCommand::PlayerLeftCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerLeftCommand::PlayerLeftCommand(const PlayerLeftCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerLeftCommand& PlayerLeftCommand::operator=(const PlayerLeftCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerLeftCommand::execute() noexcept
    {
        if (_smp)
            _smp->moveLeft();

        return *this;
    }
} // Game::Inputs::Commands