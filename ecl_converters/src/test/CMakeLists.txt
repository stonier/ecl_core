##############################################################################
# Files
##############################################################################

catkin_add_gtest(test_byte_array_converters byte_array_converters.cpp)
target_link_libraries(test_byte_array_converters ${catkin_LIBRARIES})
catkin_add_gtest(test_converters converters.cpp)
target_link_libraries(test_converters ${catkin_LIBRARIES})
