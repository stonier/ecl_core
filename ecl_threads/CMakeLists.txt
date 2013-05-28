##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_threads)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_build
    ecl_config
    ecl_errors
    ecl_concepts
    ecl_exceptions
    ecl_time
    ecl_utilities
    )
catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS 
            ecl_config
            ecl_errors
            ecl_concepts
            ecl_exceptions
            ecl_time
            ecl_utilities
        )
include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Thread Detection
##############################################################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ecl_build_DIR}/modules)
include(ecl_platform_detection)
ecl_detect_threads()

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



