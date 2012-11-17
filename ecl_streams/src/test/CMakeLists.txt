###############################################################################
# GTEST SETUP
###############################################################################

rosbuild_add_gtest(test_file_streams file_streams.cpp)
rosbuild_add_gtest(test_string_streams string_streams.cpp)

target_link_libraries(test_file_streams -lecl_streams)
target_link_libraries(test_string_streams -lecl_streams)
