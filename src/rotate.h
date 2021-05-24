#pragma once

#include "common_types.h"
#include <boost/optional.hpp>
#include <stdexcept>

class IRotatable
{
public:
    virtual ~IRotatable() = default;

    virtual boost::optional<int> GetDirection() const = 0;
    virtual void SetDirection( int direction ) = 0;
    virtual boost::optional<int> GetAngularVelocity() const = 0;
    virtual boost::optional<int> GetMaxDirections() const = 0;
};

class RotateCommand : public Command
{
public:
    RotateCommand( IRotatable& rotatable ) : rotatable_(rotatable)
    {
    }

    bool execute() override
    {
        auto direction = rotatable_.GetDirection();
        if ( !direction.has_value() )
        {
            return false;
        }

        auto angVel = rotatable_.GetAngularVelocity();
        if ( !angVel.has_value() )
        {
            return false;
        }

        auto maxDirections = rotatable_.GetMaxDirections();
        if ( !maxDirections.has_value() )
        {
            return false;
        }

        int newDirection = *direction + *angVel;
        rotatable_.SetDirection( newDirection < 0 ? newDirection + *maxDirections : newDirection % *maxDirections );
        return true;
    }

private:
    IRotatable& rotatable_;
};

class RotatableAdapter : public IRotatable
{
public:
    RotatableAdapter( UObject& uObj ) : uObj_(uObj)
    {
    }

    boost::optional<int> GetDirection() const override
    {
        if ( !uObj_.count( "Direction" ) )
        {
            return {};
        }
        return boost::any_cast<int>( uObj_.at("Direction") );
    }

    void SetDirection( int direction ) override
    {
        uObj_["Direction"] = direction;
    }

    boost::optional<int> GetAngularVelocity() const override
    {
        if ( !uObj_.count( "AngularVelocity" ) )
        {
            return {};
        }
        return boost::any_cast<int>( uObj_["AngularVelocity"] );
    }

    boost::optional<int> GetMaxDirections() const override
    {
        if ( !uObj_.count( "MaxDirections" ) )
        {
            return {};
        }
        return boost::any_cast<int>( uObj_["MaxDirections"] );
    }

private:
    UObject& uObj_;
};
