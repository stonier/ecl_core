/**
 * @file /src/test/pose2d.cpp
 *
 * @ingroup UnitTests
 *
 * Use this to test the pose2d methods.
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <gtest/gtest.h>
#include <ecl/linear_algebra.hpp>
#include <ecl/math/constants.hpp>
#include "../../include/ecl/geometry/pose2d.hpp"

/*****************************************************************************
** Conveniences
*****************************************************************************/

template <typename Float>
using XYH = ecl::linear_algebra::Matrix<Float, 3, 1>;

/*****************************************************************************
** Tests
*****************************************************************************/

TEST(Pose2D,concatentate) {
  XYH<float> pose_b_rel_a, pose_c_rel_b, pose_c_rel_a;
  pose_b_rel_a << 1.0, 0.0, ecl::pi / 2.0;
  pose_c_rel_b << 1.0, 0.0, - ecl::pi;
  pose_c_rel_a << ecl::concatenate_poses(pose_b_rel_a, pose_c_rel_b);
  std::cout << "Concatenated Pose: " << pose_c_rel_a.transpose() << std::endl;

  float abs_error = 0.01;
  EXPECT_NEAR(1.0, pose_c_rel_a[0], abs_error);
  EXPECT_NEAR(1.0, pose_c_rel_a[1], abs_error);
  EXPECT_NEAR(- ecl::pi / 2.0, pose_c_rel_a[2], abs_error);
}

TEST(Pose2D,extend) {
  XYH<float> pose, extension;
  pose << 1.0, 0.0, ecl::pi / 2.0;
  extension << 1.0, 0.0, - ecl::pi;
  ecl::extend_pose(pose, extension);
  std::cout << "Extended Pose: " << pose.transpose() << std::endl;

  float abs_error = 0.01;
  EXPECT_NEAR(1.0, pose[0], abs_error);
  EXPECT_NEAR(1.0, pose[1], abs_error);
  EXPECT_NEAR(- ecl::pi / 2.0, pose[2], abs_error);
}

TEST(Pose2D,convenience_class) {
  ecl::Pose2D<float> pose(1.0, 0.0, ecl::pi / 2.0);
  ecl::Pose2D<float> update(1.0, 0.0, - ecl::pi);
  pose *= update;
  std::cout << "Pose Operator: " << pose.x() << ", " << pose.y() << ", " << pose.heading() << std::endl;
  float abs_error = 0.01;
  EXPECT_NEAR(1.0, pose.x(), abs_error);
  EXPECT_NEAR(1.0, pose.y(), abs_error);
  EXPECT_NEAR(- ecl::pi / 2.0, pose.heading(), abs_error);
}

/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


