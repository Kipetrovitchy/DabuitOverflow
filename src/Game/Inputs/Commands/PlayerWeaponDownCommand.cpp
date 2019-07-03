#include "PlayerWeaponDownCommand.h"

namespace Game::Inputs::Commands
{
    PlayerWeaponDownCommand::PlayerWeaponDownCommand(StateMachinePlayer* smp):
        PlayerCommand(smp)
    {}

    PlayerWeaponDownCommand::PlayerWeaponDownCommand(const PlayerWeaponDownCommand& pc):
        PlayerCommand(pc)
    {}

    PlayerWeaponDownCommand& PlayerWeaponDownCommand::operator=(const PlayerWeaponDownCommand& pc)
    {
        PlayerCommand::operator=(pc);

        return *this;
    }

    Command& PlayerWeaponDownCommand::execute() noexcept
    {
        if (_smp)
            _smp->changeWeapon(-1);

        return *this;
    }
} // Game::Inputs::Commands