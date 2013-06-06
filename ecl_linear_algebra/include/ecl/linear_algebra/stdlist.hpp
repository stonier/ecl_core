/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/stdlist.hpp
 *
 * @brief Convenience eigen module loader (preloads the plugin).
 *
 * @date 28/07/2010
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_STDLIST_HPP_
#define ECL_LINEAR_ALGEBRA_STDLIST_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include "formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

#include <Eigen/StdList>

#endif /* ECL_LINEAR_ALGEBRA_STDLIST_HPP_ */
