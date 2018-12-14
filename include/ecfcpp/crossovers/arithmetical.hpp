#ifndef ECFCPP_CROSSOVERS_ARITHMETICAL_HPP
#define ECFCPP_CROSSOVERS_ARITHMETICAL_HPP

#include <ecfcpp/types.hpp>

#include <cstddef>
#include <iterator>

namespace ecfcpp::crossover
{

class Arithmetical
{
public:
    constexpr Arithmetical( float const lambda ) noexcept : lambda_{ lambda } {}

    template< typename T >
    constexpr Container< T > operator()( T const & mom, T const & dad ) const
    {
        T firstChild { mom };
        T secondChild{ dad };

        for ( std::size_t i{ 0 }; i < std::size( mom ); ++i )
        {
            firstChild [ i ] = lambda_ * mom[ i ] + ( 1 - lambda_ ) * dad[ i ];
            secondChild[ i ] = lambda_ * dad[ i ] + ( 1 - lambda_ ) * mom[ i ];
        }

        return { firstChild, secondChild };
    }

private:
    float lambda_;
};

}

#endif // ECFCPP_CROSSOVERS_ARITHMETICAL_HPP
