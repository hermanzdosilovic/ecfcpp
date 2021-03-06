#ifndef ECFCPP_CROSSOVERS_COMPOSITE_HPP
#define ECFCPP_CROSSOVERS_COMPOSITE_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <vector>

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
        chooseProbability_{ 1.0f / std::size( crossovers ) },
        crossovers_{ crossovers }
    {}

    Container< T > operator()( T const & mom, T const & dad ) const
    {
        for ( auto const & crossover : crossovers_ )
        {
            if ( chooseProbability_ < random::uniform< decimal_t >() )
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
