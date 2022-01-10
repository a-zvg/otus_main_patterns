#pragma once

#include "common/command_error.h"
#include <memory>

/// @brief Класс интерфейса команды
class ICommand
{
public:
    /// @brief Деструктор
    virtual ~ICommand() = default;

    /// @brief Выполнить команду
    virtual void Execute() = 0;
};

using CommandUP = std::unique_ptr< ICommand >;
