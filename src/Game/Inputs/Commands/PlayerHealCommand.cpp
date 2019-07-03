#include "PlayerHealCommand.h"

namespace Game::Inputs::Commands
{
    PlayerHealCommand::PlayerHealCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerHealCommand::PlayerHealCommand(const PlayerHealCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerHealCommand& PlayerHealCommand::operator=(const PlayerHealCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerHealCommand::execute() noexcept
    {
        if (_smp)
            _smp->heal();

        return *this;
    }
} // Game::Inputs::Commands