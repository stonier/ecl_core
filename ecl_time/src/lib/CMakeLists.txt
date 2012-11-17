###############################################################################
# SOURCES
###############################################################################

SET(SOURCES 
    cpuwatch_rt.cpp
    sleep_pos.cpp
    snooze_pos.cpp
      stopwatch.cpp
    timestamp_base.cpp
    timestamp_pos.cpp
    timestamp_win.cpp
    time_data.cpp
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

rosbuild_add_library(ecl_time ${SOURCES})
target_link_libraries(ecl_time ${LIBRARIES})
install(TARGETS ecl_time DESTINATION lib PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE CONFIGURATIONS Debug Release RelWithDebInfo) 

