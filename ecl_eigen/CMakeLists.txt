##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_eigen)

##############################################################################
# Find Packages
##############################################################################

# Turn -isystem off. Actually like to see warnings from underlying packages
# and regardless, have run into trouble because of the ordering it induces.
set(CMAKE_NO_SYSTEM_FROM_IMPORTED TRUE)

find_package(ament_cmake_ros REQUIRED)

##############################################################################
# Internal vs External Eigen
##############################################################################

# Internal eigen logic is quite broken since ament, surgically removed for now
# Leaving the infrastructure in place though, in case we should need to make
# use of it again

find_package(Eigen3)

##############################################################################
# Project Configuration
##############################################################################

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/ecl/eigen.hpp.in
  ${PROJECT_BINARY_DIR}/include/ecl/eigen.hpp
)

install(
  FILES ${PROJECT_BINARY_DIR}/include/ecl/eigen.hpp
  DESTINATION include/ecl
)

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
    Eigen3::Eigen
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME})

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(license)

##############################################################################
# Export
##############################################################################

# Downstream CMake3 compatibility 
ament_export_targets(${PROJECT_NAME})
# Downstream CMake2 compatibility
ament_export_include_directories(include)

ament_export_dependencies(Eigen3)
ament_package()
