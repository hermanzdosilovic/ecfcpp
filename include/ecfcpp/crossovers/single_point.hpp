#ifndef ECFCPP_CROSSOVERS_SINGLE_POINT_HPP
#define ECFCPP_CROSSOVERS_SINGLE_POINT_HPP

#include <ecfcpp/types.hpp>
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
    constexpr Container< T > operator()( T const & mom, T const & dad ) const
    {
        T firstChild { mom };
        T secondChild{ dad };

        auto const breakPoint{ random::uniform( 0UL, std::size( mom.data() ) ) };

        for ( std::size_t i{ 0 }; i < breakPoint; ++i )
        {
            firstChild .data()[ i ] = dad.data()[ i ];
            secondChild.data()[ i ] = mom.data()[ i ];
        }

        return { firstChild, secondChild };
    }
};

}

#endif // ECFCPP_CROSSOVERS_SINGLE_POINT_HPP
