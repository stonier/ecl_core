##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_geometry)

##############################################################################
# Catkin
##############################################################################

find_package(catkin
    REQUIRED
    COMPONENTS
        ecl_build 
        ecl_config 
        ecl_type_traits
        ecl_containers
        ecl_formatters
        ecl_linear_algebra
        ecl_exceptions
        ecl_math
        ecl_mpl
)

##############################################################################
# Exports
##############################################################################

catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS
        ecl_build
        ecl_config 
        ecl_type_traits
        ecl_containers
        ecl_formatters
        ecl_linear_algebra
        ecl_exceptions
        ecl_math
        ecl_mpl
        )

##############################################################################
# Project Configuration
##############################################################################

ecl_enable_cxx11_compiler()
include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



