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
# Actual project configuration
##############################################################################

ecl_package_init()
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(pkg-config)
ecl_package_finalise()

