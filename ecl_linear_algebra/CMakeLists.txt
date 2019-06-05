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

find_package(Sophus REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

ament_package_xml()
ecl_enable_cxx14_compiler()
ecl_enable_cxx_warnings()

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Exports
##############################################################################

get_target_property(IMPORTED_INCLUDE_DIRS Sophus::Sophus INTERFACE_INCLUDE_DIRECTORIES)
ament_export_include_directories(include ${IMPORTED_INCLUDE_DIRS})
ament_export_interfaces(HAS_LIBRARY_TARGET ${PROJECT_NAME})
ament_export_dependencies(
    ecl_eigen
    ecl_exceptions
    ecl_formatters
    ecl_math
    Sophus
)
ament_package()
