##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_linear_algebra)

##############################################################################
# External Eigen
##############################################################################

include(cmake/FindEigen3.cmake)
if(NOT EIGEN3_INCLUDE_DIR)
  set(ECL_EIGEN_IS_INTERNAL 1)
endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/ecl/linear_algebra/macros.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/ecl/linear_algebra/macros.hpp)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_exceptions
    ecl_formatters
    ecl_eigen
    )
catkin_package(
        INCLUDE_DIRS include ${EIGEN3_INCLUDE_DIR}
	CATKIN_DEPENDS 
            ecl_exceptions 
            ecl_formatters
            ecl_eigen
        )
include_directories(SYSTEM include ${catkin_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



