#include "rotate/rotate_command.h"

void RotateCommand::Execute()
{
    try
    {
        auto direction = rotatable_.GetDirection();
        auto angVel = rotatable_.GetAngularVelocity();
        auto maxDirections = rotatable_.GetMaxDirections();

        int newDirection = direction + angVel;
        rotatable_.SetDirection( newDirection < 0 ? newDirection + maxDirections : newDirection % maxDirections );
    }
    catch ( std::exception& )
    {
        throw RotateError();
    }
}
