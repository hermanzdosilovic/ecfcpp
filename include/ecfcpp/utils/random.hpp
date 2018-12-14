#ifndef ECFCPP_UTILS_RANDOM_HPP
#define ECFCPP_UTILS_RANDOM_HPP

#ifdef ECFCPP_USE_PCG
#include <pcg_random.hpp>
#endif

#include <algorithm>
#include <random>

namespace ecfcpp
{

namespace random
{

#ifdef ECFCPP_USE_PCG
static pcg32 randomGenerator{ pcg_extras::seed_seq_from< std::random_device >{} };
#else
static std::mt19937 randomGenerator{ std::random_device{}() };
#endif

static std::uniform_real_distribution< double > uniformDistribution{ 0, 1 };
static std::normal_distribution< double > normalDistribution{ 0, 1 };

template< typename T = double >
inline T uniform( T const lower = 0, T const upper = 1 ) noexcept
{
    auto const & [ min, max ] = std::minmax( lower, upper );
    return static_cast< T >( min + uniformDistribution( randomGenerator ) * ( max - min ) );
}

template< typename T = double >
inline T normal( double const mean = 0, double const stddev = 1 ) noexcept
{
    return static_cast< T >( mean + stddev * normalDistribution( randomGenerator ) );
}

inline bool boolean() noexcept
{
    return uniform( 0, 10 ) % 2;
}

}

}

#endif // ECFCPP_UTILS_RANDOM_HPP
