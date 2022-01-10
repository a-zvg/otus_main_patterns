#pragma once

#include "common/i_command.h"
#include "rotate/i_rotatable.h"
#include "rotate/rotate_error.h"

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
