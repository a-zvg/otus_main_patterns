#include <ioc/ioc.h>
#include <gmock/gmock.h>
#include <future>
#include <thread>

TEST( IocMtTest, TestScopes )
{
    // Регистрация стратегии GetInt в Root споупе
    EXPECT_NO_THROW( IoC::Register<int>( "GetInt", []{ return 10; } ) );

    // Регистрация и проверка стратегии GetInt в NewScope споупе
    EXPECT_NO_THROW( IoC::SwitchToScope( "NewScope" ) );
    EXPECT_NO_THROW( IoC::Register<int>( "GetInt", []{ return 5; } ) );

    int i = 0;
    EXPECT_NO_THROW( i = IoC::Resolve<int>( "GetInt" ) );
    EXPECT_EQ( i, 5 );

    // Проверка стратегии GetInt в Root споупе
    EXPECT_NO_THROW( IoC::SwitchToScope( "Root" ) );

    EXPECT_NO_THROW( i = IoC::Resolve<int>( "GetInt" ) );
    EXPECT_EQ( i, 10 );
}

TEST( IocMtTest, TestMtScopes )
{
    std::promise<void> p; // Альтернативный условным переменным C++ способ синхронизации потоков
    std::future<void> f = p.get_future();

    std::thread t1( [ f = std::move( f ) ]
        {
            // Регистрация и проверка стратегии GetInt в NewScope споупе потока 1
            EXPECT_NO_THROW( IoC::SwitchToScope( "NewScope" ) );
            EXPECT_NO_THROW( IoC::Register<int>( "GetInt", []{ return 5; } ) );

            f.wait(); // Ожидание когда поток 2 зарегистрирует аналогичную стратегию в одноименном скоупе

            int i = 0;
            EXPECT_NO_THROW( i = IoC::Resolve<int>( "GetInt" ) );
            EXPECT_EQ( i, 5 );
        } );

    std::thread t2( [ p = std::move( p ) ]() mutable
        {
            // Регистрация и проверка стратегии GetInt в NewScope споупе потока 2
            EXPECT_NO_THROW( IoC::SwitchToScope( "NewScope" ) );
            EXPECT_NO_THROW( IoC::Register<int>( "GetInt", []{ return 15; } ) );

            p.set_value(); // К этому моменту в потоке 1 и 2 одновременно зарегистрированы одноименные стратегии в одноименных скоупах

            int i = 0;
            EXPECT_NO_THROW( i = IoC::Resolve<int>( "GetInt" ) );
            EXPECT_EQ( i, 15 );
        } );

    t2.join();
    t1.join();
}
