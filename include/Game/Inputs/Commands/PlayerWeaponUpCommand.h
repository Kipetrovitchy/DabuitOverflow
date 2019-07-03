#ifndef __PLAYER_WEAPON_UP_COMMAND_H__
#define __PLAYER_WEAPON_UP_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerWeaponUpCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerWeaponUpCommand() = default;
            PlayerWeaponUpCommand(StateMachinePlayer* smp);
            PlayerWeaponUpCommand(const PlayerWeaponUpCommand& type);
            virtual ~PlayerWeaponUpCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerWeaponUpCommand& operator=(const PlayerWeaponUpCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_SHOOT_COMMAND_H__