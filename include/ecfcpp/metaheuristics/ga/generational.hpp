#ifndef ECFCPP_METAHEURISTICS_GA_GENERATIONAL_HPP
#define ECFCPP_METAHEURISTICS_GA_GENERATIONAL_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>

namespace ecfcpp::ga
{

template< typename Problem, typename Selection, typename Crossover, typename Mutation, typename Population >
[[ nodiscard ]] constexpr auto generational
(
    bool        const   useElitism,
    std::size_t const   maxGenerations,
    double      const   desiredFitness,
    double      const   precision,
    Problem     const & problem,
    Selection   const & selection,
    Crossover   const & crossover,
    Mutation    const & mutation,
    Population  const & initialPopulation
)
{
    auto population{ initialPopulation };
    auto nextPopulation{ initialPopulation };

    for ( std::size_t i{ 0 }; i < maxGenerations; ++i )
    {
        problem.evaluate( population );

        auto const & best{ *std::max_element( std::begin( population ), std::end( population ) ) };

        //std::cout << best.fitness << '\n';
        if ( std::abs( best.fitness - desiredFitness ) < precision )
        {
            return best;
        }

        if ( useElitism )
        {
            nextPopulation[ 0 ] = best;
        }

        for ( std::size_t j{ useElitism ? 1UL : 0UL }; j < std::size( population ); ++j )
        {
            nextPopulation[ j ] =
                mutation
                (
                    crossover
                    (
                        selection( population ),
                        selection( population )
                    )[ 0 ]
                );
        }

        std::swap( population, nextPopulation );
    }

    problem.evaluate( population );
    return *std::max_element( std::begin( population ), std::end( population ) );
}

}

#endif // ECFCPP_METAHEURISTICS_GA_GENERATIONAL_HPP
