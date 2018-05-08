/**
 * @file /include/ecl/manipulators/waypoint.hpp
 *
 * @brief Waypoint definitions for various manipulator contexts.
 *
 * Waypoints designating manipulator position and orientation in free space.
 *
 * @date May 2009
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_MANIPULATORS_WAYPOINT_HPP_
#define ECL_MANIPULATORS_WAYPOINT_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <string>
#include "types.hpp"
#include <ecl/containers/array.hpp>
#include <ecl/utilities/parameter.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Class [WayPoint<ManipulatorAngleType>]
*****************************************************************************/
/**
 * @brief Primary template for waypoints.
 *
 * This is not intended to be used directly, it just provides the primary
 * template for specialisations of the type enum.
 *
 * @tparam Type : the type of waypoint (either joint or cartesian based).
 *
 * @sa WayPoint<JointAngles>.
 */
template<enum ManipulatorAngleType Type = JointAngles>
class WayPoint {
    private:
        /**
         * @brief Unreachable constructor.
         *
         * Constructor, declared privately to ensure that this class
         * cannot be instantiated directly.
         */
        WayPoint() {};
};

/*****************************************************************************
** Class [WayPoint<unsigned int N,JointAngles>]
*****************************************************************************/
/**
 * @brief WayPoint specialisation with joint (motor) angle storage format.
 *
 * This class can be used to store waypoints in joint/motor angle format.
 * It is not especially useful for navigational waypoints, but often
 * the only storage format required for robotic arm tasks. This is intended
 * to be a very light class.
 *
 * @tparam N : no. of degrees of freedom for this waypoint.
 *
 * @sa @ref WayPoint "WayPoint".
 **/
template <>
class WayPoint<JointAngles>
{
    public:
        typedef Array<double> JointDataArray; /**< @brief A convenient typedef to the underlying storage array. **/


        /******************************************
        ** Constructors
        *******************************************/
        /**
         * @brief Default constructor.
         *
         * Configures the waypoint to be of zero dimension. Make sure you use the
         * redimension function later to set the dimension.
         **/
        WayPoint() :
            name(""),
            duration(0.0),
            rates_configured(false),
            accelerations_configured(false)
        {}

        /**
         * @brief Configures the waypoint for a specific dimension.
         *
         * Configuring the waypoint requires setting of many required and optional
         * parameters, some of which are initialised at construction and some of
         * which are later calculated. This is usually beyond the scope of defining a simple
         * constructor (though a very simple configuration is deployed through
         * the alternative constructor here). Consequently, manual configuration
         * must be utilised if you use this constructor:
         * @code
         * Waypoint<JointAngles> waypoint(4);
         * waypoint.name("Raised Position");               // String identifier (not req'd).
         * waypoint.nominalRates(1.0);                     // Sets a common nominal rate to the next waypoint.
         * waypoint.nominalRates << 1.0, 1.0, 0.8, 0.8;     // Sets specific angular rates to the next waypoint.
         * waypoint.angles() << 1.57, 1.57, 0, 0;           // Joint angle specification.
         * @endcode
         * Angle rates and accelerations are currently only configured by the interpolation techniques
         * that act on the waypoints. At some stage though, this may change if we want more flexible,
         * higher order interpolating functionalities.
         * @code
         * waypoint.rates() << 1.0, 1.0, 0.5, 0.5;          // Joint angle rates specification.
         * waypoint.accelerations() << 0.0, 0.0, 0.0, 0.0;  // Joint angle accelerations specification.
         * waypoint.duration(3.00);                        // Useful if you set a nominalRate of 0.0.
         * @endcode
         */
        WayPoint(const unsigned int &dimension) :
            name(""),
            duration(0.0),
            rates_configured(false),
            accelerations_configured(false),
            angle_positions(JointDataArray::Constant(dimension,0.0)),
            angle_rates(JointDataArray::Constant(dimension,0.0)),
            angle_accelerations(JointDataArray::Constant(dimension,0.0)),
            nominal_rates(JointDataArray::Constant(dimension,1.00))
        {}

        /**
         * @brief Copy constructor.
         *
         * @param waypoint
         * @return
         */
        WayPoint( const WayPoint<JointAngles> &waypoint) :
        	name(waypoint.name()),
			duration(waypoint.duration()),
			rates_configured(waypoint.rates_configured()),
			accelerations_configured(waypoint.accelerations_configured()),
			angle_positions(waypoint.angle_positions),
			angle_rates(waypoint.angle_rates),
			angle_accelerations(waypoint.angle_accelerations),
			nominal_rates(waypoint.nominal_rates)
		{}

        virtual ~WayPoint() {}

        /******************************************
        ** Configuration
        *******************************************/
        /**
         * @brief Return the waypoint dimension.
         *
         * The number of joints used to compose the waypoint.
         *
         * @return const unsigned int& the dimension of the waypoint.
         **/
        unsigned int dimension() const { return angle_positions.size(); }

        /**
         * @brief
         * @param dimension
         */
        void redimension(const unsigned int &dimension) {
        	angle_positions = JointDataArray::Constant(dimension,0.0);
        	angle_rates = JointDataArray::Constant(dimension,0.0);
        	angle_accelerations = JointDataArray::Constant(dimension,0.0);
        	nominal_rates = JointDataArray::Constant(dimension,0.0);
        }
        /**
         * @brief Handle to the joint angle array.
         *
         * Supplies a handle to the joint angle array which can be used
         * to set/modify joint angle information (can use the comma initialiser).
         *
         * Note a convenient way to set the angle information
         * is to use the comma initialiser of the underlying angle array:
         * @code
         * waypoint.angles() = 1.57, 1.57, 0, 0;
         * @endcode
         *
         * @return Array<double>& : handle to the joint angle array.
         **/
        Array<double>& angles() { return angle_positions; }
        /**
         * The const version of angles()
         * @return
         */
        const Array<double>& angles() const { return angle_positions; }

        /**
         * @brief Handle to the joint angle rates array.
         *
         * Supplies a handle to the joint angle rates array which can be used
         * to set/modify joint angle rate information (can use the comma initialiser).
         *
         * The joint angle rates represent the specified angular rate that must be
         * attained as a trajectory moves through this waypoint. It is not always
         * necessary depending on the type of interpolation being used (cubic spline vs
         * quintic spline) and the location of the waypoint in the trajectory (boundary vs internal).
         *
         * When using this method, the waypoint is flagged as having had its angular
         * rates configured.
         *
         * Note a convenient way to set the information
         * is to use the comma initialiser of the underlying angle array:
         * @code
         * waypoint.rates() << 1.0, 1.0, 0, 0;
         * @endcode
         *
         * I don't actually really like this - because we've actually got
         * no real guarantee that the lazy bastard outside the class
         * actually configured the values.
         *
         * @return Array<double>& : handle to the joint angle rates array.
         **/
        Array<double>& rates() {
            rates_configured(true);
            return angle_rates;
        }
        /**
         * The const version of rates().
         * @return
         */
        const Array<double>& rates() const{
            return angle_rates;
        }

        /**
         * @brief Handle to the joint angle accelerations array.
         *
         * Supplies a handle to the joint angle accelerations array which can be used
         * to set/modify joint angle acceleration information (can use the comma initialiser).
         *
         * The joint angle accelerations represent the specified angular acceleration that must be
         * attained as a trajectory moves through this waypoint. It is not always
         * necessary depending on the type of interpolation being used (cubic spline vs
         * quintic spline) and the location of the waypoint in the
         * trajectory (boundary vs internal).
         *
         * When using this method, the waypoint is flagged as having had its angular
         * accelerations configured.
         *
         * Note a convenient way to set the information
         * is to use the comma initialiser of the underlying angle array:
         * @code
         * waypoint.accelerations() = 1.0, 1.0, 0, 0;
         * @endcode
         *
         * @return Array<double>& : handle to the joint angle accelerations array.
         **/
        Array<double>& accelerations() {
            accelerations_configured(true);
            return angle_accelerations;
        }
        /**
         * The const version of accelerations()
         * @return
         */
        const Array<double>& accelerations() const {
            return angle_accelerations;
        }

        /**
         * @brief Handle to the nominal angle rates array.
         *
         * Supplies a handle to the nominal rates array which can be used
         * to set/modify the individual nominal rates (can use the comma initialiser).
         *
         * The nominal rates represent the recommended (which may be
         * ignored by the interpolation method) average angular rate to be used
         * over the ensuing segment until the next waypoint is reached.
         *
         * Note a convenient way to set the values
         * is to use the comma initialiser of the underlying array:
         * @code
         * waypoint.nominalRates() = 1.00, 1.00, 0.60, 0.60;
         * @endcode
         *
         * @return Array<double>>& : handle to the maximum rates array.
         **/
        Array<double>& nominalRates() { return nominal_rates; }
        /**
         * @brief Configures the nominal rates with a common value.
         *
         * Configures the nominal angular rate the next segment of each joint
         * to a common value.
         *
         * @param nom_rate : the blanket nominal angular rate to set for each joint.
         */
        void nominalRates(double nom_rate) {
        	for ( unsigned int i = 0; i < nominal_rates.size(); ++i) {
        		nominal_rates[i] = nom_rate;
        	}
        }

        /**
         * @brief Equality operator for waypoints.
         *
         * This is useful as a quick check to see if one waypoint doesn't match
         * another.
         *
         * @param other : the waypoint to check against.
         * @return bool : true if all angles are equal, false otherwise.
         */
        bool operator==(const WayPoint<JointAngles>& other) const {
        	for ( unsigned int i = 0; i < angle_positions.size(); ++i ) {
        		if ( angle_positions[i] != other.angle_positions[i] ) {
        			return false;
        		}
        	}
        	return true;
        }

        /**
         * @brief Inequality operator for waypoints.
         *
         * This is useful as a quick check to see if one waypoint doesn't match
         * another.
         *
         * @param other : the waypoint to check against.
         * @return bool : true if not all angles are equal, false otherwise.
         */
        bool operator!=(const WayPoint<JointAngles>& other) const {
        	for ( unsigned int i = 0; i < angle_positions.size(); ++i ) {
        		if ( angle_positions[i] != other.angle_positions[i] ) {
        			return true;
        		}
        	}
        	return false;
        }

        /**
         * @brief Approximately operator for waypoints.
         *
         * This is useful as a quick check to see if one waypoint is very similar
         * to another. It returns false if any individual angle difference (not the
         * sum) is greater than the supplied epsilon.
         *
         * @param other : the waypoint to check against.
         * @param epsilon : approximate to this value of approximateness.
         * @return bool : true if all angles are approximately equal, false otherwise.
         */
        bool approx(const WayPoint<JointAngles> &other, const double& epsilon = 0.01) {
        	for ( unsigned int i = 0; i < angle_positions.size(); ++i ) {
        		if ( std::fabs(angle_positions[i] - other.angle_positions[i]) > epsilon ) {
        			return false;
        		}
        	}
        	return true;
        }

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
         * @param waypoint : the waypoint.
         * @return OutputStream : the output stream.
         */
        template <typename OutputStream>
        friend OutputStream& operator << (OutputStream &ostream, WayPoint<JointAngles> &waypoint);

        /******************************************
        ** Parameters
        *******************************************/
        Parameter<std::string> name; /**< @brief String name identifier. **/
        Parameter<double> duration; /**< @brief Timestamp for this waypoint. **/
        Parameter<bool> rates_configured; /**< @brief Rates have been configured for this waypoint. **/
        Parameter<bool> accelerations_configured; /**< @brief Accelerations have been configured for this waypoint. **/

    private:
        JointDataArray angle_positions;
        JointDataArray angle_rates; // this is rates *at* the point, currently unused by ycs stuff, but might be useful
        JointDataArray angle_accelerations;
        JointDataArray nominal_rates; // this is rough rates between points (i.e. slopes)
};

/*****************************************************************************
** Implementation [WayPoint][Streaming]
*****************************************************************************/

template <typename OutputStream>
OutputStream& operator << (OutputStream &ostream, WayPoint<JointAngles> &waypoint) {

	Format< Array<double> > format; format.precision(2); format.width(6);
    if ( waypoint.name() != "" ) {
        ostream << "  Name                 : " << waypoint.name() << "\n";
    }
    ostream << "  Angles               : " << format(waypoint.angle_positions) << "\n";
    if (waypoint.rates_configured()) {
        ostream << "  Rates                : " << format(waypoint.angle_rates) << "\n";
    }
    if (waypoint.accelerations_configured()) {
        ostream << "  Accelerations        : " << format(waypoint.angle_accelerations) << "\n";
    }
    ostream << "  Nominal Rates        : " << format(waypoint.nominal_rates) << "\n";
    ostream.flush();
    return ostream;
}

/*****************************************************************************
** Typedefs
*****************************************************************************/

//typedef Waypoint<JointAngles> JointAngleWaypoint; /**< @brief Convenient typedef for joint angle waypoints. **/

}; // namespace ecl

#endif /* ECL_MANIPULATORS_WAYPOINT_HPP_ */
