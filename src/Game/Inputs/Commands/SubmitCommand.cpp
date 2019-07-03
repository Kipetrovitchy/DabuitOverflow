#include "SubmitCommand.h"

namespace Game::Inputs::Commands
{
    SubmitCommand::SubmitCommand(InputModule* module):
        InputModuleCommand(module)
    {}

    SubmitCommand::SubmitCommand(const SubmitCommand& sc):
        InputModuleCommand(sc)
    {}

    SubmitCommand& SubmitCommand::operator=(const SubmitCommand& sc)
    {
        InputModuleCommand::operator=(sc);

        return *this;
    }

    Command& SubmitCommand::execute() noexcept
    {
        if (_module)
            _module->submit() = true;

        return *this;
    }
} // Game::Inputs::Commands