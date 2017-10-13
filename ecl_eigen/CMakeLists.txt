##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_eigen)

##############################################################################
# ament
##############################################################################

find_package(ament_cmake REQUIRED)

##############################################################################
# Internal vs External Eigen
##############################################################################

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include)


if(DEFINED ECL_EIGEN_IS_INTERNAL_3_2_1)
    message(STATUS "Using ecl's internal eigen 3.2.1.")
    #ament_package(
    #        INCLUDE_DIRS include;${PROJECT_BINARY_DIR}/include;include/eigen3.2.1;include/eigen3.2.1/Eigen   # the second directory ensures the unsupported modules are available
    #        )
elseif(DEFINED ECL_EIGEN_IS_INTERNAL_3_1_2)
#    set(ECL_EIGEN_IS_INTERNAL_3_1_2 1)
    message(STATUS "Using ecl's internal eigen.")
    include_directories(
        include
        ${PROJECT_BINARY_DIR}/include
        include/eigen3.1.2
        include/eigen3.1.2/Eigen
    )
    #ament_package(
    #        INCLUDE_DIRS include;${PROJECT_BINARY_DIR}/include;include/eigen3.1.2;include/eigen3.1.2/Eigen   # the second directory ensures the unsupported modules are available
    #        )
else()
    find_package(Eigen3)
    set(ECL_EIGEN_IS_EXTERNAL 1 CACHE BOOL "Using the system's eigen3 implementation.")
    if(EIGEN3_FOUND)
        # On trusty, it sets EIGEN3_INCLUDE_DIR but not EIGEN3_INCLUDE_DIRS (xenial is fine), so help it
        if(NOT EIGEN3_INCLUDE_DIRS)
          set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
        endif()
        #ament_package(
        #    INCLUDE_DIRS include;${PROJECT_BINARY_DIR}/include
        #    DEPENDS EIGEN3
        #)
    else()
        message(STATUS "Eigen not found...using ecl's internal eigen.")
        set(ECL_EIGEN_IS_INTERNAL_3_1_2 1 CACHE BOOL "Using ecl's internal eigen implementation version 3.1.2")
        #ament_package(
        #    INCLUDE_DIRS ${PROJECT_BINARY_DIR}/include;include/eigen3.1.2;include/eigen3.1.2/Eigen   # the second directory ensures the unsupported modules are available
        #)
    endif()
endif()

##############################################################################
# Configure header macros
##############################################################################

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/ecl/eigen.hpp.in 
  ${PROJECT_BINARY_DIR}/include/ecl/eigen.hpp
)
message(STATUS "install FILES ${PROJECT_BINARY_DIR}/include/ecl/eigen.hpp ...")

ament_export_include_directories(include)
ament_package()

install(
  FILES ${PROJECT_BINARY_DIR}/include/ecl/eigen.hpp
  DESTINATION include/ecl
)

install(
  DIRECTORY include/eigen3.1.2/Eigen
  DESTINATION include
)

##############################################################################
# Actual project configuration
##############################################################################

#add_subdirectory(include)
#add_subdirectory(license)
