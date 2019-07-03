#ifndef __PLAYER_RIGHT_COMMAND_H__
#define __PLAYER_RIGHT_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerRightCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerRightCommand() = default;
            PlayerRightCommand(StateMachinePlayer* smp);
            PlayerRightCommand(const PlayerRightCommand& type);
            virtual ~PlayerRightCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerRightCommand& operator=(const PlayerRightCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_RIGHT_COMMAND_H__