##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_utilities)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_concepts REQUIRED)
find_package(ecl_mpl REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

include_directories(include
  ${ecl_concepts_INCLUDE_DIRS}
  ${ecl_mpl_INCLUDE_DIRS}
  )

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Exports
##############################################################################

ament_export_include_directories(include)
ament_export_dependencies(
    ecl_concepts
    ecl_mpl
)
ament_package()
