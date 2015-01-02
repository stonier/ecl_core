##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(ecl_devices)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS 
    ecl_config
    ecl_errors
    ecl_mpl
    ecl_type_traits
    ecl_utilities
    ecl_containers
    ecl_threads
    )
catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS 
            ecl_config 
            ecl_errors 
            ecl_mpl
            ecl_type_traits
            ecl_utilities
            ecl_containers
            ecl_threads
        )
include_directories(include ${catkin_INCLUDE_DIRS})

##############################################################################
# Actual project configuration
##############################################################################

ecl_enable_cxx11_compiler()

add_subdirectory(include)
add_subdirectory(src)



