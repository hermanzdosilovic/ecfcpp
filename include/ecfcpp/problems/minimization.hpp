#ifndef ECFCPP_PROBLEMS_MINIMIZATION_HPP
#define ECFCPP_PROBLEMS_MINIMIZATION_HPP

#include <type_traits>

namespace ecfcpp::problem
{

template< typename Function >
class Minimization
{
public:
    constexpr Minimization( Function  & function ) : function_{ function } {};
    constexpr Minimization( Function && function ) : function_{ function } {};

    constexpr inline double fitness( double const penalty ) const { return -1 * penalty; }

    template< typename Point, typename = std::enable_if_t< !std::is_floating_point_v< Point > >  >
    constexpr inline double fitness( Point const & p ) const { return fitness( penalty( p ) ); }

    template< typename Point >
    constexpr inline double penalty( Point const & p ) const { return function_( p ); }

    template< typename Population >
    constexpr void evaluate( Population & population ) const
    {
        for ( auto & individual : population )
        {
            individual.penalty = penalty( individual         );
            individual.fitness = fitness( individual.penalty );
        }
    }

private:
    Function & function_;
};

}

#endif // ECFCPP_PROBLEMS_MINIMIZATION_HPP
