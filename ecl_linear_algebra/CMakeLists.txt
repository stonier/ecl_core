##############################################################################
# Rosbuild2
##############################################################################

if(ROSBUILD)
  # This is the rosbuild2 path
  include(rosbuild.cmake OPTIONAL)
  return()
endif()

##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.4.6)

# Verbosity is useful - helps eclipse find paths also!
set(CMAKE_VERBOSE_MAKEFILE true)

##############################################################################
# Ros
##############################################################################

include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
rosbuild_init()
rosbuild_include(ecl_build ecl_package)

##############################################################################
# External Eigen
##############################################################################

include(cmake/FindEigen3.cmake)
if(NOT EIGEN3_INCLUDE_DIR)
  set(ECL_EIGEN_IS_INTERNAL 1)
endif()
configure_file(${CMAKE_SOURCE_DIR}/include/ecl/linear_algebra/macros.hpp.in ${CMAKE_SOURCE_DIR}/include/ecl/linear_algebra/macros.hpp)

##############################################################################
# Actual project configuration
##############################################################################

ecl_package_init()
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(pkg-config)
ecl_package_finalise()
