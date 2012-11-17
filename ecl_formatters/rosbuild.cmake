if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/package.cmake)
  include(${CMAKE_CURRENT_BINARY_DIR}/package.cmake)
endif()

include(${ecl_build_SOURCE_DIR}/cmake/modules/ecl_package.cmake)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(pkg-config)
