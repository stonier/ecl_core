###############################################################################
# GTEST SETUP
###############################################################################

rosbuild_add_gtest(test_arrays arrays.cpp)
rosbuild_add_gtest(test_arrays_mem_check arrays_mem_check.cpp)
rosbuild_add_gtest(test_converters converters.cpp)
rosbuild_add_gtest(test_stencil stencil.cpp)
rosbuild_add_gtest(test_fifo fifo.cpp)
rosbuild_add_gtest(test_push_and_pop push_and_pop.cpp)
