##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_devices)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_mpl REQUIRED)
find_package(ecl_type_traits REQUIRED)
find_package(ecl_utilities REQUIRED)
find_package(ecl_containers REQUIRED)
find_package(ecl_threads REQUIRED)


##############################################################################
# Project Configuration
##############################################################################

ecl_enable_cxx14_compiler()

include_directories(include
  ${ecl_build_INCLUDE_DIRS}
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_mpl_INCLUDE_DIRS}
  ${ecl_type_traits_INCLUDE_DIRS}
  ${ecl_utilities_INCLUDE_DIRS}
  ${ecl_containers_INCLUDE_DIRS}
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
    ecl_config
    ecl_containers
    ecl_errors
    ecl_mpl
    ecl_type_traits
    ecl_utilities
)
ament_package()
