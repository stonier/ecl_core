###############################################################################
# GTEST SETUP
###############################################################################

rosbuild_add_gtest(test_shared_memory shared_memory.cpp)
rosbuild_add_gtest(test_semaphores semaphores.cpp)
rosbuild_add_gtest(test_semaphores_timed semaphores_timed.cpp)

target_link_libraries(test_shared_memory ecl_ipc)
target_link_libraries(test_semaphores ecl_ipc)
target_link_libraries(test_semaphores_timed ecl_ipc)
