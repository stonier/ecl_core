###############################################################################
# Gtest
###############################################################################

macro(ecl_math_add_gtest test_name)
  catkin_add_gtest(test_${test_name} ${test_name}.cpp)
  target_link_libraries(test_${test_name} ${catkin_LIBRARIES})
endmacro()

ecl_math_add_gtest(constants)
ecl_math_add_gtest(fuzzy)
ecl_math_add_gtest(norms)
ecl_math_add_gtest(simple)

