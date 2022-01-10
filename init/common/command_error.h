#pragma once

#include <stdexcept>

/// @brief Класс исключения выполнения команды
class CommandError : public std::runtime_error
{
public:
    /// @brief Конструктор
    CommandError() : std::runtime_error("")
    {
    }
};
