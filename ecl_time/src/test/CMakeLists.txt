###############################################################################
# Google Tests
###############################################################################

catkin_add_gtest(test_cpuwatch cpuwatch_rt.cpp)
target_link_libraries(test_cpuwatch ${PROJECT_NAME})

catkin_add_gtest(test_sleep sleep.cpp)
target_link_libraries(test_sleep ${PROJECT_NAME})

catkin_add_gtest(test_snooze snooze.cpp)
target_link_libraries(test_snooze ${PROJECT_NAME})

catkin_add_gtest(test_timestamp timestamp.cpp)
target_link_libraries(test_timestamp ${PROJECT_NAME})

catkin_add_gtest(test_time_data time_data.cpp)
target_link_libraries(test_time_data ${PROJECT_NAME})

catkin_add_gtest(test_stopwatch stopwatch.cpp)
target_link_libraries(test_stopwatch ${PROJECT_NAME})
