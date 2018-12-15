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
        float const mutationProbability,
        bool  const forceMutation,
        float const sigma
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

        for ( auto & value : mutant.data() )
        {
            if ( random::uniform< decltype( mutationProbability_ ) >() < mutationProbability_ )
            {
                mutationHappened = true;
                value += random::normal< typename T::value_type >( 0.0f, sigma_ );
            }
        }

        if ( !mutationHappened && forceMutation_ )
        {
            mutant.data()[ random::uniform( 0UL, std::size( mutant.data() ) ) ] +=
                random::normal< typename T::value_type >( 0.0f, sigma_ );
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
    float sigma_;
};

}

#endif // ECFCPP_MUTATIONS_GAUSSIAN_HPP
