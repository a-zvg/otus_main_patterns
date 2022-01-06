#include <state_executor/command_executor.h>
#include <state_executor/special_commands.h>

CommandExecutor::CommandExecutor( std::shared_ptr< CommandQueue > queue, ExecutorStateUP initState )
    : queue_( std::move( queue ) ), state_( std::move( initState ) )
{
    thread_ = std::thread( [this]
         {
             Process();
         } );
}

CommandExecutor::~CommandExecutor()
{
    queue_->push( GetHardStopCommand() );
    thread_.join();
}

CommandSP CommandExecutor::GetHardStopCommand()
{
    return CommandSP( std::make_shared<HardStopCommand>( state_ ) );
}

CommandSP CommandExecutor::GetMoveToCommand( CommandQueue& moveToQueue )
{
    return CommandSP( std::make_shared<MoveToCommand>( state_, moveToQueue ) );
}

CommandSP CommandExecutor::GetRunCommand()
{
    return CommandSP( std::make_shared<RunCommand>( state_ ) );
}

void CommandExecutor::Process()
{
    while ( state_ )
    {
        try
        {
            state_->Handle();
        }
        catch ( const std::exception& )
        {
        }
    }
}
