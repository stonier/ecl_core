##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_threads)

##############################################################################
# Thread Detection
##############################################################################

find_package(ament_cmake REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_errors REQUIRED)
find_package(ecl_concepts REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_time REQUIRED)
find_package(ecl_utilities REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

ecl_detect_threads()

set (thread_INCLUDE_DIRS "" CACHE STRING "Platform thread include directories")
if(ECL_PLATFORM_HAS_POSIX_THREADS)
  set (thread_LIBRARIES "pthread" CACHE STRING "Platform thread libraries")
else()
  set (thread_LIBRARIES "" CACHE STRING "Platform thread libraries")
endif()

include_directories(include
  ${ecl_build_INCLUDE_DIRS}
  ${ecl_config_INCLUDE_DIRS}
  ${ecl_errors_INCLUDE_DIRS}
  ${ecl_concepts_INCLUDE_DIRS}
  ${ecl_exceptions_INCLUDE_DIRS}
  ${ecl_time_INCLUDE_DIRS}
  ${ecl_utilities_INCLUDE_DIRS}
  )

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Exports
##############################################################################

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(
    ecl_config
    ecl_errors
    ecl_concepts
    ecl_exceptions
    ecl_time
    ecl_utilities
    thread
)
ament_package()
