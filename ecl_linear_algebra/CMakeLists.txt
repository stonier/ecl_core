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
    INCLUDE_DIRS include
	CATKIN_DEPENDS 
            ecl_exceptions 
            ecl_formatters
            ecl_eigen
    )
include_directories(include ${catkin_INCLUDE_DIRS})


##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)



