#include "rotate.h"
#include <gmock/gmock.h>

using ::testing::Return;

class MockRotatable : public IRotatable
{
public:
     MOCK_METHOD( boost::optional<int>, GetDirection, (), (const, override) );
     MOCK_METHOD( void, SetDirection, ( int direction ), (override) );
     MOCK_METHOD( boost::optional<int>, GetAngularVelocity, (), (const, override) );
     MOCK_METHOD( boost::optional<int>, GetMaxDirections, (), (const, override) );
};

TEST( RotatingTest, Test1 )
{
    MockRotatable rotatable;
    EXPECT_CALL( rotatable, GetDirection() )
        .WillOnce( Return( 1 ) )
        .WillOnce( Return( 3 ) );
    EXPECT_CALL( rotatable, GetAngularVelocity() )
        .WillOnce( Return( -2 ) );
    EXPECT_CALL( rotatable, GetMaxDirections() )
        .WillOnce( Return( 4 ) );
    EXPECT_CALL( rotatable, SetDirection( 3 ) );

    RotateCommand cmd( rotatable );
    EXPECT_NO_THROW( cmd.execute() );
    EXPECT_EQ( rotatable.GetDirection(), 3 );
}

TEST( RotatingTest, Test2 )
{
    MockRotatable rotatable;
    EXPECT_CALL( rotatable, GetDirection() )
        .WillOnce( Return( boost::none ) );

    RotateCommand cmd(rotatable);
    EXPECT_EQ( cmd.execute(), false );
}

TEST( RotatingTest, Test3 )
{
    MockRotatable rotatable;
    EXPECT_CALL( rotatable, GetDirection() )
        .WillOnce( Return( 1 ) );
    EXPECT_CALL( rotatable, GetAngularVelocity() )
        .WillOnce( Return( boost::none ) );

    RotateCommand cmd(rotatable);
    EXPECT_EQ( cmd.execute(), false );
}

TEST( RotatingTest, Test4 )
{
    MockRotatable rotatable;
    EXPECT_CALL( rotatable, GetDirection() )
        .WillOnce( Return( 1 ) );
    EXPECT_CALL( rotatable, GetAngularVelocity() )
        .WillOnce( Return( -2 ) );
    EXPECT_CALL( rotatable, GetMaxDirections() )
        .WillOnce( Return( boost::none ) );

    RotateCommand cmd(rotatable);
    EXPECT_EQ( cmd.execute(), false );
}
