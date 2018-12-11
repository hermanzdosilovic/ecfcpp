#ifndef ECFCPP_UTILS_RANDOM_HPP
#define ECFCPP_UTILS_RANDOM_HPP

#include <algorithm>
#include <random>

namespace ecfcpp
{

namespace random
{

static std::random_device randomDevice;
static std::mt19937 randomGenerator{ randomDevice() };
static std::uniform_real_distribution< double > uniformDistribution{ 0, 1 };
static std::normal_distribution< double > normalDistribution{ 0, 1 };

template< typename T = double >
T uniform( T const lower = 0, T const upper = 1 ) noexcept
{
    auto const & [ min, max ] = std::minmax( lower, upper );
    return static_cast< T >( min + uniformDistribution( randomGenerator ) * ( max - min ) );
}

template< typename T = double >
T normal( double const mean = 0, double const stddev = 1 ) noexcept
{
    return static_cast< T >( mean + stddev * normalDistribution( randomGenerator ) );
}

}

}

#endif // ECFCPP_UTILS_RANDOM_HPP
