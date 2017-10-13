##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_streams)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_concepts REQUIRED)
find_package(ecl_devices REQUIRED)
find_package(ecl_time REQUIRED)
find_package(ecl_converters REQUIRED)
find_package(ecl_type_traits REQUIRED)

include_directories(include 
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_concepts_INCLUDE_DIRS}
  ${ecl_devices_INCLUDE_DIRS}
  ${ecl_time_INCLUDE_DIRS}
  ${ecl_converters_INCLUDE_DIRS}
  ${ecl_type_traits_INCLUDE_DIRS}
  )

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_package()
