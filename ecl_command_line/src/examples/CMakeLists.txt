###############################################################################
# Macros
###############################################################################

macro(ecl_command_line_add_demo name)
  add_executable(ecl_demo_${name} ${name}.cpp)
  set_target_properties(ecl_demo_${name} PROPERTIES OUTPUT_NAME demo_${name})
  install(TARGETS ecl_demo_${name} RUNTIME DESTINATION lib/${PROJECT_NAME})
endmacro()

###############################################################################
# Examples
###############################################################################

ecl_command_line_add_demo(command_line)

