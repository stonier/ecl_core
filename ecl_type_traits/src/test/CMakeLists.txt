##############################################################################
# Files
##############################################################################

catkin_add_gtest(test_numeric_limits numeric_limits)
target_link_libraries(test_numeric_limits ${PROJECT_NAME})
#target_link_libraries(test_numeric_limits ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)

catkin_add_gtest(test_fundamental_types fundamental_types)
target_link_libraries(test_fundamental_types ${PROJECT_NAME})
#target_link_libraries(test_fundamental_types ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)


