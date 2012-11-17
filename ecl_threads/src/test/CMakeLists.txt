###############################################################################
# GTEST SETUP
###############################################################################

rosbuild_add_gtest(test_mutex mutex.cpp)
rosbuild_add_gtest(test_priorities priorities.cpp)
rosbuild_add_gtest(test_threadable threadable.cpp)
rosbuild_add_gtest(test_threads threads.cpp)

target_link_libraries(test_mutex ecl_threads)
target_link_libraries(test_priorities ecl_threads)
target_link_libraries(test_threadable ecl_threads)
target_link_libraries(test_threads ecl_threads)
