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
    constexpr BlxAlpha( float const alpha ) noexcept : alpha_{ alpha } {}

    template< typename T >
    constexpr Container< T > operator()( T const & mom, T const & dad ) const
    {
        T child{ mom };
        for ( std::size_t i{ 0 }; i < std::size( child.data() ); ++i )
        {
            auto const [ cmin, cmax ] = std::minmax( mom.data()[ i ], dad.data()[ i ] );
            auto const interval{ ( cmax - cmin ) * ( 1 - 2 * alpha_ ) };
            child.data()[ i ] = cmin - ( cmax - cmin ) * alpha_ + interval * random::uniform();
        }
        return { child };
    }

private:
    float alpha_;
};

}

#endif // ECFCPP_CROSSOVERS_BLX_ALPHA_HPP
