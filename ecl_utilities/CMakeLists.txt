##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_utilities)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_mpl REQUIRED)
find_package(ecl_concepts REQUIRED)
include_directories(include 
  ${ecl_mpl_INCLUDE_DIRS}
  ${ecl_concepts_INCLUDE_DIRS}
  )

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_package()
