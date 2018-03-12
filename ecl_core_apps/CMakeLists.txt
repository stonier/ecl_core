##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_core_apps)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config  REQUIRED)
find_package(ecl_linear_algebra REQUIRED)
find_package(ecl_command_line REQUIRED)
find_package(ecl_converters REQUIRED)
find_package(ecl_containers REQUIRED)
find_package(ecl_devices REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_formatters REQUIRED)
find_package(ecl_geometry REQUIRED)
find_package(ecl_ipc REQUIRED)
find_package(ecl_sigslots REQUIRED)
find_package(ecl_streams REQUIRED)
find_package(ecl_threads REQUIRED)
find_package(ecl_type_traits REQUIRED)
find_package(ecl_time_lite REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

include_directories(include
  ${ecl_build_INCLUDE_DIRS}
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_linear_algebra_INCLUDE_DIRS}
  ${ecl_command_line_INCLUDE_DIRS}
  ${ecl_converters_INCLUDE_DIRS}
  ${ecl_containers_INCLUDE_DIRS}
  ${ecl_devices_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_exceptions_INCLUDE_DIRS}
  ${ecl_formatters_INCLUDE_DIRS}
  ${ecl_geometry_INCLUDE_DIRS}
  ${ecl_ipc_INCLUDE_DIRS}
  ${ecl_sigslots_INCLUDE_DIRS}
  ${ecl_streams_INCLUDE_DIRS}
  ${ecl_threads_INCLUDE_DIRS}
  ${ecl_type_traits_INCLUDE_DIRS}
  ${ecl_time_lite_INCLUDE_DIRS}
  )
ecl_enable_cxx14_compiler()

##############################################################################
# Sources
##############################################################################

add_subdirectory(src)


ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_package()
