#pragma once

#include <boost/any.hpp>
#include <memory>

/// @brief Класс интерфейса универсального объекта
class IObject
{
public:
    /// @brief Деструктор
    virtual ~IObject() = default;

    /// @brief Получить значение свойства объекта
    /// @param key Ключ свойства
    /// @return Значение свойства
    virtual const boost::any& Get( const std::string& key ) const = 0;

    /// @brief Установить значение свойства объекта
    /// @param key Ключ свойства
    /// @param value Значение свойства
    virtual void Set( const std::string& key, const boost::any& value ) = 0;

    /// @brief Проверка есть установленные свойства у объекта
    /// @return Результат проверки
    virtual bool IsEmpty() const = 0;
};

using IObjectSP = std::shared_ptr< IObject >;
