#ifndef ECFCPP_MUTATIONS_COMPOSITE_HPP
#define ECFCPP_MUTATIONS_COMPOSITE_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <vector>

namespace ecfcpp::mutation
{

template< typename T >
class Composite
{
public:
    using Mutation = std::function< T( T const & ) >;

    Composite
    ( 
        std::initializer_list< Mutation > const & mutations
    ) : 
        chooseProbability_{ 1 / static_cast< decltype( chooseProbability_ ) >( std::size( mutations ) ) },
        mutations_{ mutations }
    {}

    T operator()( T const & individual ) const
    {
        for ( auto const & mutation : mutations_ )
        {
            if ( chooseProbability_ < random::uniform< decltype( chooseProbability_ ) >() )
            {
                return mutation( individual );
            }
        }

        return mutations_.back()( individual );
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
    decimal_t chooseProbability_;
    std::vector< Mutation > mutations_;
};

}

#endif // ECFCPP_MUTATIONS_COMPOSITE_HPP
