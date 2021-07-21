#include <macro_command/fuel/burn_fuel_command.h>
#include <gmock/gmock.h>
#include <memory>
#include <stdexcept>

using ::testing::Return;
using ::testing::Throw;

class MockFuelBurnable : public IFuelBurnable
{
public:
    MOCK_METHOD( int, GetFuelLevel, (), (const, override) );
    MOCK_METHOD( int, GetFuelBurnSpeed, (), (const, override) );
    MOCK_METHOD( void, SetFuelLevel, ( int ), (override) );
};

TEST( BurnFuelTest, TestBurnFuelSuccess )
{
    auto mockUP = std::make_unique<MockFuelBurnable>();
    EXPECT_CALL( *mockUP, GetFuelLevel() )
        .WillOnce( Return( 100 ) );
    EXPECT_CALL( *mockUP, GetFuelBurnSpeed() )
        .WillOnce( Return( 10 ) );
    EXPECT_CALL( *mockUP, SetFuelLevel( 90 ) );

    BurnFuelCommand cmd( std::move( mockUP ) );
    EXPECT_NO_THROW( cmd.Execute() );
}

TEST( BurnFuelTest, TestBurnFuelFail )
{
    auto mockUP = std::make_unique<MockFuelBurnable>();
    EXPECT_CALL( *mockUP, GetFuelLevel() )
        .WillOnce( Return( 0 ) );
    EXPECT_CALL( *mockUP, GetFuelBurnSpeed() )
        .WillOnce( Return( 10 ) );

    BurnFuelCommand cmd( std::move( mockUP ) );
    EXPECT_THROW( cmd.Execute(), CommandError );
}
