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

# Don't think we need these any longer, ecl_threads and ecl_time handle the
# specifics.
#IF ( ECL_PLATFORM_HAS_POSIX_THREADS ) 
#  SET (LIBRARIES "-pthread ${LIBRARIES}")
#ENDIF ()
#
#IF(ECL_PLATFORM_HAS_RT_TIMERS)
#  SET (LIBRARIES "-lrt ${LIBRARIES}")
#ENDIF()

# Remove leading and trailing whitespace
#string(STRIP "${LIBRARIES}" LIBRARIES) 

###############################################################################
# Install
###############################################################################

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

