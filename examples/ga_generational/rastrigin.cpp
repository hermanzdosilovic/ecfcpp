#include <ecfcpp/ecfcpp.hpp>

#include <cstddef>
#include <iostream>

int main()
{
    constexpr std::size_t numberOfComponents{ 500 };
    constexpr std::size_t populationSize{ 100 };

    constexpr bool        enableElitism{ true };
    constexpr std::size_t maxGenerations{ 1000000 };
    constexpr double      desiredFitness{ 0 };
    constexpr double      precision{ 1e-5 };

    constexpr std::size_t tournamentSize{ 3 };

    constexpr float alpha{ 0.2 };

    constexpr double mutationProbability{ 0.01 };
    constexpr bool   forceMutation{ true };
    constexpr double sigma{ 0.3 };

    using Chromosome = ecfcpp::Vector< float, numberOfComponents >;

    constexpr auto function{ ecfcpp::function::CallCounter{ ecfcpp::function::rastrigin< Chromosome > } };

    auto const result
    {
        ecfcpp::ga::generational
        (
            enableElitism,
            maxGenerations,
            desiredFitness,
            precision,
            ecfcpp::problem::Minimization{ function },
            ecfcpp::selection::Tournament{ tournamentSize },
            ecfcpp::crossover::BlxAlpha{ alpha },
            ecfcpp::mutation::Gaussian{ mutationProbability, forceMutation, sigma },
            ecfcpp::factory::create( Chromosome{ -10, 10 }, populationSize, [](){ return ecfcpp::random::uniform( -10, -5 ); } )
        )
    };

    std::cout << "Found solution in " << function.callCount() << " function evaluations.\n";
    std::cout << "Fitness: " << result.fitness << '\n';

    return 0;
}
