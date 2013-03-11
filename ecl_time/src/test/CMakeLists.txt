###############################################################################
# Test Macro
###############################################################################

macro(ecl_time_add_gtest test_name)
  catkin_add_gtest(ecl_test_${test_name} ${test_name}.cpp)
  # If we don't have gtest installed, then the target doesn't get made - check!
  if(TARGET ecl_test_${test_name})
      target_link_libraries(ecl_test_${test_name} ${PROJECT_NAME})
  endif()
endmacro()

###############################################################################
# Google Tests
###############################################################################

ecl_time_add_gtest(cpuwatch cpuwatch_rt.cpp)
ecl_time_add_gtest(sleep sleep.cpp)
ecl_time_add_gtest(snooze snooze.cpp)
ecl_time_add_gtest(timestamp timestamp.cpp)
ecl_time_add_gtest(time_data time_data.cpp)
ecl_time_add_gtest(stopwatch stopwatch.cpp)
