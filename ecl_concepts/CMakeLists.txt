##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_concepts)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_type_traits REQUIRED)

##############################################################################
# Project configuration
##############################################################################

include_directories(
    ${ecl_config_INCLUDE_DIRS}
    ${ecl_type_traits_INCLUDE_DIRS}
)

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Exports
##############################################################################

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(
    ecl_config
    ecl_type_traits
)
ament_package()
