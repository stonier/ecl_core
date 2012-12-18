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

#include <ecl/linear_algebra/macros.hpp>

/*****************************************************************************
** Plugins
*****************************************************************************/

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

/*****************************************************************************
** Includes
*****************************************************************************/

#include "linear_algebra/core.hpp"
#include "linear_algebra/cholesky.hpp"
#include "linear_algebra/dense.hpp"
#include "linear_algebra/eigenvalues.hpp"
#include "linear_algebra/geometry.hpp"
#include "linear_algebra/householder.hpp"
#include "linear_algebra/jacobi.hpp"
//#include "linear_algebra/least_squares.hpp" // This is an eigen2 support module, forget it.
#include "linear_algebra/lu.hpp"
#include "linear_algebra/qr.hpp"
// #include "linear_algebra/qtalignedmalloc.hpp" // This one is bad, it doesn't inline headers (v3.01)
#ifdef EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
  #include "linear_algebra/sparse.hpp"
#endif
#include "linear_algebra/stddeque.hpp"
#include "linear_algebra/stdlist.hpp"
#include "linear_algebra/stdvector.hpp"
#include "linear_algebra/svd.hpp"
// unsupported modules
#include "linear_algebra/unsupported/numerical_diff.hpp"
#include "linear_algebra/unsupported/nonlinear_optimization.hpp"

namespace ecl {
    namespace linear_algebra = Eigen;
}

#endif /*ECL_MATH_LINEAR_ALGEBRA_HPP_*/
