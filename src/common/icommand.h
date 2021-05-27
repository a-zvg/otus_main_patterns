/// @file
/// @brief Файл с объявлением абстрактного класса команды

#pragma once

/// @brief Класс интерфейса команды
class ICommand
{
public:
    /// @brief Деструктор класса
    virtual ~ICommand() = default;

    /// @brief Выполнить команду
    virtual void execute() = 0;
};
