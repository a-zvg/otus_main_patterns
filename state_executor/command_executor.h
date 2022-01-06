#pragma once

#include <state_executor/command_queue.h>
#include <state_executor/i_executor_state.h>
#include <thread>

/// @brief Класс исполнителя команд в отдельном потоке
class CommandExecutor
{
public:
    /// @brief Коструктор класс
    CommandExecutor( std::shared_ptr< CommandQueue > queue, ExecutorStateUP initState );

    /// @brief Деструктор класса
    ~CommandExecutor();

   /// @brief Создать команду HardStopCommand
   /// @return Команда HardStopCommand
   CommandSP GetHardStopCommand();

    /// @brief Создать команду MoveToCommand
    /// @param moveToQueue Очередь для перенаправления
    /// @return Команда MoveToCommand
   CommandSP GetMoveToCommand( CommandQueue& moveToQueue );

   /// @brief Создать команду RunCommand
   /// @return Команда RunCommand
   CommandSP GetRunCommand();

private:
    /// @brief Перейти в основной цикл потока
    void Process();

    std::shared_ptr< CommandQueue > queue_;  ///< Потокобезопасная очередь
    ExecutorStateUP state_;                  ///< Режим обработки команд
    std::thread thread_;                     ///< Объект потока
};
