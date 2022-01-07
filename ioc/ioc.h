#pragma once

#include <ioc/resolve_error.h>
#include <functional>
#include <map>
#include <string>
#include <boost/any.hpp>

/// @brief Вспомогательный тип для вывода типа std::function на основе лямбда-объекта
template < typename T >
struct Identity
{
    using type = T;
};

/// @brief Класс IoC контейнера
class IoC
{
public:
    /// @brief Зарегистрировать стратегию разрешения зависимости
    /// @tparam R Тип возвращаемого значения стратегии разврешения зависимости
    /// @tparam Args Типы параметров стратегии разврешения зависимости
    /// @param name Имя стратегии разрешения зависимости
    /// @param f Стратегия разрешения зависимости
    template< typename R, typename... Args >
    static void Register( const std::string& name, typename Identity< std::function< R( const Args&... ) > >::type f )
    {
        GetCurrentScopeContainer()[ name ] = std::move( f );
    }

    /// @brief Разрешить зависимость (исполнить стратегию)
    /// @tparam R Тип значения зависимости
    /// @tparam Args Типы параметров стратегии разрешения зависимости. Могут не указываться, т.к.
    ///              C++ их может сам вывести по аргументам зависимости
    /// @param name Имя зависимости
    /// @param args Аргументы зависимости (стратегии разрешения зависимости)
    /// @return Значение зависимости
    template< typename R, typename... Args >
    static R Resolve( const std::string& name, const Args&... args )
    {
        try
        {
            Container& container = GetCurrentScopeContainer();
            auto f = boost::any_cast< std::function< R( const Args&... ) > >( container.at( name ) );
            return f( args... );
        }
        catch ( const std::exception& )
        {
            throw ResolveError();
        }
    }

    /// @brief Сделать текущим новый скоуп
    /// @param scopeId Имя скоупа
    /// @note Если скоупа еще не существует, то при переключении на него он будет создан
    static void SwitchToScope( const std::string& scopeId );

protected:
    using Container = std::map< std::string, boost::any >;

    /// @brief Получить IoC контейнер текущего скоупа
    /// @return IoC контейнер текущего скоупа
    static Container& GetCurrentScopeContainer();

private:
    static Container rootContainer_;                                 ///< Контейнер Root скоупа
    thread_local static std::map< std::string, Container > scopes_;  ///< Пользовательские скоупы
};
