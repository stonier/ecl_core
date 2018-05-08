/**
 * @file /src/test/trajectories.cpp
 *
 * @brief Unit Test for trajectories, results also get saved in a file.
 *
 * @date July, 1st, 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <ecl/containers/array.hpp>
#include <ecl/formatters/floats.hpp>
#include <ecl/formatters/strings.hpp>
#include <ecl/geometry/polynomial.hpp>
#include <ecl/geometry/spline_function.hpp>
#include "../../include/ecl/manipulators/waypoint.hpp"
#include "../../include/ecl/manipulators/trajectory.hpp"


/*****************************************************************************
** Using
*****************************************************************************/

using std::cout;
using std::endl;
using std::string;
using ecl::Array;
using ecl::RightAlign;
using ecl::Format;
using ecl::CubicPolynomial;
using ecl::GenericSplineFunction;
using ecl::SplineFunction;
using ecl::JointAngles;
using ecl::Trajectory;
using ecl::WayPoint;

/*****************************************************************************
** Tests
*****************************************************************************/

TEST(TrajectoryTests,allEggsInOneBasket) {
	// Haven't got around to running this properly through gtests yet.
	SUCCEED();
}

/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {

    Format<string> string_format; string_format.width(8); string_format.align(RightAlign);
    Format<double> format; format.width(8); format.precision(2); format.align(RightAlign);
    int n = 200;
    
    std::ofstream tension_file_output, linear_file_output;
	tension_file_output.open("tension_interpolation.dat");
	linear_file_output.open("linear_interpolation.dat");
	tension_file_output << "# Created by trajectories_output_to_file test." << endl;
	tension_file_output << "# name: tension_interpolation" << endl;
	tension_file_output << "# type: matrix" << endl;
	tension_file_output << "# rows: " << (n + 1) * 3 << endl;
	tension_file_output << "# columns: " << 1 + 2 * 3 << endl;
	tension_file_output << endl;
	linear_file_output << "# Created by trajectories_output_to_file test." << endl;
	linear_file_output << "# name: linear_interpolation" << endl;
	linear_file_output << "# type: matrix" << endl;
	linear_file_output << "# rows: " << (n + 1) * 3 << endl;
	linear_file_output << "# columns: " << 1 + 2 * 3 << endl;
	linear_file_output << endl;
	
    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                    Constructor" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    Trajectory<JointAngles> trajectory(2,"Crash Test Dummy");

    /******************************************
    ** Common Waypoint Parameters
    *******************************************/
    WayPoint<JointAngles> initial_waypoint(2), waypoint(2), final_waypoint(2);

    initial_waypoint.name("Initial Position");
    initial_waypoint.angles() << 1.0, 1.0;
    initial_waypoint.rates() << 0.0, 2.0;
    initial_waypoint.nominalRates(0.5);
    trajectory.append(initial_waypoint);

    waypoint.name("Second Waypoint");
    waypoint.angles() << 2.0, 0.0;
    waypoint.nominalRates(1.0);
    trajectory.append(waypoint);

    waypoint.name("Mid Waypoint");
    waypoint.angles() << 1.0, 5.0;
    waypoint.nominalRates(1.2);
    trajectory.append(waypoint);

    waypoint.name("Fourth Waypoint");
    waypoint.angles() << 3.0, 3.0;
    waypoint.nominalRates(0.5);
    trajectory.append(waypoint);

    final_waypoint.name("End Position");
    final_waypoint.angles() << 4.0, 2.0;
    final_waypoint.nominalRates(0.5);
    final_waypoint.rates() << 0.0, 1.0;
    trajectory.append(final_waypoint);

    std::cout << trajectory << std::endl;

    trajectory.maxAccelerations(5);

    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "              Tension Spline Interpolation" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    trajectory.tensionSplineInterpolation(4.0); // Tension arg

//    cout << string_format("t  ");
//    cout << string_format("y  ");
//    cout << string_format("y' ");
//    cout << string_format("y''");
//    cout << string_format("y  ");
//    cout << string_format("y' ");
//    cout << string_format("y''");
//    cout << endl;
    for ( int i = 0; i <= n; ++i ) {
        double x;
        if ( i != n ) {
        	x = i*(trajectory.duration())/n;
        } else {
        	x = trajectory.duration();
        }
//        cout << format(x);
//        cout << format(trajectory(0,x));
//        cout << format(trajectory.derivative(0,x));
//        cout << format(trajectory.dderivative(0,x));
//        cout << format(trajectory(1,x));
//        cout << format(trajectory.derivative(1,x));
//        cout << format(trajectory.dderivative(1,x));
//        cout << endl;
        
        tension_file_output << format(x);
        tension_file_output << format(trajectory(0,x));
        tension_file_output << format(trajectory.derivative(0,x));
        tension_file_output << format(trajectory.dderivative(0,x));
        tension_file_output << format(trajectory(1,x));
        tension_file_output << format(trajectory.derivative(1,x));
        tension_file_output << format(trajectory.dderivative(1,x));
        tension_file_output << endl;
    }


    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "            Smooth Linear Spline Interpolation" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    trajectory.maxAccelerations(5);
    trajectory.linearSplineInterpolation();

//    cout << string_format("t  ");
//    cout << string_format("y  ");
//    cout << string_format("y' ");
//    cout << string_format("y''");
//    cout << string_format("y  ");
//    cout << string_format("y' ");
//    cout << string_format("y''");
//    cout << endl;
    for ( int i = 0; i <= n; ++i ) {
		double x;
		if ( i != n ) {
			x = i*(trajectory.duration())/n;
		} else {
			x = trajectory.duration();
		}
//        cout << format(x);
//        cout << format(trajectory(0,x));
//        cout << format(trajectory.derivative(0,x));
//        cout << format(trajectory.dderivative(0,x));
//        cout << format(trajectory(1,x));
//        cout << format(trajectory.derivative(1,x));
//        cout << format(trajectory.dderivative(1,x));
//        cout << endl;

        linear_file_output << format(x);
        linear_file_output << format(trajectory(0,x));
        linear_file_output << format(trajectory.derivative(0,x));
        linear_file_output << format(trajectory.dderivative(0,x));
        linear_file_output << format(trajectory(1,x));
        linear_file_output << format(trajectory.derivative(1,x));
        linear_file_output << format(trajectory.dderivative(1,x));
        linear_file_output << endl;
    }


    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                      Passed" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    tension_file_output.close();
    linear_file_output.close();
	std::cout << "Trajectories written to files 'linear_interpolation.dat', 'tension_interpolation.dat'." << std::endl;
	
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

