#pragma once

#include <macro_command/fuel/i_fuel_checkable.h>

/// @brief Класс интерфейса объекта с топливом
class IFuelBurnable : public IFuelCheckable
{
public:
    /// @brief Устновить новый уровень топлива
    /// @param fuelLevel Уровень топлива
    virtual void SetFuelLevel( int fuelLevel ) = 0;
};

using IFuelBurnableUP = std::unique_ptr< IFuelBurnable >;
