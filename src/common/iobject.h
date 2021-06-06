#pragma once

#include <boost/any.hpp>

class IObject
{
public:
    virtual ~IObject() = default;

    virtual const boost::any& Get( const std::string& key ) const = 0;
    virtual void Set( const std::string& key, const boost::any& value ) = 0;
};
