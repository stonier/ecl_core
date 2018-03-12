###############################################################################
# Sources
###############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

###############################################################################
# Install
###############################################################################

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${ament_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
  ${ecl_config_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_concepts_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_time_LIBRARIES}
  ${ecl_utilities_LIBRARIES}
  ${thread_INTERFACE}
)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
#   PUBLIC_HEADER DESTINATION include
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
