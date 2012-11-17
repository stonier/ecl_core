###############################################################################
# Sources
###############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

###############################################################################
# External Library Dependencies
###############################################################################

IF ( PLATFORM_HAS_POSIX_THREADS ) 
  SET (LIBRARIES "-pthread ${LIBRARIES}")
ENDIF ( PLATFORM_HAS_POSIX_THREADS )

# Remove leading and trailing whitespace
string(STRIP "${LIBRARIES}" LIBRARIES) 

###############################################################################
# Install
###############################################################################

rosbuild_add_library(ecl_threads ${SOURCES})
target_link_libraries(ecl_threads ${LIBRARIES})
install(TARGETS ecl_threads DESTINATION lib PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE) 
