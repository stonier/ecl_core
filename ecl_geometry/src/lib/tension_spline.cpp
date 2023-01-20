/**
 * @file /src/lib/tension_spline.cpp
 *
 * @brief Implementation for tension splines.
 *
 * Implementation for tension splines.
 *
 * @sa @ref splinesGeometry "Math::Splines.
 *
 * @author Daniel J. Stonier
 * @date 20/05/2009
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/ecl/geometry/tension_spline.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Implementation
*****************************************************************************/

double TensionSpline::operator()(const double &x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = 0;
    while ( x > discretised_domain[index+1] ) {
        ++index;
    }
    return functions[index](tension,x);
}

double TensionSpline::derivative(const double &x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = 0;
    while ( x > discretised_domain[index+1] ) {
        ++index;
    }
    return functions[index].derivative(tension,x);
}

  std::map<int, double> TensionSpline::derivative(const int &last_index, const double &x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = last_index;
    while ( x > discretised_domain[index+1] ) {
      ++index;
    }
    std::map<int, double> m = {{index, functions[index].derivative(tension,x)}};
    return m;
  }

double TensionSpline::dderivative(const double &x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = 0;
    while ( x > discretised_domain[index+1] ) {
        ++index;
    }
    return functions[index].dderivative(tension,x);
}

std::map<int, double> TensionSpline::dderivative(const int &last_index, const double &x) const {
  ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
  int index = last_index;
  while ( x > discretised_domain[index+1] ) {
    ++index;
  }
  std::map<int, double> m = {{index, functions[index].dderivative(tension, x)}};
  return m;
}

} // namespace ecl
