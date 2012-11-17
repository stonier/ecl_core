###############################################################################
# GTEST SETUP
###############################################################################

rosbuild_add_gtest(test_sigslots sigslots.cpp)
target_link_libraries(test_sigslots -lecl_sigslots)
