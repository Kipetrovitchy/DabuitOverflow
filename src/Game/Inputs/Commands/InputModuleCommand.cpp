#include "InputModuleCommand.h"

namespace Game::Inputs::Commands
{
    InputModuleCommand::InputModuleCommand():
        _module { nullptr }
    {} 

    InputModuleCommand::InputModuleCommand(InputModule* module):
        _module { module }
    {}

    InputModuleCommand::InputModuleCommand(const InputModuleCommand& imc):
        _module { imc._module }
    {
        _enabled = imc._enabled;
    }

    InputModuleCommand& InputModuleCommand::operator=(const InputModuleCommand& imc)
    {
        _enabled = imc._enabled;
        _module = imc._module;

        return *this;
    }
} // Game::Inputs::Commands
