#ifndef __PLAYER_WEAPON_DOWN_COMMAND_H__
#define __PLAYER_WEAPON_DOWN_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerWeaponDownCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerWeaponDownCommand() = default;
            PlayerWeaponDownCommand(StateMachinePlayer* smp);
            PlayerWeaponDownCommand(const PlayerWeaponDownCommand& type);
            virtual ~PlayerWeaponDownCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerWeaponDownCommand& operator=(const PlayerWeaponDownCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_SHOOT_COMMAND_H__