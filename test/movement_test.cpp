#include "move/move_command.h"
#include <gmock/gmock.h>
#include <stdexcept>

using ::testing::Return;
using ::testing::Throw;

class MockMovable : public IMovable
{
public:
    MOCK_METHOD( Point, GetPosition, (), (const, override) );
    MOCK_METHOD( void, SetPosition, ( const Point& position ), (override) );
    MOCK_METHOD( Point, GetVelocity, (), (const, override) );
};

TEST( MovementTest, MoveSuccessfulTest )
{
    MockMovable movable;
    EXPECT_CALL( movable, GetPosition() )
        .WillOnce( Return( Point(12, 5) ) )
        .WillOnce( Return( Point(5, 8) ) );
    EXPECT_CALL( movable, GetVelocity() )
        .WillOnce( Return( Point(-7, 3) ) );
    EXPECT_CALL( movable, SetPosition( Point(5, 8) ) );

    MoveCommand cmd( movable );
    EXPECT_NO_THROW( cmd.execute() );
    EXPECT_EQ( movable.GetPosition(), Point(5, 8) );
}

TEST( MovementTest, GetPositionErrorTest )
{
    MockMovable movable;
    EXPECT_CALL( movable, GetPosition() )
        .WillRepeatedly( Throw( std::runtime_error("") ) );
    EXPECT_CALL( movable, GetVelocity() )
        .WillRepeatedly( Return( Point(-7, 3) ) );

    MoveCommand cmd(movable);
    EXPECT_THROW( cmd.execute(), MoveError );
}

TEST( MovementTest, GetVelocityErrorTest )
{
    MockMovable movable;
    EXPECT_CALL( movable, GetPosition() )
        .WillRepeatedly( Return( Point(12, 5) ) );
    EXPECT_CALL( movable, GetVelocity() )
        .WillRepeatedly( Throw( std::runtime_error("") ) );

    MoveCommand cmd(movable);
    EXPECT_THROW( cmd.execute(), MoveError );
}

TEST( MovementTest, SetPositionErrorTest )
{
    MockMovable movable;
    EXPECT_CALL( movable, GetPosition() )
        .WillOnce( Return( Point(12, 5) ) );
    EXPECT_CALL( movable, GetVelocity() )
        .WillOnce( Return( Point(-7, 3) ) );
    EXPECT_CALL( movable, SetPosition( Point(5, 8) ) )
        .WillOnce( Throw( std::runtime_error("") ) );

    MoveCommand cmd(movable);
    EXPECT_THROW( cmd.execute(), MoveError );
}
