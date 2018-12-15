#ifndef ECFCPP_CHROMOSOMES_BINARY_ARRAY_HPP
#define ECFCPP_CHROMOSOMES_BINARY_ARRAY_HPP

#include <ecfcpp/types.hpp>

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace ecfcpp
{

template
<
    typename    T,
    std::size_t N,
    typename =  std::enable_if_t< std::is_floating_point_v< T > >
>
class BinaryArray
{
public:
    using value_type = T;

    constexpr BinaryArray
    (
        value_type   const lowerBound,
        value_type   const upperBound,
        std::uint8_t const precision
    ) :
        lowerBound_{ lowerBound                },
        upperBound_{ upperBound                },
        boundWidth_{ upperBound_ - lowerBound_ },
        precision_ { precision                 },
        chromosomeLength_
        {
            static_cast< std::uint8_t >
            (
                std::round
                (
                    std::log10( std::floor( 1 + boundWidth_ * std::pow( 10, precision_ ) ) )
                    /
                    std::log10( 2 )
                )
            )
        },
        maxValue_{ static_cast< uint32_t >( 1 << chromosomeLength_ ) - 1 },
        data_( N * chromosomeLength_, 0 )
    {
        assert( lowerBound        <= upperBound );
        assert( chromosomeLength_ <= 64         );
    }

    constexpr BinaryArray( BinaryArray const & other ) = default;

    constexpr BinaryArray( BinaryArray && other ) = default;

    constexpr value_type operator[]( std::size_t const index ) const
    {
        assert( index < N );

        value_type result{ 0 };
        std::uint32_t base{ 1 };
        for ( std::size_t i{ index * chromosomeLength_ }; i < ( index + 1 ) * chromosomeLength_; ++i )
        {
            result += data_[ i ] ? base : 0;
            base *= 2;
        }
        return lowerBound_ + result * boundWidth_ / maxValue_;
    }

    constexpr inline bool operator< ( BinaryArray const & rhs ) const { return fitness < rhs.fitness; }
    constexpr inline bool operator> ( BinaryArray const & rhs ) const { return rhs < *this;           }
    constexpr inline bool operator<=( BinaryArray const & rhs ) const { return !( *this > rhs );      }
    constexpr inline bool operator>=( BinaryArray const & rhs ) const { return !( rhs > *this );      }

    constexpr inline bool operator==( BinaryArray const & rhs ) const { return data_ == rhs.data_; }
    constexpr inline bool operator!=( BinaryArray const & rhs ) const { return !( *this == rhs );  }

    constexpr auto & operator=( BinaryArray const & rhs )
    {
        lowerBound_       = rhs.lowerBound_;
        upperBound_       = rhs.upperBound_;
        boundWidth_       = rhs.boundWidth_;
        precision_        = rhs.precision_;
        chromosomeLength_ = rhs.chromosomeLength_;
        maxValue_         = rhs.maxValue_;
        data_             = rhs.data_;
        return *this;
    }

    constexpr auto & operator=( BinaryArray && rhs )
    {
        lowerBound_       = rhs.lowerBound_;
        upperBound_       = rhs.upperBound_;
        boundWidth_       = rhs.boundWidth_;
        precision_        = rhs.precision_;
        chromosomeLength_ = rhs.chromosomeLength_;
        maxValue_         = rhs.maxValue_;
        data_             = std::move( rhs.data_ );
        return *this;
    }

    class iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type        = BinaryArray::value_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type *;
        using reference         = value_type &;

        explicit constexpr iterator
        (
            BinaryArray       & array,
            std::size_t const   index
        ) :
            array_{ array },
            index_{ index }
        {}

        inline bool operator==( iterator const & other ) const
        {
            return index_ == other.index_ && &array_ == &other.array_;
        }

        inline bool operator!=( iterator const & other ) const { return !( *this == other ); }

        inline iterator & operator++() { ++index_; return *this; }

        inline reference operator*() { return array_[ index_ ]; }

    private:
        BinaryArray & array_;
        std::size_t   index_;
    };

    class const_iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type        = BinaryArray::value_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type *;
        using reference         = value_type &;

        explicit constexpr const_iterator
        (
            BinaryArray const & array,
            std::size_t const   index
        ) :
            array_{ array },
            index_{ index }
        {}

        inline bool operator==( const_iterator const & other ) const
        {
            return index_ == other.index_ && &array_ == &other.array_;
        }

        inline bool operator!=( const_iterator const & other ) const { return !( *this == other ); }

        inline const_iterator & operator++() { ++index_; return *this; }

        // Returning value_type should be OK since value_type is arithmetic.
        inline value_type operator*() const { return array_[ index_ ]; }

    private:
        BinaryArray const & array_;
        std::size_t         index_;
    };

    constexpr inline auto       & data()       { return data_; }
    constexpr inline auto const & data() const { return data_; }

    constexpr inline auto size() const { return N; }

    constexpr inline auto begin() const { return const_iterator( *this, 0 ); }
    constexpr inline auto end  () const { return const_iterator( *this, N ); }

    constexpr inline auto begin() { return iterator( *this, 0 ); }
    constexpr inline auto end  () { return iterator( *this, N ); }

private:
    value_type                  lowerBound_;
    value_type                  upperBound_;
    value_type                  boundWidth_;
    std::uint8_t                precision_;
    std::uint8_t                chromosomeLength_;
    std::uint32_t               maxValue_;
    std::vector< std::uint8_t > data_;

public:
    value_type fitness{ constant::worstFitness< value_type >() };
    value_type penalty{ constant::worstPenalty< value_type >() };
};

template< typename T, std::size_t N >
std::ostream & operator<<( std::ostream & stream, ecfcpp::BinaryArray< T, N > const & vector )
{
    stream << '{';

    char separator[]{ '\0', ' ', '\0' };
    for ( auto const value : vector.data() )
    {
        stream << separator << static_cast< std::uint16_t >( value );
        separator[ 0 ] = ',';
    }

    stream << '}';

    return stream;
}

}

#endif // ECFCPP_CHROMOSOMES_BINARY_ARRAY_HPP
