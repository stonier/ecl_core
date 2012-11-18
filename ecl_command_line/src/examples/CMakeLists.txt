##############################################################################
# Files
##############################################################################

add_executable(demo_command_line command_line.cpp)
install(TARGETS demo_command_line RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

