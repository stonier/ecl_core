##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_time)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_time_lite REQUIRED)

##############################################################################
# Project configuration
##############################################################################


ecl_enable_cxx11_compiler()
include_directories(include 
  ${ecl_build_INCLUDE_DIRS}
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_exceptions_INCLUDE_DIRS}
  ${ecl_time_lite_INCLUDE_DIRS}
  )

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(ecl_time_lite)
ament_package()
