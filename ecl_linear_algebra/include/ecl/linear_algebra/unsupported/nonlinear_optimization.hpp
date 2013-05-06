/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/unsupported/nonlinear_optimization.hpp
 *
 * @brief Unsupported nonlinear optimisation module.
 *
 * @date Dec 2010
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_NONLINEAR_OPTIMIZATION_HPP_
#define ECL_LINEAR_ALGEBRA_NONLINEAR_OPTIMIZATION_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/linear_algebra/macros.hpp>

#ifndef EIGEN_MATRIXBASE_PLUGIN
//   #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

#ifdef ECL_EIGEN_IS_INTERNAL
  #include <ecl/Eigen3/unsupported/Eigen/NonLinearOptimization>
#elif defined ECL_EIGEN_IS_INTERNAL_3_1_2
  #include <ecl/Eigen3.1.2/unsupported/Eigen/NonLinearOptimization>
#else
  #include <unsupported/Eigen/NonLinearOptimization>
#endif

#endif /* ECL_LINEAR_ALGEBRA_NONLINEAR_OPTIMIZATION_HPP_ */
