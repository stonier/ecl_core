###############################################################################
# GTEST SETUP
###############################################################################

# problems running as the jenkins user
set(ECL_JENKINS $ENV{ECL_JENKINS})
if("${ECL_JENKINS}" STREQUAL "")
  catkin_add_gtest(test_mutex mutex.cpp)
  target_link_libraries(test_mutex ${PROJECT_NAME})
endif()

# Ok Tests
catkin_add_gtest(test_priorities priorities.cpp)
catkin_add_gtest(test_threadable threadable.cpp)
catkin_add_gtest(test_threads threads.cpp)

target_link_libraries(test_priorities ${PROJECT_NAME})
target_link_libraries(test_threadable ${PROJECT_NAME})
target_link_libraries(test_threads ${PROJECT_NAME})
