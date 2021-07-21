#pragma once

#include <stdexcept>

/// @brief Класс исключения поворота
class RotateError : public std::runtime_error
{
public:
    /// @brief Конструктор
    RotateError() : std::runtime_error("")
    {
    }
};
