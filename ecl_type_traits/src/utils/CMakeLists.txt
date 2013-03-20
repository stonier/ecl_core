##############################################################################
# Files
##############################################################################

add_executable(ecl_detect_sizes detect_sizes.cpp)
target_link_libraries(ecl_detect_sizes ${PROJECT_NAME})
install(TARGETS ecl_detect_sizes RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
