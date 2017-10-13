##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_devices)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_mpl REQUIRED)
find_package(ecl_type_traits REQUIRED)
find_package(ecl_utilities REQUIRED)
find_package(ecl_containers REQUIRED)
find_package(ecl_threads REQUIRED)

include_directories(include
  ${ecl_build_INCLUDE_DIRS}
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_mpl_INCLUDE_DIRS}
  ${ecl_type_traits_INCLUDE_DIRS}
  ${ecl_utilities_INCLUDE_DIRS}
  ${ecl_containers_INCLUDE_DIRS}
  )

##############################################################################
# Actual project configuration
##############################################################################

ecl_enable_cxx11_compiler()

add_subdirectory(include)
add_subdirectory(src)


ament_export_include_directories(include)
ament_export_dependencies(ecl_errors)
ament_export_dependencies(ecl_mpl)
ament_export_dependencies(ecl_type_traits)
ament_export_dependencies(ecl_utilities)
ament_export_dependencies(ecl_containers)
ament_export_dependencies(ecl_threads)
ament_export_libraries(${PROJECT_NAME})
ament_package()
