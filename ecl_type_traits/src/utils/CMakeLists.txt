##############################################################################
# Files
##############################################################################

add_executable(detect_sizes detect_sizes.cpp)
target_link_libraries(detect_sizes ${PROJECT_NAME})
install(TARGETS detect_sizes RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
