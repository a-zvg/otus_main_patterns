#include <macro_command/common/macro_command.h>
#include <gmock/gmock.h>
#include <memory>
#include <stdexcept>

using ::testing::Return;
using ::testing::Throw;

class MockCommand : public ICommand
{
public:
    MOCK_METHOD( void, Execute, (), (override) );
};

TEST( MacroCommandTest, TestExecuteEveryCommand )
{
    auto first = std::make_unique<MockCommand>();
    auto second = std::make_unique<MockCommand>();

    EXPECT_CALL( *first, Execute() )
        .WillOnce( Return() );
    EXPECT_CALL( *second, Execute() )
        .WillOnce( Return() );

    MacroCommand cmd( std::move( first ) );
    EXPECT_NO_THROW( cmd.Add( std::move( second ) ) );
    EXPECT_NO_THROW( cmd.Execute() );
}

TEST( MacroCommandTest, TestMacroCommandFail )
{
    auto first = std::make_unique<MockCommand>();
    auto second = std::make_unique<MockCommand>();
    auto third = std::make_unique<MockCommand>();

    EXPECT_CALL( *first, Execute() )
        .WillOnce( Return() );
    EXPECT_CALL( *second, Execute() )
        .WillOnce( Throw( CommandError() ) );
    EXPECT_CALL( *third, Execute() )
        .Times( 0 );

    MacroCommand cmd( std::move( first ) );

    EXPECT_NO_THROW( cmd.Add( std::move( second ) ) );
    EXPECT_NO_THROW( cmd.Add( std::move( third ) ) );
    EXPECT_THROW( cmd.Execute(), CommandError );
}
