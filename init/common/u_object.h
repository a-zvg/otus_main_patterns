#pragma once

#include "common/i_object.h"
#include <unordered_map>

/// @brief Класс универсального объекта
class UObject : public IObject
{
public:
    /// @brief Получить значение свойства объекта
    /// @param key Ключ свойства
    /// @return Значение свойства
    const boost::any& Get( const std::string& key ) const override
    {
        return properties_.at( key );
    }

    /// @brief Установить значение свойства объекта
    /// @param key Ключ свойства
    /// @param value Значение свойства
    void Set( const std::string& key, const boost::any& value ) override
    {
        properties_[ key ] = value;
    }

    /// @brief Проверка есть установленные свойства у объекта
    /// @return Результат проверки
    bool IsEmpty() const override
    {
        return properties_.empty();
    }

private:
    std::unordered_map< std::string, boost::any > properties_; ///< Свойства объекта
};
