###############################################################################
# GTest setup
###############################################################################

# Gtest is not picking up -pthreads when --as-needed is on, so force it.
ecl_link_no_as_needed(ECL_LINK_NO_AS_NEEDED_FLAG)

MACRO(ecl_add_gtest TESTNAME)
  rosbuild_add_gtest(test_${TESTNAME} ${TESTNAME}.cpp)
  target_link_libraries(test_${TESTNAME} -lecl_geometry ${ECL_LINK_NO_AS_NEEDED_FLAG} -lpthread)
ENDMACRO(ecl_add_gtest)

###############################################################################
# GTests
###############################################################################

ecl_add_gtest(angles)
ecl_add_gtest(cartesian_points)
ecl_add_gtest(cubic_splines)
ecl_add_gtest(homogeneous_points)
ecl_add_gtest(polynomials)
ecl_add_gtest(pose2d)
ecl_add_gtest(pose3d)
ecl_add_gtest(smooth_linear_splines)
ecl_add_gtest(tension_function)
ecl_add_gtest(tension_splines)
