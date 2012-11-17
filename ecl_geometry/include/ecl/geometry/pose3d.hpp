/**
 * @file /ecl_geometry/include/ecl/geometry/pose2d.hpp
 *
 * @brief Pose representations.
 *
 * These are particularly suited for mobile robot representaitons.
 *
 * @date September 2010
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_GEOMETRY_POSE3D_HPP_
#define ECL_GEOMETRY_POSE3D_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/linear_algebra.hpp>

#ifdef ECL_USES_EIGEN2
  #include "pose3d_eigen2.hpp"
#else
  #include "pose3d_eigen3.hpp"
#endif

#endif /* ECL_GEOMETRY_POSE3D_HPP_ */
