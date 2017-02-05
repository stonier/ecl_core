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

# This finds the platform specific filesystem libraries and sets them in the
# variable ECL_PLATFORM_FILESYSTEM_LIBRARIES. Right now this is super simple
# (typical just 'rt' on linux), but if this gets more complicated then
# appropriate dependencies need to be listed in catkin_package's DEPENDS.
ecl_detect_filesystem()

##############################################################################
# Catkin
##############################################################################

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS
            ecl_config
            ecl_errors
)
include_directories(include ${CATKIN_DEVEL_PREFIX}/include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



