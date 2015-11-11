/**
 * @file /ecl_linear_algebra/include/ecl/linear_algebra/eigen.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ecl_linear_algebra_LINEAR_ALGEBRA_EIGEN_HPP_
#define ecl_linear_algebra_LINEAR_ALGEBRA_EIGEN_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include "eigen/formatters.hpp"

#ifndef EIGEN_MATRIXBASE_PLUGIN
  #define EIGEN_MATRIXBASE_PLUGIN <ecl/linear_algebra/eigen/plugin.hpp>
#endif

#include <Eigen/Cholesky>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>
#include <Eigen/Householder>
#include <Eigen/Jacobi>
// #include <Eigen/LeastSquares> // This is an eigen2 support module, forget it.
#include <Eigen/LU>
#include <Eigen/QR>
// This one is bad - it doesn't inline its headers (Eigen v3.01) - avoid it for now.
// #include <Eigen/QtAlignedMalloc>
#ifdef EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
  #include <Eigen/Sparse>
#endif
#include <Eigen/StdDeque>
#include <Eigen/StdList>
#include <Eigen/StdVector>
#include <Eigen/SVD>

#endif /* ecl_linear_algebra_LINEAR_ALGEBRA_EIGEN_HPP_ */
