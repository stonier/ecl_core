###############################################################################
# GTEST SETUP
###############################################################################

# Gtest is not picking up -pthreads when --as-needed is on, so force it.
ecl_link_no_as_needed(ECL_LINK_NO_AS_NEEDED_FLAG)

rosbuild_add_gtest(test_concepts concepts.cpp)
target_link_libraries(test_concepts ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)

