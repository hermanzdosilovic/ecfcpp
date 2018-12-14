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
#include <type_traits>

namespace ecfcpp
{

template
<
    typename    T,
    std::size_t N,
    typename    Decimal = decimal_t,
    typename =  std::enable_if_t< std::is_arithmetic_v< T > >
>
class Vector
{
public:
    using value_type = T;

    constexpr Vector() = default;

    constexpr Vector
    (
        value_type const lowerBound,
        value_type const upperBound
    ) :
        lowerBound_{ lowerBound },
        upperBound_{ upperBound }
    {
        assert( lowerBound_ <= upperBound_ );
    }

    constexpr Vector( Vector const & other ) :
        data_      { other.data_       },
        lowerBound_{ other.lowerBound_ },
        upperBound_{ other.upperBound_ },
        fitness    { other.fitness     },
        penalty    { other.penalty     }
    {}

    constexpr Vector( Vector && other ) :
        data_      { std::move( other.data_ ) },
        lowerBound_{ other.lowerBound_        },
        upperBound_{ other.upperBound_        },
        fitness    { other.fitness            },
        penalty    { other.penalty            }
    {}

    constexpr inline value_type operator[]( std::size_t const index ) const
    {
        assert( index < N );
        return std::clamp( data_[ index ], lowerBound_, upperBound_ );
    }

    constexpr inline value_type & operator[]( std::size_t const index )
    {
        assert( index < N );
        data_[ index ] = std::clamp( data_[ index ], lowerBound_, upperBound_ );
        return data_[ index ];
    }

    constexpr inline bool operator< ( Vector const & rhs ) const { return fitness < rhs.fitness; }
    constexpr inline bool operator> ( Vector const & rhs ) const { return rhs < *this;           }
    constexpr inline bool operator<=( Vector const & rhs ) const { return !( *this > rhs );      }
    constexpr inline bool operator>=( Vector const & rhs ) const { return !( rhs > *this );      }

    constexpr inline bool operator==( Vector const & rhs ) const { return data_ == rhs.data_; }
    constexpr inline bool operator!=( Vector const & rhs ) const { return !( *this == rhs );  }

    constexpr inline auto & operator=( Vector const & rhs )
    {
        data_       = rhs.data_;
        lowerBound_ = rhs.lowerBound_;
        upperBound_ = rhs.upperBound_;
        fitness     = rhs.fitness;
        penalty     = rhs.penalty;
        return *this;
    }

    constexpr inline auto & operator=( Vector< T, N, Decimal > && rhs )
    {
        data_       = std::move( rhs.data_ );
        lowerBound_ = rhs.lowerBound_;
        upperBound_ = rhs.upperBound_;
        fitness     = rhs.fitness;
        penalty     = rhs.penalty;
        return *this;
    }

    class iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type        = Vector::value_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type *;
        using reference         = value_type &;

        explicit constexpr iterator( Vector & vector, std::size_t const index ) : vector_{ vector }, index_{ index } {}
        inline bool operator==( iterator const & other ) const { return index_ == other.index_ && &vector_ == &other.vector_; }
        inline bool operator!=( iterator const & other ) const { return !( *this == other ); }
        inline iterator & operator++() { ++index_; return *this; }
        inline reference operator*() { return vector_[ index_ ]; }

    private:
        Vector & vector_;
        std::size_t index_;
    };

    class const_iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type        = Vector::value_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type *;
        using reference         = value_type &;

        explicit constexpr const_iterator( Vector const & vector, std::size_t const index ) : vector_{ vector }, index_{ index } {}
        inline bool operator==( const_iterator const & other ) const { return index_ == other.index_ && &vector_ == &other.vector_; }
        inline bool operator!=( const_iterator const & other ) const { return !( *this == other ); }
        inline const_iterator & operator++() { ++index_; return *this; }
        inline value_type operator*() const { return vector_[ index_ ]; }

    private:
        Vector const & vector_;
        std::size_t index_;
    };

    constexpr auto size() const { return N; }

    constexpr auto begin() const { return const_iterator( *this, 0 ); }
    constexpr auto end  () const { return const_iterator( *this, N ); }

    constexpr auto begin() { return iterator( *this, 0 ); }
    constexpr auto end  () { return iterator( *this, N ); }

private:
    std::array< value_type, N > data_{};
    value_type lowerBound_
    {
        std::is_floating_point_v< value_type > ?
            -1 * std::numeric_limits< value_type >::max() :
                 std::numeric_limits< value_type >::min()
    };
    value_type upperBound_{ std::numeric_limits< value_type >::max() };

public:
    Decimal fitness{ constant::worstFitness< Decimal >() };
    Decimal penalty{ constant::worstPenalty< Decimal >() };
};

}

template< typename T, std::size_t N >
std::ostream & operator<<( std::ostream & stream, ecfcpp::Vector< T, N > const & vector )
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
