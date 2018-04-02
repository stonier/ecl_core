##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_linear_algebra)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake_ros REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_eigen REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_formatters REQUIRED)
find_package(ecl_math REQUIRED)

find_package(sophus REQUIRED)

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
    ecl_eigen
    ecl_exceptions
    ecl_formatters
    ecl_math
    sophus
)
ament_package()
