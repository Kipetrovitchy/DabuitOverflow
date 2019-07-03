#ifndef __PLAYER_LEFT_COMMAND_H__
#define __PLAYER_LEFT_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerLeftCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerLeftCommand() = default;
            PlayerLeftCommand(StateMachinePlayer* smp);
            PlayerLeftCommand(const PlayerLeftCommand& type);
            virtual ~PlayerLeftCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerLeftCommand& operator=(const PlayerLeftCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_LEFT_COMMAND_H__