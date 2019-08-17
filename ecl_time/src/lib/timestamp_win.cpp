/**
 * @file /ecl_time/src/lib/timestamp_win.cpp
 *
 * @brief Windows implementation of the timestamp class.
 *
 * @date May 22, 2010
 **/
/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config.hpp>
#if defined(ECL_IS_WIN32)

/*****************************************************************************
** Includes
*****************************************************************************/

#include <chrono>
#include <ecl/config/windows.hpp>
#include <ecl/exceptions/standard_exception.hpp>
#include "../../include/ecl/time/timestamp_win.hpp"
// #include "../../include/ecl/time/detail/time_functions_win.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Implementation [Constructors]
*****************************************************************************/

// TODO: check if chrono is compatible for both linux and win now, we can
// probably collapse them, and even remove some of the functions from
// time_functions_win.hpp
TimeStamp::TimeStamp() {
	std::chrono::high_resolution_clock clock;
	auto now = clock.now();

	auto time_since_epoch = now.time_since_epoch();
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time_since_epoch);
	auto num_seconds = seconds.count();
	auto num_nanoseconds = time_since_epoch.count() % 1000000000;

	time.tv_sec = num_seconds;
	time.tv_nsec = num_nanoseconds;
}

TimeStamp::TimeStamp (const double& decimal_time_value) :
	TimeStampBase(decimal_time_value)
{
}

TimeStamp::TimeStamp (const time_t& seconds, const long& nanoseconds) :
	TimeStampBase(seconds, nanoseconds)
{
}

TimeStamp::TimeStamp(const TimeStampBase& base) : TimeStampBase(base) {}

/*****************************************************************************
** Implementation [Stamps]
*****************************************************************************/

const TimeStamp& TimeStamp::stamp() {
    return (*this);
}

} // namespace ecl

#endif /* ECL_IS_WIN32 */
