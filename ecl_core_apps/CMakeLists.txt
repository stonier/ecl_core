##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_core_apps)

##############################################################################
# ament
##############################################################################

# Turn -isystem off. Actually like to see warnings from underlying packages
# and regardless, have run into trouble because of the ordering it induces.

# Getting some confounding variadic warnings from Sophus, so turn isystem
# back on so this build hides those warnings.
# set(CMAKE_NO_SYSTEM_FROM_IMPORTED TRUE)

find_package(ament_cmake_ros REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config  REQUIRED)
find_package(ecl_linear_algebra REQUIRED)
find_package(ecl_command_line REQUIRED)
find_package(ecl_converters REQUIRED)
find_package(ecl_containers REQUIRED)
find_package(ecl_devices REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_formatters REQUIRED)
find_package(ecl_geometry REQUIRED)
find_package(ecl_ipc REQUIRED)
find_package(ecl_sigslots REQUIRED)
find_package(ecl_streams REQUIRED)
find_package(ecl_threads REQUIRED)
find_package(ecl_type_traits REQUIRED)
find_package(ecl_time_lite REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

ament_package_xml()
ecl_enable_cxx14_compiler()
ecl_enable_cxx_warnings()

##############################################################################
# Sources
##############################################################################

add_subdirectory(src)

##############################################################################
# Exports
##############################################################################

ament_package()
