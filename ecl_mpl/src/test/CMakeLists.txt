###############################################################################
# Gtests
###############################################################################

rosbuild_add_gtest(test_enable_if enable_if.cpp)
# Bad hack
if ( UNIX ) 
  target_link_libraries(test_enable_if -pthread)
endif()
