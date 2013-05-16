/**
 * @file /include/ecl/devices/access.hpp
 *
 * @brief Determine accessibility of a file
 *
 * @date May 2013
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_DEVICES_ACCESS_HPP_
#define ECL_DEVICES_ACCESS_HPP_

/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config/ecl.hpp>
#if defined(ECL_IS_WIN32)

/*****************************************************************************
** Includes
*****************************************************************************/

#include "macros.hpp"

/*****************************************************************************
** Macro Definition
*****************************************************************************/
/**
 * @brief Values for the second argument to access.
 */
#define R_OK    4
#define W_OK    2
#define X_OK    1
#define F_OK    0

/*****************************************************************************
** Function Declaration
*****************************************************************************/
/**
 * @brief Determine accessibility of a file.
 *
 * This uses to determine accessibility of a object
 * including files, physical disks and volumes, communications resources
 * such as serial port.
 *
 * Windows has _access() corresponding posix access(),
 * but it does not work correctly for serial port.
 * This function aims to operate same as posix access().
 *
 * @param path : path name of the object.
 * @param amode : access mode.
 * @return int : return 0 if the file has the given mode, or return -1.
 */
ecl_devices_PUBLIC int access(const char* path, int mode);


#endif /* ECL_IS_WIN32 */
#endif /* ECL_DEVICES_ACCESS_HPP_ */
