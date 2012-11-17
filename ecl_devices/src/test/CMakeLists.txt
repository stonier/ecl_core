###############################################################################
# GTEST SETUP
###############################################################################

rosbuild_add_gtest(test_files files.cpp)
target_link_libraries(test_files -lecl_devices)

rosbuild_add_gtest(test_shared_files shared_files.cpp)
target_link_libraries(test_shared_files -lecl_devices)

