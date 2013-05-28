##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_core_apps)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
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
    ecl_type_traits
    ecl_time_lite
    )
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(src)



