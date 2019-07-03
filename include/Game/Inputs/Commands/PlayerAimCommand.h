#ifndef __PLAYER_AIM_COMMAND_H__
#define __PLAYER_AIM_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerAimCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerAimCommand() = default;
            PlayerAimCommand(StateMachinePlayer* smp);
            PlayerAimCommand(const PlayerAimCommand& type);
            virtual ~PlayerAimCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerAimCommand& operator=(const PlayerAimCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_AIM_COMMAND_H__