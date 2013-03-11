###############################################################################
# Test Macro
###############################################################################

macro(ecl_time_add_gtest test_name)
  catkin_add_gtest(test_${test_name} ${test_name}.cpp)
  # If we don't have gtest installed, then the target doesn't get made - check!
  if(TARGET test_${test_name})
      target_link_libraries(test_${test_name} ${PROJECT_NAME})
  endif()
endmacro()

###############################################################################
# Google Tests
###############################################################################

ecl_time_add_gtest(test_cpuwatch cpuwatch_rt.cpp)
ecl_time_add_gtest(test_sleep sleep.cpp)
ecl_time_add_gtest(test_snooze snooze.cpp)
ecl_time_add_gtest(test_timestamp timestamp.cpp)
ecl_time_add_gtest(test_time_data time_data.cpp)
ecl_time_add_gtest(test_stopwatch stopwatch.cpp)
