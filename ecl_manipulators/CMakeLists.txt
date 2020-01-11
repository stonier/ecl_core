##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(ecl_manipulators)

##############################################################################
# Find Packages
##############################################################################

# Turn -isystem off. Actually like to see warnings from underlying packages
# and regardless, have run into trouble because of the ordering it induces.
set(CMAKE_NO_SYSTEM_FROM_IMPORTED TRUE)

find_package(ament_cmake_ros REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_exceptions REQUIRED)
find_package(ecl_formatters REQUIRED)
find_package(ecl_geometry REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

ament_package_xml()
ecl_enable_cxx14_compiler()
ecl_enable_cxx_warnings()

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Installs
##############################################################################

install(
  DIRECTORY scripts
  DESTINATION share/${PROJECT_NAME}
  PATTERN "CMakeLists.txt" EXCLUDE
)


##############################################################################
# Exports
##############################################################################

ament_export_interfaces(HAS_LIBRARY_TARGET ${PROJECT_NAME})
ament_export_dependencies(
    ecl_exceptions
    ecl_formatters
    ecl_geometry
)
ament_package()

