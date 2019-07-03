#ifndef __PLAYER_JUMP_COMMAND_H__
#define __PLAYER_JUMP_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerJumpCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerJumpCommand() = default;
            PlayerJumpCommand(StateMachinePlayer* smp);
            PlayerJumpCommand(const PlayerJumpCommand& type);
            virtual ~PlayerJumpCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerJumpCommand& operator=(const PlayerJumpCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_JUMP_COMMAND_H__