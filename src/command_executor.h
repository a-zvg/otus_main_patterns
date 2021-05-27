/// @file
/// @brief Файл с объявлением класса исполнителя команд

#pragma once

#include "common/icommand.h"
#include <tbb/concurrent_queue.h>
#include <memory>
#include <thread>

/// @brief Класс выполнения команд в отдельном потоке
class CommandExecutor
{
private:
    /// @brief Класс исключения для остановки потока
    class HardStop
    {
    };

    /// @brief Класс исключения для остановки потока, после того, как все команды завершат свою работу
    class SoftStop
    {
    };

public:
    /// @brief Вспомогательный класс для выражения типа размера очереди
    struct QueueSize
    {
        size_t value;
    };

    /// @brief Команда остановки потока
    class HardStopCommand : public ICommand
    {
    public:
        void execute() override
        {
            throw HardStop();
        }
    };

    /// @brief Команда остановки потока, после того, как все команды завершат свою работу
    class SoftStopCommand : public ICommand
    {
    public:
        void execute() override
        {
            throw SoftStop();
        }
    };

public:
    /// @brief Коструктор класс
    /// @param s размер очереди команд
    CommandExecutor( QueueSize s );

    /// @brief Деструктор класса
    ~CommandExecutor();

    /// @brief Получить ссылку на очередь команд
    /// @return очередь команд
    tbb::concurrent_bounded_queue< std::shared_ptr<ICommand> >& GetQueue()
    {
        return queue_;
    }

private:
    /// @brief Перейти в основной цикл потока
    void Process();

    tbb::concurrent_bounded_queue< std::shared_ptr<ICommand> > queue_; ///< Потокобезопасная очередь
    bool softStop_ = false;  ///< Признак необходимости попыток "мягкой" остановки потока
    std::thread thread_;     ///< Объект потока
};
