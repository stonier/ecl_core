###############################################################################
# GTest setup
###############################################################################

macro(ecl_add_gtest TESTNAME)
  catkin_add_gtest(ecl_test_${TESTNAME} ${TESTNAME}.cpp)
  if(TARGET ecl_test_${TESTNAME})
    target_link_libraries(ecl_test_${TESTNAME} ${PROJECT_NAME} ${catkin_LIBRARIES})
  endif()
endmacro(ecl_add_gtest)

###############################################################################
# GTests
###############################################################################

ecl_add_gtest(angles)
ecl_add_gtest(cartesian_points)
ecl_add_gtest(cubic_splines)
ecl_add_gtest(homogeneous_points)
ecl_add_gtest(linear_segment)
ecl_add_gtest(polynomials)
ecl_add_gtest(legacy_pose2d)
ecl_add_gtest(legacy_pose3d)
ecl_add_gtest(smooth_linear_splines)
ecl_add_gtest(tension_function)
ecl_add_gtest(tension_splines)
ecl_add_gtest(odometry_helper)
