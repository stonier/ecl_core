##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_linear_algebra)

##############################################################################
# Catkin
##############################################################################

find_package(catkin
    REQUIRED
    COMPONENTS
        ecl_build
        ecl_eigen
        ecl_exceptions
        ecl_formatters
        ecl_math
)

find_package(Sophus REQUIRED)

##############################################################################
# Exports
##############################################################################

# For the catkin 'DEPENDS' export
get_target_property(Sophus_INCLUDE_DIRS Sophus::Sophus INTERFACE_INCLUDE_DIRECTORIES)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS
        ecl_build
        ecl_eigen
        ecl_exceptions
        ecl_formatters
        ecl_math
    DEPENDS
        Sophus  # not actually setting Sophus_INCLUDE_DIRS here
    )

##############################################################################
# Project Configuration
##############################################################################

ecl_enable_cxx11_compiler()
include_directories(include ${catkin_INCLUDE_DIRS} ${sophus_INCLUDE_DIRS})

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



