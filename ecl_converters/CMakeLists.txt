##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_converters)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_concepts REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_mpl REQUIRED)
find_package(ecl_type_traits REQUIRED)

##############################################################################
# Platform Configuration
##############################################################################

ecl_enable_cxx14_compiler()

##############################################################################
# Header Library Targets
##############################################################################

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(
  ${PROJECT_NAME}
  INTERFACE
    ecl_concepts::ecl_concepts
    ecl_config::ecl_config
    ecl_errors::ecl_errors
    ecl_mpl::ecl_mpl
    ecl_type_traits::ecl_type_traits
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

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
    ecl_concepts
    ecl_config
    ecl_errors
    ecl_exceptions
    ecl_mpl
    ecl_type_traits
)
ament_package()
