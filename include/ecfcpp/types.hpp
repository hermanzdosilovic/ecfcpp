#ifndef ECFCPP_TYPES_HPP
#define ECFCPP_TYPES_HPP

#include <vector>
#include <ostream>

namespace ecfcpp
{

template< typename T >
using Population = std::vector< T >;

template< typename T >
using Container = std::vector< T >;

using decimal_t = float;

}

template< typename T >
std::ostream & operator<<( std::ostream & stream, ecfcpp::Population< T > const & population )
{
    stream << '{';

    char separator[]{ '\0', ' ', '\0' };
    for ( auto const & individual : population )
    {
        stream << separator << individual;
        separator[ 0 ] = ',';
    }

    stream << '}';

    return stream;
}

#endif // ECFCPP_TYPES_HPP
