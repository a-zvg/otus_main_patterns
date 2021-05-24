#include "move.h"
#include <gmock/gmock.h>

using ::testing::Return;

class MockMovable : public IMovable
{
public:
    MOCK_METHOD( boost::optional<Point>, GetPosition, (), (const, override) );
    MOCK_METHOD( void, SetPosition, ( const Point& position ), (override) );
    MOCK_METHOD( boost::optional<Point>, GetVelocity, (), (const, override) );
};

TEST( MovementTest, Test1 )
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

TEST( MovementTest, Test2 )
{
    MockMovable movable;
    EXPECT_CALL( movable, GetPosition() )
        .WillOnce( Return( boost::none ) );

    MoveCommand cmd(movable);
    EXPECT_EQ( cmd.execute(), false );
}

TEST( MovementTest, Test3 )
{
    MockMovable movable;
    EXPECT_CALL( movable, GetPosition() )
        .WillOnce( Return( Point(12, 5) ) );
    EXPECT_CALL( movable, GetVelocity() )
        .WillOnce( Return( boost::none ) );

    MoveCommand cmd(movable);
    EXPECT_EQ( cmd.execute(), false );
}
