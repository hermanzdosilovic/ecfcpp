#ifndef ECFCPP_CROSSOVERS_FLAT_HPP
#define ECFCPP_CROSSOVERS_FLAT_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>

namespace ecfcpp::crossover
{

class Flat
{
public:
    constexpr Flat() noexcept = default;

    template< typename T >
    constexpr Container< T > operator()( T const & mom, T const & dad ) const
    {
        T child{ mom };
        for ( std::size_t i{ 0 }; i < std::size( child ); ++i )
        {
            auto const [ min, max ] = std::minmax( mom[ i ], dad[ i ] );
            child[ i ] = random::uniform( min, max );
        }
        return { child };
    }
};

}

#endif // ECFCPP_CROSSOVERS_FLAT_HPP
