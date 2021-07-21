#pragma once

#include <memory>

/// @brief Класс интерфейса объекта с топливом
class IFuelCheckable
{
public:
     /// @brief Деструктор
    virtual ~IFuelCheckable() = default;

    /// @brief Получить уровень топлива
    /// @return Уровень топлива
    virtual int GetFuelLevel() const = 0;

    /// @brief Получить скорость расхода топлива
    /// @return Скорость расхода топлива
    virtual int GetFuelBurnSpeed() const = 0;
};

using IFuelCheckableUP = std::unique_ptr< IFuelCheckable >;
