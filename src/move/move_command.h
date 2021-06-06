#pragma once

#include "common/icommand.h"
#include "move/imovable.h"
#include "move/move_error.h"

class MoveCommand : public ICommand
{
public:
    MoveCommand( IMovable& movable ) : movable_(movable)
    {
    }

    void execute() override
    {
        try
        {
            movable_.SetPosition( movable_.GetPosition() + movable_.GetVelocity() );
        }
        catch ( std::exception& )
        {
            throw MoveError();
        }
    }

private:
    IMovable& movable_;
};
