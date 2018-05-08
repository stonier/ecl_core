###############################################################################
# Macros
###############################################################################

macro(ecl_mobile_robot_add_demo name)
  add_executable(ecl_demo_${name} ${name}.cpp)
  target_link_libraries(
    ecl_demo_${name}
    PUBLIC
      ${PROJECT_NAME}
      ecl_formatters::ecl_formatters
      ecl_geometry::ecl_geometry
      ecl_linear_algebra::ecl_linear_algebra
      ecl_math::ecl_math
  )
  set_target_properties(ecl_demo_${name} PROPERTIES OUTPUT_NAME demo_${name})
  install(TARGETS ecl_demo_${name} RUNTIME DESTINATION lib/${PROJECT_NAME})
endmacro()

###############################################################################
# Demos
###############################################################################

ecl_mobile_robot_add_demo(partial_inverse)
