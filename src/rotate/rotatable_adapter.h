#pragma once

#include "common/iobject.h"
#include "rotate/irotatable.h"

class RotatableAdapter : public IRotatable
{
public:
    RotatableAdapter( IObject& iObj ) : uObj_(iObj)
    {
    }

    int GetDirection() const override
    {
        return boost::any_cast<int>( uObj_.Get("Direction") );
    }

    void SetDirection( int direction ) override
    {
        uObj_.Set("Direction", direction);
    }

    int GetAngularVelocity() const override
    {
        return boost::any_cast<int>( uObj_.Get("AngularVelocity") );
    }

    int GetMaxDirections() const override
    {
        return boost::any_cast<int>( uObj_.Get("MaxDirections") );
    }

private:
    IObject& uObj_;
};
