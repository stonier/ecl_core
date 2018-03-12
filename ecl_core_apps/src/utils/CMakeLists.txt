###############################################################################
# Macro
###############################################################################

macro(ecl_add_utility name)
  add_executable(ecl_${name} ${name}.cpp)
  target_link_libraries(ecl_${name}
  ${ecl_build_LIBRARIES}
  ${ecl_config_LIBRARIES}
  ${ecl_linear_algebra_LIBRARIES}
  ${ecl_command_line_LIBRARIES}
  ${ecl_converters_LIBRARIES}
  ${ecl_containers_LIBRARIES}
  ${ecl_devices_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_formatters_LIBRARIES}
  ${ecl_geometry_LIBRARIES}
  ${ecl_ipc_LIBRARIES}
  ${ecl_sigslots_LIBRARIES}
  ${ecl_streams_LIBRARIES}
  ecl_threads::ecl_threads
  ${ecl_time_lite_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
  )
  install(TARGETS ecl_${name} RUNTIME DESTINATION bin)
endmacro()

macro(ecl_add_global_utility name)
  add_executable(ecl_${name} ${name}.cpp)
  target_link_libraries(ecl_${name}
  ${ecl_build_LIBRARIES}
  ${ecl_config_LIBRARIES}
  ${ecl_linear_algebra_LIBRARIES}
  ${ecl_command_line_LIBRARIES}
  ${ecl_converters_LIBRARIES}
  ${ecl_containers_LIBRARIES}
  ${ecl_devices_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_formatters_LIBRARIES}
  ${ecl_geometry_LIBRARIES}
  ${ecl_ipc_LIBRARIES}
  ${ecl_sigslots_LIBRARIES}
  ${ecl_streams_LIBRARIES}
  ecl_threads::ecl_threads
  ${ecl_time_lite_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
  )
  set_target_properties(ecl_${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
  install(TARGETS ecl_${name} RUNTIME DESTINATION bin)
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
