/**
 * @file /src/test/grid_map.cpp
 *
 * @brief Test the old inverse was the same as the new partial inverse function.
 *
 * @date October 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <iostream>
#include <gtest/gtest.h>
#include <ecl/linear_algebra.hpp>
#include <ecl/math.hpp>
#include "../../include/ecl/mobile_robot/differential_drive.hpp"

/*****************************************************************************
** Tests
*****************************************************************************/

TEST(DifferentialDriveTests,allEggsInOneBasket) {
  std::cout << std::endl;
  std::cout << "***********************************************************" << std::endl;
  std::cout << "              Pose to Base Differential" << std::endl;
  std::cout << "***********************************************************" << std::endl;
  std::cout << std::endl;

  ecl::linear_algebra::Vector3d a; a << 1.0, 2.0, ecl::pi/2.0;
  ecl::linear_algebra::Vector3d b; b << 2.0, 3.0, ecl::pi;

  ecl::linear_algebra::Vector2d base_differential;
  base_differential = ecl::DifferentialDrive::Kinematics::PoseToBaseDifferential(a, b);

  std::cout << "Base Differential: " << base_differential.transpose() << std::endl;
  std::cout << std::endl;

  float abs_error = 0.01;
  EXPECT_NEAR(std::sqrt(2.0), base_differential[0], abs_error);
  EXPECT_NEAR(ecl::pi/2.0, base_differential[1], abs_error);
}
/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


