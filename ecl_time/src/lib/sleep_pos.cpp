/**
 * @file /src/lib/sleep_pos.cpp
 *
 * @brief Posix rt-timer implementation of the sleep classes.
 *
 * @date August 2009
 **/
/*****************************************************************************
** Platform Check
*****************************************************************************/

#include <ecl/config.hpp>
#if defined(ECL_IS_POSIX)

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/errors/macros.hpp>
#include "../../include/ecl/time/duration.hpp"
#include "../../include/ecl/time/sleep_pos.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Implementation [Sleep]
*****************************************************************************/
Sleep::Sleep(const Duration &duration) {
  required.tv_sec = duration.sec();
  required.tv_nsec = duration.nsec();
}

Sleep::Sleep(const unsigned long &seconds) {
  required.tv_sec = seconds;
  required.tv_nsec = 0;
}

void Sleep::operator ()() {
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result;
}

void Sleep::operator ()(const Duration &duration) {
  required.tv_sec = duration.sec();
  required.tv_nsec = duration.nsec();
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result; // for unused variable warnings, in case the assert wasn't triggered
}

void Sleep::operator ()(const unsigned long &seconds) {
  required.tv_sec = seconds;
  required.tv_nsec = 0;
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result; // for unused variable warnings, in case the assert wasn't triggered
}

/*****************************************************************************
** Implementation [MilliSleep]
*****************************************************************************/

MilliSleep::MilliSleep(const unsigned long &milliseconds) {
  required.tv_sec = milliseconds/1000; // integer division
  required.tv_nsec = (milliseconds%1000)*1000000;
}

void MilliSleep::operator ()() {
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result; // for unused variable warnings, in case the assert wasn't triggered
}

void MilliSleep::operator ()(const unsigned long &milliseconds) {
  required.tv_sec = milliseconds/1000; // integer division
  required.tv_nsec = (milliseconds%1000)*1000000;
  // required.tv_nsec = 1000000*milli_seconds;
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result; // for unused variable warnings, in case the assert wasn't triggered
}

/*****************************************************************************
** Implementation [MicroSleep]
*****************************************************************************/

MicroSleep::MicroSleep(const unsigned long &microseconds) {
  required.tv_sec = microseconds/1000000; // integer division
  required.tv_nsec = (microseconds%1000000)*1000;
}

void MicroSleep::operator ()() {
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result; // for unused variable warnings, in case the assert wasn't triggered
}

void MicroSleep::operator ()(const unsigned long &micro_seconds) {
  required.tv_nsec = 1000*micro_seconds;
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result; // for unused variable warnings, in case the assert wasn't triggered
}

/*****************************************************************************
** Implementation [NanoSleep]
*****************************************************************************/

NanoSleep::NanoSleep(const unsigned long &nanoseconds) {
  required.tv_sec = nanoseconds/1000000000; // integer division
  required.tv_nsec = nanoseconds%1000000000;
}

void NanoSleep::operator ()() {
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result; // for unused variable warnings, in case the assert wasn't triggered
}

void NanoSleep::operator ()(const unsigned long &nanoseconds) {
  required.tv_nsec = nanoseconds;
  int result = nanosleep(&required, &remaining);
  ecl_assert_throw( result == 0, time::throwSleepException(LOC) );
  (void) result; // for unused variable warnings, in case the assert wasn't triggered
}

} // namespace ecl

#endif /* ECL_IS_POSIX */

