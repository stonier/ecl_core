###############################################################################
# Files
###############################################################################

add_executable(demo_thread thread.cpp)
target_link_libraries(demo_thread ${PROJECT_NAME})
install(TARGETS demo_thread RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(demo_mutex mutex.cpp)
target_link_libraries(demo_mutex ${PROJECT_NAME})
install(TARGETS demo_mutex RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
