#ifndef __PLAYER_BACKWARD_COMMAND_H__
#define __PLAYER_BACKWARD_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerBackwardCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerBackwardCommand() = default;
            PlayerBackwardCommand(StateMachinePlayer* smp);
            PlayerBackwardCommand(const PlayerBackwardCommand& type);
            virtual ~PlayerBackwardCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerBackwardCommand& operator=(const PlayerBackwardCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_BACKWARD_COMMAND_H__