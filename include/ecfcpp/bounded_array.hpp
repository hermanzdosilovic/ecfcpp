#ifndef ECFCPP_BOUNDED_ARRAY_HPP
#define ECFCPP_BOUNDED_ARRAY_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <type_traits>

namespace ecfcpp
{

template< typename T, std::size_t N, typename = std::enable_if_t< std::is_arithmetic_v< T > > >
class BoundedArray
{
public:
    using value_type = T;

    constexpr BoundedArray() = default;

    constexpr BoundedArray
    (
        value_type const lowerBound,
        value_type const upperBound
    ) :
        lowerBound_{ lowerBound },
        upperBound_{ upperBound }
    {
        assert( lowerBound_ <= upperBound_ );
    }

    constexpr BoundedArray( BoundedArray const & other ) :
        data_      { other.data_       },
        lowerBound_{ other.lowerBound_ },
        upperBound_{ other.upperBound_ }
    {}

    constexpr BoundedArray( BoundedArray && other ) :
        data_      { std::move( other.data_ ) },
        lowerBound_{ other.lowerBound_        },
        upperBound_{ other.upperBound_        }
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

    constexpr inline bool operator< ( BoundedArray const & rhs ) const { return data_ < rhs.data_; }
    constexpr inline bool operator> ( BoundedArray const & rhs ) const { return rhs < *this;           }
    constexpr inline bool operator<=( BoundedArray const & rhs ) const { return !( *this > rhs );      }
    constexpr inline bool operator>=( BoundedArray const & rhs ) const { return !( rhs > *this );      }

    constexpr inline bool operator==( BoundedArray const & rhs ) const { return data_ == rhs.data_; }
    constexpr inline bool operator!=( BoundedArray const & rhs ) const { return !( *this == rhs );  }

    constexpr auto & operator=( BoundedArray const & rhs )
    {
        data_       = rhs.data_;
        lowerBound_ = rhs.lowerBound_;
        upperBound_ = rhs.upperBound_;
        return *this;
    }

    constexpr auto & operator=( BoundedArray && rhs )
    {
        data_       = std::move( rhs.data_ );
        lowerBound_ = rhs.lowerBound_;
        upperBound_ = rhs.upperBound_;
        return *this;
    }

    class iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type        = BoundedArray::value_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type *;
        using reference         = value_type &;

        explicit constexpr iterator
        (
            BoundedArray       & array,
            std::size_t  const   index
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
        BoundedArray & array_;
        std::size_t index_;
    };

    class const_iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type        = BoundedArray::value_type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type *;
        using reference         = value_type &;

        explicit constexpr const_iterator
        (
            BoundedArray const & array,
            std::size_t  const   index
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
        BoundedArray const & array_;
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
};

}

#endif // ECFCPP_BOUNDED_ARRAY_HPP
