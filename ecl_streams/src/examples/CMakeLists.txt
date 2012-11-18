##############################################################################
# Files
##############################################################################

add_executable(demo_console_streams console_streams.cpp)
target_link_libraries(demo_console_streams ${PROJECT_NAME} ${catkin_LIBRARIES})
install(TARGETS demo_console_streams RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(demo_log_streams log_streams.cpp)
target_link_libraries(demo_log_streams ${PROJECT_NAME} ${catkin_LIBRARIES})
install(TARGETS demo_log_streams RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
