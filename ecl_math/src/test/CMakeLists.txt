###############################################################################
# Macros
###############################################################################

macro(ecl_math_add_gtest test_name)
  ament_add_gtest(ecl_test_${test_name} ${test_name}.cpp)
  if(TARGET ecl_test_${test_name})
    target_link_libraries(ecl_test_${test_name} ecl_type_traits::ecl_type_traits)
  endif()
endmacro()

###############################################################################
# Google Tests
###############################################################################

ecl_math_add_gtest(constants)
ecl_math_add_gtest(fuzzy)
ecl_math_add_gtest(norms)
ecl_math_add_gtest(simple)

