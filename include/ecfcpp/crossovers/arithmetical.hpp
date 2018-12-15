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

        for ( std::size_t i{ 0 }; i < std::size( mom.data() ); ++i )
        {
            firstChild .data()[ i ] = lambda_ * mom.data()[ i ] + ( 1 - lambda_ ) * dad.data()[ i ];
            secondChild.data()[ i ] = lambda_ * dad.data()[ i ] + ( 1 - lambda_ ) * mom.data()[ i ];
        }

        return { firstChild, secondChild };
    }

private:
    float lambda_;
};

}

#endif // ECFCPP_CROSSOVERS_ARITHMETICAL_HPP
