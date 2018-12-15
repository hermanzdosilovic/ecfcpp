#ifndef ECFCPP_FACTORIES_VECTOR_FACTORY_HPP
#define ECFCPP_FACTORIES_VECTOR_FACTORY_HPP

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
            std::generate( std::begin( individual.data() ), std::end( individual.data() ), initializer );
        }
    );
}

}

template
<
    typename Container,
    typename Function,
    typename std::enable_if_t< !std::is_same< bool, typename Container::value_type >::value > * = nullptr
>
Population< Container > create
(
    Container const & templateContainer,
    std::size_t const size,
    Function && initializer = [](){ return random::normal< typename Container::value_type >(); }
)
{
    Population< Container > population( size, templateContainer );
    detail::initialize( population, initializer );
    return population;
}

template
<
    typename Container,
    typename Function,
    typename std::enable_if_t< std::is_same< bool, typename Container::value_type >::value > * = nullptr
>
Population< Container > create
(
    Container const & templateContainer,
    std::size_t const size,
    Function && initializer = [](){ return random::boolean(); }
)
{
    Population< Container > population( size, templateContainer );
    detail::initialize( population, initializer );
    return population;
}

}

#endif // ECFCPP_FACTORIES_VECTOR_FACTORY_HPP
