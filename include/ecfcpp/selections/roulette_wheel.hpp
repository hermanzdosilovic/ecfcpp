#ifndef ECFCPP_SELECTIONS_ROULETTE_WHEEL_HPP
#define ECFCPP_SELECTIONS_ROULETTE_WHEEL_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <cmath>
#include <iterator>
#include <numeric>

namespace ecfcpp::selection
{

class RouletteWheel
{
public:
    constexpr RouletteWheel() noexcept = default;

    constexpr RouletteWheel( bool const useFitness ) noexcept : useFitness_{ useFitness } {}

    template< typename T >
    constexpr T const & operator()( Population< T > const & population ) const noexcept
    {
        auto const fitnessSum
        {
            std::accumulate
            (
                std::begin( population ),
                std::end  ( population ),
                static_cast< typename T::decimal_t >( 0 ),
                [ this ]( auto const & current, auto const & individual )
                {
                    return current + std::abs( useFitness_ ? individual.fitness : individual.penalty );
                }
            )
        };

        auto const randomValue{ random::uniform< typename T::decimal_t >() }; 
        typename T::decimal_t cumulativeFitness{ 0 };

        for ( auto const & individual : population )
        {
            cumulativeFitness += std::abs( useFitness_ ? individual.fitness : individual.penalty );
            if ( randomValue < cumulativeFitness / fitnessSum )
            {
                return individual;
            }
        }

        return population.back();
    }

private:
    bool useFitness_{ true };
};

}

#endif // ECFCPP_SELECTIONS_ROULETTE_WHEEL_HPP
