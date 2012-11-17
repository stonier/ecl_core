###############################################################################
# Google Tests
###############################################################################

rosbuild_add_gtest(test_cpuwatch cpuwatch_rt.cpp)
target_link_libraries(test_cpuwatch ecl_time)

rosbuild_add_gtest(test_sleep sleep.cpp)
target_link_libraries(test_sleep ecl_time)

rosbuild_add_gtest(test_snooze snooze.cpp)
target_link_libraries(test_snooze ecl_time)

rosbuild_add_gtest(test_timestamp timestamp.cpp)
target_link_libraries(test_timestamp ecl_time)

rosbuild_add_gtest(test_time_data time_data.cpp)
target_link_libraries(test_time_data ecl_time)

rosbuild_add_gtest(test_stopwatch stopwatch.cpp)
target_link_libraries(test_stopwatch ecl_time)
