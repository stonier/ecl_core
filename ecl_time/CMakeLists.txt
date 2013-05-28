##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_time)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_config
    ecl_errors
    ecl_time_lite
    ecl_exceptions
    )
catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS ecl_config ecl_errors ecl_time_lite ecl_exceptions
        )
include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



