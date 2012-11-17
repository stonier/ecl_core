/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/qtalignedmalloc.hpp
 *
 * @brief Convenience eigen module loader (preloads the plugin).
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_QTALIGNEDMALLOC_HPP_
#define ECL_LINEAR_ALGEBRA_QTALIGNEDMALLOC_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include "macros.hpp"
#include "formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

// This one is bad - it doesn't inline its headers (Eigen v3.01) - avoid it for now.

#ifdef ECL_EIGEN_IS_INTERNAL
  #include <ecl/Eigen3/QtAlignedMalloc>
#else
  #include <eigen3/Eigen/QtAlignedMalloc>
#endif

#endif /* ECL_LINEAR_ALGEBRA_QTALIGNEDMALLOC_HPP_ */
