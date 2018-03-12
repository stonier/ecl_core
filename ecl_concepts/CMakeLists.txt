##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_concepts)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_type_traits REQUIRED)

##############################################################################
# Project configuration
##############################################################################

ecl_enable_cxx14_compiler()

include_directories(
    ${ecl_config_INCLUDE_DIRS}
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
    ecl_config
    ecl_type_traits
)
ament_package()
