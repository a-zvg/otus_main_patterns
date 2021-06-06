#pragma once

#include <stdexcept>

class MoveError : public std::runtime_error
{
public:
    MoveError() : std::runtime_error("")
    {
    }
};
