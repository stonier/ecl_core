###############################################################################
# Macro
###############################################################################

macro(ecl_add_utility name)
  add_executable(ecl_${name} ${name}.cpp)
  target_link_libraries(
    ecl_${name}
    PRIVATE
      ecl_config::ecl_config
      ecl_command_line::ecl_command_line
      ecl_converters::ecl_converters
      ecl_containers::ecl_containers
      ecl_devices::ecl_devices
      ecl_errors::ecl_errors
      ecl_exceptions::ecl_exceptions
      ecl_formatters::ecl_formatters
      ecl_geometry::ecl_geometry
      ecl_ipc::ecl_ipc
      ecl_linear_algebra::ecl_linear_algebra
      ecl_sigslots::ecl_sigslots
      ecl_streams::ecl_streams
      ecl_threads::ecl_threads
      ecl_time_lite::ecl_time_lite
      ecl_type_traits::ecl_type_traits
  )
  install(TARGETS ecl_${name} RUNTIME DESTINATION lib/${PROJECT_NAME})
endmacro()

macro(ecl_add_global_utility name)
  add_executable(ecl_${name} ${name}.cpp)
  target_link_libraries(
    ecl_${name}
    PRIVATE
      ecl_config::ecl_config
      ecl_command_line::ecl_command_line
      ecl_converters::ecl_converters
      ecl_containers::ecl_containers
      ecl_devices::ecl_devices
      ecl_errors::ecl_errors
      ecl_exceptions::ecl_exceptions
      ecl_formatters::ecl_formatters
      ecl_geometry::ecl_geometry
      ecl_ipc::ecl_ipc
      ecl_linear_algebra::ecl_linear_algebra
      ecl_sigslots::ecl_sigslots
      ecl_streams::ecl_streams
      ecl_threads::ecl_threads
      ecl_time_lite::ecl_time_lite
      ecl_type_traits::ecl_type_traits
  )
  set_target_properties(ecl_${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
  install(TARGETS ecl_${name} RUNTIME DESTINATION bin)
endmacro()

###############################################################################
# Setup
###############################################################################

ecl_add_utility(hex)
ecl_add_utility(serial)
ecl_add_utility(socket_client)
ecl_add_utility(socket_server)
ecl_add_global_utility(process_statistics)
ecl_add_global_utility(quaternion2yaw)
ecl_add_global_utility(yaw2quaternion)
