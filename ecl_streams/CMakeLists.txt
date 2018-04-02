##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_streams)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake_ros REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_concepts REQUIRED)
find_package(ecl_converters REQUIRED)
find_package(ecl_devices REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_threads REQUIRED)  # only required for demos
find_package(ecl_time REQUIRED)
find_package(ecl_type_traits REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

ecl_enable_cxx14_compiler()

include_directories(include
  ${ecl_concepts_INCLUDE_DIRS}
  ${ecl_converters_INCLUDE_DIRS}
  ${ecl_devices_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_time_INCLUDE_DIRS}
  ${ecl_type_traits_INCLUDE_DIRS}
  )

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Exports
##############################################################################

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(
    ecl_concepts
    ecl_converters
    ecl_devices
    ecl_errors
    ecl_time
    ecl_type_traits
)
ament_package()
