###############################################################################
# SOURCES
###############################################################################

# Note, macro magic stops us compiling objects for the wrong implementations below
SET(SOURCES
    realpath.cpp
)
###############################################################################
# Install
###############################################################################

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
    ecl_config::ecl_config
    ecl_errors::ecl_errors
    ${ECL_PLATFORM_FILESYSTEM_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

