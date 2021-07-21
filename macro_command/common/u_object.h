#pragma once

#include <macro_command/common/i_object.h>
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

private:
    std::unordered_map< std::string, boost::any > properties_; ///< Свойства объекта
};
