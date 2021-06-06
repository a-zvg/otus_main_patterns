#pragma once

#include <stdexcept>

class RotateError : public std::runtime_error
{
public:
    RotateError() : std::runtime_error("")
    {
    }
};
