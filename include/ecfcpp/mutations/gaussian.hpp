#ifndef ECFCPP_MUTATIONS_GAUSSIAN_HPP
#define ECFCPP_MUTATIONS_GAUSSIAN_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <cstdint>
#include <iterator>

namespace ecfcpp::mutation
{

class Gaussian
{
public:

    enum class Type : std::uint8_t
    {
        Set,
        Add
    };

    constexpr Gaussian
    (
        decimal_t const mutationProbability,
        bool      const forceMutation,
        decimal_t const sigma,
        Type      const type = Type::Add
    ) :
        mutationProbability_{ mutationProbability },
        forceMutation_{ forceMutation },
        sigma_{ sigma },
        type_{ type }
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
                auto const randomValue{ random::normal< typename T::value_type >( 0.0f, sigma_ ) };
                value = randomValue + ( type_ == Type::Set ? 0 : value );
            }
        }

        if ( !mutationHappened && forceMutation_ )
        {
            auto const randomIndex{ random::uniform( 0UL, std::size( mutant.data() ) ) };
            auto const randomValue{ random::normal< typename T::value_type >( 0.0f, sigma_ ) };
            mutant.data()[ randomIndex ] = randomValue + ( type_ == Type::Set ? 0 : mutant.data()[ randomIndex ] );
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
    decimal_t mutationProbability_;
    bool      forceMutation_;
    decimal_t sigma_;
    Type      type_;
};

}

#endif // ECFCPP_MUTATIONS_GAUSSIAN_HPP
