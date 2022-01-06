#include <state_executor/moveto_state.h>
#include <state_executor/special_commands.h>

MoveToState::MoveToState( CommandQueue& queue, CommandQueue& moveToQueue )
    : queue_( queue ), moveToQueue_( moveToQueue )
{
}

void MoveToState::Handle()
{
    CommandSP c;
    queue_.pop( c );

    // Необходимый хак, т.к. чтобы сменить состояние необходимо выполнить соответствующие команды, но состояние
    // MoveToState само не выполняет команды, а только перенаправляет, поэтому для команд смены состояний это
    // приходится делать явно
    if ( dynamic_cast< HardStopCommand* >( c.get() ) )
    {
        c->Execute();
        return;
    }
    else if ( dynamic_cast< RunCommand* >( c.get() ) )
    {
        c->Execute();
        return;
    }

    moveToQueue_.push( std::move( c ) );
}

CommandQueue& MoveToState::GetExecutorQueue() const
{
    return queue_;
}
