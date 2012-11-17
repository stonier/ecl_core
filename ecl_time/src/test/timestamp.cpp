/**
 * @file /src/test/timestamp.cpp
 *
 * @brief Unit Test for timestamp objects.
 *
 * @date May 2009
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <cstdlib>
#include <gtest/gtest.h>
#include "../../include/ecl/time/timestamp.hpp"

/*****************************************************************************
** Platform Check
*****************************************************************************/

#ifdef ECL_HAS_TIMESTAMP

/*****************************************************************************
** Using
*****************************************************************************/

using ecl::TimeStamp;

TEST(TimeStampTests,construction) {
    TimeStamp time;
    SUCCEED();
    TimeStamp time_pair(3,123456789L);
    EXPECT_FLOAT_EQ(3.123456789,time_pair);
    TimeStamp time_double(3.00001);
    EXPECT_FLOAT_EQ(3.00001,time_double);
}

TEST(TimeStampTests,timestamps) {
    TimeStamp time;
    time.stamp();
    long t = time.sec();
    t = time.msec();
    t = time.usec();
    t = time.nsec();
    SUCCEED();
    time.stamp(3,1425);
    EXPECT_FLOAT_EQ(3.000001425,time);
    time.stamp(4.00000142);
    EXPECT_FLOAT_EQ(4.00000142,time);
}

TEST(TimeStampTests,copyConstruction) {
    TimeStamp time(3,100);
	TimeStamp time_copy(time);
	EXPECT_EQ(3,time_copy.sec());
	EXPECT_EQ(100,time_copy.nsec());
}

TEST(TimeStampTests,copyAssignment) {
    TimeStamp time(3,100);
	TimeStamp time_copy;
    time_copy = time;
	EXPECT_EQ(3,time_copy.sec());
	EXPECT_EQ(100,time_copy.nsec());
}

TEST(TimeStampTests,comparisonOperators) {
    TimeStamp time(3,100);
	TimeStamp time_copy(time);
	EXPECT_TRUE(time==time_copy);
	EXPECT_FALSE(time!=time_copy);
	EXPECT_TRUE(time<=time_copy);
	EXPECT_TRUE(time>=time_copy);
	EXPECT_FALSE(time<time_copy);
	EXPECT_FALSE(time>time_copy);
    time.stamp();
	EXPECT_FALSE(time==time_copy);
	EXPECT_TRUE(time!=time_copy);
	EXPECT_FALSE(time<=time_copy);
	EXPECT_TRUE(time>=time_copy);
	EXPECT_FALSE(time<time_copy);
	EXPECT_TRUE(time>time_copy);
}

TEST(TimeStampTests,mathematicalOperators) {
	TimeStamp time, time_copy;
    time.stamp(1,100100100L);
    time_copy.stamp(1,900100100L);
    time += time_copy;
    EXPECT_EQ(3,time.sec());
    EXPECT_EQ(200200,time.nsec());
    time.stamp(1,100100100L);
    time = time + time_copy;
    EXPECT_EQ(3,time.sec());
    EXPECT_EQ(200200,time.nsec());
    time.stamp(2,100100100L);
    time -= time_copy;
    EXPECT_EQ(0,time.sec());
    EXPECT_EQ(200000000,time.nsec());
    time.stamp(2,100100100L);
    time = time - time_copy;
    EXPECT_EQ(0,time.sec());
    EXPECT_EQ(200000000,time.nsec());
}

#endif /* ECL_HAS_TIMESTAMP */

/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {

//	TimeStamp time;
//	std::cout << time << std::endl;
//	time.stamp();
//	std::cout << time << std::endl;
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
