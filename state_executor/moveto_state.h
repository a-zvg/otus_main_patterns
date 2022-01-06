#include <state_executor/i_executor_state.h>

/// @brief Класс состояния MoveTo исполнителя команд
class MoveToState : public IExecutorState
{
public:
    /// @brief Конструктор
    /// @param queue Очередь исполнителя команд
    /// @param moveToQueue Очередь для перенаправления
    MoveToState( CommandQueue& queue, CommandQueue& moveToQueue );

    /// @brief Обработчик команд
    void Handle() override;

    /// @brief Получить очередь исполнителя команд
    /// @return Очередь исполнителя команд
    CommandQueue& GetExecutorQueue() const override;

private:
    CommandQueue& queue_;        ///< Очередь исполнителя команд
    CommandQueue& moveToQueue_;  ///< Очередь для перенаправления
};
