#ifndef ECL_ODOMETRY_ODOMETRY_HELPER_HPP_
#define ECL_ODOMETRY_ODOMETRY_HELPER_HPP_

#include "odometry_typedefs.hpp"

namespace ecl {
namespace odometry {

/** @brief Shortest distance between a pose and a trajectory
 *
 * This uses straight lines between the trajectory poses
 * to calculate the distance to the pose
 */
double distance(const Pose2D& pose, const Trajectory2D& trajectory);
/** @brief Shortest distance between a position and a trajectory
 *
 * This uses straight lines between the trajectory poses
 * to calculate the distance to the pose
 */
double distance(const Position2D& position, const Trajectory2D& trajectory);

bool empty(const Trajectory2D& trajectory); /**< @brief Check if trajectory ptr is empty (ptr not set or has no poses) */
bool empty(const Odom2DTrajectory& trajectory); /**< @brief Check if trajectory ptr is empty (ptr not set or has no odometries) */

int size(const Trajectory2D& trajectory); /**< @brief Get the size of the trajectory */
int size(const Odom2DTrajectory& trajectory); /**< @brief Get the size of the trajectory */

double distance(const Odom2D& a, const Odom2D& b); /**< @brief Distance between the positions of odometries */
double distance(const Pose2D& a, const Pose2D& b); /**< @brief Distance between poses */
double distance(const Pose2D& a, const Odom2D& b); /**< @brief Distance between a pose and the position of a odometry */
double distanceSqared(const Odom2D& a, const Odom2D& b); /**< @brief Squared distance between the positions of odometries */
double distanceSqared(const Pose2D& a, const Pose2D& b); /**< @brief Squared distance between poses */

/**< @brief Concat two trajectories
 *
 * Adds a trajectory to the end of another trajectory.
 * Shouldn't be used for frequent adding because of bad performance.
 */
void addAtEnd(Trajectory2D& target, const Trajectory2D& addition);
/**< @brief Concat two odometry trajectories
 *
 * Adds a trajectory to the end of another trajectory.
 * Shouldn't be used for frequent adding because of bad performance.
 */
void addAtEnd(Odom2DTrajectory& target, const Odom2DTrajectory& addition);

Trajectory2D vectorToTrajectory(const std::vector<Pose2D>& vec); /**< @brief Convert vector of Pose2D to Trajectory2D */
Odom2DTrajectory vectorToTrajectory(const std::vector<Odom2D>& vec); /**< @brief Convert vector of Odom2D to Odom2DTrajectory */

/**< @brief Resizes trajectory appending uninitialised values if needed
 *
 * This is conservative, meaning elements in the trajectory don't change.
 * (Opposed to the default Eigen resize)
 */
void resize(Trajectory2D& trajectory, const int& size);
/**< @brief Resizes trajectory appending uninitialised values if needed
 *
 * This is conservative, meaning elements in the trajectory don't change.
 * (Opposed to the default Eigen resize)
 */
void resize(Odom2DTrajectory& trajectory, const int& size);

void setAt(Trajectory2D& trajectory, const int& index,  const Pose2D& pose); /**< @brief Set element at index of trajectory */
void setAt(Odom2DTrajectory& trajectory, const int& index, const Odom2D& odom); /**< @brief Set element at index of trajectory */

Pose2D getAt(const Trajectory2D& trajectory, const int& index); /**< @brief Get element of trajectory */
Odom2D getAt(const Odom2DTrajectory& trajectory, const int& index); /**< @brief Get element of trajectory */

Pose2D getFront(const Trajectory2D& trajectory); /**< @brief Get front (first) element of trajectory */
Pose2D getBack(const Trajectory2D& trajectory); /**< @brief Get back (last) element of trajectory */
Odom2D getFront(const Odom2DTrajectory& trajectory); /**< @brief Get front (first) element of trajectory */
Odom2D getBack(const Odom2DTrajectory& trajectory); /**< @brief Get back (last) element of trajectory */

Trajectory2D getPoses(const Odom2DTrajectory& trajectory); /**< @brief Extract poses of odom trajectory */
Twist2DVector getTwists(const Odom2DTrajectory& trajectory); /**< @brief Extract twists of odom trajectory */

void setVelocityX(Odom2D& odom, const float& value); /**< @brief Set linear velocity x direction */
void setVelocityY(Odom2D& odom, const float& value); /**< @brief Set linear velocity y direction */
void setVelocityAngular(Odom2D& odom, const float& value); /**< @brief Set angular velocity */

void setVelocityX(Twist2D& twist, const float& value); /**< @brief Set linear velocity x direction */
void setVelocityY(Twist2D& twist, const float& value); /**< @brief Set linear velocity y direction */
void setVelocityAngular(Twist2D& twist, const float& value); /**< @brief Set angular velocity */

void setX(Odom2D& odom, const float& value); /**< @brief Set x position */
void setY(Odom2D& odom, const float& value); /**< @brief Set y position */
void setYaw(Odom2D& odom, const float& value); /**< @brief Set yaw (heading) */

void setX(Pose2D& pose, const float& value); /**< @brief Set x position */
void setY(Pose2D& pose, const float& value); /**< @brief Set y position */
void setYaw(Pose2D& pose, const float& value); /**< @brief Set yaw (heading) */

void setX(Position2D& position, const float& value); /**< @brief Set x position */
void setY(Position2D& position, const float& value); /**< @brief Set y position */

float getVelocityX(const Odom2D& odom); /**< @brief Get linear velocity x direction */
float getVelocityY(const Odom2D& odom); /**< @brief Get linear velocity y direction */
float getVelocityAngular(const Odom2D& odom); /**< @brief Get angular velocity */

float getVelocityX(const Twist2D& twist); /**< @brief Get linear velocity x direction */
float getVelocityY(const Twist2D& twist); /**< @brief Get linear velocity y direction */
float getVelocityAngular(const Twist2D& twist); /**< @brief Get angular velocity */

float getX(const Odom2D& odom); /**< @brief Get x position */
float getY(const Odom2D& odom); /**< @brief Get y position */
float getYaw(const Odom2D& odom); /**< @brief Get yaw (heading) */

Pose2D getPose(const Odom2D& odom); /**< @brief Extract pose from odometry */
Position2D getPosition(const Odom2D& odom); /**< @brief Extract position from odometry */
Twist2D getTwist(const Odom2D& odom); /**< @brief Extract twist from odometry */

float getX(const Pose2D& pose); /**< @brief Get x position */
float getY(const Pose2D& pose); /**< @brief Get y position */
float getYaw(const Pose2D& pose); /**< @brief Get yaw (heading) */

Position2D getPosition(const Pose2D& pose); /**< @brief Extract position from pose */

float getX(const Position2D& position); /**< @brief Get x position */
float getY(const Position2D& position); /**< @brief Get y position */


/*****************************************************************************
** c++11 helpers
*****************************************************************************/

#if defined(ECL_CXX11_FOUND)

  bool empty(const Trajectory2DPtr& trajectory_ptr); /**< @brief Check if trajectory ptr is empty (ptr not set or has no poses) */
  bool empty(const Odom2DTrajectoryPtr& trajectory_ptr); /**< @brief Check if trajectory ptr is empty (ptr not set or has no odometries) */

  int size(const Trajectory2DPtr& trajectory); /**< @brief Get the size of the trajectory */
  int size(const Odom2DTrajectoryPtr& trajectory); /**< @brief Get the size of the trajectory */

  Trajectory2DPtr vectorToTrajectoryPtr(const std::vector<Pose2D>& vec); /**< @brief Convert vector of Pose2D to Trajectory2DPtr */
  Odom2DTrajectoryPtr vectorToTrajectoryPtr(const std::vector<Odom2D>& vec); /**< @brief Convert vector of Odom2D to Odom2DTrajectoryPtr */

#endif /*ECL_CXX11_FOUND*/

} // namespace odometry
} // namsepace ecl

#endif /*ECL_ODOMETRY_ODOMETRY_HELPER_HPP_*/

