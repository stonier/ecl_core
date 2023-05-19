/**
 * @file /src/lib/cubic_spline.cpp
 *
 * @brief Implementation for cubic splines.
 *
 * Implementation for cubic splines.
 *
 * @sa @ref splinesGeometry "Math::Splines.
 *
 * @date June 2009
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/exceptions/standard_exception.hpp>
#include "../../include/ecl/geometry/cubic_spline.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Implementation
*****************************************************************************/

double CubicSpline::operator()(const double &x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = 0;
    while ( x > discretised_domain[index+1] ) {
        ++index;
    }
    return cubic_polynomials[index](x);
}

std::map<int, double> CubicSpline::operator()(int last_index, const double &x) {
  ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
  int index = last_index;
  while ( x > discretised_domain[index+1] ) {
    ++index;
  }
  std::map<int, double> m = {{index, cubic_polynomials[index](x)}};
  return m;
}

double CubicSpline::derivative(double x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = 0;
    while ( x > discretised_domain[index+1] ) {
        ++index;
    }
    return cubic_polynomials[index].derivative()(x);
}

std::map<int, double> CubicSpline::derivative(const int &last_index, const double &x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = last_index;
    while ( x > discretised_domain[index+1] ) {
      ++index;
    }
    std::map<int, double> m = {{index, cubic_polynomials[index].derivative()(x)}};
    return m;
}

double CubicSpline::dderivative(double x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = 0;
    while ( x > discretised_domain[index+1] ) {
        ++index;
    }
    return cubic_polynomials[index].derivative().derivative()(x);
}

std::map<int, double> CubicSpline::dderivative(const int &last_index, const double &x) const {
    ecl_assert_throw( ( ( x >= discretised_domain.front() ) && ( x <= discretised_domain.back() ) ), StandardException(LOC,OutOfRangeError) );
    int index = last_index;
    while ( x > discretised_domain[index+1] ) {
      ++index;
    }
    std::map<int, double> m = {{index, cubic_polynomials[index].derivative().derivative()(x)}};
    return m;
}


} // namespace ecl
