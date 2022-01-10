#include "common/common_init.h"
#include "ioc/ioc.h"

std::vector<IObjectSP> CommonInit( const std::vector<std::string>& initList, size_t count )
{
    std::vector<IObjectSP> objects;

    for ( size_t i = 0; i < count; ++i )
    {
        IObjectSP obj = IoC::Resolve<IObjectSP>( "NewObject" );
        for ( const auto& c : initList )
        {
            IoC::Resolve<void, IObjectSP>( c, obj );
        }
        objects.push_back( std::move(obj) );
    }

    return objects;
}
