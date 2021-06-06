#pragma once

#include "move/point.h"

class IMovable
{
public:
    virtual ~IMovable() = default;

    virtual Point GetPosition() const = 0;
    virtual void SetPosition( const Point& position ) = 0;
    virtual Point GetVelocity() const = 0;
};
