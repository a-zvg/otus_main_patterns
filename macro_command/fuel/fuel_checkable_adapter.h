#pragma once

#include <macro_command/common/i_object.h>
#include <macro_command/fuel/i_fuel_checkable.h>

/// @brief Класс-адаптер для объекта с топливом
class FuelCheckableAdapter : public IFuelCheckable
{
public:
    /// @brief Конструктор
    /// @param iObj Универсальный объект
    FuelCheckableAdapter( IObjectSP iObj ) : uObj_( std::move( iObj ) )
    {
    }

    /// @brief Получить уровень топлива
    /// @return Уровень топлива
    int GetFuelLevel() const override
    {
        return boost::any_cast< int >( uObj_->Get( "FuelLevel" ) );
    }

    /// @brief Получить скорость расхода топлива
    /// @return Скорость расхода топлива
    int GetFuelBurnSpeed() const override
    {
        return boost::any_cast< int >( uObj_->Get( "FuelBurnSpeed" ) );
    }

private:
    IObjectSP uObj_; ///< Универсальный объект
};
