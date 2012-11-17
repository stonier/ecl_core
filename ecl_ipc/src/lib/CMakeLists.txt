###############################################################################
# SOURCES
###############################################################################

SET(SOURCES 
    semaphore_pos.cpp
    shared_memory_pos.cpp
) 

###############################################################################
# External Library Dependencies
###############################################################################

IF ( PLATFORM_HAS_POSIX_THREADS ) 
  SET (LIBRARIES "-pthread ${LIBRARIES}")
ENDIF ( PLATFORM_HAS_POSIX_THREADS )

IF(ECL_PLATFORM_HAS_RT_TIMERS)
  SET (LIBRARIES "-lrt ${LIBRARIES}")
ENDIF()

# Remove leading and trailing whitespace
string(STRIP "${LIBRARIES}" LIBRARIES) 

###############################################################################
# Install
###############################################################################

rosbuild_add_library(ecl_ipc ${SOURCES})
target_link_libraries(ecl_ipc ${LIBRARIES})

install(TARGETS ecl_ipc DESTINATION lib PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE) 
