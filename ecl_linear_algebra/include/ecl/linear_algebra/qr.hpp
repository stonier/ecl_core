/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/qr.hpp
 *
 * @brief Convenience eigen module loader (preloads the plugin).
 *
 * @date 28/07/2010
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_LINEAR_ALGEBRA_QR_HPP_
#define ECL_LINEAR_ALGEBRA_QR_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/linear_algebra/macros.hpp>
#include "formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen_plugin.hpp>
#endif

#ifdef ECL_EIGEN_IS_INTERNAL
  #include <ecl/Eigen3/QR>
#elif defined ECL_EIGEN_IS_INTERNAL_3_1_2          
  #include <ecl/Eigen3.1.2/QR>
#else
  #include <eigen3/Eigen/QR>
#endif

#endif /* ECL_LINEAR_ALGEBRA_QR_HPP_ */
