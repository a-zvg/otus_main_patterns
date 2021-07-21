#pragma once

#include <macro_command/common/i_object.h>
#include <macro_command/fuel/i_fuel_burnable.h>

/// @brief Класс-адаптер для объекта с топливом
class FuelBurnableAdapter : public IFuelBurnable
{
public:
    /// @brief Конструктор
    /// @param iObj Универсальный объект
    FuelBurnableAdapter( IObjectSP iObj ) : uObj_( std::move( iObj ) )
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

    /// @brief Устновить новый уровень топлива
    /// @param fuelLevel Уровень топлива
    void SetFuelLevel( int fuelLevel ) override
    {
        uObj_->Set( "FuelLevel", fuelLevel );
    }

private:
    IObjectSP uObj_; ///< Универсальный объект
};
