###############################################################################
# Examples
###############################################################################

add_executable(demo_serial_timeouts serial_timeouts.cpp)
target_link_libraries(demo_serial_timeouts ${PROJECT_NAME} ${catkin_LIBRARIES})
install(TARGETS demo_serial_timeouts RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
