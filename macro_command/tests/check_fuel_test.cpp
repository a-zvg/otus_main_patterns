#include <macro_command/fuel/check_fuel_command.h>
#include <gmock/gmock.h>
#include <memory>
#include <stdexcept>

using ::testing::Return;
using ::testing::Throw;

class MockFuelCheckable : public IFuelCheckable
{
public:
    MOCK_METHOD( int, GetFuelLevel, (), (const, override) );
    MOCK_METHOD( int, GetFuelBurnSpeed, (), (const, override) );
};

TEST( CheckFuelTest, TestCheckFuelSuccess )
{
    auto mockUP = std::make_unique<MockFuelCheckable>();
    MockFuelCheckable& mockObj = *mockUP.get();

    EXPECT_CALL( mockObj, GetFuelLevel() )
        .WillOnce( Return( 100 ) );
    EXPECT_CALL( mockObj, GetFuelBurnSpeed() )
        .WillOnce( Return( 10 ) );

    CheckFuelCommand cmd( std::move( mockUP ) );
    EXPECT_NO_THROW( cmd.Execute() );

    // Проверка граничного условия
    EXPECT_CALL( mockObj, GetFuelLevel() )
        .WillOnce( Return( 10 ) );
    EXPECT_CALL( mockObj, GetFuelBurnSpeed() )
        .WillOnce( Return( 10 ) );

    EXPECT_NO_THROW( cmd.Execute() );
}

TEST( CheckFuelTest, TestCheckFuelFail )
{
    auto mockUP = std::make_unique<MockFuelCheckable>();
    EXPECT_CALL( *mockUP, GetFuelLevel() )
        .WillOnce( Return( 0 ) );
    EXPECT_CALL( *mockUP, GetFuelBurnSpeed() )
        .WillOnce( Return( 10 ) );

    CheckFuelCommand cmd( std::move( mockUP ) );
    EXPECT_THROW( cmd.Execute(), CommandError );
}
