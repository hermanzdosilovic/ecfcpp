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
    constexpr CallCounter( Function function ) : function_{ function } {}

    constexpr CallCounter( CallCounter const & other ) = default;
    constexpr CallCounter( CallCounter && other ) = default;

    template< typename Point >
    [[ nodiscard ]] constexpr auto operator()( Point const & p ) const noexcept
    {
        ++callCounter_;
        return function_( p );
    }

    constexpr inline auto callCount() const noexcept { return callCounter_; }

private:
    Function function_;
    mutable std::uint64_t callCounter_{};
};

// http://benchmarkfcns.xyz/benchmarkfcns/ackleyfcn.html
template
<
    typename Point,
    typename Decimal = std::conditional_t< std::is_floating_point_v< typename Point::value_type >, typename Point::value_type, decimal_t >,
    typename = std::enable_if_t< std::is_arithmetic_v< typename Point::value_type > >
>
[[ nodiscard ]] constexpr auto ackley( Decimal const a = 20, Decimal const b = 0.2, Decimal const c = constant::tau< Decimal >() ) noexcept
{
    return
    [ a, b, c ]
    ( Point const & p ) constexpr -> Decimal
    {
        Decimal clause1{ 0 }, clause2{ 0 };
        for ( auto const & x : p )
        {
            auto const v{ static_cast< Decimal >( x ) };
            clause1 += v * v;
            clause2 += std::cos( c * v );
        }

        clause1 = -1 * b * std::sqrt( clause1 / std::size( p ) );
        clause2 /= std::size( p );

        return -1 * a * std::exp( clause1 ) - exp( clause2 ) + a + constant::e< Decimal >();
    };
}

// http://benchmarkfcns.xyz/benchmarkfcns/ackleyn4fcn.html
template
<
    typename Point,
    typename Decimal = std::conditional_t< std::is_floating_point_v< typename Point::value_type >, typename Point::value_type, decimal_t >,
    typename = std::enable_if_t< std::is_arithmetic_v< typename Point::value_type > >
>
[[ nodiscard ]] constexpr Decimal ackleyn4( Point const & p ) noexcept
{
    constexpr auto e02{ std::exp( static_cast< Decimal >( -0.2 ) ) };

    Decimal result{ 0 };
    for ( std::size_t i{ 0 }; i < std::size( p ) - 1; ++i )
    {
        auto const x{ static_cast< Decimal >( p[ i     ] ) };
        auto const y{ static_cast< Decimal >( p[ i + 1 ] ) };

        result += e02 * std::hypot( x, y ) + 3 * ( std::cos( 2 * x ) + std::sin( 2 * y ) );
    }

    return result;
}

// http://benchmarkfcns.xyz/benchmarkfcns/alpinen1fcn.html
template
<
    typename Point,
    typename Decimal = std::conditional_t< std::is_floating_point_v< typename Point::value_type >, typename Point::value_type, decimal_t >,
    typename = std::enable_if_t< std::is_arithmetic_v< typename Point::value_type > >
>
[[ nodiscard ]] constexpr Decimal alpinen1( Point const & p ) noexcept
{
    Decimal result{ 0 };
    for ( auto const & x : p )
    {
        auto const v{ static_cast< Decimal >( x ) };
        result += std::abs( v * std::sin( v ) + 0.1 * v );
    }
    return result;
}


// http://benchmarkfcns.xyz/benchmarkfcns/alpinen2fcn.html
template
<
    typename Point,
    typename Decimal = std::conditional_t< std::is_floating_point_v< typename Point::value_type >, typename Point::value_type, decimal_t >,
    typename = std::enable_if_t< std::is_arithmetic_v< typename Point::value_type > >
>
[[ nodiscard ]] constexpr Decimal alpinen2( Point const & p ) noexcept
{
    Decimal result{ 1 };
    for ( auto const & x : p )
    {
        auto const v{ static_cast< Decimal >( x ) };
        result *= std::sqrt( v ) * std::sin( v );
    }
    return result;
}


// http://benchmarkfcns.xyz/benchmarkfcns/exponentialfcn.html
template
<
    typename Point,
    typename Decimal = std::conditional_t< std::is_floating_point_v< typename Point::value_type >, typename Point::value_type, decimal_t >,
    typename = std::enable_if_t< std::is_arithmetic_v< typename Point::value_type > >
>
[[ nodiscard ]] constexpr Decimal exponential( Point const & p ) noexcept
{
    Decimal result{ 0 };
    for ( auto const & x : p )
    {
        auto const v{ static_cast< Decimal >( x ) };
        result += v * v;
    }
    return -1 * std::exp( -0.5 * result );
}

// http://benchmarkfcns.xyz/benchmarkfcns/griewankfcn.html
template
<
    typename Point,
    typename Decimal = std::conditional_t< std::is_floating_point_v< typename Point::value_type >, typename Point::value_type, decimal_t >,
    typename = std::enable_if_t< std::is_arithmetic_v< typename Point::value_type > >
>
[[ nodiscard ]] constexpr Decimal griewank( Point const & point ) noexcept
{
    Decimal clause1{ 0 }, clause2{ 1 };

    std::size_t i{ 0 };
    for ( auto const & x : point )
    {
        auto const v{ static_cast< Decimal >( x ) };

        clause1 += v * v;
        clause2 *= std::cos( v / std::sqrt( static_cast< Decimal >( i ) ) );

        ++i;
    }

    clause1 /= 4000;

    return 1 + clause1 - clause2;
}

// http://benchmarkfcns.xyz/benchmarkfcns/rastriginfcn.html
template
<
    typename Point,
    typename Decimal = std::conditional_t< std::is_floating_point_v< typename Point::value_type >, typename Point::value_type, decimal_t >,
    typename = std::enable_if_t< std::is_arithmetic_v< typename Point::value_type > >
>
[[ nodiscard ]] constexpr Decimal rastrigin( Point const & point ) noexcept
{
    Decimal result{ 10 * std::size( point ) };
    for ( auto const & x : point )
    {
        auto const v{ static_cast< Decimal >( x ) };
        result += v * v - 10 * std::cos( constant::tau< Decimal >() * v );
    }
    return result;
}

// http://benchmarkfcns.xyz/benchmarkfcns/rosenbrockfcn.html
template
<
    typename Point,
    typename Decimal = std::conditional_t< std::is_floating_point_v< typename Point::value_type >, typename Point::value_type, decimal_t >,
    typename = std::enable_if_t< std::is_arithmetic_v< typename Point::value_type > >
>
[[ nodiscard ]] constexpr auto rosenbrock( Decimal const a = 1, Decimal const b = 100 ) noexcept
{
    return
    [ a, b ]
    ( Point const & point ) constexpr -> Decimal
    {
        Decimal result{ 0 };
        for ( std::size_t i{ 0 }; i < std::size( point ) - 1; ++i )
        {
            auto const x{ static_cast< Decimal >( point[ i     ] ) };
            auto const y{ static_cast< Decimal >( point[ i + 1 ] ) };
            result += b * ( y - x * x ) * ( y - x * x ) + ( a - x ) * ( a - x );
        }
        return result;
    };
}

}

#endif // ECFCPP_FUNCTIONS_FUNCTIONS_HPP
