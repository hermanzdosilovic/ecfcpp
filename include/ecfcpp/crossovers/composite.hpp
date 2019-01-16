#ifndef ECFCPP_CROSSOVERS_COMPOSITE_HPP
#define ECFCPP_CROSSOVERS_COMPOSITE_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <any>
#include <cstddef>
#include <functional>
#include <iterator>
#include <vector>
#include <initializer_list>

namespace ecfcpp::crossover
{

template< typename T >
class Composite
{
public:
    using Crossover = std::function< Container< T >( T const &, T const & ) >;

    Composite
    ( 
        std::initializer_list< Crossover > const & crossovers
    ) : 
        chooseProbability_{ 1 / static_cast< decltype( chooseProbability_ ) >( std::size( crossovers ) ) },
        crossovers_{ crossovers }
    {}

    Container< T > operator()( T const & mom, T const & dad ) const
    {
        for ( auto const & crossover : crossovers_ )
        {
            if ( chooseProbability_ < random::uniform< decltype( chooseProbability_ ) >() )
            {
                return crossover( mom, dad );
            }
        }

        return crossovers_.back()( mom, dad );
    }

private:
    decimal_t chooseProbability_;
    std::vector< Crossover > crossovers_;
};

}

#endif // ECFCPP_CROSSOVERS_COMPOSITE_HPP
