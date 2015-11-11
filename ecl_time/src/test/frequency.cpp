/**
 * @file /src/test/frequency.cpp
 *
 * @brief Unit Test for the FrequncyMonitor class.
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <gtest/gtest.h>
#include "../../include/ecl/time/sleep.hpp"
#include "../../include/ecl/time/timestamp.hpp"
#include "../../include/ecl/time/frequency_diagnostics.hpp"

/*****************************************************************************
** Platform Check
*****************************************************************************/

#ifdef ECL_HAS_TIMESTAMP


/*****************************************************************************
** Tests
*****************************************************************************/

TEST(FrequencyMonitorTests,silent) {

  ecl::FrequencyMonitor monitor(0.5, true);
  ecl::FrequencyDiagnostics diagnostics;

  ecl::MilliSleep sleep_ms;
  unsigned int period = 100;

  float epsilon = 0.3;
  for ( unsigned int i = 0; i < 50; ++i ) {
    monitor.update();
    diagnostics = monitor.analyse();
    if ( i == 25 ) {
      period = 200;
      std::cout << diagnostics << std::endl;
      EXPECT_NEAR(diagnostics.hz, 10.0, epsilon);
    }
    sleep_ms(period);
  }
  std::cout << diagnostics << std::endl;
  EXPECT_NEAR(diagnostics.hz, 5.0, epsilon);
}

#endif /* ECL_HAS_TIMESTAMP */

/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
