##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_filesystem)

##############################################################################
# Find Packages
##############################################################################

# Turn -isystem off. Actually like to see warnings from underlying packages
# and regardless, have run into trouble because of the ordering it induces.
set(CMAKE_NO_SYSTEM_FROM_IMPORTED TRUE)

find_package(ament_cmake_ros REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_config REQUIRED)
find_package(ecl_errors REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

ament_package_xml()

# This finds the platform specific filesystem libraries and sets them in the
# variable ECL_PLATFORM_FILESYSTEM_LIBRARIES. Right now this is super simple
# (typical just 'rt' on linux), but if this gets more complicated then
# appropriate dependencies need to be listed in catkin_package's DEPENDS.
ecl_detect_filesystem()

ecl_enable_cxx14_compiler()
ecl_enable_cxx_warnings()

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Exports
##############################################################################

# Do we need to export ${ECL_PLATFORM_FILESYSTEM_LIBRARIES} or does that
# automagically get covered by the exported target with target_link_libraries?

# Downstream CMake3 compatibility 
ament_export_targets(HAS_LIBRARY_TARGET ${PROJECT_NAME})
# Downstream CMake2 compatibility
ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})

ament_export_dependencies(
    ecl_config
    ecl_errors
)
ament_package()
