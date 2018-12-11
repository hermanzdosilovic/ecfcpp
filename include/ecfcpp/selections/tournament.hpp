#ifndef ECFCPP_SELECTIONS_TOURNAMENT_HPP
#define ECFCPP_SELECTIONS_TOURNAMENT_HPP

#include <ecfcpp/types.hpp>
#include <ecfcpp/utils/random.hpp>

#include <cassert>
#include <cstdint>
#include <iterator>

namespace ecfcpp::selection
{

class Tournament
{
public:
    constexpr Tournament( std::size_t const size ) noexcept : size_{ size }
    {
        assert( size_ > 0 );
    }

    template< typename T >
    constexpr T const & operator()( Population< T > const & population ) const noexcept
    {
        assert( std::size( population ) >= size_ );

        auto const N{ std::size( population ) };

        T const * best{ nullptr };

        std::size_t tournaments{ size_ - 1 };
        while ( tournaments-- > 0 )
        {
            auto const * picked{ &population[ random::uniform( 0UL, N ) ] };
            if ( best == nullptr || *picked > *best )
            {
                best = picked;
            }
        }

        return *best;
    }

private:
    std::size_t size_;
};

}

#endif // ECFCPP_SELECTIONS_TOURNAMENT_HPP
