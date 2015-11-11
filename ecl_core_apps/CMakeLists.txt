##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_core_apps)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_build
    ecl_config 
    ecl_linear_algebra
    ecl_command_line
    ecl_converters
    ecl_containers
    ecl_devices
    ecl_errors
    ecl_exceptions
    ecl_formatters
    ecl_geometry
    ecl_ipc
    ecl_sigslots
    ecl_streams
    ecl_threads
    ecl_type_traits
    ecl_time_lite
    )
catkin_package()

##############################################################################
# Project Configuration
##############################################################################

include_directories(include ${catkin_INCLUDE_DIRS})
ecl_enable_cxx11_compiler()

##############################################################################
# Sources
##############################################################################

add_subdirectory(src)



