##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_ipc)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_time_lite REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_time REQUIRED)

ecl_detect_threads()

include_directories(include 
  ${ecl_build_INCLUDE_DIRS}
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_time_lite_INCLUDE_DIRS}
  ${ecl_exceptions_INCLUDE_DIRS}
  ${ecl_time_INCLUDE_DIRS}
  )

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_package()



