##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_exceptions)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_errors REQUIRED)
include_directories(include 
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
)

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_export_dependencies(ecl_errors)
ament_export_libraries(${PROJECT_NAME})
ament_package()
