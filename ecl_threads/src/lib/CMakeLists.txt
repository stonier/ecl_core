###############################################################################
# Sources
###############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

###############################################################################
# External Library Dependencies
###############################################################################

if(ECL_PLATFORM_HAS_POSIX_THREADS) 
  set (thread_LIBRARIES "-pthread")
endif()

# Remove leading and trailing whitespace
string(STRIP "${LIBRARIES}" LIBRARIES) 

###############################################################################
# Install
###############################################################################

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} 
  ${ecl_build_LIBRARIES}
  ${ecl_config_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_concepts_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_time_LIBRARIES}
  ${ecl_utilities_LIBRARIES}
  ${thread_LIBRARIES}
  )
install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
