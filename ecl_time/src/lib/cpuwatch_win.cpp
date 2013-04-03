/**
 * @file /src/lib/cpuwatch_win.cpp
 *
 * @brief Implementation of the cpuwatch class.
 *
 * @date April 2013
 **/
/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config.hpp>

#if defined(ECL_IS_WIN32)

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/ecl/time/cpuwatch_win.hpp"
#include <ecl/time_lite/cpu_time.hpp>
#include <ecl/time_lite/functions.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Implementation [CpuWatch]
*****************************************************************************/

CpuWatch::CpuWatch() {
	epoch_time(tmp);
	start_time.stamp(tmp.tv_sec, tmp.tv_nsec);
	split_time = start_time;
};

/*****************************************************************************
** Implementation
*****************************************************************************/

void CpuWatch::restart()
{
	epoch_time(tmp);
	start_time.stamp(tmp.tv_sec, tmp.tv_nsec);
    split_time = start_time;
}

TimeStamp CpuWatch::elapsed()
{
	epoch_time(tmp);
    TimeStamp current_time(tmp.tv_sec, tmp.tv_nsec);
    return ( current_time - start_time );
}

TimeStamp CpuWatch::split()
{
    TimeStamp last_time = split_time;
    epoch_time(tmp);
    split_time.stamp(tmp.tv_sec,tmp.tv_nsec);
    return (split_time - last_time);
}

}; // namespace ecl

#endif /* ECL_IS_WIN32 */

