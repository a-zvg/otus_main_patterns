#include "common/u_object.h"
#include "common/common_init.h"
#include "ioc/ioc.h"
#include "move/movable_adapter.h"
#include "rotate/rotatable_adapter.h"

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

int count_ = 6; // Общее кол-во инициализируемых объектов
IObjectSP obj_; // Тестовый объект

TEST( InitTest, TestIocRegisterCreateNewEmptyObject )
{
    ASSERT_NO_THROW( IoC::Register<IObjectSP>( "NewObject", []
        {
            return std::make_shared< UObject >();
        } ) );
};

TEST( InitTest, TestCreateNewEmptyObject )
{
    ASSERT_NO_THROW( obj_ = IoC::Resolve<IObjectSP>( "NewObject" ) );
    EXPECT_TRUE( obj_ );
    EXPECT_TRUE( obj_->IsEmpty() );
};

TEST( InitTest, TestIocRegisterSetObjectPosition )
{
    ASSERT_NO_THROW(( IoC::Register<void, IObjectSP>( "SetPosition", [ count = count_ ]( IObjectSP obj )
        {
            static int i = 1; // Счетчик текущего объекта/вызова стратегии

            int x = 0;
            int y = 0;
            if ( i <= (count/2) )
            {
                x = i * 3;
                y = 1;
            }
            else
            {
                x = ( i - (count/2) ) * 3;
                y = 3;
            }

            MovableAdapter adapter( std::move( obj ) );
            adapter.SetPosition( Point( x, y ) );

            ++i;
        } ) ));
}

TEST( InitTest, TestSetObjectPosition )
{
    ASSERT_NO_THROW(( IoC::Resolve<void, IObjectSP>( "SetPosition", obj_ ) ));

    MovableAdapter adapter( obj_ );
    EXPECT_EQ( adapter.GetPosition(), Point( 3, 1 ) );
}

TEST( InitTest, TestIocRegisterSetObjectDirection )
{
    ASSERT_NO_THROW(( IoC::Register<void, IObjectSP>( "SetDirection", [ count = count_ ]( IObjectSP obj )
        {
            static int i = 1; // Счетчик текущего объекта/вызова стратегии

            int direction = 0;
            if ( i <= (count/2) )
            {
                direction = 2;
            }
            else
            {
                direction = 0;
            }

            RotatableAdapter adapter( std::move( obj ) );
            adapter.SetDirection( direction );

            ++i;
        } ) ));
}

TEST( InitTest, TestSetObjectDirection )
{
    ASSERT_NO_THROW(( IoC::Resolve<void, IObjectSP>( "SetDirection", obj_ ) ));

    RotatableAdapter adapter( obj_ );
    EXPECT_EQ( adapter.GetDirection(), 2 );
}

TEST( InitTest, TestCommonInit )
{
    std::vector<std::string> initList = { "SetPosition", "SetDirection" };
    std::vector<IObjectSP> objList;
    ASSERT_NO_THROW( objList = CommonInit( initList, count_-1 ) ); // -1, т.к. в предыдущих тестах первый танк уже был
                                                                   // установлен и проверен, теперь проверяются оставшиеся 5
    int i = 2;
    for ( auto& obj : objList )
    {
        int x = 0;
        int y = 0;
        if ( i <= (count_/2) )
        {
            x = i * 3;
            y = 1;
        }
        else
        {
            x = ( i - (count_/2) ) * 3;
            y = 3;
        }

        MovableAdapter adapter( obj );
        EXPECT_EQ( adapter.GetPosition(), Point( x, y ) );

        ++i;
    }

    i = 2;
    for ( auto& obj : objList )
    {
        int direction = 0;
        if ( i <= (count_/2) )
        {
            direction = 2;
        }
        else
        {
            direction = 0;
        }

        RotatableAdapter adapter( obj );
        EXPECT_EQ( adapter.GetDirection(), direction );

        ++i;
    }
}
