#pragma once

#include <state_executor/command_queue.h>

class IExecutorState;
using ExecutorStateUP = std::unique_ptr< IExecutorState >;

/// @brief Интерфейс состояния исполнителя команд
class IExecutorState
{
public:
    /// @brief Деструктор
    virtual ~IExecutorState() = default;

    /// @brief Обработчик команд
    virtual void Handle() = 0;

    /// @brief Получить очередь исполнителя команд
    /// @return Очередь исполнителя команд
    virtual CommandQueue& GetExecutorQueue() const = 0;
};
