###############################################################################
# GTEST SETUP
###############################################################################

add_executable(demo_formatters formatters.cpp)
target_link_libraries(demo_formatters ${PROJECT_NAME} ${catkin_LIBRARIES})
install(TARGETS demo_formatters RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
