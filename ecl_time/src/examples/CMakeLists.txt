###############################################################################
# GTEST SETUP
###############################################################################

add_executable(demo_sleep sleep.cpp)
target_link_libraries(demo_sleep ${PROJECT_NAME})
install(TARGETS demo_sleep RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

