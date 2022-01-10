#pragma once

/// @brief Класс точки в двухмерном пространстве
class Point
{
public:
    /// @brief Конструктор
    /// @param x Позиция x
    /// @param y Позиция y
    Point( int x, int y ) : x_(x), y_(y)
    {
    }

    /// @brief Сложение двух точек в пространстве
    /// @param p1 Точка 1
    /// @param p2 Точка 2
    /// @return Новая позиция в пространстве
    friend Point operator+( const Point& p1, const Point& p2 )
    {
        return { p1.x_ + p2.x_, p1.y_ + p2.y_ };
    }

    /// @brief Сравнение двух точек в пространстве
    /// @param p1 Точка 1
    /// @param p2 Точка 2
    /// @return true, если позиции указывают на одну точку, иначе false
    friend bool operator==( const Point& p1, const Point& p2 )
    {
        return p1.x_ == p2.x_ && p1.y_ == p2.y_;
    }

private:
    int x_; ///< Позиция x
    int y_; ///< Позиция y
};
