##############################################################################
# Macros
##############################################################################

macro(ecl_threads_add_demo name)
  add_executable(ecl_demo_${name} ${name}.cpp)
  target_link_libraries(
    ecl_demo_${name}
    PUBLIC
      ${PROJECT_NAME}
      ecl_config::ecl_config
      ecl_time::ecl_time
  )
  set_target_properties(ecl_demo_${name} PROPERTIES OUTPUT_NAME demo_${name})
  install(TARGETS ecl_demo_${name} RUNTIME DESTINATION lib/${PROJECT_NAME})
endmacro()

##############################################################################
# Executables
##############################################################################

ecl_threads_add_demo(thread)
ecl_threads_add_demo(mutex)
