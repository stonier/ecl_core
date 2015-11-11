/**
 * @file /ecl_linear_algebra/src/lib/sophus_helpers.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <cmath>
#include <ecl/linear_algebra.hpp>
#include "../../include/ecl/linear_algebra/sophus/helpers.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace Sophus {

/*****************************************************************************
** Implementation
*****************************************************************************/

Eigen::Vector3f toPose2D(const Sophus::SE3f& pose)
{
  Eigen::Vector3f pose2d;

  Eigen::Matrix3f R = pose.rotationMatrix();
  float yaw_angle = std::atan2( R(1,0), R(0,0) );
  pose2d.head<2>() = pose.translation().head<2>();
  pose2d.z() = yaw_angle;
  return pose2d;
}

Sophus::SE3fPtr points2DToSophusTransform(float from_x, float from_y, float to_x, float to_y) {
  // copied code from output receiver
  Eigen::Vector3f origin(from_x, from_y, 0.0);
  double angle = std::atan2(to_y-from_y, to_x-from_x);
  Eigen::Quaternion<float> q; q = Eigen::AngleAxis<float>(angle, Eigen::Vector3f::UnitZ ());
  return std::make_shared<Sophus::SE3f>(q, origin);
//  std::cout << "  Origin: " << origin.transpose() << std::endl;
//  std::cout << "  Angle : " << angle << std::endl;
}

} // namespace Sophus
