#include "command_executor.h"
#include <gmock/gmock.h>
#include <chrono>
#include <memory>
#include <future>
#include <stdexcept>
#include <thread>

using ::testing::Return;
using ::testing::Throw;

class MockCommand : public ICommand
{
public:
    MOCK_METHOD( void, execute, (), (override) );
};

TEST( CommandExecutorTest, TestStart )
{
    CommandExecutor executor( CommandExecutor::QueueSize{100} );
    tbb::concurrent_bounded_queue< std::shared_ptr<ICommand> >& q = executor.GetQueue();

    auto command = std::make_shared<MockCommand>();
    std::promise<void> p;

    EXPECT_CALL( *command, execute() )
        .WillOnce( [ &p ]() mutable { p.set_value(); } );

    q.push( std::move(command) );

    EXPECT_EQ( p.get_future().wait_for( std::chrono::seconds(1) ), std::future_status::ready );
}

TEST( CommandExecutorTest, TestExceptionStability )
{
    CommandExecutor executor( CommandExecutor::QueueSize{100} );
    tbb::concurrent_bounded_queue< std::shared_ptr<ICommand> >& q = executor.GetQueue();

    auto command = std::make_shared<MockCommand>();
    std::promise<void> p;

    EXPECT_CALL( *command, execute() )
        .WillOnce( Throw( std::runtime_error("") ) )
        .WillOnce( [ &p ]() mutable { p.set_value(); } );

    q.push( command );
    q.push( std::move(command) );

    EXPECT_EQ( p.get_future().wait_for( std::chrono::seconds(1) ), std::future_status::ready );
}

TEST( CommandExecutorTest, TestHardStop )
{
    int counter = 0;
    {
        CommandExecutor executor( CommandExecutor::QueueSize{100} );
        tbb::concurrent_bounded_queue< std::shared_ptr<ICommand> >& q = executor.GetQueue();

        for ( int i = 0; i < 11; ++i )
        {
            if ( i < 5 )
            {
                auto command = std::make_shared<MockCommand>();
                EXPECT_CALL( *command, execute() )
                    .WillOnce( [ &counter ]{ std::this_thread::sleep_for( std::chrono::milliseconds(100) ); ++counter; } );

                q.push( std::move(command) );
                continue;
            }
            else if ( i == 5 )
            {
                q.push( std::make_shared<CommandExecutor::HardStopCommand>() );
                continue;
            }
            else // i > 5
            {
                auto command = std::make_shared<MockCommand>();
                EXPECT_CALL( *command, execute() )
                    .WillRepeatedly( [ &counter ]{ std::this_thread::sleep_for( std::chrono::milliseconds(100) ); ++counter; } );

                q.push( std::move(command) );
            }
        }
    }
    EXPECT_EQ( counter, 5 );
}

TEST( CommandExecutorTest, TestSoftStop )
{
    int counter = 0;
    {
        CommandExecutor executor( CommandExecutor::QueueSize{100} );
        tbb::concurrent_bounded_queue< std::shared_ptr<ICommand> >& q = executor.GetQueue();

        for ( int i = 0; i < 11; ++i )
        {
            if ( i < 5 )
            {
                auto command = std::make_shared<MockCommand>();
                EXPECT_CALL( *command, execute() )
                    .WillOnce( [ &counter ]{ std::this_thread::sleep_for( std::chrono::milliseconds(100) ); ++counter; } );

                q.push( std::move(command) );
                continue;
            }
            else if ( i == 5 )
            {
                q.push( std::make_shared<CommandExecutor::SoftStopCommand>() );
                continue;
            }
            else // i > 5
            {
                auto command = std::make_shared<MockCommand>();
                EXPECT_CALL( *command, execute() )
                    .WillRepeatedly( [ &counter ]{ std::this_thread::sleep_for( std::chrono::milliseconds(100) ); ++counter; } );

                q.push( std::move(command) );
            }
        }
    }
    EXPECT_EQ( counter, 10 );
}
