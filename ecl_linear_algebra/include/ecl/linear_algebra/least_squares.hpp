/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/least_squares.hpp
 *
 * @brief Convenience eigen module loader (preloads the plugin).
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_LEAST_SQUARES_HPP_
#define ECL_LINEAR_ALGEBRA_LEAST_SQUARES_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include "macros.hpp"
#include "formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

// This is an eigen2 support module, forget it.

//#ifdef ECL_EIGEN_IS_INTERNAL
//  #include <ecl/Eigen3/LeastSquares>
//#else
//  #include <eigen3/Eigen/LeastSquares>
//#endif

#endif /* ECL_LINEAR_ALGEBRA_LEAST_SQUARES_HPP_ */
