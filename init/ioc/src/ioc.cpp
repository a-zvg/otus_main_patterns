#include "ioc/ioc.h"

std::map< std::string, boost::any > IoC::rootContainer_;
thread_local std::map< std::string, IoC::Container > IoC::scopes_;

namespace
{

thread_local std::string currentScopeId_ = "Root";

}

IoC::Container& IoC::GetCurrentScopeContainer()
{
    if ( currentScopeId_ == "Root" )
    {
        return rootContainer_;
    }

    try
    {
        return scopes_.at( currentScopeId_ );
    }
    catch ( const std::exception& )
    {
        throw ResolveError();
    }
}

void IoC::SwitchToScope( const std::string& scopeId )
{
    if ( scopes_.count( scopeId ) == 0 )
    {
        scopes_[ scopeId ] = {};
    }
    currentScopeId_ = scopeId;
}
