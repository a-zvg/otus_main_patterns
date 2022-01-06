#include <state_executor/i_executor_state.h>

/// @brief Класс состояния "Обычное" исполнителя команд
class NormalState : public IExecutorState
{
public:
    /// @brief Конструктор
    /// @param queue Очередь исполнителя команд
    NormalState( CommandQueue& queue );

    /// @brief Обработчик команд
    void Handle() override;

    /// @brief Получить очередь исполнителя команд
    /// @return Очередь исполнителя команд
    CommandQueue& GetExecutorQueue() const override;

private:
    CommandQueue& queue_;  ///< Очередь исполнителя команд
};
