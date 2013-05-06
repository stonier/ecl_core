/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/unsupported/numerical_diff.hpp
 *
 * @brief Unsupported numerical differentiation module.
 *
 * @date Dec 2010
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_NUMERICAL_DIFF_HPP_
#define ECL_LINEAR_ALGEBRA_NUMERICAL_DIFF_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/linear_algebra/macros.hpp>

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

#ifdef ECL_EIGEN_IS_INTERNAL
  #include <ecl/Eigen3/unsupported/Eigen/NumericalDiff>
#elif defined ECL_EIGEN_IS_INTERNAL_3_1_2
  #include <ecl/Eigen3.1.2/unsupported/Eigen/NumericalDiff>
#else
  #include <unsupported/Eigen/NumericalDiff>
#endif

#endif /* ECL_LINEAR_ALGEBRA_NUMERICAL_DIFF_HPP_ */
