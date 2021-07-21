#pragma once

#include <macro_command/common/i_command.h>
#include <macro_command/fuel/i_fuel_burnable.h>

/// @brief Класс команды сжигания топлива
class BurnFuelCommand : public ICommand
{
public:
    /// @brief Конструктор
    /// @param fuelBurnable Объект с топливом
    BurnFuelCommand( IFuelBurnableUP fuelBurnable ) : fuelBurnable_( std::move( fuelBurnable ) )
    {
    }

    /// @brief Выполнить команду
    void Execute() override;

private:
    IFuelBurnableUP fuelBurnable_; ///< Объект с топливом
};
