###############################################################################
# Macro
###############################################################################

macro(ecl_add_utility name)
  add_executable(ecl_${name} ${name}.cpp)
  target_link_libraries(ecl_${name} ${catkin_LIBRARIES})
  install(TARGETS ecl_${name} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endmacro()

macro(ecl_add_global_utility name)
  add_executable(ecl_${name} ${name}.cpp)
  target_link_libraries(ecl_${name} ${catkin_LIBRARIES})
  set_target_properties(ecl_${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_BIN_DESTINATION})
  install(TARGETS ecl_${name} RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
endmacro()

###############################################################################
# Setup
###############################################################################

ecl_add_utility(process_statistics)
ecl_add_utility(hex)
ecl_add_utility(serial)
ecl_add_utility(socket_client)
ecl_add_utility(socket_server)
ecl_add_global_utility(yaw2quaternion)
ecl_add_global_utility(quaternion2yaw)
