#ifndef __PLAYER_SHOOT_COMMAND_H__
#define __PLAYER_SHOOT_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerShootCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerShootCommand() = default;
            PlayerShootCommand(StateMachinePlayer* smp);
            PlayerShootCommand(const PlayerShootCommand& type);
            virtual ~PlayerShootCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerShootCommand& operator=(const PlayerShootCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_SHOOT_COMMAND_H__