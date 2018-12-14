#ifndef ECFCPP_FACTORIES_VECTOR_FACTORY_HPP
#define ECFCPP_FACTORIES_VECTOR_FACTORY_HPP

#include <ecfcpp/chromosomes/vector.hpp>
#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <algorithm>
#include <cstddef>
#include <type_traits>

namespace ecfcpp::factory
{

namespace detail
{

template< typename Population, typename Function >
void initialize( Population & population, Function && initializer )
{
    std::for_each
    (
        std::begin( population ),
        std::end  ( population ),
        [ & initializer ]( auto & individual )
        {
            std::generate( std::begin( individual ), std::end( individual ), initializer );
        }
    );
}

}

template
<
    typename Vector,
    typename Function,
    typename std::enable_if_t< !std::is_same< bool, typename Vector::value_type >::value > * = nullptr
>
Population< Vector > create
(
    Vector const & templateVector,
    std::size_t const size,
    Function && initializer = [](){ return random::normal(); }
)
{
    Population< Vector > population( size, templateVector );
    detail::initialize( population, initializer );
    return population;
}

template
<
    typename Vector,
    typename Function,
    typename std::enable_if_t< std::is_same< bool, typename Vector::value_type >::value > * = nullptr
>
Population< Vector > create
(
    Vector const & templateVector,
    std::size_t const size,
    Function && initializer = [](){ return random::uniform( 0, 10 ) % 2; }
)
{
    Population< Vector > population( size, templateVector );
    detail::initialize( population, initializer );
    return population;
}

}

#endif // ECFCPP_FACTORIES_VECTOR_FACTORY_HPP
