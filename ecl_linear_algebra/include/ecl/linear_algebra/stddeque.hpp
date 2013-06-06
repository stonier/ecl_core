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

#include "formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

#include <Eigen/StdDeque>

#endif /* ECL_LINEAR_ALGEBRA_STDDEQUE_HPP_ */
