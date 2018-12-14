#ifndef ECFCPP_CROSSOVERS_SINGLE_POINT_HPP
#define ECFCPP_CROSSOVERS_SINGLE_POINT_HPP

#include <ecfcpp/utils/random.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>

namespace ecfcpp::crossover
{

class SinglePoint
{
public:
    constexpr SinglePoint() noexcept = default;

    template< typename T >
    constexpr T operator()( T const & mom, T const & dad ) const
    {
        T child{ mom };
        auto const breakPoint{ random::uniform( 0UL, std::size( child ) ) };

        for ( std::size_t i{ 0 }; i < breakPoint; ++i )
        {
            child[ i ] = mom[ i ];
        }

        for ( auto i{ breakPoint }; i < std::size( child ); ++i )
        {
            child[ i ] = dad[ i ];
        }

        return child;
    }
};

}

#endif // ECFCPP_CROSSOVERS_SINGLE_POINT_HPP
