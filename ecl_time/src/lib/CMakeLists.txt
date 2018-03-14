###############################################################################
# SOURCES
###############################################################################

# Note, macro magic stops us compiling objects for the wrong implementations below
SET(SOURCES
    cpuwatch_rt.cpp
    frequency.cpp
    sleep_win.cpp
    sleep_pos.cpp
    snooze_pos.cpp
    snooze_win.cpp
    stopwatch.cpp
    timestamp_base.cpp
    timestamp_pos.cpp
    timestamp_win.cpp
    time_data.cpp
)

###############################################################################
# Targets
###############################################################################

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
    ecl_config::ecl_config
    ecl_errors::ecl_errors
    ecl_exceptions::ecl_exceptions
    ecl_time_lite::ecl_time_lite
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

