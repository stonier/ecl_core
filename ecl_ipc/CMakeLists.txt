##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_ipc)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_config
    ecl_errors
    ecl_time_lite
    ecl_exceptions
    ecl_time
    )

if(ECL_PLATFORM_HAS_POSIX_THREADS) 
    catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
        CATKIN_DEPENDS 
            ecl_config
            ecl_errors
            ecl_time_lite
            ecl_exceptions
            ecl_time
        )
else()
    catkin_package(
        INCLUDE_DIRS include
        CATKIN_DEPENDS 
            ecl_config
            ecl_errors
            ecl_time_lite
            ecl_exceptions
            ecl_time
        )
endif()

include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Platform Detection
##############################################################################

# Don't think we need this any longer, dependencies handle the specifics.
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ecl_build_DIR}/modules)
#include(ecl_platform_detection)
#ecl_detect_platform()

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



