#pragma once

#include "common/i_object.h"
#include "move/i_movable.h"

/// @brief Класс-адаптер для движимого объекта
class MovableAdapter : public IMovable
{
public:
    /// @brief Конструктор
    /// @param iObj Универсальный объект
    MovableAdapter( IObjectSP iObj ) : uObj_( std::move( iObj ) )
    {
    }

    /// @brief Получить позицию объекта
    /// @return Точка позиции объекта
    Point GetPosition() const override
    {
        return boost::any_cast< Point >( uObj_->Get( "Position" ) );
    }

    /// @brief Установить позицию объекта
    /// @param position Точка позиции объекта
    void SetPosition( const Point& position ) override
    {
        uObj_->Set( "Position", position );
    }

    /// @brief Получить вектор мнгновенной скорости объекта
    /// @return Вектор мнгновенной скорости объекта
    Point GetVelocity() const override
    {
        return boost::any_cast< Point >( uObj_->Get( "Velocity" ) );
    }

private:
    IObjectSP uObj_; ///< Универсальный объект
};
