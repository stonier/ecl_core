##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_geometry)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_type_traits REQUIRED)
find_package(ecl_containers REQUIRED)
find_package(ecl_formatters REQUIRED)
find_package(ecl_linear_algebra REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_math REQUIRED)
find_package(ecl_mpl REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

ecl_enable_cxx11_compiler()
include_directories(include 
  ${ecl_build_INCLUDE_DIRS}
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_type_traits_INCLUDE_DIRS}
  ${ecl_containers_INCLUDE_DIRS}
  ${ecl_formatters_INCLUDE_DIRS}
  ${ecl_linear_algebra_INCLUDE_DIRS}
  ${ecl_exceptions_INCLUDE_DIRS}
  ${ecl_math_INCLUDE_DIRS}
  ${ecl_mpl_INCLUDE_DIRS}
  )

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_package()
