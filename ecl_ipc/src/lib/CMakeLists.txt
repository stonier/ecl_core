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
target_link_libraries(${PROJECT_NAME} 
  ${ecl_build_LIBRARIES}
  ${ecl_config_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_time_lite_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_time_LIBRARIES}
  )

install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

