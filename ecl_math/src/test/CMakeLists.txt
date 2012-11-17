###############################################################################
# GTEST SETUP
###############################################################################

# Gtest is not picking up -pthreads when --as-needed is on, so force it.
ecl_link_no_as_needed(ECL_LINK_NO_AS_NEEDED_FLAG)

rosbuild_add_gtest(test_constants constants.cpp)
target_link_libraries(test_constants ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
rosbuild_add_gtest(test_fuzzy fuzzy.cpp)
target_link_libraries(test_fuzzy ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
rosbuild_add_gtest(test_norms norms.cpp)
target_link_libraries(test_norms ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
rosbuild_add_gtest(test_simple simple.cpp)
target_link_libraries(test_simple ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
