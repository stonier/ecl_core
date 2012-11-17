/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/stddeque.hpp
 *
 * @brief Convenience eigen module loader (preloads the plugin).
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_STDDEQUE_HPP_
#define ECL_LINEAR_ALGEBRA_STDDEQUE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include "macros.hpp"
#include "formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

#ifdef ECL_EIGEN_IS_INTERNAL
  #include <ecl/Eigen3/StdDeque>
#else
  #include <eigen3/Eigen/StdDeque>
#endif

#endif /* ECL_LINEAR_ALGEBRA_STDDEQUE_HPP_ */
