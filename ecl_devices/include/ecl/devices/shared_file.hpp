/**
 * @file /include/ecl/devices/shared_file.hpp
 *
 * @brief Output file specially suited for logging across threads.
 *
 * Output file specially suited for logging across threads.
 *
 * @date January, 2010
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_DEVICES_SHARED_FILE_HPP_
#define ECL_DEVICES_SHARED_FILE_HPP_

/*****************************************************************************
** Cross Platform Functionality
*****************************************************************************/

#include <ecl/config/ecl.hpp>

/*****************************************************************************
** Includes
*****************************************************************************/

// This is only temporary while ofile is posix only
#if defined(ECL_IS_POSIX)
  #include "shared_file_pos.hpp"
#endif

#endif /* ECL_DEVICES_SHARED_FILE_HPP_ */
