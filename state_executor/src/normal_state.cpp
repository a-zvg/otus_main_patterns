#include <state_executor/normal_state.h>

NormalState::NormalState( CommandQueue& queue )
    : queue_( queue )
{
}

void NormalState::Handle()
{
    CommandSP c;
    queue_.pop( c );

    try
    {
        c->Execute();
    }
    catch ( std::exception& )
    {
    }
}

CommandQueue& NormalState::GetExecutorQueue() const
{
    return queue_;
}
