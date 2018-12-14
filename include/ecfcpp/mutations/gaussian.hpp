#ifndef ECFCPP_MUTATIONS_GAUSSIAN_HPP
#define ECFCPP_MUTATIONS_GAUSSIAN_HPP

#include <ecfcpp/utils/random.hpp>

namespace ecfcpp::mutation
{

class Gaussian
{
public:
    constexpr Gaussian
    (
        double const mutationProbability,
        bool   const forceMutation,
        double const sigma
    ) :
        mutationProbability_{ mutationProbability },
        forceMutation_{ forceMutation },
        sigma_{ sigma }
    {}

    template< typename T >
    constexpr T operator()( T const & individual ) const
    {
        T mutant{ individual };
        bool mutationHappened{ false };

        for ( auto & value : mutant )
        {
            if ( random::uniform() < mutationProbability_ )
            {
                mutationHappened = true;
                value += random::normal( 0, sigma_ );
            }
        }

        if ( !mutationHappened && forceMutation_ )
        {
            mutant[ random::uniform( 0UL, std::size( mutant ) ) ] += random::normal( 0, sigma_ );
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
    double mutationProbability_;
    bool   forceMutation_;
    double sigma_;
};

}

#endif // ECFCPP_MUTATIONS_GAUSSIAN_HPP
