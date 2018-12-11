#ifndef ECFCPP_FUNCTIONS_FUNCTIONS_HPP
#define ECFCPP_FUNCTIONS_FUNCTIONS_HPP

#include <ecfcpp/constants.hpp>

#include <cmath>
#include <cstdint>
#include <iterator>

namespace ecfcpp::function
{

template< typename Function >
class CallCounter
{
public:
    constexpr CallCounter( Function & function ) : function_{ function } {}

    template< typename Point >
    [[ nodiscard ]] constexpr double operator()( Point const & p ) const noexcept
    {
        ++callCounter_;
        return function_( p );
    }

    constexpr inline auto callCount() const noexcept { return callCounter_; }

private:
    Function & function_;
    mutable std::uint64_t callCounter_{ 0 };
};

// http://benchmarkfcns.xyz/benchmarkfcns/ackleyfcn.html
template< typename Point >
[[ nodiscard ]] constexpr auto ackley( double const a = 20, double const b = 0.2, double const c = constant::tau ) noexcept
{
    return
    [ a, b, c ]
    ( Point const & p ) -> double
    {
        double clause1{ 0 }, clause2{ 0 };
        for ( auto const & x : p )
        {
            clause1 += std::pow( x, 2 );
            clause2 += std::cos( c * x );
        }

        clause1 = -1 * b * std::sqrt( clause1 / std::size( p ) );
        clause2 /= std::size( p );

        return -1 * a * std::exp( clause1 ) - exp( clause2 ) + a + constant::e;
    };
}

// http://benchmarkfcns.xyz/benchmarkfcns/ackleyn4fcn.html
template< typename Point >
[[ nodiscard ]] constexpr double ackleyn4( Point const & p ) noexcept
{
    constexpr double e02{ std::exp( -0.2 ) };

    double result{ 0 };
    for ( decltype( std::size( p ) ) i{ 0 }; i < std::size( p ) - 1; ++i )
    {
        result += e02 * std::hypot( p[ i ], p[ i + 1 ] ) + 3 * ( std::cos( 2 * p[ i ] ) + std::sin( 2 * p[ i + 1 ] ) );
    }

    return result;
}

// http://benchmarkfcns.xyz/benchmarkfcns/alpinen1fcn.html
template< typename Point >
[[ nodiscard ]] constexpr double alpinen1( Point const & p ) noexcept
{
    double result{ 0 };
    for ( auto const & x : p )
    {
        result += std::abs( x * std::sin( x ) + 0.1 * x );
    }
    return result;
}


// http://benchmarkfcns.xyz/benchmarkfcns/alpinen2fcn.html
template< typename Point >
[[ nodiscard ]] constexpr double alpinen2( Point const & p ) noexcept
{
    double result{ 1 };
    for ( auto const & x : p )
    {
        result *= std::sqrt( x ) * std::sin( x );
    }
    return result;
}


// http://benchmarkfcns.xyz/benchmarkfcns/exponentialfcn.html
template< typename Point >
[[ nodiscard ]] constexpr double exponential( Point const & p ) noexcept
{
    double result{ 0 };
    for ( auto const & x : p )
    {
        result += std::pow( x, 2 );
    }
    return -1 * std::exp( -0.5 * result );
}

// http://benchmarkfcns.xyz/benchmarkfcns/griewankfcn.html
template< typename Point >
[[ nodiscard ]] constexpr double griewank( Point const & p ) noexcept
{
    double clause1{ 0 }, clause2{ 1 };

    decltype( std::size( p ) ) i{ 0 };
    for ( auto const & x : p )
    {
        clause1 += std::pow( x, 2 );
        clause2 *= std::cos( x / std::sqrt( static_cast< double >( i ) ) );
        ++i;
    }

    clause1 /= 4000;

    return 1 + clause1 - clause2;
}

// http://benchmarkfcns.xyz/benchmarkfcns/rastriginfcn.html
template< typename Point >
[[ nodiscard ]] constexpr double rastrigin( Point const & p ) noexcept
{
    double result{ 10 * std::size( p ) };
    for ( auto const & x : p )
    {
        result += std::pow( x, 2 ) - 10 * std::cos( constant::tau * x );
    }
    return result;
}

}

#endif // ECFCPP_FUNCTIONS_FUNCTIONS_HPP
