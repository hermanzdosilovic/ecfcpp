#ifndef ECFCPP_FUNCTIONS_FUNCTIONS_HPP
#define ECFCPP_FUNCTIONS_FUNCTIONS_HPP

#include <ecfcpp/constants.hpp>
#include <ecfcpp/types.hpp>

#include <cmath>
#include <cstdint>
#include <iterator>
#include <type_traits>

namespace ecfcpp::function
{

template< typename Function >
class CallCounter
{
public:
    constexpr CallCounter( Function  & function ) : function_{ function } {}
    constexpr CallCounter( Function && function ) : function_{ function } {}

    template< typename Point >
    [[ nodiscard ]] constexpr auto operator()( Point const & p ) const noexcept
    {
        ++callCounter_;
        return function_( p );
    }

    constexpr inline auto callCount() const noexcept { return callCounter_; }

private:
    Function & function_;
    mutable std::uint64_t callCounter_{};
};

// http://benchmarkfcns.xyz/benchmarkfcns/ackleyfcn.html
template< typename Point, typename Decimal = decimal_t, typename = std::enable_if_t< std::is_same_v< typename Point::value_type, Decimal > > >
[[ nodiscard ]] constexpr auto ackley( Decimal const a = 20, Decimal const b = 0.2, Decimal const c = constant::tau< Decimal >() ) noexcept
{
    return
    [ a, b, c ]
    ( Point const & p ) constexpr -> Decimal
    {
        Decimal clause1{ 0 }, clause2{ 0 };
        for ( auto const & x : p )
        {
            clause1 += x * x;
            clause2 += std::cos( c * x );
        }

        clause1 = -1 * b * std::sqrt( clause1 / std::size( p ) );
        clause2 /= std::size( p );

        return -1 * a * std::exp( clause1 ) - exp( clause2 ) + a + constant::e< Decimal >();
    };
}

// http://benchmarkfcns.xyz/benchmarkfcns/ackleyn4fcn.html
template< typename Point, typename Decimal = decimal_t, typename = std::enable_if_t< std::is_same_v< typename Point::value_type, Decimal > > >
[[ nodiscard ]] constexpr Decimal ackleyn4( Point const & p ) noexcept
{
    constexpr auto e02{ std::exp( static_cast< Decimal >( -0.2 ) ) };

    Decimal result{ 0 };
    for ( std::size_t i{ 0 }; i < std::size( p ) - 1; ++i )
    {
        result += e02 * std::hypot( p[ i ], p[ i + 1 ] ) + 3 * ( std::cos( 2 * p[ i ] ) + std::sin( 2 * p[ i + 1 ] ) );
    }

    return result;
}

// http://benchmarkfcns.xyz/benchmarkfcns/alpinen1fcn.html
template< typename Point, typename Decimal = decimal_t, typename = std::enable_if_t< std::is_same_v< typename Point::value_type, Decimal > > >
[[ nodiscard ]] constexpr Decimal alpinen1( Point const & p ) noexcept
{
    Decimal result{ 0 };
    for ( auto const & x : p )
    {
        result += std::abs( x * std::sin( x ) + 0.1 * x );
    }
    return result;
}


// http://benchmarkfcns.xyz/benchmarkfcns/alpinen2fcn.html
template< typename Point, typename Decimal = decimal_t, typename = std::enable_if_t< std::is_same_v< typename Point::value_type, Decimal > > >
[[ nodiscard ]] constexpr Decimal alpinen2( Point const & p ) noexcept
{
    Decimal result{ 1 };
    for ( auto const & x : p )
    {
        result *= std::sqrt( x ) * std::sin( x );
    }
    return result;
}


// http://benchmarkfcns.xyz/benchmarkfcns/exponentialfcn.html
template< typename Point, typename Decimal = decimal_t, typename = std::enable_if_t< std::is_same_v< typename Point::value_type, Decimal > > >
[[ nodiscard ]] constexpr Decimal exponential( Point const & p ) noexcept
{
    Decimal result{ 0 };
    for ( auto const & x : p )
    {
        result += x * x;
    }
    return -1 * std::exp( -0.5 * result );
}

// http://benchmarkfcns.xyz/benchmarkfcns/griewankfcn.html
template< typename Point, typename Decimal = decimal_t, typename = std::enable_if_t< std::is_same_v< typename Point::value_type, Decimal > > >
[[ nodiscard ]] constexpr Decimal griewank( Point const & p ) noexcept
{
    Decimal clause1{ 0 }, clause2{ 1 };

    std::size_t i{ 0 };
    for ( auto const & x : p )
    {
        clause1 += x * x;
        clause2 *= std::cos( x / std::sqrt( static_cast< Decimal >( i ) ) );
        ++i;
    }

    clause1 /= 4000;

    return 1 + clause1 - clause2;
}

// http://benchmarkfcns.xyz/benchmarkfcns/rastriginfcn.html
template< typename Point, typename Decimal = decimal_t, typename = std::enable_if_t< std::is_same_v< typename Point::value_type, Decimal > > >
[[ nodiscard ]] constexpr Decimal rastrigin( Point const & p ) noexcept
{
    Decimal result{ 10 * std::size( p ) };
    for ( auto const & x : p )
    {
        result += x * x - 10 * std::cos( constant::tau< Decimal >() * x );
    }
    return result;
}

}

#endif // ECFCPP_FUNCTIONS_FUNCTIONS_HPP
