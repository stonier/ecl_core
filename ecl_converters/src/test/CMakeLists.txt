##############################################################################
# Files
##############################################################################

# Gtest is not picking up -pthreads when --as-needed is on, so force it.
ecl_link_no_as_needed(ECL_LINK_NO_AS_NEEDED_FLAG)

rosbuild_add_gtest(test_byte_array_converters byte_array_converters.cpp)
target_link_libraries(test_byte_array_converters ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)

rosbuild_add_gtest(test_converters converters.cpp)
target_link_libraries(test_converters ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
