##############################################################################
# Actual project configuration
##############################################################################

rosbuild_add_gtest(test_plugin plugin.cpp)
rosbuild_add_gtest(test_formatters formatters.cpp)

# Hack just to make sure our tests pass if we're using external eigen3
# Note that this is covered for dependant packages
# in the manifest.xml externally via a hunt for pkg-config
if ( EIGEN3_INCLUDE_DIR )
  set_target_properties(test_formatters PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -I${EIGEN3_INCLUDE_DIR}")
  set_target_properties(test_plugin PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -I${EIGEN3_INCLUDE_DIR}")
endif()

if ( UNIX )
  target_link_libraries(test_formatters -pthread)
  target_link_libraries(test_plugin -pthread)
endif()

