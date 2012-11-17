/**
 * @file /src/test/mutex.cpp
 *
 * @brief Unit Test for the @ref ecl::Mutex "Mutex" class.
 *
 * Use this to test the @ref ecl::Mutex "Mutex" class. Currently this
 * only tests the posix mutex class.
 *
 * @date June 2009
 **/
/*****************************************************************************
** Platform Check
*****************************************************************************/
#include <iostream>
#include <ecl/config/ecl.hpp>
#if defined(ECL_IS_POSIX)

/*****************************************************************************
** Includes
*****************************************************************************/

#include <iostream>
#include <gtest/gtest.h>
#include <ecl/config/ecl.hpp>
#include <ecl/exceptions/standard_exception.hpp>
#include <ecl/time/timestamp.hpp>
#include "../../include/ecl/threads/mutex.hpp"

/*****************************************************************************
** Using
*****************************************************************************/

using ecl::StandardException;
using ecl::Mutex;
using ecl::Duration;

/*****************************************************************************
** Macros
*****************************************************************************/

// Make sure we can test the debug mode properties.
#if defined(NDEBUG) || defined(ECL_NDEBUG)
	#undef NDEBUG
	#undef ECL_NDEBUG
#endif

/*****************************************************************************
** TESTS
*****************************************************************************/

TEST(MutexTests,selfDestruct) {
	// It will now attempt to self-destruct while locked and throw an exception.
	Mutex mutex;
    mutex.lock();
    try {
    	mutex.lock();
    } catch ( StandardException &e ) {
    	SUCCEED();
    }
    mutex.unlock();
}

TEST(MutexTests,tryLock) {
	// It will now attempt to self-destruct while locked and throw an exception.
	Mutex mutex;
    mutex.trylock();
    EXPECT_FALSE(mutex.trylock());
    mutex.unlock();
}

TEST(MutexTests,timedLock) {
	// It will now attempt to self-destruct while locked and throw an exception.
	// Trying to activate from the same thread will cause a deadlock
	// and thus exception. Need to make a test with different threads here.
	// Duration duration(1,500000000);
	// Mutex mutex;
	// mutex.lock();
	// mutex.timedlock(duration);
}

/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


#else

/*****************************************************************************
** Alternative main
*****************************************************************************/

int main(int argc, char **argv) {

	std::cout << "Currently not supported on your platform." << std::endl;
}

#endif /* ECL_IS_POSIX */
