#ifndef __PLAYER_FORWARD_COMMAND_H__
#define __PLAYER_FORWARD_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerForwardCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerForwardCommand() = default;
            PlayerForwardCommand(StateMachinePlayer* smp);
            PlayerForwardCommand(const PlayerForwardCommand& type);
            virtual ~PlayerForwardCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerForwardCommand& operator=(const PlayerForwardCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_FORWARD_COMMAND_H__