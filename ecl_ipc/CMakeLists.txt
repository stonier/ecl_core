##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_ipc)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_build
    ecl_config
    ecl_errors
    ecl_time_lite
    ecl_exceptions
    ecl_time
    )

ecl_detect_threads()

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
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



