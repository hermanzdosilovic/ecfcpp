#ifndef ECFCPP_MUTATIONS_BIT_FLIP_HPP
#define ECFCPP_MUTATIONS_BIT_FLIP_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

namespace ecfcpp::mutation
{

class BitFlip
{
public:
    constexpr BitFlip
    (
        float  const mutationProbability,
        bool   const forceMutation
    ) :
        mutationProbability_{ mutationProbability },
        forceMutation_{ forceMutation }
    {}

    template< typename T >
    constexpr T operator()( T const & individual ) const
    {
        T mutant{ individual };
        bool mutationHappened{ false };

        for ( auto & value : mutant.data() )
        {
            if ( random::uniform< decltype( mutationProbability_ ) >() < mutationProbability_ )
            {
                mutationHappened = true;
                value = !value;
            }
        }

        if ( !mutationHappened && forceMutation_ )
        {
            auto const randIndex{ random::uniform( 0UL, std::size( mutant.data() ) ) };
            mutant.data()[ randIndex ] = !mutant.data()[ randIndex ];
        }

        return mutant;
    }

    template< typename T >
    constexpr Container< T > operator()( Container< T > const & individuals ) const
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
    float mutationProbability_;
    bool  forceMutation_;
};

}

#endif // ECFCPP_MUTATIONS_GAUSSIAN_HPP
