##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_formatters)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake_ros REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_converters REQUIRED)
find_package(ecl_exceptions REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

ament_package_xml()
ecl_enable_cxx14_compiler()

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Exports
##############################################################################

ament_export_interfaces(${PROJECT_NAME})
ament_export_dependencies(
    ecl_config
    ecl_converters
    ecl_exceptions
)
ament_export_libraries(${PROJECT_NAME})
ament_package()
