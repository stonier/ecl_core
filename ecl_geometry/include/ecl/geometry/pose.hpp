/**
 * @file /ecl_geometry/include/ecl/geometry/pose.hpp
 *
 * It is much more flexible for users to have standard pose data structures
 * that can be passed around easily (often with existing code of their
 * own) and have an accompanying library for extra functionality than to
 * have custom c++ pose classes (as we do in pose2d.hpp and pose3d.hpp).
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ecl_geometry_GEOMETRY_POSE_HPP_
#define ecl_geometry_GEOMETRY_POSE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/linear_algebra.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Interfaces
*****************************************************************************/

typedef Eigen::Vector3f SimplePose2D;  /**< @brief 2D float representation of planner poses (x, y, heading). **/
typedef Sophus::SE3f    SimplePose3D;  /**< @brief 3D float representation of planner poses. **/

// Haven't had the need to use doubles yet...

/*****************************************************************************
** Trailers
*****************************************************************************/

} // namespace ecl

#endif /* ecl_geometry_GEOMETRY_POSE_HPP_ */
