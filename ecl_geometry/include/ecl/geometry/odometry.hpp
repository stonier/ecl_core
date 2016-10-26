#ifndef ECL_GEOMETRY_LEGACY_ODOMETRY_HPP_
#define ECL_GEOMETRY_LEGACY_ODOMETRY_HPP_

#include <Eigen/Dense>
#include <memory>

namespace ecl {
namespace geometry {


typedef Eigen::Vector2f Position2D; /**< @brief 2D float representation of planner poses (x, y, heading). **/
typedef std::shared_ptr<Position2D> Position2DPtr;

typedef Eigen::Matrix2Xf Path2D;
typedef std::shared_ptr<Path2D> Path2DPtr;

typedef Eigen::Vector3f Pose2D; /**< @brief 2D float representation of planner poses (x, y, heading). **/
typedef std::shared_ptr<Pose2D> Pose2DPtr;

typedef Eigen::Matrix3Xf Trajectory2D;
typedef std::shared_ptr<Trajectory2D> Trajectory2DPtr;


typedef Eigen::Vector3f Twist2D; /**< @brief 2D float representation of planner twist (linear velocity x and y, angular velocity). **/
typedef std::shared_ptr<Twist2D> Twist2DPtr;

typedef Eigen::Matrix3Xf Twist2DVector;
typedef std::shared_ptr<Twist2DVector> Twist2DVectorPtr;

typedef Eigen::Matrix<float, 6, 1> Odom2D;
typedef std::shared_ptr<Odom2D> Odom2DPtr;

typedef Eigen::Matrix<float, 6, Eigen::Dynamic> Odom2DTrajectory;
typedef std::shared_ptr<Odom2DTrajectory> Odom2DTrajectoryPtr;

} // namespace geometry
} // namespace ecl

#endif
