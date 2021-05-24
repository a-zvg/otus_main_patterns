#pragma once

#include <boost/any.hpp>
#include <unordered_map>

using UObject = std::unordered_map< std::string, boost::any >;

class Command
{
public:
    virtual ~Command() = default;

    virtual bool execute() = 0;
};
