#pragma once

#include "common/iobject.h"
#include "move/imovable.h"

class MovableAdapter : public IMovable
{
public:
    MovableAdapter( IObject& iObj ) : uObj_(iObj)
    {
    }

    Point GetPosition() const override
    {
        return boost::any_cast<Point>( uObj_.Get("Position") );
    }

    void SetPosition( const Point& position ) override
    {
        uObj_.Set( "Position", position);
    }

    Point GetVelocity() const override
    {
        return boost::any_cast<Point>( uObj_.Get("Velocity") );
    }

private:
    IObject& uObj_;
};
