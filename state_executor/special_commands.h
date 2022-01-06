#pragma once

#include <state_executor/i_executor_state.h>

/// @brief Команда остановки потока исполнителя команд
class HardStopCommand : public ICommand
{
public:
    /// @brief Конструктор
    /// @param state Состояние исполнителя команд
    HardStopCommand( ExecutorStateUP& state );

    /// @brief Выполнить команду
    void Execute() override;

private:
    ExecutorStateUP& state_; ///< Состояние исполнителя команд
};

/// @brief Команда перенаправления команд из очереди исполнителя
class MoveToCommand: public ICommand
{
public:
    /// @brief Конструктор
    /// @param state Состояние исполнителя команд
    /// @param moveToQueue Очередь для перенаправления
    MoveToCommand( ExecutorStateUP& state, CommandQueue& moveToQueue );

    /// @brief Выполнить команду
    void Execute() override;

private:
    ExecutorStateUP& state_;     ///< Состояние исполнителя команд
    CommandQueue& moveToQueue_;  ///< Очередь для перенаправления
};

/// @brief Команда для перехода исполнителя команд в "Обычное" состояние
class RunCommand: public ICommand
{
public:
    /// @brief Конструктор
    /// @param state Состояние исполнителя команд
    RunCommand( ExecutorStateUP& state );

    /// @brief Выполнить команду
    void Execute() override;

private:
    ExecutorStateUP& state_; ///< Состояние исполнителя команд
};
