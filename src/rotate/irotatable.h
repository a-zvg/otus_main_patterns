#pragma once

class IRotatable
{
public:
    virtual ~IRotatable() = default;

    virtual int GetDirection() const = 0;
    virtual void SetDirection( int direction ) = 0;
    virtual int GetAngularVelocity() const = 0;
    virtual int GetMaxDirections() const = 0;
};
