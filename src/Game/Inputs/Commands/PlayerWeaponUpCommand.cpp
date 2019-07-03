#include "PlayerWeaponUpCommand.h"

namespace Game::Inputs::Commands
{
    PlayerWeaponUpCommand::PlayerWeaponUpCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerWeaponUpCommand::PlayerWeaponUpCommand(const PlayerWeaponUpCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerWeaponUpCommand& PlayerWeaponUpCommand::operator=(const PlayerWeaponUpCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerWeaponUpCommand::execute() noexcept
    {
        if (_smp)
            _smp->changeWeapon(1);

        return *this;
    }
} // Game::Inputs::Commands