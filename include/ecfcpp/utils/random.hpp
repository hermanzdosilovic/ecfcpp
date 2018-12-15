#ifndef ECFCPP_UTILS_RANDOM_HPP
#define ECFCPP_UTILS_RANDOM_HPP

#ifdef ECFCPP_USE_PCG
#include <pcg_random.hpp>
#endif

#include <algorithm>
#include <random>
#include <type_traits>

namespace ecfcpp
{

namespace random
{

#ifdef ECFCPP_USE_PCG
static pcg32 randomGenerator{ pcg_extras::seed_seq_from< std::random_device >{} };
#else
static std::mt19937 randomGenerator{ std::random_device{}() };
#endif

template< typename T, typename = std::enable_if_t< std::is_floating_point_v< T > > >
inline auto normalDistribution();

template<>
inline auto normalDistribution< float >()
{
    static std::normal_distribution< float > distribution{ 0, 1 };
    return distribution( randomGenerator );
}

template<>
inline auto normalDistribution< double >()
{
    static std::normal_distribution< double > distribution{ 0, 1 };
    return distribution( randomGenerator );
}

template< typename T, typename = std::enable_if_t< std::is_floating_point_v< T > > >
inline auto uniformDistribution();

template<>
inline auto uniformDistribution< float >()
{
    static std::uniform_real_distribution< float > distribution{ 0, 1 };
    return distribution( randomGenerator );
}

template<>
inline auto uniformDistribution< double >()
{
    static std::uniform_real_distribution< double > distribution{ 0, 1 };
    return distribution( randomGenerator );
}

template
<
    typename T = decimal_t,
    typename Decimal = std::conditional_t< std::is_floating_point_v< T >, T, decimal_t >
>
inline T uniform( T const lower = 0, T const upper = 1 ) noexcept
{
    auto const & [ min, max ] = std::minmax( lower, upper );
    return static_cast< T >( min + uniformDistribution< Decimal >() * ( max - min ) );
}

template
<
    typename T = decimal_t,
    typename Decimal = std::conditional_t< std::is_floating_point_v< T >, T, decimal_t >
>
inline T normal( Decimal const mean = 0, Decimal const stddev = 1 ) noexcept
{
    return static_cast< T >( mean + stddev * normalDistribution< Decimal >() );
}

inline bool boolean() noexcept
{
    return uniform( 0, 10 ) % 2;
}

}

}

#endif // ECFCPP_UTILS_RANDOM_HPP
