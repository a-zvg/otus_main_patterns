#include "rotate/rotate_command.h"
#include <gmock/gmock.h>
#include <stdexcept>

using ::testing::Return;
using ::testing::Throw;

class MockRotatable : public IRotatable
{
public:
     MOCK_METHOD( int, GetDirection, (), (const, override) );
     MOCK_METHOD( void, SetDirection, ( int direction ), (override) );
     MOCK_METHOD( int, GetAngularVelocity, (), (const, override) );
     MOCK_METHOD( int, GetMaxDirections, (), (const, override) );
};

TEST( RotatingTest, RotateSuccessfulTest )
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

TEST( RotatingTest, GetDirectionErrorTest )
{
    MockRotatable rotatable;
    EXPECT_CALL( rotatable, GetDirection() )
        .WillRepeatedly( Throw( std::runtime_error("") ) );
    EXPECT_CALL( rotatable, GetAngularVelocity() )
        .WillRepeatedly( Return( -2 ) );
    EXPECT_CALL( rotatable, GetMaxDirections() )
        .WillRepeatedly( Return( 4 ) );

    RotateCommand cmd(rotatable);
    EXPECT_THROW( cmd.execute(), RotateError );
}

TEST( RotatingTest, GetAngularVelocityErrorTest )
{
    MockRotatable rotatable;
    EXPECT_CALL( rotatable, GetDirection() )
        .WillRepeatedly( Return( 1 ) );
    EXPECT_CALL( rotatable, GetAngularVelocity() )
        .WillRepeatedly( Throw( std::runtime_error("") ) );
    EXPECT_CALL( rotatable, GetMaxDirections() )
        .WillRepeatedly( Return( 4 ) );

    RotateCommand cmd(rotatable);
    EXPECT_THROW( cmd.execute(), RotateError );
}

TEST( RotatingTest, GetMaxDirectionsErrorTest )
{
    MockRotatable rotatable;
    EXPECT_CALL( rotatable, GetDirection() )
        .WillRepeatedly( Return( 1 ) );
    EXPECT_CALL( rotatable, GetAngularVelocity() )
        .WillRepeatedly( Return( -2 ) );
    EXPECT_CALL( rotatable, GetMaxDirections() )
        .WillRepeatedly( Throw( std::runtime_error("") ) );

    RotateCommand cmd(rotatable);
    EXPECT_THROW( cmd.execute(), RotateError );
}

TEST( RotatingTest, SetDirectionErrorTest )
{
    MockRotatable rotatable;
    EXPECT_CALL( rotatable, GetDirection() )
        .WillOnce( Return( 1 ) );
    EXPECT_CALL( rotatable, GetAngularVelocity() )
        .WillOnce( Return( -2 ) );
    EXPECT_CALL( rotatable, GetMaxDirections() )
        .WillOnce( Return( 4 ) );
    EXPECT_CALL( rotatable, SetDirection( 3 ) )
        .WillOnce( Throw( std::runtime_error("") ) );

    RotateCommand cmd(rotatable);
    EXPECT_THROW( cmd.execute(), RotateError );
}
