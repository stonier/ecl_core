##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_converters)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_concepts REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_mpl REQUIRED)
find_package(ecl_type_traits REQUIRED)

##############################################################################
# Platform Configuration
##############################################################################

ecl_enable_cxx14_compiler()

include_directories(include
  ${ecl_concepts_INCLUDE_DIRS}
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_exceptions_INCLUDE_DIRS}
  ${ecl_mpl_INCLUDE_DIRS}
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
ament_export_dependencies(
    ecl_concepts
    ecl_config
    ecl_errors
    ecl_exceptions
    ecl_mpl
    ecl_type_traits
)
ament_package()
