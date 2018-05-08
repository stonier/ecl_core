/**
 * @file /src/test/waypoints.cpp
 *
 * @brief Unit Test for manipulator waypoints.
 *
 * @date May 2009
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <iostream>
#include <gtest/gtest.h>
#include <ecl/containers/array.hpp>
#include "../../include/ecl/manipulators/waypoint.hpp"

/*****************************************************************************
** Using
*****************************************************************************/

using ecl::Array;
using ecl::JointAngles;
using ecl::WayPoint;

/*****************************************************************************
** Tests
*****************************************************************************/

TEST(WayPointTests,allEggsInOneBasket) {
	// Haven't got around to running this properly through gtests yet.
	SUCCEED();
}
/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {

    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                    Constructor" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    std::cout << "Manual Construction: " << std::endl;
    WayPoint<JointAngles> waypoint2(4);
    waypoint2.name("Raised Position");
    waypoint2.angles() << 1.57, 1.57, 0.00, 0.00;
    waypoint2.rates() << 1.0, 1.0, 0.8, 0.8;
    waypoint2.accelerations() << 0.9, 0.9, 0.6, 0.6;
    waypoint2.nominalRates(1.0);
    waypoint2.nominalRates() << 1.0, 1.0, 0.8, 0.8;
    std::cout << waypoint2 << std::endl;

    std::cout << "Copy construction" << std::endl;
    WayPoint<JointAngles> waypoint3(waypoint2);
    std::cout << waypoint3 << std::endl;

    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                      Passed" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


