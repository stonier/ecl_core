###############################################################################
# GTest setup
###############################################################################

MACRO(ecl_add_gtest TESTNAME)
  rosbuild_add_gtest(test_${TESTNAME} ${TESTNAME}.cpp)
  target_link_libraries(test_${TESTNAME} -lecl_statistics)
  if ( UNIX )
    target_link_libraries(test_${TESTNAME} -pthread)
  endif()
ENDMACRO(ecl_add_gtest)

###############################################################################
# GTests
###############################################################################

ecl_add_gtest(covariance_ellipsoids)
