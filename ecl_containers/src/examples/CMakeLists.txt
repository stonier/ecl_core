###############################################################################
# Macros
###############################################################################

macro(ecl_containers_add_demo name)
  add_executable(ecl_demo_${name} ${name}.cpp)
  target_link_libraries(
    ecl_demo_${name}
    PUBLIC
      ecl_config::ecl_config
      ecl_converters::ecl_converters
      ecl_errors::ecl_errors
      ecl_exceptions::ecl_exceptions
      ecl_formatters::ecl_formatters
      ecl_mpl::ecl_mpl
      ecl_type_traits::ecl_type_traits
      ecl_utilities::ecl_utilities
  )
  set_target_properties(ecl_demo_${name} PROPERTIES OUTPUT_NAME demo_${name})
  install(TARGETS ecl_demo_${name} RUNTIME DESTINATION lib/${PROJECT_NAME})
endmacro()

###############################################################################
# Examples
###############################################################################

ecl_containers_add_demo(formatters)
