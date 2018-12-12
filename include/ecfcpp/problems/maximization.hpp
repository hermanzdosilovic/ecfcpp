#ifndef ECFCPP_PROBLEMS_MAXIMIZATION_HPP
#define ECFCPP_PROBLEMS_MAXIMIZATION_HPP

namespace ecfcpp::problem
{

template< typename Function >
class Maximization
{
public:
    constexpr Maximization( Function  & function ) : function_{ function } {};
    constexpr Maximization( Function && function ) : function_{ function } {};

    template< typename Point >
    constexpr inline double fitness( Point const & p ) const { return function_( p ); }

    constexpr inline double penalty( double const fitness ) const { return -1 * fitness; }

    template< typename Point, typename = std::enable_if_t< !std::is_floating_point_v< Point > > >
    constexpr inline double penalty( Point const & p ) const { return penalty( fitness( p ) ); }

    template< typename Population >
    constexpr void evaluate( Population & population ) const
    {
        for ( auto & individual : population )
        {
            individual.fitness = fitness( individual         );
            individual.penalty = penalty( individual.fitness );
        }
    }

private:
    Function & function_;
};

}

#endif // ECFCPP_PROBLEMS_MAXIMIZATION_HPP
