###############################################################################
# GTest setup
###############################################################################

macro(ecl_add_gtest TESTNAME)
  catkin_add_gtest(test_${TESTNAME} ${TESTNAME}.cpp)
  target_link_libraries(test_${TESTNAME} ${PROJECT_NAME} ${catkin_LIBRARIES})
endmacro(ecl_add_gtest)

###############################################################################
# GTests
###############################################################################

ecl_add_gtest(covariance_ellipsoids)
