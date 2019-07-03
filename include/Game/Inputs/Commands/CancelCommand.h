#ifndef __CANCELCOMMAND_H__
#define __CANCELCOMMAND_H__

#include "InputModuleCommand.h"


namespace Game::Inputs::Commands
{
    class CancelCommand : public InputModuleCommand
    {    
        public:
            #pragma region Constructors
            CancelCommand() = default;
            CancelCommand(InputModule* module);
            CancelCommand(const CancelCommand& sc);
            virtual ~CancelCommand() = default;
            #pragma endregion
    
            #pragma region Operators
            CancelCommand& operator=(const CancelCommand& sc);
            #pragma endregion
    
            #pragma region Functions
            Command& execute() noexcept override;
            #pragma endregion
    };
} // Game::Commands


#endif//__CANCELCOMMAND_H__