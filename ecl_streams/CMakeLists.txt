##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_streams)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_errors
    ecl_concepts
    ecl_devices
    ecl_time
    ecl_converters
    ecl_type_traits
    )
catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS 
            ecl_errors
            ecl_concepts
            ecl_devices
            ecl_time
            ecl_converters
            ecl_type_traits
        )
include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



