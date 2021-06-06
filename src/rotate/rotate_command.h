#pragma once

#include "common/icommand.h"
#include "rotate/irotatable.h"
#include "rotate/rotate_error.h"

class RotateCommand : public ICommand
{
public:
    RotateCommand( IRotatable& rotatable ) : rotatable_(rotatable)
    {
    }

    void execute() override
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

private:
    IRotatable& rotatable_;
};
