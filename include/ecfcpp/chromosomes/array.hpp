#ifndef ECFCPP_CHROMOSOMES_ARRAY_HPP
#define ECFCPP_CHROMOSOMES_ARRAY_HPP

#include <ecfcpp/bounded_array.hpp>
#include <ecfcpp/constants.hpp>
#include <ecfcpp/types.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <ostream>
#include <type_traits>

namespace ecfcpp
{

template
<
    typename    T,
    std::size_t N,
    typename    Decimal = std::conditional_t< std::is_floating_point_v< T >, T, decimal_t >,
    typename =  std::enable_if_t< std::is_arithmetic_v< T > >
>
class Array
{
public:
    using value_type = T;

    constexpr Array() = default;

    constexpr Array( value_type const lowerBound, value_type const upperBound ) : data_{ lowerBound, upperBound } {}

    constexpr Array( Array const & other ) :
        data_      { other.data_       },
        fitness    { other.fitness     },
        penalty    { other.penalty     }
    {}

    constexpr Array( Array && other ) :
        data_      { std::move( other.data_ ) },
        fitness    { other.fitness            },
        penalty    { other.penalty            }
    {}

    constexpr inline value_type operator[]( std::size_t const index ) const
    {
        assert( index < N );
        return data_[ index ];
    }

    constexpr inline value_type & operator[]( std::size_t const index )
    {
        assert( index < N );
        return data_[ index ];
    }

    constexpr inline bool operator< ( Array const & rhs ) const { return fitness < rhs.fitness; }
    constexpr inline bool operator> ( Array const & rhs ) const { return rhs < *this;           }
    constexpr inline bool operator<=( Array const & rhs ) const { return !( *this > rhs );      }
    constexpr inline bool operator>=( Array const & rhs ) const { return !( rhs > *this );      }

    constexpr inline bool operator==( Array const & rhs ) const { return data_ == rhs.data_; }
    constexpr inline bool operator!=( Array const & rhs ) const { return !( *this == rhs );  }

    constexpr auto & operator=( Array const & rhs )
    {
        data_       = rhs.data_;
        fitness     = rhs.fitness;
        penalty     = rhs.penalty;
        return *this;
    }

    constexpr auto & operator=( Array && rhs )
    {
        data_       = std::move( rhs.data_ );
        fitness     = rhs.fitness;
        penalty     = rhs.penalty;
        return *this;
    }

    friend std::ostream & operator<<( std::ostream & stream, Array const & array )
    {
        stream << '{';

        char separator[]{ '\0', ' ', '\0' };
        for ( auto const value : array )
        {
            stream << separator << value;
            separator[ 0 ] = ',';
        }

        stream << '}';

        return stream;
    }

    constexpr auto       & data()       { return data_; }
    constexpr auto const & data() const { return data_; }

    constexpr auto size() const { return N; }

    constexpr auto begin() { return std::begin( data_ ); }
    constexpr auto end  () { return std::end  ( data_ ); }

    constexpr auto begin() const { return std::begin( data_ ); }
    constexpr auto end  () const { return std::end  ( data_ ); }

private:
    BoundedArray< value_type, N > data_{};

public:
    Decimal fitness{ constant::worstFitness< Decimal >() };
    Decimal penalty{ constant::worstPenalty< Decimal >() };
};

}

#endif // ECFCPP_CHROMOSOMES_ARRAY_HPP
