#ifndef __INPUTMODULE_COMMAND_H__
#define __INPUTMODULE_COMMAND_H__

#include "Command.h"
#include "InputModule.h"

namespace Game::Inputs::Commands
{

    class InputModuleCommand : public Command
    {   
        protected:
            #pragma region Attributes
            InputModule* _module;
            #pragma endregion

        public:
            #pragma region Constructors
            InputModuleCommand();
            InputModuleCommand(InputModule* _module);
            InputModuleCommand(const InputModuleCommand& imc);
            virtual ~InputModuleCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            InputModuleCommand& operator=(const InputModuleCommand& imc);
            #pragma endregion
    
            #pragma region Functions
            virtual Command& execute() noexcept = 0;
            #pragma endregion
    };
} // Commands


#endif//__INPUTMODULE_COMMAND_H__