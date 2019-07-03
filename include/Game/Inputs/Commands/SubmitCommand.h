#ifndef __SUBMITCOMMAND_H__
#define __SUBMITCOMMAND_H__

#include "InputModuleCommand.h"


namespace Game::Inputs::Commands
{
    class SubmitCommand : public InputModuleCommand
    {    
        public:
            #pragma region Constructors
            SubmitCommand() = default;
            SubmitCommand(InputModule* module);
            SubmitCommand(const SubmitCommand& sc);
            virtual ~SubmitCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            SubmitCommand& operator=(const SubmitCommand& sc);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__SUBMITCOMMAND_H__