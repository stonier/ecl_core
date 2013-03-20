##############################################################################
# Files
##############################################################################

add_executable(ecl_detect_sizes detect_sizes.cpp)
set_target_properties(ecl_detect_sizes PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_BIN_DESTINATION})
target_link_libraries(ecl_detect_sizes ${PROJECT_NAME})
install(TARGETS ecl_detect_sizes RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
