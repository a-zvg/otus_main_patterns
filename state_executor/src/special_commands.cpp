#include <state_executor/special_commands.h>
#include <state_executor/normal_state.h>
#include <state_executor/moveto_state.h>

HardStopCommand::HardStopCommand( ExecutorStateUP& state )
    : state_( state )
{
}

void HardStopCommand::Execute()
{
    state_ = {};
}

MoveToCommand::MoveToCommand( ExecutorStateUP& state, CommandQueue& moveToQueue )
    : state_( state ), moveToQueue_( moveToQueue )
{
}

void MoveToCommand::Execute()
{
    state_ = std::make_unique< MoveToState >( state_->GetExecutorQueue(), moveToQueue_ );
}

RunCommand::RunCommand( ExecutorStateUP& state )
    : state_( state )
{
}

void RunCommand::Execute()
{
    state_ = std::make_unique< NormalState >( state_->GetExecutorQueue() );
}
