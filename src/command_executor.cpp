#include "command_executor.h"

CommandExecutor::CommandExecutor( QueueSize s )
{
    queue_.set_capacity( s.value );
    thread_ = std::thread( [this]
         {
             Process();
         } );
}

CommandExecutor::~CommandExecutor()
{
    queue_.push( std::make_shared<HardStopCommand>() );
    thread_.join();
}

void CommandExecutor::Process()
{
    while ( true )
    {
        std::shared_ptr<ICommand> c;
        queue_.pop( c );

        try
        {
            c->execute();
        }
        catch ( HardStop& )
        {
            break;
        }
        catch ( SoftStop& )
        {
            softStop_ = true;
        }
        catch ( std::exception& )
        {
        }

        if ( softStop_ && queue_.empty() )
        {
            break;
        }
    }
}
