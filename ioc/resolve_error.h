#pragma once

#include <stdexcept>

/// @brief Класс исключения разрешения зависимости
class ResolveError : public std::runtime_error
{
public:
    /// @brief Конструктор
    ResolveError() : std::runtime_error("")
    {
    }
};

