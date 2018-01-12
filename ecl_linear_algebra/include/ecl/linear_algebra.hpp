/**
 * @file /include/ecl/linear_algebra.hpp
 *
 * @brief Mathematical tools for linear algebra.
 *
 * Various linear algebraic classes and methods aliased to and provided
 * by the eigen library.
 *
 * @date May 2009
 **/

/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_HPP_
#define ECL_LINEAR_ALGEBRA_HPP_

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#include <math.h> // M_PI
#endif // _MSC_VER

#include "linear_algebra/eigen.hpp"
#include "linear_algebra/sophus.hpp"

// want to get rid of this, but there is legacy issues.
namespace ecl {
    namespace linear_algebra = Eigen;
}

#endif /*ECL_MATH_LINEAR_ALGEBRA_HPP_*/
