###############################################################################
# Macro
###############################################################################

macro(ecl_streams_add_example name)
  set(target_name ecl_time_example_${name})
  add_executable(${target_name} ${name}.cpp)
  target_link_libraries(${target_name}
    ${PROJECT_NAME}
    ecl_devices::ecl_devices
    ecl_threads::ecl_threads
  )
  set_target_properties(${target_name} PROPERTIES OUTPUT_NAME demo_${name})
  install(TARGETS ${target_name} RUNTIME DESTINATION lib/${PROJECT_NAME})
endmacro()

###############################################################################
# Examples
###############################################################################

ecl_streams_add_example(console_streams)
ecl_streams_add_example(log_streams)
