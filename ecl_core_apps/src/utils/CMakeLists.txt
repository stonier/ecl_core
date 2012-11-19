###############################################################################
# Macro
###############################################################################

macro(ecl_add_utility name)
  add_executable(ecl_${name} ${name}.cpp)
  target_link_libraries(ecl_${name} ${catkin_LIBRARIES})
  install(TARGETS ecl_${name} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endmacro()

###############################################################################
# Setup
###############################################################################

ecl_add_utility(process)
ecl_add_utility(hex)
ecl_add_utility(serial)
ecl_add_utility(socket_client)
ecl_add_utility(socket_server)

