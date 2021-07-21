#include <macro_command/common/macro_command.h>
#include <macro_command/common/command_error.h>

void MacroCommand::Execute()
{
    try
    {
        for ( auto& c : commands_ )
        {
            c->Execute();
        }
    }
    catch ( std::exception& )
    {
        throw CommandError();
    }
}
