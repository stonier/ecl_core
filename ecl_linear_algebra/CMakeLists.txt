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
file(MAKE_DIRECTORY ${CATKIN_DEVEL_PREFIX}/include)
catkin_package(
        INCLUDE_DIRS include ${CATKIN_DEVEL_PREFIX}/include
	CATKIN_DEPENDS 
            ecl_exceptions 
            ecl_formatters
            ecl_eigen
        )
include_directories(SYSTEM include ${catkin_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIR} ${CATKIN_DEVEL_PREFIX}/include)

##############################################################################
# External Eigen
##############################################################################

# TODO : Fix this later when we need internal eigen.
#find_package(Eigen)
#if(NOT EIGEN_INCLUDE_DIR)
#  set(ECL_EIGEN_IS_INTERNAL 1)
#endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/ecl/linear_algebra/macros.hpp.in ${CATKIN_DEVEL_PREFIX}/include/ecl/linear_algebra/macros.hpp) 
install(FILES ${CATKIN_DEVEL_PREFIX}/include/ecl/linear_algebra/macros.hpp DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/ecl/linear_algebra)



##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



