###############################################################################
# Examples
###############################################################################

add_executable(demo_container_formatters formatters.cpp)
target_link_libraries(demo_container_formatters ${catkin_LIBRARIES})
install(TARGETS demo_container_formatters RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
