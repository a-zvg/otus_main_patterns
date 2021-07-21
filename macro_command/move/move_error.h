#pragma once

#include <stdexcept>

/// @brief Класс исключения движения
class MoveError : public std::runtime_error
{
public:
    /// @brief Конструктор
    MoveError() : std::runtime_error("")
    {
    }
};
