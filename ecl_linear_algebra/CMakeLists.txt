##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_linear_algebra)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_exceptions
    ecl_formatters
    ecl_eigen
    )
catkin_package(
        INCLUDE_DIRS include # Note that this only helps with the devel space, not the install space
	CATKIN_DEPENDS 
            ecl_exceptions 
            ecl_formatters
            ecl_eigen
        )
include_directories(SYSTEM include ${catkin_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIR})

##############################################################################
# External Eigen
##############################################################################

# TODO : Fix this later when we need internal eigen.
#find_package(Eigen)
#if(NOT EIGEN_INCLUDE_DIR)
#  set(ECL_EIGEN_IS_INTERNAL 1)
#endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/ecl/linear_algebra/macros.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/ecl/linear_algebra/macros.hpp)


##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



