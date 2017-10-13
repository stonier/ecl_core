##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_sigslots)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_threads REQUIRED)

message("aaa ${ecl_threads_INCLUDE_DIRS} bb ${ecl_threads_LIBRARIES} ccc")

include_directories(include 
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_threads_INCLUDE_DIRS}
  )

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_package()
