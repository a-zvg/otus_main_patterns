#pragma once

#include "common_types.h"
#include <boost/optional.hpp>
#include <stdexcept>

class Point
{
public:
    Point( int x, int y ) : x_(x), y_(y)
    {
    }

    friend Point operator+( const Point& p1, const Point& p2 )
    {
        return { p1.x_ + p2.x_, p1.y_ + p2.y_ };
    }

    friend bool operator==( const Point& p1, const Point& p2 )
    {
        return p1.x_ == p2.x_ && p1.y_ == p2.y_;
    }

private:
    int x_;
    int y_;
};

class IMovable
{
public:
    virtual ~IMovable() = default;

    virtual boost::optional<Point> GetPosition() const = 0;
    virtual void SetPosition( const Point& position ) = 0;
    virtual boost::optional<Point> GetVelocity() const = 0;
};

class MoveCommand : public Command
{
public:
    MoveCommand( IMovable& movable ) : movable_(movable)
    {
    }

    bool execute() override
    {
        auto pos = movable_.GetPosition();
        if ( !pos.has_value() )
        {
            return false;
        }

        auto vel = movable_.GetVelocity();
        if ( !vel.has_value() )
        {
            return false;
        }

        movable_.SetPosition( *pos + *vel );
        return true;
    }

private:
    IMovable& movable_;
};

class MovableAdapter : public IMovable
{
public:
    MovableAdapter( UObject& uObj ) : uObj_(uObj)
    {
    }

    boost::optional<Point> GetPosition() const override
    {
        if ( !uObj_.count( "Position" ) )
        {
            return {};
        }
        return boost::any_cast<Point>( uObj_.at("Position") );
    }

    void SetPosition( const Point& position ) override
    {
        uObj_["Position"] = position;
    }

    boost::optional<Point> GetVelocity() const override
    {
        if ( !uObj_.count( "Velocity" ) )
        {
            return {};
        }
        return boost::any_cast<Point>( uObj_["Velocity"] );
    }

private:
    UObject& uObj_;
};
