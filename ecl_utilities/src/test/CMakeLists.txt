###############################################################################
# GTEST SETUP
###############################################################################

catkin_add_gtest(test_function_objects function_objects.cpp)
catkin_add_gtest(test_references references.cpp)
catkin_add_gtest(test_singleton singleton.cpp)
catkin_add_gtest(test_parameters parameters.cpp)
catkin_add_gtest(test_flags flags.cpp)
