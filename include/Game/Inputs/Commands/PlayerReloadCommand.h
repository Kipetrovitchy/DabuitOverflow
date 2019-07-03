#ifndef __PLAYER_RELOAD_COMMAND_H__
#define __PLAYER_RELOAD_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerReloadCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerReloadCommand() = default;
            PlayerReloadCommand(StateMachinePlayer* smp);
            PlayerReloadCommand(const PlayerReloadCommand& type);
            virtual ~PlayerReloadCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerReloadCommand& operator=(const PlayerReloadCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_RELOAD_COMMAND_H__