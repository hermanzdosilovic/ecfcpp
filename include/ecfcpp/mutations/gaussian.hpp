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
    constexpr T & operator()( T & individual ) const noexcept
    {
        bool mutationHappened{ false };

        for ( auto & value : individual )
        {
            if ( random::uniform() < mutationProbability_ )
            {
                mutationHappened = true;
                value += random::normal( 0, sigma_ );
            }
        }

        if ( !mutationHappened && forceMutation_ )
        {
            individual[ random::uniform( 0UL, std::size( individual ) ) ] += random::normal( 0, sigma_ );
        }

        return individual;
    }

private:
    double mutationProbability_;
    bool   forceMutation_;
    double sigma_;
};

}

#endif // ECFCPP_MUTATIONS_GAUSSIAN_HPP
