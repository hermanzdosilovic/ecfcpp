#ifndef ECFCPP_CHROMOSOMES_VECTOR_HPP
#define ECFCPP_CHROMOSOMES_VECTOR_HPP

#include <ecfcpp/constants.hpp>
#include <ecfcpp/types.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <ostream>

namespace ecfcpp
{

template< typename T, std::size_t N, typename Fitness = fitness_type >
class UnboundedVector
{
public:
    using value_type = T;

    constexpr UnboundedVector() = default;

    constexpr UnboundedVector( Fitness const fitness ) : fitness{ fitness }, penalty{ -1 * fitness } {}

    constexpr UnboundedVector( UnboundedVector< T, N, Fitness > const & other ) :
        fitness{ other.fitness },
        penalty{ other.penalty },
        data_  { other.data_   }
    {}

    constexpr UnboundedVector( UnboundedVector< T, N, Fitness > && other ) :
        fitness{ other.fitness },
        penalty{ other.penalty },
        data_  { std::move( other.data_ ) }
    {}

    constexpr value_type operator[]( std::size_t const index ) const
    {
        assert( index < N );
        return data_[ index ];
    }

    constexpr value_type & operator[]( std::size_t const index )
    {
        assert( index < N );
        return data_[ index ];
    }

    constexpr inline bool operator< ( UnboundedVector< T, N, Fitness > const & rhs ) const { return fitness < rhs.fitness; }
    constexpr inline bool operator> ( UnboundedVector< T, N, Fitness > const & rhs ) const { return rhs < *this;           }
    constexpr inline bool operator<=( UnboundedVector< T, N, Fitness > const & rhs ) const { return !( *this > rhs );      }
    constexpr inline bool operator>=( UnboundedVector< T, N, Fitness > const & rhs ) const { return !( rhs > *this );      }

    constexpr inline bool operator==( UnboundedVector< T, N, Fitness > const & rhs ) const { return data_ == rhs.data_; }
    constexpr inline bool operator!=( UnboundedVector< T, N, Fitness > const & rhs ) const { return !( *this == rhs );  }

    constexpr inline auto & operator=( UnboundedVector< T, N, Fitness > const & rhs )
    {
        fitness = rhs.fitness;
        penalty = rhs.penalty;
        data_ = rhs.data_;
        return *this;
    }

    constexpr inline auto & operator=( UnboundedVector< T, N, Fitness > && rhs )
    {
        fitness = rhs.fitness;
        penalty = rhs.penalty;
        data_ = std::move( rhs.data_ );
        return *this;
    }

    constexpr friend void swap( UnboundedVector< T, N, Fitness > & first, UnboundedVector< T, N, Fitness > & second )
    {
        using std::swap;
        swap( first.fitness, second.fitness );
        swap( first.penalty, second.penalty );
        swap( first.data_  , second.data_   );
    }

    constexpr auto size() const { return N; }

    constexpr auto begin() const { return std::begin( data_ ); }
    constexpr auto end  () const { return std::end  ( data_ ); }

    constexpr auto begin() { return std::begin( data_ ); }
    constexpr auto end  () { return std::end  ( data_ ); }

    Fitness fitness{ constant::worstFitness< Fitness >() };
    Fitness penalty{ constant::worstPenalty< Fitness >() };

private:
    std::array< value_type, N > data_{};
};

template< typename T, std::size_t N, typename Fitness = fitness_type >
using Vector = UnboundedVector< T, N, Fitness >;

template< std::size_t N, typename Fitness = fitness_type >
using UnboundedIntVector = UnboundedVector< std::int32_t, N, Fitness >;

template< std::size_t N, typename Fitness = fitness_type >
using IntVector = UnboundedIntVector< N, Fitness >;

template< std::size_t N, typename Fitness = fitness_type >
using UnboundedRealVector = UnboundedVector< double, N, Fitness >;

template< std::size_t N, typename Fitness = fitness_type >
using RealVector = UnboundedRealVector< N, Fitness >;

template< std::size_t N, typename Fitness = fitness_type >
using UnboundedBitVector = UnboundedVector< bool, N, Fitness >;

template< std::size_t N, typename Fitness = fitness_type >
using BitVector = UnboundedBitVector< N, Fitness >;

}

template< typename T, std::size_t N >
std::ostream & operator<<( std::ostream & stream, ecfcpp::UnboundedVector< T, N > const & vector )
{
    stream << '{';

    char separator[]{ '\0', ' ', '\0' };
    for ( auto const & value : vector )
    {
        stream << separator << value;
        separator[ 0 ] = ',';
    }

    stream << '}';

    return stream;
}

#endif // ECFCPP_CHROMOSOMES_VECTOR_HPP
