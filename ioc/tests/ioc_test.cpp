#include <ioc/src/ioc.h>
#include <gmock/gmock.h>
#include <memory>
#include <mutex>

TEST( IocTest, TestNonexistenStrategy )
{
    EXPECT_THROW( IoC::Resolve<double>("Get"), ResolveError );
    EXPECT_THROW( IoC::Resolve<int>("GetSome"), ResolveError );
}

TEST( IocTest, TestStrategyWithoutArguments )
{
    // Тест с простым типом возвращаемого значения
    EXPECT_NO_THROW( IoC::Register<int>( "GetInt", []{ return 10; } ) );

    int i = 0;
    EXPECT_NO_THROW( i = IoC::Resolve<int>( "GetInt" ) );
    EXPECT_EQ( i, 10 );

    // Тест с пользовательским типом возвращаемого значения, созданного в куче
    class A
    {
    public:
        int testValue_ = 1;
    };

    EXPECT_NO_THROW( IoC::Register< std::unique_ptr<A> >( "GetA", []{ return std::make_unique<A>(); } ) );

    std::unique_ptr<A> a;
    EXPECT_NO_THROW( a = IoC::Resolve< std::unique_ptr<A> >( "GetA" ) );
    EXPECT_EQ( a->testValue_, 1 );
}

TEST( IocTest, TestStrategyWithArguments )
{
    // Тест с простым типом возвращаемого значения, инициализированным значением переданного аргумента
    EXPECT_NO_THROW(( IoC::Register<int, int>( "GetInt", []( int i ){ return i; } ) ));

    int i = 0;
    EXPECT_NO_THROW(( i = IoC::Resolve<int, int>( "GetInt", 5 ) ));
    EXPECT_EQ( i, 5 );

    // Тест с пользовательским типом возвращаемого значения, созданного в куче на основе значения переданного аргумента
    class A
    {
    public:
        A( int i ) : testValue_( i )
        {
        }

        int testValue_ = 0;
    };

    EXPECT_NO_THROW(( IoC::Register< std::unique_ptr<A>, int >( "GetA", []( int i ){ return std::make_unique<A>( i ); } ) ));

    std::unique_ptr<A> a;
    EXPECT_NO_THROW(( a = IoC::Resolve< std::unique_ptr<A>, int >( "GetA", 1 ) ));
    EXPECT_EQ( a->testValue_, 1 );
}

TEST( IocTest, TestSigletonStrategy )
{
    class Singleton
    {
    public:
        int testValue_ = 2;
    };

    IoC::Register< std::shared_ptr<Singleton> >( "GetSingleton", []
            {
                static std::shared_ptr< Singleton > instance;
                static std::once_flag onceFlag; // Защита для многопоточной инициализации синглетона
                std::call_once( onceFlag, []
                    {
                        instance = std::make_shared< Singleton >();
                    } );
                return instance;
            } );

    {
        auto s = IoC::Resolve< std::shared_ptr<Singleton> >( "GetSingleton" );
        EXPECT_EQ( s->testValue_, 2 );
        s->testValue_ = 3;
    }
    {
        auto s = IoC::Resolve< std::shared_ptr<Singleton> >( "GetSingleton" );
        EXPECT_EQ( s->testValue_, 3 );
    }
}
