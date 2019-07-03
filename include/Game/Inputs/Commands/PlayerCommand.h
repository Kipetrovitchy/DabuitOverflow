#ifndef __PLAYER_COMMAND_H__
#define __PLAYER_COMMAND_H__

#include "Command.h"
#include "StateMachinePlayer.h"

namespace Game::Inputs::Commands
{
    typedef Game::StateMachines::StateMachinePlayer StateMachinePlayer;

    class PlayerCommand : public Command
    {   
        protected:
            #pragma region Attributes
            StateMachinePlayer* _smp;
            #pragma endregion

        public:
            #pragma region Constructors
            PlayerCommand();
            PlayerCommand(StateMachinePlayer* smp);
            PlayerCommand(const PlayerCommand& pc);
            virtual ~PlayerCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            PlayerCommand& operator=(const PlayerCommand& pc);
            #pragma endregion
    
            #pragma region Functions
            virtual Command& execute() noexcept = 0;
            #pragma endregion
    };
} // Commands


#endif//__PLAYER_COMMAND_H__