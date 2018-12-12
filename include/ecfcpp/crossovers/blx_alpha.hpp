#ifndef ECFCPP_CROSSOVERS_BLX_ALPHA_HPP
#define ECFCPP_CROSSOVERS_BLX_ALPHA_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>

namespace ecfcpp::crossover
{

class BlxAlpha
{
public:
    constexpr BlxAlpha( double const alpha ) noexcept : alpha_{ alpha } {}

    template< typename T >
    constexpr T operator()( T const & mom, T const & dad ) const
    {
        T child{ mom };
        for ( std::size_t i{ 0 }; i < std::size( child ); ++i )
        {
            auto const [ cmin, cmax ] = std::minmax( mom[ i ], dad[ i ] );
            auto const interval{ ( cmax - cmin ) * ( 1 - 2 * alpha_ ) };
            child[ i ] = cmin - ( cmax - cmin ) * alpha_ + interval * random::uniform();
        }
        return child;
    }

private:
    double alpha_;
};

}

#endif // ECFCPP_CROSSOVERS_BLX_ALPHA_HPP
