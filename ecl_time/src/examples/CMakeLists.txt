###############################################################################
# Macro
###############################################################################

macro(ecl_time_add_example name)
  set(target_name ecl_time_example_${name})
  add_executable(${target_name} ${name}.cpp)
  target_link_libraries(${target_name}
    ${PROJECT_NAME}
    ecl_config::ecl_config
  )
  set_target_properties(${target_name} PROPERTIES OUTPUT_NAME demo_${name})
  install(TARGETS ${target_name} RUNTIME DESTINATION lib/${PROJECT_NAME})
endmacro()

###############################################################################
# Examples
###############################################################################

ecl_time_add_example(random_number_generator)
ecl_time_add_example(sleep)