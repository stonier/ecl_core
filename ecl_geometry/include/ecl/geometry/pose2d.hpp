/**
 * @file /ecl_geometry/include/ecl/geometry/pose.hpp
 *
 * The ECL pose library is a library of methods built on top of
 * Eigen & Sophus data structures. This has proven to be more flexible
 * than having custom c++ Pose2D / Pose3D classes unique to the ECL
 * as it permits conversion-free interactions with other libraries
 * that have also standardised on Eigen & Sophus.
 */
/*****************************************************************************
 ** Ifdefs
 *****************************************************************************/

#ifndef ecl_geometry_GEOMETRY_POSE2D_HPP_
#define ecl_geometry_GEOMETRY_POSE2D_HPP_

/*****************************************************************************
 ** Includes
 *****************************************************************************/

#include <ecl/linear_algebra.hpp>
#include <ecl/mpl/enable_if.hpp>

#include "angle.hpp"

/*****************************************************************************
 ** Namespaces
 *****************************************************************************/

namespace ecl {

/*****************************************************************************
 ** Pose2D - Eigen::Vector3d (x, y, heading) storage
 *****************************************************************************/
/**
 * @brief Concatenate 2d poses.
 *
 * This computes the pose of frame C relative to frame A. Poses
 * are (x, y, heading) triples in Eigen::Vector3f or Eigen::Vector3d
 * containers.
 *
 * @param pose_b_rel_a: pose of frame B relative to frame A
 * @param pose_c_rel_b: pose of frame C relative to frame B
 * @param dummy: enforces compile time check for floats or doubles
 * @return Eigen::Matrix<Float, 3, 1>: pose of frame C relative to frame A
 */
template <typename Float>
linear_algebra::Matrix<Float, 3, 1> concatenate_poses(
  const linear_algebra::Matrix<Float, 3, 1> &pose_b_rel_a,
  const linear_algebra::Matrix<Float, 3, 1> &pose_c_rel_b,
  typename enable_if<ecl::is_float<Float> >::type* dummy = 0)
{
  (void) dummy;
  linear_algebra::Matrix<Float, 3, 1> pose_c_rel_a;
  Float c = std::cos(pose_b_rel_a[2]);
  Float s = std::sin(pose_b_rel_a[2]);
  pose_c_rel_a <<
    pose_b_rel_a[0] + c*pose_c_rel_b[0] - s*pose_c_rel_b[1],
    pose_b_rel_a[1] + s*pose_c_rel_b[0] + c*pose_c_rel_b[1],
    wrap_angle(pose_b_rel_a[2] + pose_c_rel_b[2]);
  // c++03 copy elision will guarantee no copy is made
  return pose_c_rel_a;
}

/**
 * @brief Extend poses.
 *
 * This concatenates the original pose with another pose, in place.
 * i.e. if pose_b_rel_a is extended by pose_c_rel_b then
 * pose_b_rel_a *becomes* pose_c_rel_a.
 *
 * @param pose: the original pose (will be updated)
 * @param extending_pose: pose to extend with
 * @param dummy: enforces compile time check for floats or doubles
 */
template <typename Float>
void extend_pose(
  linear_algebra::Matrix<Float, 3, 1> &pose,
  const linear_algebra::Matrix<Float, 3, 1> &extending_pose,
  typename enable_if<ecl::is_float<Float> >::type* dummy = 0)
{
  (void) dummy;
  Float c = std::cos(pose[2]);
  Float s = std::sin(pose[2]);
  pose <<
    pose[0] + c*extending_pose[0] - s*extending_pose[1],
    pose[1] + s*extending_pose[0] + c*extending_pose[1],
    wrap_angle(pose[2] + extending_pose[2]);
}

/*****************************************************************************
 ** Pose2D Class
 *****************************************************************************/

/**
 * @brief A simple convenience class for 2d poses.
 *
 * This could get more complicated, but likely you'll want
 * your own (use the methods above). One extension here that
 * might be useful is an alternative backend (enable via
 * a Storage template type that can be either an eigen
 * Vector3 or Transform depending on the user's
 * requirements.
 */
template <typename Float>
class Pose2D {
public:
  /****************************************
   * Typedefs
   ***************************************/
  using XYH = linear_algebra::Matrix<Float, 3, 1>;
  using Translation = linear_algebra::Matrix<Float, 2, 1>;
  using RotationMatrix = linear_algebra::Matrix<Float, 2, 2>;

  /****************************************
   * Constructors & Destructors
   ***************************************/
  /**
   * @brief Default constructor
   *
   * @param xyh: x, y, heading wrapped in an eigen vector3d type.
   */
  Pose2D(): xyh(0.0) {}

  /**
   * @brief Construction by element.
   *
   * @param x: x-translation
   * @param y: y-translation
   * @param h: heading (radians)
   */
  Pose2D(const float& x, const float& y, const float& h) {
    xyh << x, y, h;
  }

  /**
   * @brief Construction by container.
   *
   * @param xyh: x, y, heading wrapped in an eigen vector3d type.
   */
  Pose2D(const XYH& xyh) : xyh(xyh) {}

  // moving eigen vectors only possible for VectorXd types (using Vector3d here)

  /**
   * @brief Concatenate this pose with another.
   *
   * If this pose represents pose_b_rel_a, and the incoming pose is pose_c_rel_b,
   * then the return pose via this operator would be pose_c_rel_a.
   *
   * @param pose : relative to this pose's frame of reference
   * @return Pose2D<Float> : the concatenated pose
   */
  Pose2D<Float> operator*(const Pose2D<Float> &pose) const {
    return concatenate_poses(this->xyh, pose);
  }

  /**
   * @brief Extend this pose with the incoming pose.
   *
   * If this pose represents pose_b_rel_a, and the incoming pose is pose_c_rel_b,
   * then the updated pose via this operator would be pose_c_rel_a.
   *
   * @param pose : relative to this pose's frame of reference
   * @return Pose2D<Float>& : handle to the updated pose
   */
  Pose2D<Float>& operator*=(const Pose2D<Float> &pose) {
    extend_pose(this->xyh, pose.xyh);
    return (*this);
  }

  /******************************************
  ** Accessors
  *******************************************/
  const Float& x() const { return xyh[0]; }        //!< @brief Get the x-coordinate.
  const Float& y() const { return xyh[1]; }        //!< @brief Get the y-coordinate.
  const Float& heading() const { return xyh[2]; }  //!< @brief Get the heading.
  const Translation& translation() const { return xyh. template head<2>(); }
  /**
   * @brief Representation of the heading in matrix form.
   **/
  const RotationMatrix& rotationMatrix() const {
    Float c = std::cos(xyh[2]);
    Float s = std::sin(xyh[2]);
    return (RotationMatrix() << c, -s, s, c).finished();
  }

private:
  XYH xyh;
};

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace ecl

#endif /* ecl_geometry_GEOMETRY_POSE2D_HPP_ */
