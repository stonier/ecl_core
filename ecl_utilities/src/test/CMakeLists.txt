###############################################################################
# GTEST SETUP
###############################################################################

# Gtest is not picking up -pthreads when --as-needed is on, so force it.
ecl_link_no_as_needed(ECL_LINK_NO_AS_NEEDED_FLAG)

rosbuild_add_gtest(test_function_objects function_objects.cpp)
target_link_libraries(test_function_objects ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
rosbuild_add_gtest(test_references references.cpp)
target_link_libraries(test_references ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
rosbuild_add_gtest(test_singleton singleton.cpp)
target_link_libraries(test_singleton ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
rosbuild_add_gtest(test_parameters parameters.cpp)
target_link_libraries(test_parameters ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
rosbuild_add_gtest(test_flags flags.cpp)
target_link_libraries(test_flags ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
