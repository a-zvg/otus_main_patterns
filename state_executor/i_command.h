#pragma once

/// @brief Интерфейс команды
class ICommand
{
public:
    /// @brief Деструктор класса
    virtual ~ICommand() = default;

    /// @brief Выполнить команду
    virtual void Execute() = 0;
};
