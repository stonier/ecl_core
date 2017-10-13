##############################################################################
# Files
##############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} 
  ${ecl_config_LIBRARIES}
  ${ecl_errors_LIBRARIES}
)
install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
