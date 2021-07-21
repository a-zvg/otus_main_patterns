#pragma once

#include <macro_command/common/i_command.h>
#include <vector>

/// @brief Класс макрокоманды
class MacroCommand : public ICommand
{
public:
    /// @brief Конструктор
    /// @param cmd Первая команда макрокоманды
    MacroCommand( CommandUP cmd )
    {
        commands_.push_back( std::move( cmd ) );
    }

    /// @brief Добавить команду в макрокоманду
    /// @param cmd Команда
    void Add( CommandUP cmd )
    {
        commands_.push_back( std::move( cmd ) );
    }

    /// @brief Выполнить команду
    void Execute() override;

private:
    std::vector< CommandUP > commands_; ///< Массив комманд
};
