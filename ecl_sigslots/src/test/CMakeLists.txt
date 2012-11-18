###############################################################################
# GTEST SETUP
###############################################################################

catkin_add_gtest(test_sigslots sigslots.cpp)
target_link_libraries(test_sigslots ${PROJECT_NAME})
