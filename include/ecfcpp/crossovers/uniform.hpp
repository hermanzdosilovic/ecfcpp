#ifndef ECFCPP_CROSSOVERS_UNIFORM_HPP
#define ECFCPP_CROSSOVERS_UNIFORM_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <cstddef>
#include <iterator>

namespace ecfcpp::crossover
{

class Uniform
{
public:
    constexpr Uniform() noexcept = default;

    template< typename T >
    constexpr Container< T > operator()( T const & mom, T const & dad ) const
    {
        T firstChild { mom };
        T secondChild{ dad };

        for ( std::size_t i{ 0 }; i < std::size( mom.data() ); ++i )
        {
            if ( random::boolean() )
            {
                firstChild .data()[ i ] = dad.data()[ i ];
                secondChild.data()[ i ] = mom.data()[ i ];
            }
        }

        return { firstChild, secondChild };
    }
};

}

#endif // ECFCPP_CROSSOVERS_UNIFORM_HPP
