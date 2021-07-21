#pragma once

#include <macro_command/common/i_command.h>
#include <macro_command/rotate/i_rotatable.h>
#include <macro_command/rotate/rotate_error.h>

/// @brief Класс команды поворота
class RotateCommand : public ICommand
{
public:
    /// @brief Конструктор
    /// @param rotatable Поворачиваемый объект
    RotateCommand( IRotatable& rotatable ) : rotatable_( rotatable )
    {
    }

    /// @brief Выполнить команду
    void Execute() override;

private:
    IRotatable& rotatable_; ///< Поворачиваемый объект
};
