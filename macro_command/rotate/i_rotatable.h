#pragma once

/// @brief Класс интерфейса поворачиваемого объекта
class IRotatable
{
public:
    /// @brief Деструктор
    virtual ~IRotatable() = default;

    /// @brief Получить текущее направление объекта
    /// @return Направление объекта
    virtual int GetDirection() const = 0;

    /// @brief Установить направление объекта
    /// @param direction Направление объекта
    virtual void SetDirection( int direction ) = 0;

    /// @brief Получить угловую скорость объекта
    /// @return Угловая скорость
    virtual int GetAngularVelocity() const = 0;

    /// @brief Получить количество вариантов направлений объекта
    /// @return Количество вариантов направлений объекта
    virtual int GetMaxDirections() const = 0;
};
