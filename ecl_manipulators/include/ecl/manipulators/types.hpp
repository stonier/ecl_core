/**
 * @file /include/ecl/manipulators/types.hpp
 *
 * @brief Type definitions for manipulators.
 *
 * @date May 2008
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_MANIPULATORS_TYPES_HPP_
#define ECL_MANIPULATORS_TYPES_HPP_

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Enums
*****************************************************************************/

/**
 * @brief Angle usage type for the manipulator trajectory definitions.
 *
 * Angle usage type for the manipulator. Most simple manipulators simply use
 * joint angles - more complicated manipulators that have to interact with
 * the environment require measurements of the end effector in cartesians.
 */
enum ManipulatorAngleType {
    JointAngles,        /**< @brief Joint angle representations are being used. **/
    Cartesians          /**< @brief Cartesian representations are being used. **/
};

}; // namespace ecl

#endif /* ECL_MANIPULATORS_TYPES_HPP_ */
