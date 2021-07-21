#pragma once

#include <macro_command/common/i_command.h>
#include <macro_command/fuel/i_fuel_checkable.h>

/// @brief Класс команды проверки уровня топлива
class CheckFuelCommand : public ICommand
{
public:
    /// @brief Конструктор
    /// @param fuelCheckable Объект с топливом
    CheckFuelCommand( IFuelCheckableUP fuelCheckable ) : fuelCheckable_( std::move( fuelCheckable ) )
    {
    }

    /// @brief Выполнить команду
    void Execute() override;

private:
    IFuelCheckableUP fuelCheckable_; ///< Объект с топливом
};
