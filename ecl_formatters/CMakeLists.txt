##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_formatters)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_config
    ecl_exceptions
    ecl_converters
    )
catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS 
            ecl_config
            ecl_exceptions
            ecl_converters
        )
include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



