#ifndef ECFCPP_MUTATIONS_COMPOSITE_HPP
#define ECFCPP_MUTATIONS_COMPOSITE_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

namespace ecfcpp::mutation
{

template< typename T >
class Composite
{
public:
    using Mutation = std::function< T( T const & ) >;
    using MutationDesirability = std::pair< Mutation, std::uint8_t >;

    Composite
    ( 
        std::initializer_list< MutationDesirability > const & mutations
    ) : 
        mutations_{ mutations }
    {
        auto const desirabilitySum
        {
            std::accumulate
            (
                std::begin( mutations_ ),
                std::end  ( mutations_ ),
                static_cast< decimal_t >( 0 ),
                []( auto const & current, auto const & mutation )
                {
                    return current + mutation.second;
                }
            )
        };

        chooseProbability_.reserve( std::size( mutations_ ) );

        for ( auto const & mutation : mutations_ )
        {
            chooseProbability_.emplace_back( mutation.second / desirabilitySum );
        }
    }

    T operator()( T const & individual ) const
    {
        auto const randomValue{ random::uniform< decimal_t >() };
        decimal_t probabilitySum{ 0 };

        for ( auto const & mutation : mutations_ )
        {
            probabilitySum += mutation.second;
            if ( randomValue < probabilitySum )
            {
                return mutation.first( individual );
            }
        }

        return mutations_.back().first( individual );
    }

    Container< T > operator()( Container< T > const & individuals ) const
    {
        Container< T > mutants;
        mutants.reserve( std::size( individuals ) );

        for ( auto const & individual : individuals )
        {
            mutants.emplace_back( ( *this )( individual ) );
        }

        return mutants;
    }

private:
    std::vector< decimal_t > chooseProbability_;
    std::vector< MutationDesirability > mutations_;
};

}

#endif // ECFCPP_MUTATIONS_COMPOSITE_HPP
