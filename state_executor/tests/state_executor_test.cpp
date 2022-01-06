#include <state_executor/command_executor.h>
#include <state_executor/normal_state.h>
#include <state_executor/moveto_state.h>
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
    MOCK_METHOD( void, Execute, (), (override) );
};

TEST( CommandExecutorTest, TestBasicWork )
{
    std::shared_ptr<CommandQueue> q = std::make_shared<CommandQueue>();
    q->set_capacity( 100 );

    ExecutorStateUP normalState = std::make_unique<NormalState>( *q );
    CommandExecutor executor( q, std::move( normalState ) );

    std::promise<void> p; // Альтернативный условным переменным C++ способ синхронизации потоков
    std::future<void> f = p.get_future();

    auto command = std::make_shared<MockCommand>();
    EXPECT_CALL( *command, Execute() )
        .WillOnce( [ &p ]() mutable
            {
                p.set_value();
            } );

    q->push( std::move( command ) );
    EXPECT_EQ( f.wait_for( std::chrono::seconds(1) ), std::future_status::ready );
}

TEST( CommandExecutorTest, TestHardStopCommand )
{
    std::shared_ptr<CommandQueue> q = std::make_shared<CommandQueue>();
    q->set_capacity( 100 );

    ExecutorStateUP normalState = std::make_unique<NormalState>( *q );
    CommandExecutor executor( q, std::move( normalState ) );

    std::promise<void> p;
    // Вставка в очередь первой команды, которая заблокирует очередь в ожидании установки значения в std::promise
    {
        class WaitCommand : public ICommand
        {
        public:
            WaitCommand( std::future<void>&& f ) : f_( std::move( f ) )
            {
            }

            void Execute()
            {
                f_.wait();
            }

        private:
            std::future<void> f_;
        };

        std::future<void> f = p.get_future();
        q->push( std::make_shared<WaitCommand>( std::move( f ) ) );
    }

    // Вставка в очередь команды HardStopCommand
    q->push( executor.GetHardStopCommand() );

    auto command = std::make_shared<MockCommand>();
    EXPECT_CALL( *command, Execute() )
        .Times( 0 );

    // Вставка в очередь контрольной команды, которая не должна исполниться
    q->push( std::move( command ) );

    // Продолжить выполнение первой команды
    p.set_value();
}

TEST( CommandExecutorTest, TestMoveToCommand )
{
    std::shared_ptr<CommandQueue> q = std::make_shared<CommandQueue>();
    q->set_capacity( 100 );

    ExecutorStateUP normalState = std::make_unique<NormalState>( *q );
    CommandExecutor executor( q, std::move( normalState ) );

    std::shared_ptr<CommandQueue> q2 = std::make_shared<CommandQueue>();
    q2->set_capacity( 100 );
    // Вставка в очередь команды MoveToCommand
    q->push( executor.GetMoveToCommand( *q2 ) );

    auto command = std::make_shared<MockCommand>();
    EXPECT_CALL( *command, Execute() )
        .WillOnce( []{} );

    // Вставка в очередь контрольной команды, которая должна попасть в очередь q2
    q->push( std::move( command ) );

    // Проверка контрольной команды из очереди q2
    CommandSP c;
    q2->pop( c );
    c->Execute();
}

TEST( CommandExecutorTest, TestRunCommand )
{
    std::shared_ptr<CommandQueue> q = std::make_shared<CommandQueue>();
    q->set_capacity( 100 );

    std::shared_ptr<CommandQueue> q2 = std::make_shared<CommandQueue>();
    q2->set_capacity( 100 );

    ExecutorStateUP moveToState = std::make_unique<MoveToState>( *q, *q2 );
    CommandExecutor executor( q, std::move( moveToState ) );

    // Вставка в очередь команды RunCommand
    q->push( executor.GetRunCommand() );

    std::promise<void> p;
    std::future<void> f = p.get_future();

    auto command = std::make_shared<MockCommand>();
    EXPECT_CALL( *command, Execute() )
        .WillOnce( [ &p ]() mutable
            {
                p.set_value();
            } );

    // Вставка в очередь контрольной команды, которая должна выполниться в исполнителе команд executor
    q->push( std::move( command ) );
    EXPECT_EQ( f.wait_for( std::chrono::seconds(1) ), std::future_status::ready );
}
