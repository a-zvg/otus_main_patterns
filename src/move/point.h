#pragma once

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
