##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_filesystem)

##############################################################################
# Thread Detection
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_build
    ecl_config
    ecl_errors
    )

ecl_detect_filesystem()

#set (thread_INCLUDE_DIRS "" CACHE STRING "Platform thread include directories")
#if(ECL_PLATFORM_HAS_POSIX_THREADS)
#  set (thread_LIBRARIES "pthread" CACHE STRING "Platform thread libraries")
#else()
#  set (thread_LIBRARIES "" CACHE STRING "Platform thread libraries")
#endif()
##############################################################################
# Catkin
##############################################################################

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS 
            ecl_config
            ecl_errors
    DEPENDS ${ECL_PLATFORM_FILESYSTEM_LIBRARIES}
)
include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



