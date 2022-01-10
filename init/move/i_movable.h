#pragma once

#include "move/point.h"
#include <memory>

/// @brief Класс интерфейса движимого объекта
class IMovable
{
public:
     /// @brief Деструктор
    virtual ~IMovable() = default;

    /// @brief Получить позицию объекта
    /// @return Точка позиции объекта
    virtual Point GetPosition() const = 0;

    /// @brief Установить позицию объекта
    /// @param position Точка позиции объекта
    virtual void SetPosition( const Point& position ) = 0;

    /// @brief Получить вектор мнгновенной скорости объекта
    /// @return Вектор мнгновенной скорости объекта
    virtual Point GetVelocity() const = 0;
};

using IMovableUP = std::unique_ptr< IMovable >;
