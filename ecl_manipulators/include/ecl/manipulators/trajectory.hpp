/**
 * @file /include/ecl/manipulators/trajectory.hpp
 *
 * @brief Trajectory generation for manipulators.
 *
 * @date May 2009
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_MANIPULATORS_TRAJECTORY_HPP_
#define ECL_MANIPULATORS_TRAJECTORY_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include "types.hpp"
#include "waypoint.hpp"
#include <ecl/geometry/polynomial.hpp>
#include <ecl/geometry/function_math.hpp>
#include <ecl/geometry/smooth_linear_spline.hpp>
#include <ecl/geometry/spline_function.hpp>
#include <ecl/geometry/tension_spline.hpp>
#include <ecl/concepts/streams.hpp>
#include <ecl/exceptions/macros.hpp>
#include <ecl/exceptions/data_exception.hpp>
#include <ecl/exceptions/standard_exception.hpp>
#include <ecl/utilities/parameter.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Interface [Trajectory][PrimaryTemplate]
*****************************************************************************/
/**
 * @brief  Primary template for manipulator trajectories.
 *
 * This is not intended to be used directly, it just provides the primary
 * template for specialisations of the type enum.
 *
 * @tparam Type : manipulator state representation type (either joint or cartesian based).
 *
 * @sa Trajectory<N,JointAngles>.
 **/
template <enum ManipulatorAngleType Type = JointAngles>
class Trajectory {
    private:
        /**
         * @brief Unreachable constructor.
         *
         * Constructor, declared privately to ensure that this class
         * cannot be instantiated directly.
         */
        Trajectory () {};
        virtual ~Trajectory () {};
};

/*****************************************************************************
** Interface [Trajectory][JointAngles]
*****************************************************************************/
/**
 * @brief  Joint angle based manipulator trajectory.
 *
 * Joint angle based manipulator trajectory. Construction simply provides an
 * empty instantiation for the trajectory. You must
 *
 * - Populate it with desired way points (use the append method).
 * - Generate the interpolation (use one of the interpolators).
 *
 * to fully define the resulting trajectory.
 *
 * @sa Trajectory.
 **/
template <>
class Trajectory<JointAngles> {
    public:
        /**
         * @brief Default constructor, only (optionally) configures the trajectory name.
         *
         * @param name_identifier : string identifier for the trajectory name.
         */
        Trajectory(const char* name_identifier = "") :
            name(name_identifier)
        {}
        /**
         * @brief Configures the joint dimension, and also (optionally) the trajectory name.
         *
         * @param dimension : number of joints in this trajectory.
         * @param name_identifier : string identifier for the trajectory name.
         */
        Trajectory(const unsigned int& dimension, const char* name_identifier = "") :
            name(name_identifier),
            spline_functions(dimension),
            max_accelerations(Array<double>::Constant(dimension,0.0))
        {}

        /**
         * @brief Default destructor.
         *
         * Cleans up the memory allocations for the spline functions.
         */
        virtual ~Trajectory() { clearSplines(); waypoints.clear(); }
        /**
         * @brief Clear the waypoints and splines.
         */
        void clear() { clearSplines(); waypoints.clear(); }
        /**
         * @brief Number of waypoints in the trajectory.
         *
         * @return unsigned int : number of waypoints stored in the trajectory.
         */
        unsigned int size() const { return waypoints.size(); }

        /**
         * @brief Dimension, or degrees of freedom for the trajectory.
         *
         * This is the number of joints being interpolated by the trajectory.
         * @return int : number of joints.
         */
        unsigned int dimension() const { return max_accelerations.size(); }

        /**
         * @brief Reset the dimension, or degrees of freedom for the trajectory.
         *
         * Reset the number of joints being interpolated by the trajectory.
         *
         * @param dim : number of joints in this trajectory.
         */
        void redimension(const unsigned int &dim) {
        	clear();
        	spline_functions.resize(dim);
        	max_accelerations = Array<double>::Constant(dim,0.0);
        }

        /**
         * @brief Appends a waypoint to the trajectory specification.
         *
         * This is the only means of configuring waypoints for the trajectory.
         * Note that you cannot delete them, nor insert them into the middle
         * of the waypoint sequence. These functions are not really necessary
         * and just complicate the interface, but keep it in mind when programming
         * for trajectories.
         *
         * @exception : StandardException : throws if waypoint dimension doesn't match.
         */
        void append(const WayPoint<JointAngles> &waypoint) ecl_assert_throw_decl(StandardException) {
        	ecl_assert_throw(dimension() == waypoint.dimension(), StandardException(LOC, InvalidInputError, "Mismatched trajectory and waypoint dimensions.") );
            waypoints.push_back(waypoint);
        }

        /**
         * @brief Get the last waypoint in the trajectory.
         *
         * This is just a utility function for checking the last waypoint in the
         * trajectory.
         *
         * @return const WayPoint<JointAngles>& : const handle to the last waypoint in the traectory.
         */
        WayPoint<JointAngles>& last() {
        	return waypoints.back();
        }

        /**
         * @brief Const version of the last waypoint in the trajectory.
         *
         * This is just a utility function for checking the last waypoint in the
         * trajectory.
         *
         * @return const WayPoint<JointAngles>& : const handle to the last waypoint in the traectory.
         */
        const WayPoint<JointAngles>& last() const {
        	return waypoints.back();
        }
        /**
         * @brief Get a handle to the specified waypoint.
         *
         * This is just a utility function for retrieving a waypoint (const version).
         *
         * @param index : index of the waypoint to get a handle to.
         * @return WayPoint : the waypoint, if index was correct.
         *
         * @exception : StandardException : throws if index is outside the number of stored waypoints [debug mode only].
         */
        const WayPoint<JointAngles>& waypoint(const unsigned int &index) ecl_assert_throw_decl(StandardException) {
        	ecl_assert_throw(index < waypoints.size(), StandardException(LOC, OutOfRangeError, "The index used exceeds the number of waypoints stored in the trajectory."));
        	return waypoints[index];
        }

        /**
         * @brief Generate a tension spline interpolation from the specified waypoints.
         *
         * This generates an interpolation across the waypoints with the following characteristics.
         *
         * - Interpolation begins and ends with y' = y'' = 0.
         * - C2 continuous.
         * - Spline functions are connected as follows:
         *   - Quintic Polynomial : needed to ensure y' = y'' = 0.
         *   - Tension Spline : guarantees C2 continuity across the interpolation.
         *   - Quintic Polynomial : needed to ensure y' = y'' = 0.
         *
         * The quintics are generated from internally generated pseudo-waypoints to ensure that the
         * initial and final resting conditions are met.
         *
         * Before you call this function, make sure the following requirements are met.
         * - @ref ecl::WayPoint "Waypoints" are assigned with following data set:
         *   - angles (y)
         *   - nominal rates (i.e. estimated velocities) OR durations
         *   - maximum accelerations have been set (via this classes maxAccelerations methods)
         */
        void tensionSplineInterpolation(const double &tension) ecl_assert_throw_decl(StandardException);
        /**
         * @brief Generate a smoothed linear spline interpolation from the specified waypoints.
         *
         * This generates an interpolation across the waypoints with the following characteristics.
         *
         * - Interpolation begins and ends with y' = y'' = 0.
         * - C2 continuous.
         * - Spline functions are connected as follows:
         *   - Quintic Polynomial : needed to ensure y' = y'' = 0.
         *   - Smooth Linear Spline : composition of segments and corners.
         *   - Quintic Polynomial : needed to ensure y' = y'' = 0.
         *
         * The quintics are generated from internally generated pseudo-waypoints to ensure that the
         * initial and final resting conditions are met.
         *
         * Before you call this function, make sure the following requirements are met.
         * - @ref ecl::WayPoint "Waypoints" are assigned with following data set:
         *   - angles (y)
         *   - nominal rates (i.e. estimated velocities) OR durations
         *   - maximum accelerations have been set (via this classes maxAccelerations methods)
         */
        void linearSplineInterpolation() throw(StandardException);

        /**
         * @brief Access the value of the joint trajectory at the specified point.
         * @param joint : specifies the joint you are interested in.
         * @param time : the time at which you wish to calculate the value for.
         * @return double : the value of the specified joint trajectory at x.
         * @exception : StandardException : throws if input time value is outside the domain [debug mode only].
         */
        double operator ()(const unsigned int& joint, const double& time ) ecl_assert_throw_decl(StandardException);
        /**
         * @brief Access the derivative of the joint trajectory at the specified point.
         * @param joint : specifies the joint you are interested in.
         * @param time : the time at which you wish to calculate the value for.
         * @return double : the derivative of the specified joint trajectory at x.
         * @exception : StandardException : throws if input time value is outside the domain [debug mode only].
         */
        double  derivative(const unsigned int& joint, const double& time ) ecl_assert_throw_decl(StandardException);
        /**
         * @brief Access the 2nd derivative of the joint trajectory at the specified point.
         * @param joint : specifies the joint you are interested in.
         * @param time : the time at which you wish to calculate the value for.
         * @return double : the 2nd derivative of the specified joint trajectory at x.
         * @exception : StandardException : throws if input time value is outside the domain [debug mode only].
         */
        double dderivative(const unsigned int& joint, const double& time ) ecl_assert_throw_decl(StandardException);

        /*********************
        ** Accessors
        **********************/
        /**
         * @brief Handle to the max accelerations array, use to initialise the polynomial.
         *
         * This returns a handle to the max accelerations array. Use this with
         * the comma initialiser to conveniently set the polynomial.
         *
         * @code
         * Trajectory<2> trajectory;
         * trajectory.maxAccelerations() = 0.8,0.6;
         * @endcode
         *
         * @return Array<double>& : reference to the max accelerations array.
         **/
        Array<double>& maxAccelerations() { return max_accelerations; };
        /**
         * @brief Configure the entire trajectory with a uniform max acceleration bound.
         *
         * Configure the entire trajectory with a uniform max acceleration bound
         * (i.e. each joint's acceleration is limited similarly).
         *
         * @param max_acceleration : the uniform maximum acceleration bound to use.
         */
        void maxAccelerations(const double &max_acceleration) {
        	for ( unsigned int i = 0; i < dimension(); ++i ) {
        		max_accelerations[i] = max_acceleration;
        	}
        }
        /**
         * @brief Non-modifiable handle to the max accelerations array.
         *
         * @return const Array<double,N>& : non-modifiable reference to the max accelerations array.
         **/
        const Array<double>& maxAccelerations() const { return max_accelerations; };

        /******************************************
        ** Streaming
        *******************************************/
        /**
         * @brief Streaming output insertion operator for for waypoints.
         *
         * Streaming output insertion operator for waypoints.
         *
         * @tparam OutputStream : the type of stream being used.
         *
         * @param ostream : the output stream being used.
         * @param trajectory : the trajectory.
         * @return OutputStream : the output stream.
         */
        template <typename OutputStream>
        friend OutputStream& operator << (OutputStream &ostream, Trajectory<JointAngles> &trajectory);

        /******************************************
        ** Parameters
        *******************************************/
        /**
         * @brief Total trajectory duration (in seconds).
         *
         * Trajectory duration (in seconds).
         *
         * @return const double& : the time required for the entire trajectory.
         **/
        const double& duration() const { return trajectory_duration; }
        Parameter<std::string> name; /**< @brief String name identifier. **/

    private:
        std::vector< WayPoint<JointAngles> > waypoints;
        Array< std::vector<GenericSplineFunction*> > spline_functions;
        Array< double> max_accelerations;
        double trajectory_duration;

        /**
         * @brief Clean up the memory allocated to the spline functions.
         *
         * This is used internally by the various interpolation algorithms.
         */
public:
        void clearSplines();
        /**
         * Unlike the other generators, this generates the spline over all the waypoints.
         * It is not used in combination with another spline function.
         */
        Array<SmoothLinearSpline> generateLinearSplines() throw(DataException<int>);
        /**
         * This creates the tension splines across waypoints w_0 -> w_n for the
         * quinticTensionInterpolation. Note that the quintic tension will
         * insert pseudo points at the beginning and end later which will forcibly
         * modify the behaviour of the tension spline endpoints for specific boundary conditions.
         */
        Array<TensionSpline> generateTensionSplines(const double& tension, const double initial_time = 0.0);
        /**
         * This checks various properties of the waypoints to make sure they're valid.
         * Generally, this is used by the interpolations, who then throw if something's
         * gone wrong.
         */
        bool validateWaypoints(unsigned int min_no_waypoints);
        /**
         * This uses the nominal rates to guess durations between each waypoint.
         * Generally, this is used by the interpolations, who then throw if something's
         * gone wrong.
         */
        bool initialiseWaypointDurations();
        /**
         * This is a convenient function for interpolation members to use to
         * update the duration with the latest calculation determined from
         * the sum of the waypoint durations. This is oft used since the
         * interpolations will often adjust the waypoint durations while
         * interpolating.
         */
        void updateDuration();
};

/*****************************************************************************
** Implementation [Trajectory][Streaming]
*****************************************************************************/

template <typename OutputStream>
OutputStream& operator << (OutputStream &ostream, Trajectory<JointAngles> &trajectory) {

	ecl_compile_time_concept_check(StreamConcept<OutputStream>);

    for (unsigned int i = 0; i < trajectory.waypoints.size(); ++i ) {
        ostream << "Waypoint " << i << "\n";
        ostream << trajectory.waypoints[i] << "\n";
    }
    ostream.flush();
    return ostream;
}

}; // namespace ecl

#endif /* ECL_MANIPULATORS_TRAJECTORY_HPP_ */
