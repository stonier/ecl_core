/**
 * @file /ecl_mobile_robot/src/lib/kinematics/differential_drive.cpp
 *
 * @brief Implementation of the differential drive class.
 *
 * @date May 2010
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/linear_algebra.hpp>
#include <ecl/geometry/angle.hpp>
#include "../../include/ecl/mobile_robot/kinematics/differential_drive.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {
namespace mobile_robot {

/*****************************************************************************
** Using
*****************************************************************************/

using ecl::Angle;
using ecl::linear_algebra::Vector2d;
using ecl::linear_algebra::Vector3d;
using ecl::linear_algebra::Rotation2D;

/*****************************************************************************
** Implementation [Kinematics]
*****************************************************************************/

ecl::linear_algebra::Vector3d DifferentialDriveKinematics::poseUpdateFromWheelDifferential(const double &dleft, const double& dright) const {

  double ds = radius*(dleft+dright)/2.0;
  double domega = radius*(dright-dleft)/bias;
  // Local robot frame of reference has the x axis pointing forward
  // Since the pose update is using the robot frame of reference, the y update is zero
  ecl::linear_algebra::Vector3d pose_update;
  pose_update << ds, 0, ecl::wrap_angle(domega);
  return pose_update;
}

ecl::linear_algebra::Vector3d DifferentialDriveKinematics::poseUpdateFromBaseDifferential(
    const double & translation,
    const double & rotation
) const {
  // Local robot frame of reference has the x axis pointing forward
  // Since the pose update is using the robot frame of reference, the y update is zero
  ecl::linear_algebra::Vector3d pose_update;
  pose_update << translation, 0, ecl::wrap_angle(rotation);
  return pose_update;
}

Vector2d DifferentialDriveKinematics::baseToWheelVelocities(const double &linear_velocity, const double &angular_velocity) const {
//	radius*(theta_dot_l+theta_dot_r)/2.0 = linear_velocity
//	radius*(theta_dot_r-theta_dot_l)/bias = angular_velocity
	Vector2d rates;
	double right = (2*linear_velocity+angular_velocity*bias)/(2*radius);
	double left = 2*linear_velocity/radius - right;
	rates << left, right;
	return rates;
}

Vector2d DifferentialDriveKinematics::PoseToBaseDifferential(
    const ecl::linear_algebra::Vector3d &a,
    const ecl::linear_algebra::Vector3d &b)
{
  Vector2d diff;
  diff << b[0] - a[0], b[1] - a[1];
  // This rotation doesn't affect the magnitude of ds,
  // but it so the sign can work out properly
  Vector2d dr = ecl::Angle<double>(a[2]).rotationMatrix().inverse()*diff;
  double ds = sqrt(dr(0)*dr(0)+dr(1)*dr(1));
  if ( dr(0) < 0.0 ) {
    ds = -ds;
  }
  double dtheta = b[2] - a[2]; // difference in headings
  ecl::wrap_angle(dtheta);

  return (diff << ds, dtheta).finished();
}

} // namespace mobile_robot
} // namespace ecl
