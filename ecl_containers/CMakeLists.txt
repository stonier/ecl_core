##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_containers)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_formatters REQUIRED)
find_package(ecl_converters REQUIRED)
find_package(ecl_mpl REQUIRED)
find_package(ecl_type_traits REQUIRED)
find_package(ecl_utilities REQUIRED)

include_directories(include
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_exceptions_INCLUDE_DIRS}
  ${ecl_formatters_INCLUDE_DIRS}
  ${ecl_converters_INCLUDE_DIRS}
  ${ecl_mpl_INCLUDE_DIRS}
  ${ecl_type_traits_INCLUDE_DIRS}
  ${ecl_utilities_INCLUDE_DIRS}
)

##############################################################################
# Actual project configuration
##############################################################################

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_package()
