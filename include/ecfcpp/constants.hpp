#ifndef ECFCPP_CONSTANTS_HPP
#define ECFCPP_CONSTANTS_HPP

#include "types.hpp"

#include <limits>
#include <type_traits>

namespace ecfcpp::constant
{

template< typename T = decimal_t, typename = std::enable_if_t< std::is_floating_point_v< T > > >
constexpr inline T pi() { return static_cast< T >( 3.141592653589793238462643383279502884 ); }

template< typename T = decimal_t, typename = std::enable_if_t< std::is_floating_point_v< T > > >
constexpr inline T tau() { return static_cast< T >( 6.283185307179586476925286766559005768 ); }

template< typename T = decimal_t, typename = std::enable_if_t< std::is_floating_point_v< T > > >
constexpr inline T e() { return static_cast< T >( 2.718281828459045235360287471352662497 ); }

template< typename T = decimal_t, typename = std::enable_if_t< std::is_floating_point_v< T > > >
constexpr inline T phi() { return static_cast< T >( 1.618033988749894848204586834365638117 ); }

template< typename T = decimal_t, typename = std::enable_if_t< std::is_floating_point_v< T > > >
constexpr inline T bestFitness() { return std::numeric_limits< T >::max(); }

template< typename T = decimal_t, typename = std::enable_if_t< std::is_floating_point_v< T > > >
constexpr inline T worstFitness() { return -1 * std::numeric_limits< T >::max(); }

template< typename T = decimal_t, typename = std::enable_if_t< std::is_floating_point_v< T > > >
constexpr inline T bestPenalty() { return -1 * std::numeric_limits< T >::max(); }

template< typename T = decimal_t, typename = std::enable_if_t< std::is_floating_point_v< T > > >
constexpr inline T worstPenalty() { return std::numeric_limits< T >::max(); }

}

#endif // ECFCPP_CONSTANTS_HPP
