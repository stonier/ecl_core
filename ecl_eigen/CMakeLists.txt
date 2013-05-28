##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_eigen)

##############################################################################
# Catkin
##############################################################################

find_package(catkin)
find_package(Eigen)
# This folder structure probably wont work
# Disabling for now till I can guarantee a working solution.
catkin_package(
        #INCLUDE_DIRS include/ecl/Eigen3.1.2
        DEPENDS Eigen
        )
include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(license)


