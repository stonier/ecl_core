###############################################################################
# GTest setup
###############################################################################

macro(ecl_add_mobile_robot_gtest test_name)
  ament_add_gtest(ecl_test_${test_name} ${test_name}.cpp)
  if(TARGET ecl_test_${test_name})
    target_link_libraries(ecl_test_${test_name}
      ${PROJECT_NAME}
      ecl_formatters::ecl_formatters
      ecl_geometry::ecl_geometry
      ecl_linear_algebra::ecl_linear_algebra
      ecl_math::ecl_math
    )
  endif()
endmacro(ecl_add_mobile_robot_gtest)

###############################################################################
# GTests
###############################################################################

ecl_add_mobile_robot_gtest(partial_inverse)

