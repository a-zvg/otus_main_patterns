#pragma once

#include "common/iobject.h"
#include <unordered_map>

class UObject : public IObject
{
public:
    const boost::any& Get( const std::string& key ) const override
    {
        return properties_.at(key);
    }

    void Set( const std::string& key, const boost::any& value ) override
    {
        properties_[key] = value;
    }

private:
    std::unordered_map< std::string, boost::any > properties_;
};
