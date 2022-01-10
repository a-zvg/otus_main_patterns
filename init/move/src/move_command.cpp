#include "move/move_command.h"

void MoveCommand::Execute()
{
    try
    {
        movable_->SetPosition( movable_->GetPosition() + movable_->GetVelocity() );
    }
    catch ( std::exception& )
    {
        throw CommandError();
    }
}
