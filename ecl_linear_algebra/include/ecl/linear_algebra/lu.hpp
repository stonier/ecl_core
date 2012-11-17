/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/lu.hpp
 *
 * @brief Convenience eigen module loader (preloads the plugin).
 *
 * @date 28/07/2010
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_LU_HPP_
#define ECL_LINEAR_ALGEBRA_LU_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include "macros.hpp"
#include "formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

#ifdef ECL_EIGEN_IS_INTERNAL
  #include <ecl/Eigen3/LU>
#else
  #include <eigen3/Eigen/LU>
#endif

#endif /* ECL_LINEAR_ALGEBRA_LU_HPP_ */
