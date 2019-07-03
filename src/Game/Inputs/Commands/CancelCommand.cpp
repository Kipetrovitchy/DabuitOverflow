#include "CancelCommand.h"

namespace Game::Inputs::Commands
{
    CancelCommand::CancelCommand(InputModule* module):
        InputModuleCommand(module)
    {}

    CancelCommand::CancelCommand(const CancelCommand& sc):
        InputModuleCommand(sc)
    {}

    CancelCommand& CancelCommand::operator=(const CancelCommand& sc)
    {
        InputModuleCommand::operator=(sc);

        return *this;
    }

    Command& CancelCommand::execute() noexcept
    {
        if (_module)
            _module->cancel() = true;
        return *this;
    }
} // Game::Inputs::Commands