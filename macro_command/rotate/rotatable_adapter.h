#pragma once

#include <macro_command/common/i_object.h>
#include <macro_command/rotate/i_rotatable.h>

/// @brief Класс-адаптер для поворачиваемого объекта
class RotatableAdapter : public IRotatable
{
public:
    /// @brief Конструктор
    /// @param iObj Универсальный объект
    RotatableAdapter( IObject& iObj ) : uObj_( iObj )
    {
    }

    /// @brief Получить текущее направление объекта
    /// @return Направление объекта
    int GetDirection() const override
    {
        return boost::any_cast< int >( uObj_.Get( "Direction" ) );
    }

    /// @brief Установить направление объекта
    /// @param direction Направление объекта
    void SetDirection( int direction ) override
    {
        uObj_.Set( "Direction", direction );
    }

    /// @brief Получить угловую скорость объекта
    /// @return Угловая скорость
    int GetAngularVelocity() const override
    {
        return boost::any_cast< int >( uObj_.Get( "AngularVelocity" ) );
    }

    /// @brief Получить количество вариантов направлений объекта
    /// @return Количество вариантов направлений объекта
    int GetMaxDirections() const override
    {
        return boost::any_cast< int >( uObj_.Get( "MaxDirections" ) );
    }

private:
    IObject& uObj_; ///< Универсальный объект
};
