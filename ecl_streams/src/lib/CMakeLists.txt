###############################################################################
# SOURCES
###############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

###############################################################################
# INSTALL
###############################################################################

add_library(ecl_streams ${SOURCES})
target_link_libraries(${PROJECT_NAME} 
  ${ecl_errors_LIBRARIES}
  ${ecl_concepts_LIBRARIES}
  ${ecl_devices_LIBRARIES}
  ${ecl_time_LIBRARIES}
  ${ecl_converters_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
)
install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
