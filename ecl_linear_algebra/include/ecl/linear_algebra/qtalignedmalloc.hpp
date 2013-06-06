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

#include "formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

// This one is bad - it doesn't inline its headers (Eigen v3.01) - avoid it for now.

#include <Eigen/QtAlignedMalloc>

#endif /* ECL_LINEAR_ALGEBRA_QTALIGNEDMALLOC_HPP_ */
