#ifndef __PLAYER_HEAL_COMMAND_H__
#define __PLAYER_HEAL_COMMAND_H__

#include "PlayerCommand.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerHealCommand : public PlayerCommand
    {    
        public:
            #pragma region Constructors
            PlayerHealCommand() = default;
            PlayerHealCommand(StateMachinePlayer* smp);
            PlayerHealCommand(const PlayerHealCommand& type);
            virtual ~PlayerHealCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerHealCommand& operator=(const PlayerHealCommand& type);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__PLAYER_HEAL_COMMAND_H__