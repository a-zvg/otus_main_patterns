#pragma once

#include <macro_command/common/i_command.h>
#include <macro_command/move/i_movable.h>

/// @brief Класс команды движения
class MoveCommand : public ICommand
{
public:
    /// @brief Конструктор
    /// @param movable Движимый объект
    MoveCommand( IMovableUP movable ) : movable_( std::move( movable ) )
    {
    }

    /// @brief Выполнить команду
    void Execute() override;

private:
    IMovableUP movable_; ///< Движимый объект
};
