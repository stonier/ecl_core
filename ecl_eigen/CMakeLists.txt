##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_eigen)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake_ros REQUIRED)

##############################################################################
# Internal vs External Eigen
##############################################################################

# Internal eigen logic is quite broken since ament, surgically removed for now
# Leaving the infrastructure in place though, in case we should need to make
# use of it again

find_package(Eigen3)
if(EIGEN3_FOUND)
    set(ECL_EIGEN_IS_EXTERNAL 1 CACHE BOOL "Using the system's eigen3 implementation.")
    # On trusty, it sets EIGEN3_INCLUDE_DIR but not EIGEN3_INCLUDE_DIRS (xenial is fine), so help it
    if(NOT EIGEN3_INCLUDE_DIRS)
      set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
    endif()
else()
    message(STATUS "Eigen not found...using ecl's internal eigen.")
    set(ECL_EIGEN_IS_EXTERNAL 0 CACHE BOOL "Using the system's eigen3 implementation.")
    message(FATAL_ERROR "An internal version of eigen is currently not supported.")
endif()

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
    $<INSTALL_INTERFACE:${EIGEN3_INCLUDE_DIRS}>
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

ament_export_interfaces(${PROJECT_NAME})
ament_export_dependencies(Eigen3)
ament_package()
