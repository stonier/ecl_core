###############################################################################
# Sources
###############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

###############################################################################
# Targets
###############################################################################

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
    ecl_concepts::ecl_concepts
    ecl_config::ecl_config
    ecl_errors::ecl_errors
    ecl_exceptions::ecl_exceptions
    ecl_time::ecl_time
    ecl_utilities::ecl_utilities
    ${thread_INTERFACE}
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    SOVERSION ${${PROJECT_NAME}_VERSION}
    VERSION ${${PROJECT_NAME}_VERSION}
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
