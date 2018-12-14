#ifndef ECFCPP_CROSSOVERS_ARITHMETICAL_HPP
#define ECFCPP_CROSSOVERS_ARITHMETICAL_HPP

#include <cstddef>
#include <iterator>

namespace ecfcpp::crossover
{

class Arithmetical
{
public:
    constexpr Arithmetical( float const lambda ) noexcept : lambda_{ lambda } {}

    template< typename T >
    constexpr T operator()( T const & mom, T const & dad ) const
    {
        T child{ mom };
        for ( std::size_t i{ 0 }; i < std::size( child ); ++i )
        {
            child[ i ] = lambda_ * mom[ i ] + ( 1 - lambda_ ) * dad[ i ];
        }
        return child;
    }

private:
    float lambda_;
};

}

#endif // ECFCPP_CROSSOVERS_ARITHMETICAL_HPP
