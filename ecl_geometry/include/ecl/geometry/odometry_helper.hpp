#ifndef ECL_GEOMETRY_ODOMETRY_HELPER_HPP_
#define ECL_GEOMETRY_ODOMETRY_HELPER_HPP_

#include "odometry.hpp"

namespace ecl {
namespace geometry {

double distance(const Pose2D& pose, const Trajectory2D& trajectory);
double distance(const Position2D& pose, const Trajectory2D& trajectory);

bool empty(const Trajectory2DPtr& trajectory_ptr);
bool empty(const Odom2DTrajectoryPtr& trajectory_ptr);

int size(const Trajectory2DPtr& trajectory);
int size(const Odom2DTrajectoryPtr& trajectory);

int size(const Trajectory2D& trajectory);
int size(const Odom2DTrajectory& trajectory);

double distance(const Odom2D& a, const Odom2D& b);
double distance(const Pose2D& a, const Pose2D& b);
double distance(const Pose2D& a, const Odom2D& b);
double distanceSqared(const Odom2D& a, const Odom2D& b);
double distanceSqared(const Pose2D& a, const Pose2D& b);

void addAtEnd(Trajectory2D& target, const Trajectory2D& addition);
void addAtEnd(Odom2DTrajectory& target, const Odom2DTrajectory& addition);

Trajectory2DPtr vectorToTrajectory(const std::vector<Pose2D>& vec);
Odom2DTrajectoryPtr vectorToTrajectory(const std::vector<Odom2D>& vec);

void resize(Trajectory2D& trajectory, const int& size);
void resize(Odom2DTrajectory& trajectory, const int& size);

void setAt(Trajectory2D& trajectory, const int& index,  const Pose2D& pose);
void setAt(Odom2DTrajectory& trajectory, const int& index, const Odom2D& odom);

Pose2D getAt(const Trajectory2D& trajectory, const int& index);
Odom2D getAt(const Odom2DTrajectory& trajectory, const int& index);

Pose2D getFront(const Trajectory2D& trajectory);
Pose2D getBack(const Trajectory2D& trajectory);
Odom2D getFront(const Odom2DTrajectory& trajectory);
Odom2D getBack(const Odom2DTrajectory& trajectory);

Trajectory2D getPoses(const Odom2DTrajectory& trajectory);
Twist2DVector getTwists(const Odom2DTrajectory& trajectory);

void setVelocityX(Odom2D& odom, const float& value);
void setVelocityY(Odom2D& odom, const float& value);
void setVelocityAngular(Odom2D& odom, const float& value);

void setVelocityX(Twist2D& twist, const float& value);
void setVelocityY(Twist2D& twist, const float& value);
void setVelocityAngular(Twist2D& twist, const float& value);

void setX(Odom2D& odom, const float& value);
void setY(Odom2D& odom, const float& value);
void setYaw(Odom2D& odom, const float& value);

void setX(Pose2D& pose, const float& value);
void setY(Pose2D& pose, const float& value);
void setYaw(Pose2D& pose, const float& value);

void setX(Position2D& position, const float& value);
void setY(Position2D& position, const float& value);

float getVelocityX(const Odom2D& odom);
float getVelocityY(const Odom2D& odom);
float getVelocityAngular(const Odom2D& odom);

float getVelocityX(const Twist2D& twist);
float getVelocityY(const Twist2D& twist);
float getVelocityAngular(const Twist2D& twist);

float getX(const Odom2D& odom);
float getY(const Odom2D& odom);
float getYaw(const Odom2D& odom);

Pose2D getPose(const Odom2D& odom);
Position2D getPosition(const Odom2D& odom);
Twist2D getTwist(const Odom2D& odom);

float getX(const Pose2D& pose);
float getY(const Pose2D& pose);
float getYaw(const Pose2D& pose);

Position2D getPosition(const Pose2D& pose);

float getX(const Position2D& position);
float getY(const Position2D& position);

} // namespace geometry
} // namsepace ecl

#endif

